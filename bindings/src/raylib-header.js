import {QuickJsGenerator,getDefaultReturn,getaliasedVariable,ctojsType,jsToC,getStaticArrayLen,subrepeat,jsToCallback} from "./quickjs.js"
import {getsubtype} from "./cgen.js"
import { TypeScriptDeclaration } from "./typescript.js"
import {source_parser,simpleregex,azZ0,a0} from "./source_parser.js";
import * as fs from "./fs.js";
import {studio_h,stdlib_h,string_h} from "./stdLibs_includes.js";
export class RayJsHeader {
    parent;root;name='';
    exported= {};
    body;
    includeGen;
    structGen;structArgs={};
    functionGen;functionArgs={};
    callbackGen;callbackArgs={};
    moduleFunctionList;
    moduleInit;
    moduleEntry;
    constructor(name,c_source,sharedFnNames={}) {
        const thiz=this;
        this.typings = new TypeScriptDeclaration('rayjs:'+name);
        this.name = name;
        this.c_source = c_source;
        this.root = new QuickJsGenerator();
        this.body = this.root.cgen.header("JS_" + this.name + "_GUARD");
        this.includeGen = this.body.section();
        //TODO: move includes upstream so generation could be split to modules
        //this.includeGen.include("",config_h);
        this.includeGen.include("stdio.h",studio_h);
        this.includeGen.include("stdlib.h",stdlib_h);
        this.includeGen.include("string.h",string_h);
        this.includeGen.include("rayjs_base.h",globalThis.toolsSource);
        this.shared={cgen:this.body.section(),fnMap:{},sharedFnNames};
        this.definitions = new QuickJsGenerator(this.body.section());
        this.structGen = new QuickJsGenerator(this.body.section());
        this.callbackGen = new QuickJsGenerator(this.body.section());
        this.functionGen = new QuickJsGenerator(this.body.section());
        this.moduleFunctionList = this.body.declare("static const JSCFunctionListEntry []",`js${name}_funcs`,[]);
        const module_name="js_" + this.name + "_init";
        let moduleInit;
        this.body.function("int",module_name, [{ type: "JSContext *", name: "ctx" }, { type: "JSModuleDef *", name: "m" }], true,(moduleInitFunc)=>{
            moduleInitFunc.section((moduleInitSection)=>{
                moduleInit = moduleInitSection;
                moduleInit.call('countof',[this.moduleFunctionList.text.name],{type:'size_t',name:'listcount'});
                moduleInit.call('JS_SetModuleExportList',['ctx','m',this.moduleFunctionList.text.name,'listcount']);
            });
            moduleInitFunc.return("0");
        });
        this.moduleInit=moduleInit;
        let moduleEntry;
        this.body.function("JSModuleDef *","js_init_module_" + this.name, [{ type: "JSContext *", name: "ctx" }, { type: "const char *", name: "module_name" }], false,(moduleEntryFunc)=>{
            moduleEntryFunc.section((moduleEntrySection)=>{
                moduleEntry=moduleEntrySection;
                moduleEntry.call('JS_NewCModule',['ctx','module_name',module_name],{type:'JSModuleDef *',name:'m'});
                moduleEntry.if(['!m'],(ctx)=>{
                    ctx.return('NULL');
                });
                moduleEntry.call('countof',[this.moduleFunctionList.text.name],{type:'size_t',name:'listcount'});
                moduleEntry.call('JS_AddModuleExportList',['ctx','m',this.moduleFunctionList.text.name,'listcount']);
            });
            moduleEntryFunc.return("m");
        });
        this.moduleEntry=moduleEntry;
    }
    writeTo(filename) {
        fs.writeFileSync(filename, this.root.cgen.toString());
    }
    paramAllocLen(param){
        let match= param.type.match(/\*/g);
        if(match==null)return 0;
        let len=match.length;
        //Do not remove length for opaque, pointers need to be re-evaluated manually
        return len;
    };
    addCallback(apiName,callbackName,callback,attachMultiple=false,threaded=false){
        //TODO: transform their (void *) types into proper ones
        if(callback.binding&&callback.binding.ignore)return;
        console.log(`Binding callback ${callbackName} as ${apiName}`);
        this.callbackGen.cgen.declare('static trampolineContext *',`${callbackName}_arr`,'NULL');
        if(threaded)this.callbackGen.cgen.declare('static JSContext *',`${callbackName}_ctx`,'NULL');
        if(attachMultiple)this.callbackGen.cgen.declare('static size_t',`${callbackName}_size`,0);
        let dynamicAlloc=false;
        let thiz=this;
        function addcall(sub,arr){
            sub.declare('bool','error',0);
            sub.declare('trampolineContext','tctx',arr);
            sub.declare('JSContext *','ctx',threaded?`${callbackName}_ctx`:'tctx.ctx');
            //init parameters
            for(let i=0;i<callback.args.length;i++){
                let type=callback.args[i].type;
                let arrtype=type.replace(/[^*&]/g,'');
                if(arrtype.length>0){
                    if(arrtype=='&'){
                        type = type.replaceAll('&','*');
                    }else{
                        type = type.replaceAll(' &','');
                    }
                }
                if(callback.args[i].type.endsWith('&') && attachMultiple){//reuse js args if passed by reference
                    sub.if(`i==0`,(ctx)=>{
                        (new QuickJsGenerator(ctx)).cToJs(type,'js'+i,callback.args[i].name,{dynamicAlloc,altReturn:getDefaultReturn(callback.returnType),supressDeclaration:true},0,structuredClone(callback.args[i].sizeVars));
                    })
                }else{
                    (new QuickJsGenerator(sub)).cToJs(type,'js'+i,callback.args[i].name,{dynamicAlloc,altReturn:getDefaultReturn(callback.returnType)},0,structuredClone(callback.args[i].sizeVars));
                }
            }
            let argv=callback.args.map((el,i)=>'js'+i);
            if(threaded){
                sub.declare('JSValue ['+(argv.length+1)+']','argv',['tctx.func_obj'].concat(argv));
                sub.call('js_postMessage',['ctx', 'tctx.thread_id', `${argv.length+1}`,'argv'],{type:'JSValue',name:'js_ret'});
            }else{
                sub.declare('JSValue ['+argv.length+']','argv',argv);
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
            for (let i = 0; i < callback.args.length; i++) {
                let j=i;
                if(threaded)j++;
                if(!callback.args[i].type.endsWith('&')){
                    sub.call('JS_FreeValue',['ctx',`argv[${j}]`]);
                }else{
                    cleanupList.push(`argv[${j}]`);
                }
            }
            function saveReferences(ctx){
                for (let i = 0; i < callback.args.length; i++) {
                    if(callback.args[i].type.endsWith('&')){
                        thiz.jsToC(ctx,callback.args[i].type,callback.args[i].name,'js'+i,structuredClone(callback.args[i].sizeVars));
                    }
                }
                if(callback.returnType!=='void'){
                    thiz.jsToC(ctx,callback.returnType,'resp', 'js_ret',[]);
                    errorCleanupFn(ctx);
                    ctx.return('resp');
                }else{
                    errorCleanupFn(ctx);
                }
            }
            if(attachMultiple){
                sub.if(`i==${callbackName}_size-1`,saveReferences);
            }else{
                saveReferences(sub);
            }

        }
        const variables=this.includeGen.getVariables();
        if(variables[callbackName]==undefined){
            debugger;return;
        }
        variables[callbackName].callback=apiName;//save information about the bound callback
        let args=[];
        for(let arg of callback.args){
            args.push({name:arg.name,type:arg.type.replace('&','[1]')});
        };
        const sub = this.callbackGen.cgen.function(callback.returnType, apiName, args, true, (sub)=>{
            let allocLen=0;
            for(let i=0;i<callback.args.length;i++){
                allocLen=Math.max(allocLen , this.paramAllocLen(callback.args[i]));
            }
            if(allocLen>=2){
                dynamicAlloc=true;
                sub.call('calloc',[1,'sizeof(memoryNode)'],{type:'memoryNode *',name:'memoryHead'})
                sub.declare('memoryNode *', 'memoryCurrent','memoryHead');
            }
            //declare js variables so re-use is possible
            for(let i=0;i<callback.args.length;i++){
                if(callback.args[i].type.endsWith('&') && attachMultiple){
                    sub.declare('JSValue','js'+i);
                }
            }

            sub.declare('JSValue','func1');
            if(attachMultiple){
                sub.for(0, `${callbackName}_size`,(ctx)=>{
                    addcall(ctx,`${callbackName}_arr[i]`);
                });
            }else{
                addcall(sub,`${callbackName}_arr`);
            }
        });
        //Add to typings
        args=[];
        args.returnType=callback.returnType;
        for(let i=0;i<callback.args.length;i++){
            let arg={ type: callback.args[i].type, name: "arg_"+callback.args[i].name, sizeVars:callback.args[i].sizeVars||[] };
            args.push(arg);
        }
        this.typings.addCallback(callback.name, args);
    }

    /** Package JSValue to c equivalent using reusable functions
     * @param ctx {CodeScope} The function to add the final call to
     * @param returnType {string} The c type of return
     * @param returnName {string} Name of variable to return the result to
     * @param src {string} Name of variable to get result from
     * @param (sizeVars) {(string|int)[]} Variables describing
     */
    jsToC(ctx,returnType,returnName,src,sizeVars=[]){
        //a basic implementation is to call quickjs ctojs
        //rather than inline eneration:
        //check if fnMap already has the function to reuse
        returnType=returnType.replaceAll('const ','');
        if(returnType=='void &'){
            //only prepare a return adress
            let target=ctx.allocVariable('target');
            ctx.declare('void *',`target`);
            ctx.assign(returnName,`${target}&`);
            return;
        }
        let pos=0;
        let jsType=ctojsType(ctx.getVariables(), returnType);
        let functionName='';
        let returnType_ptr='';
        while(pos!==false){
            let capture;
            pos=simpleregex(returnType,['r+',azZ0+'*& '],pos,capture=[]);
            if(pos==false)break;
            functionName+=capture[0];
            returnType_ptr+=capture[0];
            pos=simpleregex(returnType,['s','[','r+',azZ0+' +*/','s',']'],pos,capture=[]);
            if(pos==false)break;
            if(isNaN(capture[1])){
                functionName+='_arr';
            }else{
                functionName+='_arr'+capture[1];
            }
            returnType_ptr+='*';
        }
        let isFunction=jsType.length==1&&typeof(jsType[0])=='object' && jsType[0].type=='type'&& jsType[0].subtype=='function';
        if(isFunction){
            returnType_ptr='JSValue';
            returnType='JSValue';
            functionName='js_getFunction';
        }else{
            returnType_ptr=returnType_ptr.replaceAll('&','*');
            returnType=returnType.replaceAll('&','*');
            functionName='js_get'+functionName.replaceAll(' ','').replaceAll('&','_ptr').replaceAll('*','_arr');
        }
        if(sizeVars.length>0){
            functionName+='_arg'+sizeVars.length;
        }

        if(this.shared.fnMap[functionName]==undefined){
            //create function
            const args = [
                { type: "JSContext *", name: "ctx" },
                { type: "JSValue", name: "src" },
                { type: "bool *", name: "error" },
            ];
            for(let i in sizeVars){
                args.push({ type:'int', name:`size${i}` });
            }
            this.shared.cgen.function(returnType_ptr,functionName, args, true,(fn)=>{
                let flags={
                    onError:(fn)=>{
                        fn.assign('error[0]',1);
                        fn.return(getDefaultReturn(returnType_ptr));
                    },
                    sizeVars
                };
                //Do not include implementation if this function exists in other function (c redefinition)
                if(!this.shared.sharedFnNames[functionName]){
                    jsToC(fn,jsType,returnType_ptr,"ret", "src",flags,ctx.getVariables());
                    fn.return("ret");
                    this.shared.sharedFnNames[functionName]=true;
                }
            });
            this.shared.fnMap[functionName]=true;
        }
        //call the bound function
        let params=['ctx',src,'error'];
        for(let size of sizeVars){
            params.push(size);
        }
        ctx.call(functionName,params,{type:returnType_ptr,name:returnName});
        ctx.if('error==1',(fn)=>{
            let currentFunction=ctx.getCurrentFunction();
            fn.return(getDefaultReturn(currentFunction.text.returnType));
        });
    }

    addApiFunction(api) {
        const options = api.binding || {};
        if (options.ignore) return;
        const jName = options.jsName || api.name;
        console.log("Binding function " + api.name);
        this.functionGen.jsBindingFunction(jName,fun=>{
            fun.declare('bool','error',0);
            if (options.body) {
                options.body(fun,this);
            } else {
                if (options.before)
                    options.before(fun);
                // read parameters
                api.args = api.args || [];
                const activeArgs = api.args.filter(x => !x.binding.ignore);
                //Enable dynamic de-allocation if we need to allocate more than one object:
                //Arrays in arrays require inefficient type test code in cleanup
                let hasSpread= activeArgs.length>0&&activeArgs[activeArgs.length-1].type == '...';
                let dynamicAlloc=hasSpread;
                let allocLen=0;
                for(let i=0;i<activeArgs.length;i++){
                    allocLen+=this.paramAllocLen(activeArgs[i]);
                }
                if(allocLen>=2){
                    dynamicAlloc=true;
                }
                if(dynamicAlloc){
                    fun.call('calloc',[1,'sizeof(memoryNode)'],{type:'memoryNode *',name:'memoryHead'});
                    fun.declare('memoryNode *', 'memoryCurrent','memoryHead');
                }
                allocLen=0;//re-use allocation length, now used to count the current state
                const errorCleanupFn =(ctx,maxparam=activeArgs.length)=>{
                    if(dynamicAlloc){
                        ctx.call('memoryClear',['ctx','memoryHead']);
                        return;
                    }
                    if(allocLen==0){
                        return;
                    }
                    for (let j = 0; j < maxparam; j++) {
                        const param = activeArgs[j];
                        if (param.binding.customCleanup){
                            param.binding.customCleanup(ctx, "argv[" + j + "]");
                        }
                        if (!dynamicAlloc && !param.binding.customCleanup){
                            //(new QuickJsGenerator(ctx)).jsCleanUpParameter(param.type, param.name, "argv[" + j + "]",{allowNull:param.binding.allowNull});
                        }
                    }
                };
                let len=activeArgs.length;
                if(hasSpread){
                    len-=2;
                }
                let variables=this.includeGen.getVariables();
                for (let i = 0; i < len; i++) {
                    const param = activeArgs[i];
                    allocLen+=this.paramAllocLen(param);
                    //cleans parameters initialized before an error
                    //TODO: reorder parameters to limit amount of code generated in cleanup
                    if(param.binding.typeCast!=undefined){
                        fun.declare(param.type.replaceAll('&','*'),param.name);
                    }
                    let type=param.binding.typeCast||param.type;
                    let type0=type.split(' ');
                    let typeProperties=variables[type0[0]];
                    let bound=false;
                    let flags={allowNull:param.binding.allowNull,dynamicAlloc,threaded:param.binding.threaded};
                    if(typeProperties!=undefined){
                        typeProperties=getaliasedVariable(typeProperties);
                        if(typeProperties.subtype=='struct'&&typeProperties.props.isSympleType){
                            flags.isSympleType=true;
                        }
                    }
                    if(typeProperties!=undefined&&typeProperties.subtype=='function'){
                        fun.declare('void *',param.name);
                        let capture=[];
                        simpleregex(api.name.toLowerCase(),['os','detach','os','attach','os','set'],0,capture);
                        let mode=capture.find(a=>a!='');//mode==[set|attach|detach]
                        jsToCallback(fun,typeProperties,param.name,"argv[" + i + "]",mode,param.binding);
                    }else{
                        let ctype=param.binding.typeCast||param.type.replace('const ','');
                        this.jsToC(fun,ctype,param.name,"argv[" + i + "]",[]);
                    }

                }
                //if(api.name=='GenImageFontAtlas')debugger;
                // call c function
                let args=api.args.map(x => x.name);
                this.functionArgs[api.name]=args;
                if(hasSpread){
                    //functions with bigger spread use more memory, but are less likely that user will run into limitations
                    //spreadSize Min 2, Max 127
                    //getSize based on argc-arg[i]
                    args.pop();args.pop();
                    let last=api.args[api.args.length-2];
                    let tmpname=last.name.replace(/[^\w]/g,'');
                    fun.declare("size_t", `size_${tmpname}`,'argc-'+len);
                    fun.if(`size_${tmpname}>${globalThis.config.spreadSize}`,(ctx)=>{
                        ctx.assign(`size_${tmpname}`,globalThis.config.spreadSize);
                    });
                    //[]=[].map()
                    fun.call('js_malloc',['ctx',`size_${tmpname} * sizeof(${last.type})`],{type:last.type+' *',name:last.name});
                    fun.call('memoryStore',['memoryCurrent','js_free',last.name],{type:'memoryNode *',name:'memoryCurrent'});
                    //main spread allways skips dynamicAlloc
                    fun.for('0','size_' + tmpname,(ctx,i)=>{
                        const plusstr=len>0?`+${len}`:'';
                        //subitems use dynamicAlloc, since we can not define names statically
                        this.jsToC(ctx,last.type,`${last.name}[${i}]`,`argv[${i}${plusstr}]`,[]);
                    });

                    if(api.returnType!=='void')fun.declare(api.returnType, "returnVal");
                    fun.switch('size_'+last.name,(new Array(globalThis.config.spreadSize)).fill().map((a,i)=>{return i;}),(ctx,i)=>{
                        if(i==0){
                            //0 Arguments will not compile
                            ctx.return(`JS_EXCEPTION`);
                        }else{
                            args[args.length]=last.name+'['+(i-1)+']';
                            ctx.call(api.name, structuredClone(args), api.returnType === "void" ? null : { type: api.returnType, name: "returnVal" });
                        }
                    });
                }else{
                    fun.call(api.name, args, api.returnType === "void" ? null : { type: api.returnType, name: "returnVal" });
                }

                // save references
                for (let i = 0; i < len; i++) {
                    const arg = activeArgs[i];
                    if(arg.type.endsWith('&')){
                        (new QuickJsGenerator(fun)).cToJs(arg.type,"argv[" + i + "]",arg.name,{allowNull:arg.binding.allowNull,supressDeclaration:true},0,arg.binding.sizeVars);
                    }
                }
                // return result
                if (api.returnType === "void") {
                    if (options.after) options.after(fun);
                    errorCleanupFn(fun);
                    fun.return("JS_UNDEFINED");
                }
                else {
                    (new QuickJsGenerator(fun)).cToJs(api.returnType, "ret", "returnVal", {}, 0, api.returnSizeVars);
                    if (options.after) options.after(fun);
                    errorCleanupFn(fun);
                    fun.return("ret");
                }
            }
            // add binding to function declaration
            this.moduleFunctionList.text.initial.push((new QuickJsGenerator(fun)).jsFuncDef(jName, (api.args || []).filter(x => !x.binding.ignore).length, fun.previous().text.name));
            this.typings.addFunction(api);
        });
    }
    addEnum(renum) {
        const binding = renum.binding || {};
        if (binding.ignore) return;
        console.log("Binding enum " + renum.name);
        renum.values.forEach(x => this.exportGlobalInt(x.name, x.description));
    }
    registerAlias(alias){
        this.typings.addAlias(alias.name, alias.type);
        //TODO: actually register them in cgen!

    }
    //addApiStruct is called explicitly, this creates optional structs - ok
    //addApiStruct needs to check if api struct already exists, we might need material* or material_proxy
    addApiStruct_object(struct) {
        const binding = struct.binding || {};
        if (binding.ignore) return;
        console.log("Binding struct " + struct.name);
        let variables=this.definitions.cgen.getVariables();
        const classId = variables[struct.name].props.bound_name;
        const finalizerName = this.structGen.jsStructFinalizer(classId, struct.name, (gen, ptr) => binding.destructor && gen.call(binding.destructor.name, ["*" + ptr]));
        let classFuncList = [];
        classFuncList.push(this.structGen.jsPropStringDef("[Symbol.toStringTag]", struct.name));
        this.structArgs[struct.name]=struct.fields;
        for (const field of struct.fields) {
            let _getName = undefined;
            let _setName = undefined;
            if (field.binding.get){
                _getName = this.jsStructGetter(struct.name, field, classId);
            }
            if (field.binding.set){
                _setName = this.jsStructSetter(struct.name, field, classId);
            }
            classFuncList.push(this.structGen.jsGetSetDef(field.name, _getName, _setName));
        }
        classFuncList = this.structGen.cgen.declare("static const JSCFunctionListEntry []",`js_${struct.name}_proto_funcs`,classFuncList,struct.props);

        const classDeclName = this.structGen.jsClassDeclaration(struct.name, classId, finalizerName, classFuncList.text.name);
        this.moduleInit.call(classDeclName, ["ctx", "m"]);
        if (binding?.createConstructor) {
            const constructorName = this.jsStructConstructor(struct.name, struct.fields, classId);
            this.moduleInit.call('JS_NewCFunction2',['ctx',constructorName,`"${struct.name}"`,struct.fields.length,'JS_CFUNC_constructor', 0],{type:'JSValue',name:`${struct.name}_constr`});
            this.moduleInit.call("JS_SetModuleExport", ["ctx", "m", `"${struct.name}"`, struct.name + "_constr"]);
            this.moduleEntry.call("JS_AddModuleExport", ["ctx", "m", '"' + struct.name + '"']);
        }
        //Check if castable to type[];
        if(struct.fields.length==0){
            struct.props.isSympleType=false;
        }else{
            let maintype=struct.fields[0].type;
            let isSympleType=true;
            for(let i=1;i<struct.fields.length;i++){
                if(struct.fields[i].type!=maintype){
                    isSympleType=false;
                    break;
                }
            }
            struct.props.isSympleType=isSympleType;
        }
        this.typings.addStruct(struct);
    }
    jsStructSetter(structName, field, classId) {
        //console.log('jsStructSetter',structName, classId, field, type, ids, overrideWrite);
        const args = [{ type: "JSContext *", name: "ctx" }, { type: "JSValue", name: "this_val" }, { type: "JSValue", name: "v" }];
        this.structGen.cgen.function("JSValue",`js_${structName}_set_${field.name}`, args, true,(fun)=>{
            fun.declare('bool','error',0);
            fun.call('JS_GetOpaque2',['ctx','this_val',classId],{type:`${structName} *`,name:'ptr'});
            let flags={noContextAlloc:true};
            if( (field.type.match(/\*/g)||[]).length > 1 ){
                flags.dynamicAlloc = true;
                fun.call('calloc',[1,'sizeof(memoryNode)'],{type:'memoryNode *',name:'memoryHead'});
                fun.declare('memoryNode *', 'memoryCurrent','memoryHead');
            }
            this.jsToC(fun,field.type,"value","v",[]);

            if(field.type.endsWith('*')){
                fun.if(`ptr.${field.name}!=NULL`,(ctx)=>{
                    ctx.call('jsc_free',['ctx',"ptr[0]." + field.name]);
                });
                //fun.call('js_malloc',['ctx',`sizeof(${field.type})`],{type:field.type,name:`ptr.${field.name}`});
                //fun.call(`memcpy`,[`ptr[0].${field.name}`,'value',`sizeof(${field.type})`]);
                fun.declare(field.type,`ptr[0].${field.name}`,'value');
            }else if(field.type.endsWith(']')){
                let type2=field.type.split('[');
                let amount=type2[1].substring(0,type2[1].length-1);
                type2=type2[0];
                fun.call(`memcpy`,[`ptr[0].${field.name}`,'value',`${amount} * sizeof(${type2})`]);
            }else{
                fun.assign(`ptr.${field.name}`,"value");
            }

            fun.return("JS_UNDEFINED");
        });
        return `js_${structName}_set_${field.name}`;//function name
    }
    jsStructGetter(structName, field, classId) {
        const args = [{ type: "JSContext *", name: "ctx" }, { type: "JSValue", name: "this_val" }];
        let thiz=this;

        //array proxy functions should be defined before _get_
        if(field.type.endsWith(']')){
            let type2=field.type.split('[');
            let amount=type2[1].split(']')[0].trim();
            type2=type2[0].trim();
            field=structuredClone(field);
            if(field.binding.sizeVars==undefined)field.binding.sizeVars=[];
            field.binding.sizeVars.push(amount);
            field.type=type2+' *';
            thiz.jsStructGetter_array(structName, field);
        }else if(field.type.endsWith('*')){
            thiz.jsStructGetter_array(structName, field);
        }

        this.structGen.cgen.function("JSValue",`js_${structName}_get_${field.name}`, args, true,(fun)=>{
            fun.call('JS_GetOpaque2',['ctx', 'this_val', classId],{type:`${structName} *`,name:"ptr"});
            if(field.type.endsWith(']') || field.type.endsWith('*')){
                let ArrayProxy_class = {
                    anchor:'this_val',
                    opaque:'ptr',
                    values:`js_${structName}_${field.name}_values`,
                    keys:`js_${structName}_${field.name}_keys`,
                    get:`js_${structName}_${field.name}_get`,
                    set:`js_${structName}_${field.name}_set`,
                    has:`js_${structName}_${field.name}_has`,
                };
                ArrayProxy_class='(ArrayProxy_class){'+Object.entries(ArrayProxy_class).map(a=>'.'+a[0]+' = '+a[1]).join(',')+'}';
                fun.call('js_NewArrayProxy',['ctx',ArrayProxy_class],{type:'JSValue',name:"ret"});
            }else if(field.type.endsWith('&')){
                fun.declare(field.type, field.name, "ptr." + field.name);
                //TODO: Logical issue: we create a copy here, so if someone does origin.pointer.prop = 0 this will not update properly
                (new QuickJsGenerator(fun)).cToJs(field.type, "ret", field.name,{allowNull:true},0,field.binding.sizeVars);
            }else{
                fun.declare(field.type, field.name, "ptr." + field.name);
                (new QuickJsGenerator(fun)).cToJs(field.type, "ret", field.name,{allowNull:true},0,field.binding.sizeVars);
            }
            //TODO: call addApiStruct here
            fun.return("ret");
        });

        return `js_${structName}_get_${field.name}`;//function name
    }
    jsStructConstructor(structType, fields, classId) {
        //console.log('jsStructConstructor',structType, fields, classId, ids);
        let functionName;
        this.functionGen.jsBindingFunction(structType + "_constructor",(body)=>{
            functionName=body.previous().text.name;

            body.if('argc==0',(r1)=>{
                r1.call('js_calloc',['ctx',1,`sizeof(${structType})`],{type:`${structType} *`,name:'ptr__return'});
                r1.call('JS_NewObjectClass',['ctx',classId],{type:"JSValue", name:'_return'})
                r1.call("JS_SetOpaque", ['_return', "ptr__return"]);
                r1.return("_return");
            });

            let flags={};
            for(let i = 0; i < fields.length; i++) {
                const para = fields[i];
                if( (para.type.match(/\*/g)||[]).length > 1){
                    flags.dynamicAlloc = true;
                    body.call('calloc',[1,'sizeof(memoryNode)'],{type:'memoryNode *',name:'memoryHead'});
                    body.declare('memoryNode *', 'memoryCurrent','memoryHead');
                    break;
                }
            }
            body.declare('bool','error',0);
            for(let i = 0; i < fields.length; i++) {
                const para = fields[i];
                this.jsToC(body,para.type, para.name, "argv[" + i + "]");
            }
            let structArgs=[];
            let toCopy = [];
            for(let field of fields){
                let type=field.type;
                if(type.endsWith(']')){
                    let arrayLen = getStaticArrayLen(type);
                    if(arrayLen.sizevars.some(a=>isNaN(a))){
                        //If contains variable length, fallback on memcpy
                        toCopy.push([field.name,arrayLen.type,arrayLen.sizevars]);
                    }else{
                        structArgs.push(subrepeat(field.name,arrayLen.sizevars));
                    }
                }else{
                    structArgs.push(field.name);
                }
            }
            body.declare(structType, "_struct", structArgs);
            while(toCopy.length>0){
                let [name,subtype,sizevars]=toCopy.pop();
                let size= sizevars.reduce((a,b)=>a*b,1);
                body.call('memcpy',[`_struct.${name}`,name,`sizeof(${subtype}) * ${size}`]);
                memcpy(_struct.params,params,sizeof(float) * 4);
            }
            (new QuickJsGenerator(body)).jsStructToOpq(structType, "_return", "_struct", classId);
            body.return("_return");

        });
        return functionName;
    }
    jsStructGetter_array(structName, field){
        const binding = field.binding || {};
        if (binding.ignore) return;
        console.log(`Binding struct array ${structName}.${field.name}`);
        const classId = "js_ArrayProxy_class_id";
        //multiple typed array is possible by syntax but unimplemented

        //provide ArrayProxy_function to_array, ArrayProxy_function get, ArrayProxy_function set, ArrayProxy_function free
        if(binding.sizeVars==undefined || binding.sizeVars[0]==undefined){
            throw Error(structName+' requires array length definition');
        }
        let length=binding.sizeVars[0];

        const args = {
            ctx:{ type: "JSContext *", name: "ctx" },
            ptr:{ type: "void *", name: "ptr_u" },
            set_to:{ type: "JSValue", name: "set_to" },
            property:{ type: "int", name: "property" },
            as_string:{ type: "bool", name: "as_sting" },
            keys: { type: "JSPropertyEnum * *", name: "keys" }
        };
        const get_args = [args.ctx,args.ptr,args.property,args.as_string];
        this.structGen.cgen.function("JSValue",`js_${structName}_${field.name}_values`, get_args, true,(ctx)=>{
            ctx.declare(`${structName} *`,'ptr','ptr_u');
            let ptrcast=`ptr.${field.name}`;
            if(binding.typeCast!=undefined){
                ptrcast+=`(${binding.typeCast})`;
            }
            (new QuickJsGenerator(ctx)).cToJs(binding.typeCast||field.type,'ret',ptrcast,{},0,[length]);

            ctx.if(`as_sting==true`,(ctx)=>{
                ctx.call('JS_JSONStringify',['ctx','ret','JS_UNDEFINED','JS_UNDEFINED'],{type:'JSValue',name:'ret'});
            });
            ctx.return('ret');
        });

        const keys_args = [args.ctx,args.ptr,args.keys];
        this.structGen.cgen.function( "int", `js_${structName}_${field.name}_keys`, keys_args, true,ctx=>{
            ctx.declare(`${structName} *`,'ptr','ptr_u');
            ctx.declare('int','length',length);
            ctx.call('js_malloc',['ctx','(length+1) * sizeof(JSPropertyEnum)'],{type:'JSPropertyEnum * *',name:'keys[0]'});
            ctx.for(0,'length',(ctx,loopkey)=>{
                ctx.declare('JSPropertyEnum * *',`keys[0][${loopkey}]`,`(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,${loopkey})}`);
            });

            ctx.declare('JSPropertyEnum *','keys[0][length]','(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length}');
            ctx.return('true');
        });

        this.structGen.cgen.function("JSValue", `js_${structName}_${field.name}_get`, get_args, true,(ctx)=>{
            ctx.declare(`${structName} *`,'ptr','ptr_u');
            ctx.if([`as_sting==true`,''],ctx=>{
                ctx.if([`property==JS_ATOM_length`,''],ctx=>{
                    (new QuickJsGenerator(ctx)).cToJs('int','ret',length,{});
                    ctx.return('ret');
                },ctx=>{
                    ctx.return('JS_UNDEFINED');
                });
            },ctx=>{
                ctx.if([`property>=0 && property<${length}`,''],ctx=>{
                    let type=getsubtype(field.type);
                    let ptrcast=`ptr.${field.name}`;
                    if(binding.typeCast!=undefined){
                        ptrcast=ctx.allocVariable('ptrcast');
                        ctx.declare(binding.typeCast, ptrcast, `ptr.${field.name}`);
                        type=getsubtype(binding.typeCast);
                    }
                    ctx.declare(type, 'src', `${ptrcast}[property]`);
                    (new QuickJsGenerator(ctx)).cToJs(type, "ret", 'src');
                    ctx.return('ret');
                },ctx=>{
                    ctx.return('JS_UNDEFINED');
                });
            });
        });


        const set_args = [args.ctx,args.ptr,args.set_to,args.property,args.as_string];
        this.structGen.cgen.function( "int", `js_${structName}_${field.name}_set`, set_args, true,ctx=>{
            ctx.declare(`${structName} *`,'ptr','ptr_u');
            ctx.if([`as_sting==true`,''],ctx=>{
                ctx.return('false');
            },ctx=>{
                ctx.declare('bool','error',0);
                let ctype=getsubtype(binding.typeCast||field.type);
                this.jsToC(ctx,ctype,'ret','set_to',[]);//{altReturn:'-1'}
                const cast=(binding.typeCast==undefined?'':`(${binding.typeCast})`);
                ctx.declare(binding.typeCast||field.type, `ptr.${field.name}${cast}[property]`, `ret`);
            });
            ctx.return('true');
        });


        this.structGen.cgen.function( "int",`js_${structName}_${field.name}_has`, get_args, true,ctx=>{
            ctx.declare(`${structName} *`,'ptr','ptr_u');
            ctx.if([`as_sting==true`,''],ctx=>{
                ctx.if([`property==JS_ATOM_length`,''],ctx=>{
                    ctx.return('true');
                },ctx=>{
                   ctx.return('false');
                });
            },ctx=>{
                ctx.if([`property>=0 && property<${length}`,''],(ctx)=>{
                    ctx.return('true');
                },(ctx)=>{
                    ctx.return('false');
                });
            });
        });
    }
    exportGlobalStruct(structName, exportName, values, description) {
        this.moduleInit.declare(structName,exportName+"_struct",values);
        const variables = this.includeGen.getVariables();
        if (!variables[structName]){
            throw new Error("Struct " + structName + " not found in register");
        }
        const classId = variables[structName].props.bound_name;
        (new QuickJsGenerator(this.moduleInit)).jsStructToOpq(structName, exportName + "_js", exportName + "_struct", classId);
        this.moduleInit.call("JS_SetModuleExport", ["ctx", "m", `"${exportName}"`, exportName + "_js"]);
        this.moduleEntry.call("JS_AddModuleExport", ["ctx", "m", `"${exportName}"`]);
        this.typings.addConstant(exportName, structName, description);
        this.exported[structName]='struct';
    }
    exportGlobalInt(name, description='') {
        this.moduleInit.call('JS_SetModuleExport',['ctx', 'm',`"${name}"`, `JS_NewInt32(ctx,${name})`]);
        this.moduleEntry.call('JS_AddModuleExport',['ctx','m',`"${name}"`]);
        this.typings.addConstant(name, "number", description);
        this.exported[name]='int';
    }
    exportGlobalDouble(name, description='') {
        this.moduleInit.call('JS_SetModuleExport',['ctx','m',`"${name}"`, `JS_NewFloat64(ctx,${name})`]);
        this.moduleEntry.call('JS_AddModuleExport',['ctx','m',`"${name}"`]);
        this.typings.addConstant(name, "number", description);
        this.exported[name]='float';
    }
}