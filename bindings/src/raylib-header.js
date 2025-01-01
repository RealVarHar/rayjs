import { QuickJsHeader } from "./quickjs.js"
import { TypeScriptDeclaration } from "./typescript.js"
export class RayLibHeader extends QuickJsHeader {
    constructor(name) {
        super(undefined,name);
        this.typings = new TypeScriptDeclaration();
        this.includeGen.include("raylib.h");
        //this.includes.line("#define RAYMATH_IMPLEMENTATION")
    }
    paramAllocLen(param){
        let match= param.type.match(/\*/g);
        if(match==null)return 0;
        let len=match.length;
        if(param.spread=='...')len++;
        //Do not remove length for opaque, pointers need to be re-evaluated manually
        return len;
    };
    defineCallback(api){
        const options = api.binding || {};
        if (options.ignore) return;
        console.log("Binding callback " + api.name);
        let args=[];
        args.returnType=api.returnType;
        for(let i=0;i<api.params.length;i++){
            let arg={ type: api.params[i].type, name: "arg_"+api.params[i].name, sizeVars:api.params[i].sizeVars||[] };
            args.push(arg);
        }
        this.callbackArgs["callback_" + api.name]=args;
        this.callbackLookup[api.name]="callback_" + api.name;
    }
    addCallback(apiName,callbackName,attachMultiple=false){
        //TODO: transform their (void *) types into proper ones (for fucks sake)
        this.callbackGen.statement(`static trampolineContext * ${callbackName}_arr = NULL`);
        if(attachMultiple){
            this.callbackGen.statement(`static size_t ${callbackName}_size = 0`);
        }
        let api=this.callbackArgs[apiName];
        const sub = this.callbackGen.function(callbackName+'_c', api.returnType, api, true);
        let dynamicAlloc=false;
        let allocLen=0;
        for(let i=0;i<api.length;i++){
            allocLen=Math.max(allocLen , this.paramAllocLen(api[i]));
        }
        if(allocLen>=2){
            dynamicAlloc=true;
            sub.declare('memoryNode *', 'memoryHead',false,`(memoryNode *)calloc(1,sizeof(memoryNode))`);
            sub.declare('memoryNode *', 'memoryCurrent',false,'memoryHead');
        }
        //declare js variables so re-use is possible
        for(let i=0;i<api.length;i++){
            if(api[i].type.endsWith('&') && attachMultiple){
                sub.declare('JSValue','js'+i);
            }
        }

        function addcall(sub,arr){
            sub.declare('trampolineContext','tctx',false,`${arr}`);
            sub.declare('JSContext *','ctx',false,'tctx.ctx');
            //init parameters
            for(let i=0;i<api.length;i++){
                let type=api[i].type;
                let arrtype=type.replace(/[^*&]/g,'');
                if(arrtype.length>0){
                    if(arrtype=='&'){
                        type = type.replaceAll('&','*');
                        api[i].sizeVars.push(1);
                    }else{
                        type = type.replaceAll(' &','');
                    }
                }
                if(api[i].type.endsWith('&') && attachMultiple){//reuse js params if passed by reference
                    sub.if(`i==0`).cToJs(type,'js'+i,api[i].name,{dynamicAlloc,altReturn:sub.getDefaultReturn(api.returnType),supressDeclaration:true},0,structuredClone(api[i].sizeVars));
                }else{
                    sub.cToJs(type,'js'+i,api[i].name,{dynamicAlloc,altReturn:sub.getDefaultReturn(api.returnType)},0,structuredClone(api[i].sizeVars));
                }
            }
            sub.declare('JSValue','argv[]',false,'{'+api.map((el,i)=>'js'+i).join(',')+'}');
            //No idea why, but internally, qjs sometimes moves contex count, since this is threaded, additional dup is called so that we dont end up freeing runtime
            sub.call('JS_DupContext',[`ctx`]);
            sub.call('JS_DupValue',['ctx', 'tctx.func_obj']);
            //sub.call("printf",['\"3%i\"',`JS_IsFunction(ctx,tctx.func_obj)`]);
            sub.call('JS_Call',['ctx', 'tctx.func_obj', 'JS_UNDEFINED', `${api.length}`,'argv'],{type:'JSValue',name:'js_ret'});
            sub.call('JS_FreeValue',['ctx','tctx.func_obj']);
            sub.call('JS_FreeContext',[`ctx`]);
            let cleanupList=['js_ret'];
            function errorCleanupFn(ctx){
                if(dynamicAlloc){
                    ctx.call('memoryClear',['ctx','memoryHead']);
                }
                for(let i=0;i<cleanupList.length;i++){
                    ctx.call('JS_FreeValue',['ctx',cleanupList[i]]);
                }
            }
            //cleanup
            for (let i = 0; i < api.length; i++) {
                if(!api[i].type.endsWith('&')){
                    sub.call('JS_FreeValue',['ctx',`argv[${i}]`]);
                }else{
                    cleanupList.push(`argv[${i}]`);
                }
            }
            let finish=sub;
            if(attachMultiple){
                finish=sub.if(`i==${callbackName}_size-1`);
            }
            //save references
            for (let i = 0; i < api.length; i++) {
                if(api[i].type.endsWith('&')){
                    //let jsType=api[i].type.replaceAll(" &",'');
                    finish.jsToC(api[i].type,api[i].name,'js'+i,{allowNull:false,supressDeclaration:true,supressAllocation:true,jsType:'array',altReturn:sub.getDefaultReturn(api.returnType)},0,errorCleanupFn,structuredClone(api[i].sizeVars));
                    finish.call('JS_FreeValue',['ctx',`argv[${i}]`]);
                    cleanupList=cleanupList.filter(a=>a!==`argv[${i}]`);
                }
            }
            if(api.returnType!=='void'){
                finish.jsToC(api.returnType, `resp`, 'js_ret',{altReturn:sub.getDefaultReturn(api.returnType)},0,errorCleanupFn);
                errorCleanupFn(finish);
                finish.returnExp('resp');
            }else{
                errorCleanupFn(finish);
            }
        }
        sub.declare('JSValue','func1');
        if(attachMultiple){
            sub.declare('trampolineContext *','tctx');
            sub.declare('JSContext *','ctx');
            let fo=sub.for(0, `${callbackName}_size`);
                addcall(fo,`${callbackName}_arr[i]`);
        }else{
            addcall(sub,`*${callbackName}_arr`);
        }
    }
    addApiFunction(api) {
        const options = api.binding || {};
        if (options.ignore) return;
        const jName = options.jsName || api.name.charAt(0).toLowerCase() + api.name.slice(1);
        console.log("Binding function " + api.name);
        const fun = this.functionGen.jsBindingFunction(jName);
        if (options.body) {
            options.body(fun);
        } else {
            if (options.before)
                options.before(fun);
            // read parameters
            api.params = api.params || [];
            const activeParams = api.params.filter(x => !x.binding.ignore);
            let len = activeParams.length;
            for(let param of api.params){
                param.spread='';
            }
            let hasspread=false;
            if (len>0 && activeParams[len - 1].type == '...') {
                //if using spread operator, adnotate it correctly
                hasspread=true;
                const last = activeParams[len - 2];
                last.spread = '...';
                api.params.pop();
                len--;
            }
            //Enable dynamic de-allocation if we need to allocate more than one object:
            //Arrays in arrays require inefficient type test code in cleanup
            let dynamicAlloc=false;
            let allocLen=0;
            for(let i=0;i<len;i++){
                allocLen+=this.paramAllocLen(activeParams[i]);
            }
            if(allocLen>=2){
                dynamicAlloc=true;
                fun.declare('memoryNode *', 'memoryHead',false,`(memoryNode *)calloc(1,sizeof(memoryNode))`);
                fun.declare('memoryNode *', 'memoryCurrent',false,'memoryHead');
            }
            allocLen=0;//re-use allocation length, now used to count the current state
            const errorCleanupFn =(ctx,maxparam=activeParams.length)=>{
                if(allocLen==0){
                    return;
                }
                for (let j = 0; j < maxparam; j++) {
                    const param = activeParams[j];
                    if (param.binding.customCleanup){
                        param.binding.customCleanup(ctx, "argv[" + j + "]");
                    }
                    if (!dynamicAlloc && !param.binding.customCleanup){
                        ctx.jsCleanUpParameter(param.spread+param.type, param.name, "argv[" + j + "]",{allowNull:param.binding.allowNull});
                    }
                }
                if(dynamicAlloc){
                    ctx.call('memoryClear',['ctx','memoryHead']);
                }
            };
            for (let i = 0; i < len; i++) {
                const param = activeParams[i];
                allocLen+=this.paramAllocLen(param);
                if (param.binding.customConverter) {
                    param.binding.customConverter(fun, "argv[" + i + "]");
                } else {
                    //cleans parameters initialized before an error
                    //TODO: reorder parameters to limit amount of code generated in cleanup
                    fun.jsToC(param.spread+param.type, param.name, "argv[" + i + "]", {allowNull:param.binding.allowNull,dynamicAlloc},0,(ctx)=>{errorCleanupFn(ctx,i)});
                }
            }
            // call c function
            if (options.customizeCall){
                fun.line(options.customizeCall);
            }else{
                for(let param of api.params){
                    param.cast=param.type.includes('const ')?'('+param.type.replaceAll('&','*')+')':'';
                }
                let params=api.params.map(x => x.cast+x.name);
                this.functionArgs[api.name]=params;
                if(hasspread){
                    //functions with bigger spread use more memory, but are less likely that user will run into limitations
                    //spreadSize Min 2, Max 127
                    fun.declare(api.returnType, "returnVal");
                    let last=api.params.pop();
                    params.pop();
                    let sw =fun.switch('size_'+last.name);
                    //0 Arguments will not compile
                    let s1=sw.caseBreak(0);
                    s1.statement(`return JS_EXCEPTION`);
                    for(let i=0;i<globalThis.config.spreadSize;i++){
                        s1=sw.caseBreak(i+1);
                        params[params.length]=last.cast+last.name+'['+i+']';
                        s1.call(api.name, params, api.returnType === "void" ? null : { type: '', name: "returnVal" });
                    }
                }else{
                    fun.call(api.name, params, api.returnType === "void" ? null : { type: api.returnType, name: "returnVal" });
                }
            }

            // save references
            for (let i = 0; i < len; i++) {
                const param = activeParams[i];
                if(param.type.endsWith('&')){
                    fun.cToJs(param.type,"argv[" + i + "]",param.name,{allowNull:param.binding.allowNull,supressDeclaration:true});
                }
            }
            errorCleanupFn(fun);
            // return result
            if (api.returnType === "void") {
                if (options.after)
                    options.after(fun);
                fun.statement("return JS_UNDEFINED");
            }
            else {
                fun.cToJs(api.returnType, "ret", "returnVal", {}, 0, api.returnSizeVars);
                if (options.after)
                    options.after(fun);
                fun.returnExp("ret");
            }
        }
        // add binding to function declaration
        this.moduleFunctionList.jsFuncDef(jName, (api.params || []).filter(x => !x.binding.ignore).length, fun.getTag("_name"));
        this.typings.addFunction(jName, api);
    }
    addEnum(renum) {
        console.log("Binding enum " + renum.name);
        renum.values.forEach(x => this.exportGlobalInt(x.name, x.description));
    }
    addApiStruct(struct) {
        const options = struct.binding || {};
        if (options.ignore) return;
        console.log("Binding struct " + struct.name);
        const classId = this.definitions.jsClassId(`js_${struct.name}_class_id`);
        this.structLookup[struct.name] = classId;
        options.aliases?.forEach(x => {this.structLookup[x] = classId});
        const finalizer = this.structGen.jsStructFinalizer(classId, struct.name, (gen, ptr) => options.destructor && gen.call(options.destructor.name, ["*" + ptr]));
        const propDeclarations = new this.structGen.constructor();
        this.structArgs[struct.name]=struct.fields;
        if (options && options.properties) {
            for (const field of Object.keys(options.properties)) {
                const type = struct.fields.find(x => x.name === field)?.type;
                if (!type){
                    console.log(struct.fields);
                    throw new Error(`Struct ${struct.name} does not contain field ${field}`);
                }
                const el = options.properties[field];
                let _get = undefined;
                let _set = undefined;
                if (el.get){
                    _get = this.structGen.jsStructGetter(struct.name, classId, field, type, /*Be carefull when allocating memory in a getter*/ el);
                }
                if (el.set){
                    _set = this.structGen.jsStructSetter(struct.name, classId, field, type, el.overrideWrite);
                }
                propDeclarations.jsGetSetDef(field, _get?.getTag("_name"), _set?.getTag("_name"));
            }
        }
        const classFuncList = this.structGen.jsFunctionList(`js_${struct.name}_proto_funcs`);
        classFuncList.child(propDeclarations);
        classFuncList.jsPropStringDef("[Symbol.toStringTag]", struct.name);
        const classDecl = this.structGen.jsClassDeclaration(struct.name, classId, finalizer.getTag("_name"), classFuncList.getTag("_name"));
        this.moduleInit.call(classDecl.getTag("_name"), ["ctx", "m"]);
        if (options?.createConstructor || options?.createEmptyConstructor) {
            const body = this.functionGen.jsStructConstructor(struct.name, options?.createEmptyConstructor ? [] : struct.fields, classId, this.structLookup);
            this.moduleInit.statement(`JSValue ${struct.name}_constr = JS_NewCFunction2(ctx, ${body.getTag("_name")},"${struct.name})", ${struct.fields.length}, JS_CFUNC_constructor_or_func, 0)`);
            this.moduleInit.call("JS_SetModuleExport", ["ctx", "m", `"${struct.name}"`, struct.name + "_constr"]);
            this.moduleEntry.call("JS_AddModuleExport", ["ctx", "m", '"' + struct.name + '"']);
        }
        this.typings.addStruct(struct);
    }
    exportGlobalStruct(structName, exportName, values, description) {
        this.moduleInit.declareStruct(structName, exportName + "_struct", values);
        const classId = this.structLookup[structName];
        if (!classId)
            throw new Error("Struct " + structName + " not found in register");
        this.moduleInit.jsStructToOpq(structName, exportName + "_js", exportName + "_struct", classId);
        this.moduleInit.call("JS_SetModuleExport", ["ctx", "m", `"${exportName}"`, exportName + "_js"]);
        this.moduleEntry.call("JS_AddModuleExport", ["ctx", "m", `"${exportName}"`]);
        this.typings.constants.tsDeclareConstant(exportName, structName, description);
    }
    exportGlobalInt(name, description) {
        if(name==='')debugger;
        this.moduleInit.statement(`JS_SetModuleExport(ctx, m, "${name}", JS_NewInt32(ctx, ${name}))`);
        this.moduleEntry.statement(`JS_AddModuleExport(ctx, m, "${name}")`);
        this.typings.constants.tsDeclareConstant(name, "number", description);
    }
    exportGlobalDouble(name, description) {
        this.moduleInit.statement(`JS_SetModuleExport(ctx, m, "${name}", JS_NewFloat64(ctx, ${name}))`);
        this.moduleEntry.statement(`JS_AddModuleExport(ctx, m, "${name}")`);
        this.typings.constants.tsDeclareConstant(name, "number", description);
    }
}