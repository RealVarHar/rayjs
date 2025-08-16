import {QuickJsGenerator,getDefaultReturn} from "./quickjs.js"
import {getsubtype} from "./cgen.js"
import { TypeScriptDeclaration } from "./typescript.js"
import {source_parser} from "./source_parser.js";
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
    constructor(name) {
        const thiz=this;
        this.typings = new TypeScriptDeclaration('rayjs:'+name);
        this.name = 'js_'+name;
        this.root = new QuickJsGenerator();
        this.body = this.root.cgen.header("JS_" + this.name + "_GUARD");
        this.includeGen = this.body.section();
        //TODO: move includes upstream so generation could be split to modules
        //this.includeGen.include("",config_h);
        this.includeGen.include("stdio.h",studio_h);
        this.includeGen.include("stdlib.h",stdlib_h);
        this.includeGen.include("string.h",string_h);
        this.includeGen.include("rayjs_base.h",globalThis.toolsSource);
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
        if(param.spread=='...')len++;
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
        function addcall(sub,arr){
            sub.declare('trampolineContext','tctx',arr);
            sub.declare('JSContext *','ctx',threaded?`${callbackName}_ctx`:'tctx.ctx');
            //init parameters
            for(let i=0;i<callback.params.length;i++){
                let type=callback.params[i].type;
                let arrtype=type.replace(/[^*&]/g,'');
                if(arrtype.length>0){
                    if(arrtype=='&'){
                        type = type.replaceAll('&','*');
                        callback.params[i].sizeVars.push(1);
                    }else{
                        type = type.replaceAll(' &','');
                    }
                }
                if(callback.params[i].type.endsWith('&') && attachMultiple){//reuse js params if passed by reference
                    sub.if(`i==0`,(ctx)=>{
                        (new QuickJsGenerator(ctx)).cToJs(type,'js'+i,callback.params[i].name,{dynamicAlloc,altReturn:getDefaultReturn(callback.returnType),supressDeclaration:true},0,structuredClone(callback.params[i].sizeVars));
                    })
                }else{
                    (new QuickJsGenerator(sub)).cToJs(type,'js'+i,callback.params[i].name,{dynamicAlloc,altReturn:getDefaultReturn(callback.returnType)},0,structuredClone(callback.params[i].sizeVars));
                }
            }
            let argv=callback.params.map((el,i)=>'js'+i);
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
            for (let i = 0; i < callback.params.length; i++) {
                let j=i;
                if(threaded)j++;
                if(!callback.params[i].type.endsWith('&')){
                    sub.call('JS_FreeValue',['ctx',`argv[${j}]`]);
                }else{
                    cleanupList.push(`argv[${j}]`);
                }
            }
            function saveReferences(ctx){
                for (let i = 0; i < callback.params.length; i++) {
                    if(callback.params[i].type.endsWith('&')){
                        (new QuickJsGenerator(ctx)).jsToC(callback.params[i].type,callback.params[i].name,'js'+i,{allowNull:false,supressDeclaration:true,supressAllocation:true,jsType:'array',altReturn:getDefaultReturn(callback.returnType)},0,errorCleanupFn,structuredClone(callback.params[i].sizeVars));
                    }
                }
                if(callback.returnType!=='void'){
                    (new QuickJsGenerator(ctx)).jsToC(callback.returnType, `resp`, 'js_ret',{altReturn:getDefaultReturn(callback.returnType)},0,errorCleanupFn);
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
        const params=[];
        for(let param of callback.params){
            params.push({name:param.name,type:param.type.replace('&','[1]')});
        };
        const sub = this.callbackGen.cgen.function(callback.returnType, apiName, params, true, (sub)=>{
            let allocLen=0;
            for(let i=0;i<callback.params.length;i++){
                allocLen=Math.max(allocLen , this.paramAllocLen(callback.params[i]));
            }
            if(allocLen>=2){
                dynamicAlloc=true;
                sub.call('calloc',[1,'sizeof(memoryNode)'],{type:'memoryNode *',name:'memoryHead'})
                sub.declare('memoryNode *', 'memoryCurrent','memoryHead');
            }
            //declare js variables so re-use is possible
            for(let i=0;i<callback.params.length;i++){
                if(callback.params[i].type.endsWith('&') && attachMultiple){
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
        let args=[];
        args.returnType=callback.returnType;
        for(let i=0;i<callback.params.length;i++){
            let arg={ type: callback.params[i].type, name: "arg_"+callback.params[i].name, sizeVars:callback.params[i].sizeVars||[] };
            args.push(arg);
        }
        this.typings.addCallback(callback.name, args, {variables:this.definitions.cgen.getVariables(),callbackArgs:this.callbackArgs});
    }
    addApiFunction(api) {
        const options = api.binding || {};
        if (options.ignore) return;
        const jName = options.jsName || api.name;
        console.log("Binding function " + api.name);
        this.functionGen.jsBindingFunction(jName,fun=>{
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
                    fun.call('calloc',[1,'sizeof(memoryNode)'],{type:'memoryNode *',name:'memoryHead'});
                    fun.declare('memoryNode *', 'memoryCurrent','memoryHead');
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
                            (new QuickJsGenerator(ctx)).jsCleanUpParameter(param.spread+param.type, param.name, "argv[" + j + "]",{allowNull:param.binding.allowNull});
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
                        (new QuickJsGenerator(fun)).jsToC(param.spread+param.type, param.name, "argv[" + i + "]", {allowNull:param.binding.allowNull,dynamicAlloc,threaded:param.binding.threaded},0,(ctx)=>{errorCleanupFn(ctx,i)});
                    }
                }
                // call c function
                if (options.customizeCall){
                    fun.line(options.customizeCall);
                }else{
                    let params=api.params.map(x => x.name);
                    this.functionArgs[api.name]=params;
                    if(hasspread){
                        //functions with bigger spread use more memory, but are less likely that user will run into limitations
                        //spreadSize Min 2, Max 127
                        if(api.returnType!=='void')fun.declare(api.returnType, "returnVal");
                        let last=api.params[api.params.length-1];
                        params.pop();
                        fun.switch('size_'+last.name,(new Array(globalThis.config.spreadSize)).fill().map((a,i)=>{return i;}),(ctx,i)=>{
                            if(i==0){
                                //0 Arguments will not compile
                                ctx.return(`JS_EXCEPTION`);
                            }else{
                                params[params.length]=last.name+'['+i+']';
                                ctx.call(api.name, params, api.returnType === "void" ? null : { type: api.returnType, name: "returnVal" });
                            }
                        })
                    }else{
                        fun.call(api.name, params, api.returnType === "void" ? null : { type: api.returnType, name: "returnVal" });
                    }
                }

                // save references
                for (let i = 0; i < len; i++) {
                    const param = activeParams[i];
                    if(param.type.endsWith('&')){
                        (new QuickJsGenerator(fun)).cToJs(param.type,"argv[" + i + "]",param.name,{allowNull:param.binding.allowNull,supressDeclaration:true});
                    }
                }
                errorCleanupFn(fun);
                // return result
                if (api.returnType === "void") {
                    if (options.after)
                        options.after(fun);
                    fun.return("JS_UNDEFINED");
                }
                else {
                    (new QuickJsGenerator(fun)).cToJs(api.returnType, "ret", "returnVal", {}, 0, api.returnSizeVars);
                    if (options.after)
                        options.after(fun);
                    fun.return("ret");
                }
            }
            // add binding to function declaration
            this.moduleFunctionList.text.initial.push((new QuickJsGenerator(fun)).jsFuncDef(jName, (api.params || []).filter(x => !x.binding.ignore).length, fun.previous().text.name));
            this.typings.addFunction(jName, api,{variables:this.definitions.cgen.getVariables(),includegen:this.includeGen});
        });
    }
    addEnum(renum) {
        const binding = renum.binding || {};
        if (binding.ignore) return;
        console.log("Binding enum " + renum.name);
        renum.values.forEach(x => this.exportGlobalInt(x.name, x.description));
    }
    registerAlias(alias){
        this.typings.addAlias(alias.name, alias.type, {variables:this.definitions.cgen.getVariables(),includegen:this.includeGen});
        //TODO: actually register them in cgen!

    }
    registerApiStruct(struct){
        const binding = struct.binding || {};
        if (binding.ignore) return;
        let variables=this.definitions.cgen.getVariables();
        if(variables[struct.name]==undefined){
            throw new Error("Attempted to bind an not imported struct");
        }
        if(variables[`js_${struct.name}_class_id`]!=undefined){
            throw new Error("Attempted to bind a struct twice");
        }
        console.log("Registered struct " + struct.name);
        struct.props=struct.props||{};
        struct.props.bound_name = `js_${struct.name}_class_id`;
        this.definitions.jsClassId(struct.props.bound_name);
        variables[struct.name].props = struct.props;
        //binding.aliases?.forEach(x => {this.structLookup[x] = classId});//Aliases are now handled on top level
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
        if (binding && binding.properties) {
            for (const field of Object.keys(binding.properties)) {
                const type = struct.fields.find(x => x.name === field)?.type;
                if (!type){
                    console.log(struct.fields);
                    throw new Error(`Struct ${struct.name} does not contain field ${field}`);
                }
                const el = binding.properties[field];
                el.name=field;
                let _getName = undefined;
                let _setName = undefined;
                if (el.get){
                    _getName = this.jsStructGetter(struct.name, classId, field, type, el);
                }
                if (el.set){
                    _setName = this.structGen.jsStructSetter(struct.name, classId, field, type, el);
                }
                classFuncList.push(this.structGen.jsGetSetDef(field, _getName, _setName));
            }
        }
        classFuncList = this.structGen.cgen.declare("static const JSCFunctionListEntry []",`js_${struct.name}_proto_funcs`,classFuncList,struct.props);

        const classDeclName = this.structGen.jsClassDeclaration(struct.name, classId, finalizerName, classFuncList.text.name);
        this.moduleInit.call(classDeclName, ["ctx", "m"]);
        if (binding?.createConstructor) {
            const constructorName = this.functionGen.jsStructConstructor(struct.name, struct.fields, classId);
            this.moduleInit.call('JS_NewCFunction2',['ctx',constructorName,`"${struct.name}"`,struct.fields.length,'JS_CFUNC_constructor', 0],{type:'JSValue',name:`${struct.name}_constr`});
            this.moduleInit.call("JS_SetModuleExport", ["ctx", "m", `"${struct.name}"`, struct.name + "_constr"]);
            this.moduleEntry.call("JS_AddModuleExport", ["ctx", "m", '"' + struct.name + '"']);
        }
        this.typings.addStruct(struct);
    }
    jsStructGetter(structName, classId, field, type, element, nested) {
        const args = [{ type: "JSContext *", name: "ctx" }, { type: "JSValue", name: "this_val" }];
        let thiz=this;
        let fnname=structName+'_'+element.name
        function NewArrayProxy(fun){
            let ArrayProxy_class = {};
            ArrayProxy_class['anchor']='this_val';
            ArrayProxy_class['opaque']='ptr';
            ArrayProxy_class['values']=`js_${fnname}_values`;
            ArrayProxy_class['keys']=`js_${fnname}_keys`;
            ArrayProxy_class['get']=`js_${fnname}_get`;
            ArrayProxy_class['set']=`js_${fnname}_set`;
            ArrayProxy_class['has']=`js_${fnname}_has`;
            ArrayProxy_class='(ArrayProxy_class){'+Object.entries(ArrayProxy_class).map(a=>'.'+a[0]+' = '+a[1]).join(',')+'}';
            fun.call('js_NewArrayProxy',['ctx',ArrayProxy_class],{type:'JSValue',name:"ret"});
        }
        let sizeVars=element.sizeVars||[];
        let properties={};

        if(type.endsWith(']')){
            let type2=type.split('[');
            let amount=type2[1].split(']')[0].trim();
            type2=type2[0].trim();
            properties[element.name]={sizeVars:amount};
            thiz.addApiStruct_array({name:structName, fields:[{type:type2,name:element.name,child:undefined}], binding:{properties}});
        }else if(type.endsWith('*')){
            let type2 = getsubtype(type);
            properties[element.name]={sizeVars};
            thiz.addApiStruct_array({name:structName, fields:[{type:type2,name:element.name,child:undefined}], binding:{properties}});
        }

        this.structGen.cgen.function("JSValue",`js_${structName}_get_${field}`, args, true,(fun)=>{
            fun.call('JS_GetOpaque2',['ctx', 'this_val', classId],{type:`${structName} *`,name:"ptr"});
            if(type.endsWith(']') || type.endsWith('*')){
                NewArrayProxy(fun);
            }else if(type.endsWith('&')){
                let type2 = getsubtype(type);
                properties[element.name]={sizeVars};
                fun.declare(type2+" *", field, "ptr." + field);
                //TODO: Logical issue: we create a copy here, so if someone does origin.pointer.prop = 0 this will not update properly
                (new QuickJsGenerator(fun)).cToJs(type, "ret", field,{allowNull:true},0,sizeVars);
            }else{
                fun.declare(type, field, "ptr." + field);
                (new QuickJsGenerator(fun)).cToJs(type, "ret", field,{allowNull:true},0,sizeVars);
            }
            //TODO: call addApiStruct here
            fun.return("ret");
        });

        return `js_${structName}_get_${field}`;//function name
    }
    addApiStruct_array(struct){
        const binding = struct.binding || {};
        if (binding.ignore) return;
        console.log("Binding struct array " + struct.name);
        const classId = "js_ArrayProxy_class_id";
        this.structArgs[struct.name]=struct.fields;
        //multiple typed array is possible by syntax but unimplemented

        //provide ArrayProxy_function to_array, ArrayProxy_function get, ArrayProxy_function set, ArrayProxy_function free
        const name=struct.fields[0].name;
        const structName=struct.name+'_'+name;
        const ptr=`ptr(${struct.name} *)`;
        const type=struct.fields[0].type;
        let length=binding.properties[name].sizeVars[0];
        if(length==undefined){
            throw Error(structName+' requires array length definition');
        }
        length=String(length).replaceAll('ptr.',`${ptr}.`);

        const args = { ctx:{ type: "JSContext *", name: "ctx" },
            ptr:{ type: "void *", name: "ptr" },
            set_to:{ type: "JSValue", name: "set_to" },
            property:{ type: "int", name: "property" },
            as_string:{ type: "bool", name: "as_sting" },
            keys: { type: "JSPropertyEnum * *", name: "keys" }
        };
        const get_args = [args.ctx,args.ptr,args.property,args.as_string];
        this.structGen.cgen.function("JSValue",`js_${structName}_values`, get_args, true,(ctx)=>{
            (new QuickJsGenerator(ctx)).cToJs(type+' *','ret',`${ptr}.${name}`,{},0,[length]);
            ctx.if(`as_sting==true`,(ctx)=>{
                ctx.call('JS_JSONStringify',['ctx','ret','JS_UNDEFINED','JS_UNDEFINED'],{type:'JSValue',name:'ret'});
            });
            ctx.return('ret');
        });

        const keys_args = [args.ctx,args.ptr,args.keys];
        this.structGen.cgen.function( "int", `js_${structName}_keys`, keys_args, true,ctx=>{
            ctx.declare('int','length',length);
            ctx.call('js_malloc',['ctx','(length+1) * sizeof(JSPropertyEnum)'],{type:'JSPropertyEnum * *',name:'keys[0]'});
            ctx.for(0,'length',(ctx,loopkey)=>{
                ctx.declare('JSPropertyEnum * *',`keys[0][${loopkey}]`,`(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,${loopkey})}`);
            });

            ctx.declare('JSPropertyEnum *','keys[0][length]','(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length}');
            ctx.return('true');
        });


        this.structGen.cgen.function("JSValue", `js_${structName}_get`, get_args, true,(ctx)=>{
            ctx.if([`as_sting==true`,''],ctx=>{
                ctx.if([`property==JS_ATOM_length`,''],ctx=>{
                    (new QuickJsGenerator(ctx)).cToJs('int','ret',length,{});
                    ctx.return('ret');
                },ctx=>{
                    ctx.return('JS_UNDEFINED');
                });
            },ctx=>{
                ctx.if([`property>=0 && property<${length}`,''],ctx=>{
                    ctx.declare(type, 'src', `${ptr}.${name}[property]`);
                    if(type=='void')debugger;
                    (new QuickJsGenerator(ctx)).cToJs(type, "ret", 'src');
                    ctx.return('ret');
                },ctx=>{
                    ctx.return('JS_UNDEFINED');
                });
            });
        });


        const set_args = [args.ctx,args.ptr,args.set_to,args.property,args.as_string];
        this.structGen.cgen.function( "int", `js_${structName}_set`, set_args, true,ctx=>{
            ctx.if([`as_sting==true`,''],ctx=>{
                ctx.return('false');
            },ctx=>{
                (new QuickJsGenerator(ctx)).jsToC(type,'ret','set_to',{altReturn:'-1'});
                ctx.declare(type, `${ptr}.${name}[property]`, `ret`);
            });
            ctx.return('true');
        });


        this.structGen.cgen.function( "int",`js_${structName}_has`, get_args, true,ctx=>{
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
        this.typings.constants.tsDeclareConstant(exportName, structName, description);
        this.exported[structName]='struct';
    }
    exportGlobalInt(name, description='') {
        this.moduleInit.call('JS_SetModuleExport',['ctx', 'm',`"${name}"`, `JS_NewInt32(ctx,${name})`]);
        this.moduleEntry.call('JS_AddModuleExport',['ctx','m',`"${name}"`]);
        this.typings.constants.tsDeclareConstant(name, "number", description);
        this.exported[name]='int';
    }
    exportGlobalDouble(name, description='') {
        this.moduleInit.call('JS_SetModuleExport',['ctx','m',`"${name}"`, `JS_NewFloat64(ctx,${name})`]);
        this.moduleEntry.call('JS_AddModuleExport',['ctx','m',`"${name}"`]);
        this.typings.constants.tsDeclareConstant(name, "number", description);
        this.exported[name]='float';
    }
}