import { QuickJsHeader } from "./quickjs.js"
import { TypeScriptDeclaration } from "./typescript.js"
import * as fs from "./fs.js";
const config=JSON.parse(fs.readFileSync('bindings/config/buildFlags.json','utf8'));
export class RayLibHeader extends QuickJsHeader {
    constructor(name) {
        super(name);
        this.typings = new TypeScriptDeclaration();
        this.includes.include("raylib.h");
        //this.includes.line("#define RAYMATH_IMPLEMENTATION")
    }
    addApiFunction(api) {
        const options = api.binding || {};
        if (options.ignore)
            return;
        const jName = options.jsName || api.name.charAt(0).toLowerCase() + api.name.slice(1);
        console.log("Binding function " + api.name);
        const fun = this.functions.jsBindingFunction(jName);
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
            const paramAllocLen=(param)=>{
                let match= param.type.match(/\*/g);
                if(match==null)return 0;
                let len=match.length;
                if(param.spread=='...')len++;
                //Do not remove length for opaque, pointers need to be re-evaluated manually
                return len;
            };
            for(let i=0;i<len;i++){
                allocLen+=paramAllocLen(activeParams[i]);
            }
            if(allocLen>=2){
                dynamicAlloc=true;
            }
            allocLen=0;//re-use allocation length, now used to count the current state
            if(dynamicAlloc){
                //console.log('dynamicAlloc',dynamicAlloc,JSON.stringify(activeParams.map(param=>param.spread+param.type)));
                fun.declare('memoryNode *', 'memoryHead',false,`(memoryNode *)calloc(1,sizeof(memoryNode))`);
                fun.declare('memoryNode *', 'memoryCurrent',false,'memoryHead;');
            }
            for (let i = 0; i < len; i++) {
                const param = activeParams[i];
                allocLen+=paramAllocLen(param);
                if (param.binding.customConverter) {
                    param.binding.customConverter(fun, "argv[" + i + "]");
                } else {
                    //cleans parameters initialized before an error
                    //TODO: reorder parameters to limit amount of code generated in cleanup
                    const errorCleanupFn =(ctx)=>{
                        if(allocLen==0){
                            return;
                        }
                        for (let j = 0; j < i; j++) {
                            const param = activeParams[j];
                            if (param.binding.customCleanup){
                                param.binding.customCleanup(ctx, "argv[" + j + "]");
                            }
                            if (!dynamicAlloc && !param.binding.customCleanup){
                                ctx.jsCleanUpParameter(param.spread+param.type, param.name, "argv[" + j + "]", this.structLookup,{allowNull:param.binding.allowNull});
                            }
                        }
                        if(dynamicAlloc){
                            ctx.call('memoryClear',['ctx','memoryHead']);
                        }
                    };
                    fun.jsToC(param.spread+param.type, param.name, "argv[" + i + "]", this.structLookup, {allowNull:param.binding.allowNull,dynamicAlloc},0,errorCleanupFn);
                }
            }
            // call c function
            if (options.customizeCall){
                fun.line(options.customizeCall);
            }else{
                for(let param of api.params){
                    param.cast=param.type.includes('const ')?'('+param.type+')':'';
                }
                let params=api.params.map(x => x.cast+x.name);
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
                    for(let i=0;i<config.spreadSize;i++){
                        s1=sw.caseBreak(i+1);
                        params[params.length]=last.cast+last.name+'['+i+']';
                        s1.call(api.name, params, api.returnType === "void" ? null : { type: '', name: "returnVal" });
                    }
                }else{
                    fun.call(api.name, params, api.returnType === "void" ? null : { type: api.returnType, name: "returnVal" });
                }
            }

            // clean up parameters
            if(dynamicAlloc){
                fun.call('memoryClear',['ctx','memoryHead']);
            }
            for (let i = 0; i < len; i++) {
                const param = activeParams[i];
                if(param.type.endsWith('&')){
                    fun.cToJs(param.type,"argv[" + i + "]",param.name,this.structLookup,{allowNull:param.binding.allowNull});
                }
                if(param.binding.customCleanup){
                    param.binding.customCleanup(fun, "argv[" + i + "]");
                } else if(!dynamicAlloc){
                    fun.jsCleanUpParameter(param.spread+param.type, param.name, "argv[" + i + "]", this.structLookup,{allowNull:param.binding.allowNull});
                }
            }
            // return result
            if (api.returnType === "void") {
                if (options.after)
                    options.after(fun);
                fun.statement("return JS_UNDEFINED");
            }
            else {
                fun.cToJs(api.returnType, "ret", "returnVal", this.structLookup);
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
        console.log("Binding struct " + struct.name);
        const classId = this.definitions.jsClassId(`js_${struct.name}_class_id`);
        this.registerStruct(struct.name, classId);
        options.aliases?.forEach(x => this.registerStruct(x, classId));
        const finalizer = this.structs.jsStructFinalizer(classId, struct.name, (gen, ptr) => options.destructor && gen.call(options.destructor.name, ["*" + ptr]));
        const propDeclarations = this.structs.createGenerator();
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
                if (el.get)
                    _get = this.structs.jsStructGetter(struct.name, classId, field, type, /*Be carefull when allocating memory in a getter*/ this.structLookup, el.overrideRead);
                if (el.set)
                    _set = this.structs.jsStructSetter(struct.name, classId, field, type, this.structLookup, el.overrideWrite);
                propDeclarations.jsGetSetDef(field, _get?.getTag("_name"), _set?.getTag("_name"));
            }
        }
        const classFuncList = this.structs.jsFunctionList(`js_${struct.name}_proto_funcs`);
        classFuncList.child(propDeclarations);
        classFuncList.jsPropStringDef("[Symbol.toStringTag]", struct.name);
        const classDecl = this.structs.jsClassDeclaration(struct.name, classId, finalizer.getTag("_name"), classFuncList.getTag("_name"));
        this.moduleInit.call(classDecl.getTag("_name"), ["ctx", "m"]);
        if (options?.createConstructor || options?.createEmptyConstructor) {
            const body = this.functions.jsStructConstructor(struct.name, options?.createEmptyConstructor ? [] : struct.fields, classId, this.structLookup);
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