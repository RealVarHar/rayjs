import {QuickJsGenerator} from "./quickjs.js"
import { TypeScriptDeclaration } from "./typescript.js"
import {source_parser} from "./source_parser.js";
import * as fs from "./fs.js";
import {CodeWriter} from "./generation.js";
export class RayJsHeader {
    parent;root;name='';
    #structLookup = {};structLookup;
    #callbackLookup = {};callbackLookup;
    exported= {};
    body;
    includeGen;
    structGen;structArgs={};
    functionGen;functionArgs={};
    callbackGen;callbackArgs={};
    moduleFunctionList;
    moduleInit;
    moduleEntry;
    includeDictionary;
    constructor(name,includeDictionary={},did) {
        const thiz=this;
        const lookuphandler={
            get(target, prop, receiver){
                if(target[1][prop]!=undefined){
                    return target[1][prop];
                }else{
                    if(thiz.#structLookup[1][prop]||thiz.#callbackLookup[1][prop])return;
                    let moduleId=thiz.includeDictionary.lookup[prop];
                    if(moduleId==undefined)return;
                    //add the module in question
                    const module=thiz.includeDictionary.contents[moduleId];
                    module.include(thiz);
                    for(let name in module.structLookup){
                        thiz.#structLookup[1][name]=module.structLookup[name];
                    }
                    for(let name in module.callbackLookup){
                        thiz.#callbackLookup[1][name]=module.callbackLookup[name];
                    }
                    //...
                    return target[1][prop];
                }
            },
            set(target, prop, value){
                target[0][prop] = value;
                target[1][prop] = value;
                if(includeDictionary.lookup[prop]==undefined){
                    includeDictionary.lookup[prop]=did;
                }
                return true;
            }
        }
        this.#structLookup = [includeDictionary.contents[did].structLookup,{}];
        this.structLookup = new Proxy(this.#structLookup,lookuphandler);
        this.#callbackLookup = [includeDictionary.contents[did].callbackLookup,{}];
        this.callbackLookup = new Proxy(this.#callbackLookup,lookuphandler);
        this.typings = new TypeScriptDeclaration();
        this.includeDictionary =includeDictionary;
        this.name = name;
        this.root = new QuickJsGenerator(this);
        this.body = this.root.header("JS_" + this.name + "_GUARD");
        this.includeGen = this.body.child();
        //TODO: move includes upstream so generation could be split to modules
        this.includeGen.include("stdio.h");
        this.includeGen.include("stdlib.h");
        this.includeGen.include("string.h");
        this.includeGen.breakLine();
        this.includeGen.include("quickjs.h");
        this.includeGen.include("rayjs_base.h");
        this.body.breakLine();
        this.definitions = this.body.child();
        this.body.breakLine();
        this.structGen = this.body.child();
        this.callbackGen = this.body.child();
        this.functionGen = this.body.child();
        this.moduleFunctionList = this.body.jsFunctionList("js_" + name + "_funcs");
        const moduleInitFunc = this.body.function("js_" + this.name + "_init", "int", [{ type: "JSContext *", name: "ctx" }, { type: "JSModuleDef *", name: "m" }], true);
        const moduleInit = this.moduleInit = moduleInitFunc.child();
        moduleInit.statement(`JS_SetModuleExportList(ctx, m,${this.moduleFunctionList.getTag("_name")},countof(${this.moduleFunctionList.getTag("_name")}))`);
        moduleInitFunc.returnExp("0");
        const moduleEntryFunc = this.body.function("js_init_module_" + this.name, "JSModuleDef *", [{ type: "JSContext *", name: "ctx" }, { type: "const char *", name: "module_name" }], false);
        const moduleEntry = this.moduleEntry = moduleEntryFunc.child();
        moduleEntry.statement("JSModuleDef *m");
        moduleEntry.statement(`m = JS_NewCModule(ctx, module_name, ${moduleInitFunc.getTag("_name")})`);
        moduleEntry.statement("if(!m) return NULL");
        moduleEntry.statement(`JS_AddModuleExportList(ctx, m, ${this.moduleFunctionList.getTag("_name")}, countof(${this.moduleFunctionList.getTag("_name")}))`);
        moduleEntryFunc.statement("return m");
        includeDictionary.contents[did].include(this);
    }
    writeTo(filename) {
        const writer = new CodeWriter();
        writer.writeGenerator(this.root);
        fs.writeFileSync(filename, writer.toString());
    }
    paramAllocLen(param){
        let match= param.type.match(/\*/g);
        if(match==null)return 0;
        let len=match.length;
        if(param.spread=='...')len++;
        //Do not remove length for opaque, pointers need to be re-evaluated manually
        return len;
    };
    registerCallback(api){
        const options = api.binding || {};
        if (options.ignore) return;
        console.log("Binding callback " + api.name);
        let args=[];
        args.returnType=api.returnType;
        args.threaded=options.threaded===true;
        for(let i=0;i<api.params.length;i++){
            let arg={ type: api.params[i].type, name: "arg_"+api.params[i].name, sizeVars:api.params[i].sizeVars||[] };
            args.push(arg);
        }
        this.callbackArgs["callback_" + api.name]=args;
        this.callbackLookup[api.name]="callback_" + api.name;
    }
    addCallback(apiName,callbackName,attachMultiple=false,threaded=false){
        //TODO: transform their (void *) types into proper ones
        this.callbackGen.statement(`static trampolineContext * ${callbackName}_arr = NULL`);
        if(threaded)this.callbackGen.statement(`static JSContext * ${callbackName}_ctx = NULL`);
        if(attachMultiple)this.callbackGen.statement(`static size_t ${callbackName}_size = 0`);
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
            sub.declare('JSContext *','ctx',false,threaded?`${callbackName}_ctx`:'tctx.ctx');
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
            let argv=api.map((el,i)=>'js'+i);
            if(threaded){
                sub.declare('JSValue','argv[]',false,'{'+['tctx.func_obj'].concat(argv).join(',')+'}');
                sub.call('js_postMessage',['ctx', 'tctx.thread_id', `${argv.length+1}`,'argv'],{type:'JSValue',name:'js_ret'});
            }else{
                sub.declare('JSValue','argv[]',false,'{'+argv.join(',')+'}');
                /* extra dups based on code documentation and stability testing */
                sub.call('JS_DupContext',[`ctx`]);
                sub.call('JS_DupValue',['ctx', 'tctx.func_obj']);
                sub.call('JS_Call',['ctx', 'tctx.func_obj', 'JS_UNDEFINED', `${argv.length}`,'argv'],{type:'JSValue',name:'js_ret'});
                sub.call('JS_FreeValue',['ctx','tctx.func_obj']);
                sub.call('JS_FreeContext',[`ctx`]);
            }
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
                let j=i;
                if(threaded)j++;
                if(!api[i].type.endsWith('&')){
                    sub.call('JS_FreeValue',['ctx',`argv[${j}]`]);
                }else{
                    cleanupList.push(`argv[${j}]`);
                }
            }
            let finish=sub;
            if(attachMultiple){
                finish=sub.if(`i==${callbackName}_size-1`);
            }
            //save references
            for (let i = 0; i < api.length; i++) {
                if(api[i].type.endsWith('&')){
                    finish.jsToC(api[i].type,api[i].name,'js'+i,{allowNull:false,supressDeclaration:true,supressAllocation:true,jsType:'array',altReturn:sub.getDefaultReturn(api.returnType)},0,errorCleanupFn,structuredClone(api[i].sizeVars));
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
            let fo=sub.for(0, `${callbackName}_size`);
                addcall(fo,`${callbackName}_arr[i]`);
        }else{
            addcall(sub,`*${callbackName}_arr`);
        }
    }
    addApiFunction(api) {
        const options = api.binding || {};
        if (options.ignore) return;
        const jName = options.jsName || api.name;
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
                    fun.jsToC(param.spread+param.type, param.name, "argv[" + i + "]", {allowNull:param.binding.allowNull,dynamicAlloc,threaded:param.binding.threaded},0,(ctx)=>{errorCleanupFn(ctx,i)});
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
                    if(api.returnType!=='void')fun.declare(api.returnType, "returnVal");
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
    registerAlias(alias){
        let type=this.structLookup[alias.type];
        if(type!=undefined){
            this.structLookup[alias.name] = this.structLookup[alias.type];return;
        }
        type=this.callbackLookup[alias.type];
        if(type!=undefined){
            this.callbackLookup[alias.name] = this.callbackLookup[alias.type];return;
        }
    }
    registerApiStruct(struct){
        const binding = struct.binding || {};
        if (binding.ignore) return;
        console.log("Registered struct " + struct.name);
        const classId = this.definitions.jsClassId(`js_${struct.name}_class_id`);
        this.structLookup[struct.name] = classId;
        binding.aliases?.forEach(x => {this.structLookup[x] = classId});
    }
    //addApiStruct is called explicitly, this creates optional structs - ok
    //addApiStruct needs to check if api struct already exists, we might need material* or material_proxy
    addApiStruct_object(struct) {
        const binding = struct.binding || {};
        if (binding.ignore) return;
        console.log("Binding struct " + struct.name);
        const classId = this.definitions.jsClassId(`js_${struct.name}_class_id`);
        const finalizer = this.structGen.jsStructFinalizer(classId, struct.name, (gen, ptr) => binding.destructor && gen.call(binding.destructor.name, ["*" + ptr]));
        const propDeclarations = new this.structGen.constructor();
        propDeclarations.jsPropStringDef("[Symbol.toStringTag]", struct.name);
        this.structArgs[struct.name]=struct.fields;
        if (binding && binding.properties) {
            for (const field of Object.keys(binding.properties)) {
                const type = struct.fields.find(x => x.name === field)?.type;
                if (!type){
                    console.log(struct.fields);
                    throw new Error(`Struct ${struct.name} does not contain field ${field}`);
                }
                const el = binding.properties[field];
                el.name=field;
                let _get = undefined;
                let _set = undefined;
                if (el.get){
                    _get = this.structGen.jsStructGetter(struct.name, classId, field, type, el);
                }
                if (el.set){
                    _set = this.structGen.jsStructSetter(struct.name, classId, field, type, el);
                }
                propDeclarations.jsGetSetDef(field, _get?.getTag("_name"), _set?.getTag("_name"));
            }
        }
        const classFuncList = this.structGen.jsFunctionList(`js_${struct.name}_proto_funcs`);
        classFuncList.child(propDeclarations);

        const classDecl = this.structGen.jsClassDeclaration(struct.name, classId, finalizer.getTag("_name"), classFuncList.getTag("_name"));
        this.moduleInit.call(classDecl.getTag("_name"), ["ctx", "m"]);
        if (binding?.createConstructor || binding?.createEmptyConstructor) {
            const body = this.functionGen.jsStructConstructor(struct.name, binding?.createEmptyConstructor ? [] : struct.fields, classId);
            this.moduleInit.statement(`JSValue ${struct.name}_constr = JS_NewCFunction2(ctx, ${body.getTag("_name")},"${struct.name}", ${struct.fields.length}, JS_CFUNC_constructor, 0)`);
            this.moduleInit.call("JS_SetModuleExport", ["ctx", "m", `"${struct.name}"`, struct.name + "_constr"]);
            this.moduleEntry.call("JS_AddModuleExport", ["ctx", "m", '"' + struct.name + '"']);
        }
        this.typings.addStruct(struct);
    }
    addApiStruct_array(struct){
        const binding = struct.binding || {};
        if (binding.ignore) return;
        console.log("Binding struct array" + struct.name);
        const classId = "js_ArrayProxy_class_id";
        this.structArgs[struct.name]=struct.fields;
        //multiple typed array is possible by syntax but unimplemented

        //provide ArrayProxy_function to_array, ArrayProxy_function get, ArrayProxy_function set, ArrayProxy_function free
        const name=struct.fields[0].name;
        const structName=struct.name+'_'+name;
        const ptr=`((${struct.name} *)ptr)`;
        const type=struct.fields[0].type;
        let length=binding.properties[name].sizeVars[0];
        length=String(length).replace('ptr->',`${ptr}->`);

        const args = { ctx:{ type: "JSContext *", name: "ctx" },
            ptr:{ type: "void *", name: "ptr" },
            set_to:{ type: "JSValue", name: "set_to" },
            property:{ type: "int", name: "property" },
            as_string:{ type: "bool", name: "as_sting" },
            keys: { type: "JSPropertyEnum **", name: "keys" }
        };
        const get_args = [args.ctx,args.ptr,args.property,args.as_string];
        let _values = this.structGen.function(`js_${structName}_values`, "JSValue", get_args, true);
        _values.cToJs(type+' *','ret',`${ptr}->${name}`,{},0,[length]);
        let branch1 = _values.if(`as_sting==true`);
            branch1.call('JS_JSONStringify',['ctx','ret','JS_UNDEFINED','JS_UNDEFINED'],{name:'ret'});
        _values.returnExp('ret');

        const keys_args = [args.ctx,args.ptr,args.keys];
        let _keys = this.structGen.function(`js_${structName}_keys`, "int", keys_args, true);
        _keys.declare('int','length',false,length);
        _keys.call('js_malloc',['ctx','(length+1) * sizeof(JSPropertyEnum)'],{name:'*keys'});
        branch1 = _keys.for(0,'length','i0');
            branch1.declare('JSPropertyEnum *','(*keys)[i0]',false,'(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i0)}',true);
        _keys.declare('JSPropertyEnum *','(*keys)[length]',false,'(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length}',true);
        _keys.returnExp('true');

        let _get = this.structGen.function(`js_${structName}_get`, "JSValue", get_args, true);
        branch1 = _get.if(`as_sting==true`);
            let branch2 = branch1.if(`property==JS_ATOM_length`);
                branch2.cToJs('int','ret',length,{});
                branch2.returnExp('ret');
            branch1.else().returnExp('JS_UNDEFINED');
        branch1 = _get.else();
            branch2 = branch1.if(`property>=0 && property<${length}`);
                branch2.declare(type, 'src', false, `${ptr}->${name}[property]`);
                branch2.cToJs(type, "ret", 'src');
                branch2.returnExp('ret');
            branch1.else().returnExp('JS_UNDEFINED');

        const set_args = [args.ctx,args.ptr,args.set_to,args.property,args.as_string];
        let _set = this.structGen.function(`js_${structName}_set`, "int", set_args, true);
        branch1 = _set.if(`as_sting==true`);
            branch1.returnExp('false');
        branch1 = _set.else();
            branch1.jsToC(type,'ret','set_to',{altReturn:'-1'});
            branch1.declare(type, `${ptr}->${name}[property]`, false, `ret`,true);
        _set.returnExp('true');

        let _has = this.structGen.function(`js_${structName}_has`, "int", get_args, true);
        branch1 = _has.if(`as_sting==true`);
            branch2 = branch1.if(`property==JS_ATOM_length`);
                branch2.returnExp('true');
            branch1.else().returnExp('false');
        branch1 = _has.else();
            branch2 = branch1.if(`property>=0 && property<${length}`);
                branch2.returnExp('true');
            branch1.else().returnExp('false');
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
        this.exported[structName]='struct';
    }
    exportGlobalInt(name, description='') {
        this.moduleInit.statement(`JS_SetModuleExport(ctx, m, "${name}", JS_NewInt32(ctx, ${name}))`);
        this.moduleEntry.statement(`JS_AddModuleExport(ctx, m, "${name}")`);
        this.typings.constants.tsDeclareConstant(name, "number", description);
        this.exported[name]='int';
    }
    exportGlobalDouble(name, description='') {
        this.moduleInit.statement(`JS_SetModuleExport(ctx, m, "${name}", JS_NewFloat64(ctx, ${name}))`);
        this.moduleEntry.statement(`JS_AddModuleExport(ctx, m, "${name}")`);
        this.typings.constants.tsDeclareConstant(name, "number", description);
        this.exported[name]='float';
    }
}