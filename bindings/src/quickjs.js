import { CodeWriter, CodeGenerator } from "./generation.js"
import * as fs from "./fs.js";
import { source_parser } from "./source_parser.js";
function getsubtype(type){
    if(type.endsWith(']')){
        return type.substring(0,type.lastIndexOf(' ['));
    }else if(type.endsWith('*')){
        return type.substring(0,type.lastIndexOf(' *'));
    }else if(type.endsWith('&')){
        return type.substring(0,type.lastIndexOf(' &'));
    }else{
        const last=type.lastIndexOf(' ');
        if(last<0){
            return '';
        }else{
            return type.substring(0,type.lastIndexOf(' '));
        }
    }
}
export class QuickJsGenerator extends CodeGenerator {
    jsBindingFunction(jsName) {
        const args = [
            { type: "JSContext *", name: "ctx" },
            { type: "JSValue", name: "this_val" },
            { type: "int", name: "argc" },
            { type: "JSValue *", name: "argv" },
        ];
        const sub = this.function("js_" + jsName, "JSValue", args, true);
        return sub;
    }
    getDefaultReturn(type){
        if(type.endsWith('*')){
            return 'NULL';
        }
        switch(type){
            case 'void':
                return ' ';
            case "bool":
                return 'false';
            case "char":
            case "signed char":
                return "' '";
            case "unsigned char":
            case "short":
            case "short int":
            case "signed short":
            case "signed short int":
            case "int":
            case "signed":
            case "signed int":
            case "unsigned short":
            case "unsigned short int":
            case "unsigned":
            case "unsigned int":
            case "long":
            case "long int":
            case "signed long":
            case "signed long int":
            case "wchar_t":
            case "unsigned long":
            case "unsigned long int":
            case "long long":
            case "long long int":
            case "signed long long":
            case "signed long long int":
            case "unsigned long long":
            case "unsigned long long int":
                return "0";
            case "float":
                return "0.0f";
            case "double":
            case "long double":
                return "0.0d";
            default:
                return false;
        }
    }
    getTypedArray(type){
        switch(type){
            case "char":
            case "signed char":
                return ["JS_CLASS_INT8_ARRAY"];
            case "unsigned char":
                return ["JS_CLASS_UINT8_ARRAY","JS_CLASS_UINT8C_ARRAY"];
            case "short":
            case "short int":
            case "signed short":
            case "signed short int":
            case "int":
            case "signed":
            case "signed int":
                return ["JS_CLASS_INT16_ARRAY"];
            case "unsigned short":
            case "unsigned short int":
            case "unsigned":
            case "unsigned int":
                return ["JS_CLASS_UINT16_ARRAY"];
            case "long":
            case "long int":
            case "signed long":
            case "signed long int":
                return ["JS_CLASS_INT32_ARRAY"];
            case "wchar_t":
            case "unsigned long":
            case "unsigned long int":
                return ["JS_CLASS_UINT32_ARRAY"];
            case "long long":
            case "long long int":
            case "signed long long":
            case "signed long long int":
                return ["JS_CLASS_BIG_INT64_ARRAY"];
            case "unsigned long long":
            case "unsigned long long int":
                return ["JS_CLASS_BIG_UINT64_ARRAY"];
            case "float":
                return ["JS_CLASS_FLOAT32_ARRAY"];
            case "double":
                //case "long double"://requires special conversion
                return ["JS_CLASS_FLOAT64_ARRAY"];
            default:
                return false;
        }
    }
    jsToC(type, name, src,flags={},depth=0,errorCleanupFn=((ctx)=>{}),sizeVars=[]) {
        //needs to return flags
        let jsc={'free':'js_free','malloc':'js_malloc','calloc':'js_calloc','realloc':'js_realloc'};
        if(flags.noContextAlloc){
            jsc={'free':'jsc_free','malloc':'jsc_malloc','calloc':'jsc_calloc','realloc':'jsc_realloc'};
        }
        function getArray(ctx,type,name,src,overrideElse=false){
            //define
            if(!flags.supressDeclaration){
                ctx.declare(type,name);
            }
            let tmpname=name.replace(/[^\w]/g,'');
            let ctxif='if';

            let allowArrayType=flags.jsType==undefined||flags.jsType=='array';
            let allowStringType=flags.jsType==undefined||flags.jsType=='string';
            let allowBufferType=flags.jsType==undefined||flags.jsType=='buffer';
            let allowTypedType=flags.jsType==undefined||flags.jsType=='typed';

            let typedClassIds= ctx.getTypedArray(getsubtype(type));
            let addArray = allowArrayType && !['void','char'].includes(getsubtype(type));
            let addString= allowStringType && getsubtype(type)=='char';
            let addBuffer= allowBufferType && !getsubtype(type).includes('*');
            let addTypedArray=allowTypedType && typedClassIds!==false;
            let topDefineJs=!flags.dynamicAlloc && (addBuffer||addTypedArray);

            //remember to free src if from external sources
            if(!flags.dynamicAlloc){
                ctx.declare('bool',`freesrc_${tmpname}`,false,'false');
            }

            if( topDefineJs ){
                ctx.declare('JSValue',`da_${tmpname}`);//for de-allocation
            }

            if(addArray || addString || addBuffer || addTypedArray){
                ctx.declare("int64_t","size_" + tmpname);
            }

            //Check if NULL
            if(flags.allowNull){
                ctx[ctxif](`JS_IsNull(${src}) || JS_IsUndefined(${src})`).statement(`${name} = NULL`);
                ctxif='elsif';
            }

            //TODO: (out of spec) allow bidirectional auto casting of vec2,vec3,vec4
            //TODO: check if arrayProxy, if so, call AP.to_array, replace src to use addArray path

            //Check if Array
            let arr;
            if(addArray) {

                //Is arrayProxy?
                arr = ctx[ctxif](`JS_GetClassID(${src}) == js_ArrayProxy_class_id`);
                //void * opaque = JS_GetOpaque(val, js_ArrayProxy_class_id);
                    arr.call('JS_GetOpaque',[src, 'js_ArrayProxy_class_id'],{type:'void *',name:`opaque_${tmpname}`});
                    //ArrayProxy_class AP = *(ArrayProxy_class *)opaque;
                    arr.declare('ArrayProxy_class',`AP_${tmpname}`,false,`*(ArrayProxy_class *)opaque_${tmpname}`);
                    //arr = AP.values(ctx,AP.opaque,JS_UNDEFINED,0,false);
                    arr.call(`AP_${tmpname}.values`,['ctx',`AP_${tmpname}.opaque`,0,false],{name:src});
                    if(!flags.dynamicAlloc){
                        arr.declare('bool',`freesrc_${tmpname}`,false,'true',true);
                    }else{
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &${src})`);
                    }
                //TODO: allow dynamic binding of array properties
                arr = ctx[ctxif](`JS_IsArray(${src}) == 1`);
                let srclen = sizeVars.pop();
                let size=srclen;
                //get length from existing jsArray
                if ( srclen == undefined || flags.supressAllocation  ) {
                    let fi = arr.if(`JS_GetLength(ctx,${src},&size_${tmpname})==-1`);
                    size=`size_${tmpname}`;
                    errorCleanupFn(fi);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                }
                let subtype=getsubtype(type);
                if(flags.supressAllocation){
                    if(srclen==undefined){
                        throw new Error("Missing array length with supressAllocation will cause out of bounds writes");
                    }
                    //check if ArrayLen is == srclen, otherwise return error
                    let fi = arr.if(`${size}!=${srclen}`);
                    errorCleanupFn(fi);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                }else{
                    arr.declare(type,name,false,`(${type})${jsc.malloc}(ctx, ${size} * sizeof(${subtype}))`,true);
                    if (flags.dynamicAlloc) {
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)${jsc.free}, ${name})`);
                    }
                }
                let iter = 'i' + depth;
                if(size==1){
                    arr.declare('JSValue',`js_${tmpname}`, false, `JS_GetPropertyUint32(ctx,${src},0)`);
                    arr.jsToC(subtype, `${name}[0]`, `js_${tmpname}`, {
                        supressDeclaration: true, dynamicAlloc: true, altReturn:flags.altReturn
                    }, depth + 1);
                    arr.statement(`JS_FreeValue(ctx, js_${tmpname})`);
                }else{
                    let arrf = arr.for('0', size, iter);
                    arrf.declare('JSValue',`js_${tmpname}`, false, `JS_GetPropertyUint32(ctx,${src},${iter})`);
                    arrf.jsToC(subtype, `${name}[${iter}]`, `js_${tmpname}`, {
                        supressDeclaration: true, dynamicAlloc: true, altReturn:flags.altReturn
                    }, depth + 1);
                    arrf.statement(`JS_FreeValue(ctx, js_${tmpname})`);//There is no reason for us to keep every value out of scope
                }
                ctxif = 'elsif';
            }

            //Check if String
            if(addString) {
                arr = ctx[ctxif](`JS_IsString(${src}) == 1`);
                if(flags.noContextAlloc){
                    arr.declare("char *",`js_${name}`,false,`(char *)JS_ToCStringLen(ctx, &size_${tmpname}, ${src})`);
                    arr.declare(type,name,false,`(${type})${jsc.malloc}(ctx, size_${tmpname} * sizeof(char *))`,true);
                    arr.call(`memcpy`,[name,`js_${name}`,"size_" + tmpname]);
                    arr.call('JS_FreeCString',['ctx',name]);
                    if(flags.dynamicAlloc){
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)${jsc.free}, ${name})`);
                    }
                }else{
                    arr.declare("char *",name,false,`(char *)JS_ToCStringLen(ctx, &size_${tmpname}, ${src})`,true);
                    if(flags.dynamicAlloc){
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, ${name})`);
                    }
                }
                ctxif='elsif';
            }

            //Check if Buffer
            if(addBuffer) {//check for arrayBuffer only if [] but not [][]
                arr = ctx[ctxif](`JS_IsArrayBuffer(${src}) == 1`);
                arr.declare("size_t","size_" + tmpname);

                if(flags.noContextAlloc){
                    arr.declare(type,'js_'+name, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, ${src})`);
                    arr.declare(type,`${name}`,false,`(${type})${jsc.malloc}(ctx, size_${tmpname} * sizeof(${type}))`,true);
                    arr.call(`memcpy`,[name,`js_${name}`,"size_" + tmpname]);
                    if(flags.dynamicAlloc){
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)${jsc.free}, ${name})`);
                    }
                }else{
                    //arr.declare('JSValue',`da_${tmpname}`,false,`JS_DupValue(ctx,${src})`,!flags.dynamicAlloc);
                    arr.declare(type,name, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, ${src})`,true);
                    if(flags.dynamicAlloc){
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, ${name})`);
                    }
                }
                ctxif='elsif';
            }

            //Check if typed array like int8Array
            if(addTypedArray){
                if(ctxif!='if'){
                    ctx = ctx.else();
                }
                ctx.declare('JSClassID','classid_'+tmpname,false,`JS_GetClassID(${src})`);
                arr = ctx.if('classid_'+tmpname+'=='+typedClassIds.join(' || classid_'+tmpname+'=='));
                arr.declare('size_t','offset_'+tmpname,false);
                arr.declare('size_t','size_'+tmpname,false);
                arr.declare('JSValue','da_'+tmpname,false,`JS_GetTypedArrayBuffer(ctx,${src},&offset_${tmpname},&size_${tmpname},NULL)`,!flags.dynamicAlloc);//calls js_dup, free this

                if(flags.noContextAlloc){
                    arr.declare(type, `js_${name}`, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, da_${tmpname})`);
                    arr.statement(`js_${name}+=offset_${tmpname}`);
                    arr.statement(`size_${tmpname}-=offset_${tmpname}`);

                    arr.declare(type,`${name}`,false,`(${type})${jsc.malloc}(ctx, size_${tmpname} * sizeof(${type}))`,true);
                    arr.call(`memcpy`,[name,`js_${name}`,"size_" + tmpname]);
                    arr.call('JS_FreeValuePtr',['ctx',`&da_${tmpname}`]);
                    if(flags.dynamicAlloc){
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)${jsc.free}, ${name})`);
                    }
                }else{
                    arr.declare(type,name, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, da_${tmpname})`,true);
                    arr.statement(`${name}+=offset_${tmpname}`);
                    arr.statement(`size_${tmpname}-=offset_${tmpname}`);
                    if(flags.dynamicAlloc){
                        arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_${tmpname})`);
                    }
                }
                ctxif='elsif';
            }
            const fi=ctx.else();
            if(overrideElse){
                return fi;
            }
            errorCleanupFn(fi);
            if(!flags.dynamicAlloc){
                arr = ctx.if(`freesrc_${tmpname}`);
                arr.call('JS_FreeValue',['ctx',src]);
                arr = fi.if(`freesrc_${tmpname}`);
                arr.call('JS_FreeValue',['ctx',src]);
            }
            fi.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${type}"`]);
            fi.returnExp(flags.altReturn||"JS_EXCEPTION");
            //return exception
        }
        //normalize type
        type=type.replace('const ','');
        let tmpname=name.replace(/[^\w]/g,'');

        //spread
        //TODO: spread should accept (any) instead of last type
        if(type.startsWith('...')){
            //getSize based on argc-arg[i]
            let start=(new RegExp("\\[(\\d+)]$")).exec(src);
            if(start==null){
                start=0;
            }else{
                start=start[1];
                src=src.substring(0,src.lastIndexOf('['));
            }
            type=type.substring(3);
            let initValue='argc';
            if(start>0){
                initValue+='-'+String(start);
            }
            this.declare("size_t", `size_${tmpname}`,false,initValue);
            this.statement(`if(size_${tmpname}>${globalThis.config.spreadSize})size_${tmpname}=${globalThis.config.spreadSize}`);
            //[]=[].map()
            this.declare(type+' *', name,false,`js_malloc(ctx, size_` + tmpname + ` * sizeof(${type}))`,flags.supressDeclaration);
            if(flags.dynamicAlloc){
                this.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, ${name})`);
            }
            //main spread allways skips dynamicAlloc
            let iter='i'+depth;
            const f=this.for('0','size_' + tmpname,iter);
            const plusstr=start>0?`+${start}`:'';
            //subitems use dynamicAlloc, since we can not define names statically
            f.jsToC(type,`${name}[${iter}]`,`${src}[${iter}${plusstr}]`,{supressDeclaration:true,dynamicAlloc:true,allowNull:flags.allowNull,altReturn:flags.altReturn},depth+1);
            //Arrays
        }else if(type.endsWith(']')){
            const stpos=type.indexOf('[');
            let len=type.substring(stpos+1,type.length-1).trim();
            sizeVars.push(len);
            getArray(this,getsubtype(type)+' *',name,src);
        }else if(type.endsWith('*')){
            getArray(this,type,name,src);
        }else if(type.endsWith('&')){
            let subtype=getsubtype(type);

            const classId = this.root.structLookup[subtype];
            //functions must be a pointer, don't check for them
            if (classId){
                this.declare(subtype+' *', name, false, `(${subtype} *)JS_GetOpaque(${src}, ${classId})`,flags.supressDeclaration);
                const fi=this.if(`${name} == NULL`);
                errorCleanupFn(fi);
                fi.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${subtype}"`]);
                fi.returnExp(flags.altReturn||"JS_EXCEPTION");
            }else{
                //A pointer may be declared as [el]
                let els=this;
                if(subtype.endsWith('*')){
                    getArray(this,subtype,name,src);
                }else{
                    //differrenciate between [a] and a
                    if(flags.jsType===undefined || flags.jsType==='array'){
                        els = getArray(this,subtype+' *',name,src,true);
                    }
                    if(flags.jsType===undefined || flags.jsType!=='array'){
                        //Or direct
                        els.jsToC(subtype,'js_'+tmpname,src,flags,depth,errorCleanupFn);
                        els.declare(subtype+' *', name,false,'&js_'+tmpname,true);
                    }
                }
            }
        }else{
            switch (type) {
                case "bool": {
                    this.declare('int', 'js_'+tmpname, false, `JS_ToBool(ctx, ${src})`);
                    const fi = this.if(`${'js_'+tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not a bool"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    this.declare('bool', name, false, 'js_'+tmpname, flags.supressDeclaration);
                    break;
                }
                case "char":{
                    this.declare("char *", 'js_' + tmpname, false, `(char *)JS_ToCString(ctx, ${src})`);
                    this.declare("char", name, false, `(char)js_${tmpname}[0]`, flags.supressDeclaration);
                    this.call('JS_FreeCString', ['ctx', 'js_' + tmpname]);
                    break;
                }
                case "int8_t":
                case "int":
                case "signed":
                case "signed int":
                case "short":
                case "short int":
                case "signed short":
                case "signed short int":
                case "signed char":{//too small, needs to be cast
                    this.statement(`int32_t long_${tmpname}`);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToInt32(ctx, &long_${tmpname}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    this.declare(type, name, false, `(${type})long_${tmpname}`, flags.supressDeclaration);
                    break;
                }
                case "int32_t":
                case "long":
                case "long int":
                case "signed long":
                case "signed long int": {
                    if (!flags.supressDeclaration)
                        this.declare(type, name);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToInt32(ctx, &${name}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    break;
                }
                case "uint8_t":
                case 'wchar_t':
                case "unsigned char":
                case "unsigned short":
                case "unsigned short int":
                case "unsigned":
                case "unsigned int":{//too small, needs to be cast
                    this.statement(`uint32_t long_${tmpname}`);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToUint32(ctx, &long_${tmpname}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    this.declare(type, name, false, `(${type})long_${tmpname}`, flags.supressDeclaration);
                    break;
                }
                case "uint32_t":
                case "unsigned long":
                case "unsigned long int": {
                    if (!flags.supressDeclaration)
                        this.statement(`${type} ${name}`);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToUint32(ctx, &${name}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    break;
                }
                case "int64_t":
                case "long long":
                case "long long int":
                case "signed long long":
                case "signed long long int":{
                    if (!flags.supressDeclaration)
                        this.declare(type, name);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToInt64(ctx, &${name}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    break;
                }
                case "uint64_t":
                case "unsigned long long":
                case "unsigned long long int":
                    this.statement(`uint64_t long_${tmpname}`);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToInt64(ctx, &long_${tmpname}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    this.declare(type, name, false, `(${type})long_${tmpname}`, flags.supressDeclaration);
                    break;
                case "float": {
                    this.statement("double double_" + tmpname);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToFloat64(ctx, &double_${tmpname}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    this.declare(type, name, false, `(${type})double_${tmpname}`, flags.supressDeclaration);
                    break;
                }
                case "double":
                case "long double":{
                    if (!flags.supressDeclaration)
                        this.statement(`${type} ${name}`);
                    this.declare('int', 'err_'+tmpname, false, `JS_ToFloat64(ctx, &${name}, ${src})`);
                    const fi=this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                    break;
                }
                default: {
                    const classId = this.root.structLookup[type];
                    const callbackId = this.root.callbackLookup[type];
                    if (callbackId){
                        //Input check
                        let allocName=this.tags['_name'].substring(3);
                        let attachmode='';
                        if(allocName.toLowerCase().startsWith('attach')){
                            attachmode='attach';
                            allocName=allocName.substr('attach'.length);
                        }else if(allocName.toLowerCase().startsWith('set')){
                            attachmode='set';
                            allocName=allocName.substr('set'.length);
                        }else if(allocName.toLowerCase().startsWith('detach')){
                            attachmode='detach';
                            allocName=allocName.substr('detach'.length);
                        }
                        const threaded = this.root.callbackArgs[callbackId].threaded;
                        allocName=allocName+`_${tmpname}`;
                        if(attachmode!=='detach'){
                            //Store function and give it new context (in case it is shared ans async)
                            this.declare('trampolineContext',`ctx_${tmpname}`);
                            this.statement(`ctx_${tmpname}.ctx = ctx`);
                            this.statement(`ctx_${tmpname}.func_obj = ${src}`);//store as whole, but compare as ${src}.u.ptr (in threaded, use js_isequal)
                        }
                        function addrt(fi){
                            fi.call('JS_NewRuntime3',[],{name:'rt',type:"JSRuntime*"});
                            fi.if('!rt').returnExp('JS_EXCEPTION');
                            fi.call('JS_DupContext',['ctx']);
                            fi.call('JS_SetMaxStackSize',['rt','0']);
                            fi.call('js_std_init_handlers',['rt']);
                            fi.call('JS_NewCustomContext',['rt'],{name:`${allocName}_ctx`});
                        }
                        function freert(fi){
                            fi.call('JS_GetRuntime',[`${allocName}_ctx`],{type:'JSRuntime*', name:'rt'});
                            fi.call('JS_FreeContext',[`${allocName}_ctx`]);
                            fi.call('JS_FreeContext',[`ctx`]);
                            fi.call('js_std_free_handlers',[`rt`]);
                            fi.call('JS_FreeRuntime',[`rt`]);
                        }
                        if(attachmode==='set'){
                            this.root.addCallback(callbackId,allocName,false,threaded);
                            let fi = this.if(`JS_IsUndefined(${src}) || JS_IsNull(${src})`);
                                //unset
                                fi.call('JS_FreeValue',[`${allocName}_arr->ctx`,`${allocName}_arr->func_obj`]);
                                fi.call('JS_FreeContext',[`${allocName}_arr->ctx`]);
                                fi.declare('trampolineContext *',`${allocName}_arr`,false,`NULL`,true);
                                if(threaded)freert(fi);
                            fi = this.elsif(`JS_IsFunction(ctx,${src})==1`);
                                let fi2 = fi.if(`${allocName}_arr != NULL`);
                                    //reset
                                    fi2.call('JS_FreeValue',[`${allocName}_arr->ctx`,`${allocName}_arr->func_obj`]);
                                    fi2.call('JS_FreeContext',[`${allocName}_arr->ctx`]);
                                if(threaded){
                                    fi2=fi2.else();
                                        //set
                                        addrt(fi2);
                                }
                                if(threaded){
                                    this.call('js_copyWorker',['ctx',`${allocName}_ctx`],{name:'ctx_processor.thread_id'});
                                }
                                fi.declare('trampolineContext *',`${allocName}_arr`,false,`&ctx_${tmpname}`,true);
                            fi = this.else().returnExp(flags.altReturn||"JS_EXCEPTION");
                            //prepare for call
                            if(!flags.supressDeclaration) this.declare('void *',name,false);
                            fi = this.if(`${allocName}_arr == NULL`);
                                fi.declare('void *',name,false,'NULL',true);
                            fi = this.else();
                                fi.declare('void *',name,false,allocName+'_c',true);
                            this.call('JS_DupValue',['ctx',src]);

                        }else if(attachmode==='attach'){
                            this.root.addCallback(callbackId,allocName,true,threaded);
                            this.declare('void *',name,false,allocName+'_c',flags.supressDeclaration);
                            let fi;
                            if(threaded){
                                //threaded does not support direct calls yet
                                fi = this.if(`argc==0 || (JS_IsString(${src}) == 0 && JS_IsNumber(${src}) == 0)`);
                                fi.call('JS_ThrowTypeError',['ctx',`"${src} must be string or number"`]);
                            }else{
                                fi = this.if(`JS_IsFunction(ctx,${src})==0`);
                                fi.call('JS_ThrowTypeError',['ctx',`"${src} must be a function"`]);
                            }
                            fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                            //Attaching functions is infrequent, no realloc optimization
                            fi=this.if(`${allocName}_size==0`);
                                if(threaded)addrt(fi);
                                fi.call('js_malloc',['ctx',`sizeof(trampolineContext)`],{name:`${allocName}_arr`});
                            fi=this.else();
                                fi.call('js_realloc',['ctx',`${allocName}_arr`,`sizeof(trampolineContext) * ${allocName}_size`],{name:`${allocName}_arr`});
                            this.call('JS_DupValue',['ctx',src]);
                            if(threaded){
                                this.call('js_copyWorker',['ctx',`${allocName}_ctx`],{name:'ctx_processor.thread_id'});
                            }
                            this.declare('trampolineContext *',`${allocName}_arr[${allocName}_size]`,false,`ctx_${tmpname}`,true);
                            this.statement(`${allocName}_size++`);
                            fi=this.if(`${allocName}_size>1`).returnExp(flags.altReturn||"JS_UNDEFINED");//Dont call the real attach
                        }else if(attachmode==='detach'){
                            //find in ffiAllocName the pointer and remove it
                            this.declare('int',`${tmpname}_pos`);
                            let iter='i'+depth;
                            this.declare('void *',name,false,allocName+'_c',flags.supressDeclaration);
                            this.declare('void *',`${tmpname}_ptr`,false,`${src}.u.ptr`);
                            let fi;
                            let fo = this.for(0, `${allocName}_size`, iter,'++');
                                fi = fo.if(`${allocName}_arr[${iter}].func_obj.u.ptr == ${tmpname}_ptr`);
                                    fi.call('JS_FreeValue',[`ctx`,`${allocName}_arr[${iter}].func_obj`]);
                                    fi.call('JS_FreeValue',[`${allocName}_arr[${iter}].ctx`,`${allocName}_arr[${iter}].func_obj`]);
                                    if(threaded)fi.call('JS_FreeValue',[`${allocName}_arr[${iter}].ctx`,`${allocName}_arr[${iter}].thread_id`]);
                                    fi.call('JS_FreeContext',[`${allocName}_arr[${iter}].ctx`]);
                                    let fi2 = fi.for(undefined, `${allocName}_size-1`, iter,'++');
                                        fi2.statement(`${allocName}_arr[${iter}]=${allocName}_arr[${iter}+1]`);
                                    fi.statement(`${allocName}_size--`);
                                    fi.call('js_realloc',['ctx',`${allocName}_arr`,`sizeof(void *) * ${allocName}_size`],{name:`${allocName}_arr`});
                                    fi.statement(`break`);
                            fi= this.if(`${allocName}_size!=0`);
                                fi.returnExp(flags.altReturn||"JS_UNDEFINED");
                            if(threaded)freert(this);
                        }else{
                            throw new Error("Cannot convert into parameter type: " + type);
                        }
                    }else if(classId){
                        this.declare(type + "*", 'ptr_'+tmpname, false, `(${type}*)JS_GetOpaque(${src}, ${classId})`);
                        //AllowNull unsupported for direct types
                        const fi = this.if(`ptr_${tmpname} == NULL`);
                        errorCleanupFn(fi);
                        fi.call('JS_ThrowTypeError',['ctx',`"${src} does not allow null"`]);
                        fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                        this.declare(type, name, false, `*ptr_${tmpname}`,flags.supressDeclaration);
                    }else{
                        debugger;return;
                        throw new Error("Cannot convert into parameter type: " + type);
                    }
                }
            }
        }
    }
    cToJs(type,name,src,flags={},depth=0,sizeVars=[]){
        //normalize type
        type=type.replace('const ','');
        let tmpname=name.replace(/[^\w]/g,'');
        //We try to write return from c to js
        //This needs to work with any type, also returned by reference
        //This assumes no return int &
        function setArray(ctx,type,name,src,overrideElse=false){
            console.log(type,src);
            const subtype=getsubtype(type);
            //Check if String
            if(getsubtype(type)==='char') {
                ctx.statement(`${name} = JS_NewString(ctx, ${src})`);
                return;
            }

            //Check if Array
            if(subtype==='void'){
                console.log('At: '+type,name);
                throw new Error('Cannot convert void array type');
                return;
            }
            //Dont allow dumb usecases: Array of direct opaque data, array of char
            let srclen=sizeVars.pop();
            if(srclen===undefined){
                //TODO: remove sizeof() based length
                console.log("WARNING: sizeof length is deprecated, at "+type+name);
                ctx.declare('JSValue', name, false, `JS_NewArray(ctx)`,true);
                ctx.declare('size_t','size_'+name,false,`sizeof(${src})/sizeof(${subtype})`);
                let child=ctx.for('0', 'size_'+name,'i'+depth);
                child.cToJs(subtype,'js_'+tmpname,`${src}[i${depth}]`,flags,depth+1,sizeVars);
                child.statement(`JS_DefinePropertyValueUint32(ctx,${name},i${depth},js_${tmpname},JS_PROP_C_W_E)`);

            }else if(typeof(srclen)=="number"){
                ctx.declare('JSValue', name, false, `JS_NewArray(ctx)`,true);
                for(let i=0;i<srclen;i++){
                    ctx.cToJs(subtype,'js_'+tmpname+i,src+'['+i+']',flags,depth+1,sizeVars);
                    ctx.statement(`JS_DefinePropertyValueUint32(ctx,${name},${i},js_${tmpname}${i},JS_PROP_C_W_E)`);
                }
            }else if(typeof(srclen)=="string"){
                let child=ctx;
                if(srclen==='1&'){
                    ctx.cToJs(subtype,'js_'+tmpname,`${src}[0]`,{},depth+1,sizeVars);
                    ctx.statement(`JS_DefinePropertyValueUint32(ctx,${name},0,js_${tmpname},JS_PROP_C_W_E)`);
                    return;
                }else if(srclen==='&'){
                    sizeVars.push('&');
                    ctx.declare("size_t", "size_" + tmpname);
                    ctx.statement(`JS_GetLength(ctx, ${name},&size_${tmpname} )`);
                    child=ctx.for('0', "size_" + tmpname,'i'+depth);
                }else{
                    ctx.declare('JSValue', name, false, `JS_NewArray(ctx)`,true);
                    child=ctx.for('0', srclen,'i'+depth);
                }
                let tmpflags=structuredClone(flags);
                tmpflags.supressDeclaration=false;
                child.cToJs(subtype,'js_'+tmpname,`${src}[i${depth}]`,tmpflags,depth+1,sizeVars);
                child.statement(`JS_DefinePropertyValueUint32(ctx,${name},i${depth},js_${tmpname},JS_PROP_C_W_E)`);
            }
        }

        let subtype=getsubtype(type);
        if(type.startsWith('...')){//TODO
            //Unlikely, but if exists it will be [] of &
            //define name as []
            //getglobal JS size
            //Call CtoJs in a for loop
        }else if(type.endsWith(']')){
            //get static JS size
            const strpos=type.indexOf('[');
            let len=type.substring(strpos+1,type.length-1).trim();
            //define
            if(!flags.supressDeclaration){
                this.declare('JSValue', name);
            }
            sizeVars.push(Number(len));
            setArray(this,getsubtype(type)+' *',name,src);
            //define name as (any)[] using setArray
        }else if(type.endsWith('*')){
            //define name as (any)[] using setArray
            if(!flags.supressDeclaration){
                this.declare('JSValue', name);
            }
            setArray(this,type,name,src);
        }else if(type.endsWith('&')){
            // set flag supressDeclaration=true (we already have JSValue) in the function ABOVE, for readability
            if(this.root.structLookup[subtype]){
                return;//class by pointer, no work to do
            }
            // int * & is [int,int]
            // int & is [int] or int without writeback
            if(subtype.endsWith(']')){
                const stpos=type.indexOf('[');
                let len=type.substring(stpos+1,type.length-1).trim();
                sizeVars.push(len);
                subtype=getsubtype(subtype)+' *';
            }
            //Check if NULL
            let arr=this;
            if(flags.allowNull){
                arr.if(`${src} != NULL`);
            }
            /*Experimental*/
            if(flags.supressDeclaration){
                //Check only supported if previously defined (AKA. returns by pointer)
                arr = arr.if(`JS_IsArray(${name}) == 1`);
            }else{
                arr.call('JS_NewArray',['ctx'],{type:'JSValue', name});
            }
            if(subtype.endsWith(' *')){
                sizeVars.push("&");
            }else{
                sizeVars.push('1&');
                subtype+=' *';
            }
            setArray(arr,subtype,name,src);
        }else{
            //Normal type return
            switch (type) {
                case "bool": {
                    this.declare('JSValue', name, false, `JS_NewBool(ctx, ${src})`, flags.supressDeclaration);
                    break;
                }
                case "char":{
                    this.declare("JSValue", 'js_' + name, false, `JS_NewStringLen(ctx, &${src},1)`, flags.supressDeclaration);
                    break;
                }
                case "int8_t":
                case "int":
                case "signed":
                case "signed int":
                case "short":
                case "short int":
                case "signed short":
                case "signed short int":
                case "signed char":{//too small, needs to be cast
                    this.declare('JSValue', name, false, `JS_NewInt32(ctx, (long)${src})`, flags.supressDeclaration);
                    break;
                }
                case "int32_t":
                case "long":
                case "long int":
                case "signed long":
                case "signed long int": {
                    this.declare('JSValue', name, false, `JS_NewInt32(ctx, ${src})`, flags.supressDeclaration);
                    break;
                }
                case "uint8_t":
                case "unsigned char":
                case "unsigned short":
                case "unsigned short int":
                case "unsigned":
                case "unsigned int":{//too small, needs to be cast
                    this.declare('JSValue', name, false, `JS_NewUint32(ctx, (unsigned long)${src})`, flags.supressDeclaration);
                    break;
                }
                case "uint32_t":
                case "unsigned long":
                case "unsigned long int": {
                    this.declare('JSValue', name, false, `JS_NewUint32(ctx,  ${src})`, flags.supressDeclaration);
                    break;
                }
                case "int64_t":
                case "long long":
                case "long long int":
                case "signed long long":
                case "signed long long int":{
                    this.declare('JSValue', name, false, `JS_NewInt64(ctx, ${src})`, flags.supressDeclaration);
                    break;
                }
                case "uint64_t":
                case "unsigned long long":
                case "unsigned long long int":
                    this.declare('JSValue', name, false, `JS_NewInt64(ctx, (long long)${src})`, flags.supressDeclaration);
                    break;
                case "float":
                case "long double":{
                    this.declare('JSValue', name, false, `JS_NewFloat64(ctx, (double)${src})`, flags.supressDeclaration);
                    break;
                }
                case "double":{
                    this.declare('JSValue', name, false, `JS_NewFloat64(ctx, ${src})`, flags.supressDeclaration);
                    break;
                }
                //va_list can not be generic
                //case "va_list"
                default: {
                    if(type==''){
                        debugger;
                        return;
                    }
                    const classId = this.root.structLookup[type];
                    if (!classId)
                        throw new Error("Cannot convert parameter type to Javascript: " + type);
                    this.jsStructToOpq(type, name, src, classId);
                }
            }
        }
    }
    jsStructToOpq(structType, jsVar, srcVar, classId) {
        this.declare(structType + "*", 'ptr_'+jsVar, false, `(${structType}*)js_malloc(ctx, sizeof(${structType}))`);
        this.statement("*ptr_" + jsVar + " = " + srcVar);
        this.declare("JSValue", jsVar, false, `JS_NewObjectClass(ctx, ${classId})`);
        this.call("JS_SetOpaque", [jsVar, "ptr_"+jsVar]);
    }
    jsCleanUpParameter(type, name, src, flags = {}) {
        //Data clearing when not using dynamic Allocation
        function getArray(ctx,type,name,src){
            //console.log(type,'subtype',getsubtype(type));
            //define
            let ctxif='if';
            //Check if NULL
            if(flags.allowNull){
                ctx[ctxif](`JS_IsNull(${src}) || JS_IsUndefined(${src})`);
                ctxif='elsif';
            }
            //Check if IsArray
            let arr;
            if(type!='void *'){
                arr=ctx[ctxif](`JS_IsArray(${src}) == 1`);
                arr.call('js_free',['ctx',name]);
                ctxif='elsif';
            }
            //Check if IsString
            if(getsubtype(type)=='char') {
                arr = ctx[ctxif](`JS_IsString(${src}) == 1`);
                arr.statement(`JS_FreeCString(ctx, ${name})`);
                ctxif='elsif';
            }
            let tmpname=name.replace(/[^\w]/g,'');
            //metacheck if could be arrayBuffer (is a simple int* or int{} )
            if(!getsubtype(type).includes('*')) {//check for arrayBuffer only if [] but not [][]
                arr = ctx[ctxif](`JS_IsArrayBuffer(${src}) == 1`);
                //Check if isArrayBuffer
                arr.call('JS_FreeValue',['ctx','da_'+tmpname]);
                ctxif='elsif';
            }
            let typedClassIds=ctx.getTypedArray(getsubtype(type));
            if(typedClassIds!==false){
                if(ctxif!='if'){
                    ctx = ctx.else();
                }
                ctx.declare('JSClassID', 'classid_'+tmpname,false,`JS_GetClassID(${src})`);
                arr = ctx.if('classid_'+tmpname+'=='+typedClassIds.join(' && classid_'+tmpname+'=='));
                arr.call('js_free',['ctx','&da_'+tmpname]);
                ctxif='elsif';
            }
        }
        //normalize type
        type=type.replace('const ','');
        if(type.startsWith('...')){
            this.call('js_free',['ctx',name]);
            //Arrays
        }else if(type.endsWith(']')){
            getArray(this,getsubtype(type)+' *',name,src);
        }else if(type.endsWith('*')){
            getArray(this,type,name,src);
        }else if(type.endsWith('&')){
            const classId = this.root.structLookup[type.replace(" &", "")];
            if (!classId){
                getArray(this,type,name,src);
            }
        }
    }
    jsFunctionList(name) {
        this.line("static const JSCFunctionListEntry " + name + "[] = {");
        this.indent();
        const sub = new this.constructor(this);
        sub.setTag("_type", "js-function-list");
        sub.setTag("_name", name);
        this.child(sub);
        this.unindent();
        this.statement("}");
        this.breakLine();
        return sub;
    }
    jsClassId(id) {
        this.declare("JSClassID", id, true);
        return id;
    }
    jsFuncDef(jsName, numArgs, cName, functype) {
        if(functype==undefined){
            this.line(`JS_CFUNC_DEF("${jsName}",${numArgs},${cName}),`);
        }else{
            this.line(`JS_CFUNC_MAGIC_DEF("${jsName}",${numArgs},${cName},${functype}),`);
        }
    }
    jsPropStringDef(key, value) {
        this.line(`JS_PROP_STRING_DEF("${key}","${value}", JS_PROP_CONFIGURABLE),`);
    }
    jsGetSetDef(key, getFunc, setFunc) {
        this.line(`JS_CGETSET_DEF("${key}",${getFunc || "NULL"},${setFunc || "NULL"}),`);
    }
    jsAliasDef(key, aliasof) {
        this.line(`JS_ALIAS_DEF("${key}",${aliasof || "NULL"},`);
    }
    jsStructFinalizer(classId, structName, onFinalize) {
        const args = [{ type: "JSRuntime *", name: "rt" }, { type: "JSValue", name: "val" }];
        const body = this.function(`js_${structName}_finalizer`, "void", args, true);
        body.statement(`${structName}* ptr = JS_GetOpaque(val, ${classId})`);
        body.if("ptr", cond => {
            //cond.call("TraceLog", ["LOG_INFO",`"Finalize ${structName} %p"`,"ptr"])
            if (onFinalize)
                onFinalize(cond, "ptr");
            cond.call("js_free_rt", ["rt", "ptr"]);
        });
        return body;
    }
    jsClassDeclaration(structName, classId, finalizerName, funcListName) {
        const body = this.function("js_declare_" + structName, "int",  [{ type: "JSContext *", name: "ctx" }, { type: "JSModuleDef *", name: "m" }], true);
        body.declare("JSRuntime *", "rt",false,`JS_GetRuntime(ctx)`);
        body.call("JS_NewClassID", ["rt","&" + classId]);
        const classDefName = `js_${structName}_def`;
        body.declare("JSClassDef", classDefName,  false, `{ .class_name = "${structName}", .finalizer = ${finalizerName} }`);
        body.call("JS_NewClass", ["rt", classId, "&" + classDefName]);
        body.declare("JSValue", "proto", false, "JS_NewObject(ctx)");
        body.call("JS_SetPropertyFunctionList", ["ctx", "proto", funcListName, `countof(${funcListName})`]);
        body.call("JS_SetClassProto", ["ctx", classId, "proto"]);
        body.statement("return 0");
        return body;
    }
    jsStructGetter(structName, classId, field, type, element, nested) {
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }];
        let fun;
        let thiz=this;
        function declarefunction(){
            fun = thiz.function(`js_${structName}_get_${field}`, "JSValue", args, true);
            fun.declare(structName + "*", "ptr", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
        }
        function NewArrayProxy(){
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
        let fnname=structName+'_'+element.name
        if (element.overrideRead) {
            element.overrideRead(fun);
        } else if(type.endsWith(']')){
            let type2=type.split('[');
            let amount=type2[1].split(']')[0].trim();
            type2=type2[0].trim();
            properties[element.name]={sizeVars:amount};
            this.root.addApiStruct_array({name:structName, fields:[{type:type2,name:element.name,child:undefined}], binding:{properties}});
            declarefunction();
            NewArrayProxy();
        }else if(type.endsWith('*')){
            let type2 = getsubtype(type);
            properties[element.name]={sizeVars};
            this.root.addApiStruct_array({name:structName, fields:[{type:type2,name:element.name,child:undefined}], binding:{properties}});
            declarefunction();
            NewArrayProxy();
        }else{
            declarefunction();
            fun.declare(type, field, false, "ptr->" + field);
            fun.cToJs(type, "ret", field,{allowNull:true},0,sizeVars);
        }
        //TODO: call addApiStruct here
        fun.returnExp("ret");
        return fun;
    }
    jsStructIterator(structName, classId, field, type, element, nested) {
        //not yet known what to do here,
        //We do need some function JS_CFunc_Def refers to

        return fun;
    }
    jsStructSetter(structName, classId, field, type, element, nested) {
        //console.log('jsStructSetter',structName, classId, field, type, ids, overrideWrite);
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }, { type: "JSValue", name: "v" }];
        const fun = this.function(`js_${structName}_set_${field}`, "JSValue", args, true);
        fun.declare(structName + "*", "ptr", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
        fun.jsToC(type, "value", "v",{noContextAlloc:true});
        if (element.overrideWrite) {
            element.overrideWrite(fun);
        } else {
            if(type.endsWith('*')){
                fun.if(`ptr->${field}!=NULL`)
                .call('jsc_free',['ctx',"ptr->" + field]);
            }
            if(type.endsWith(']')){
                let type2=type.split('[');
                let amount=type2[1].substring(0,type2[1].length-1);
                type2=type2[0];
                fun.call(`memcpy`,[`ptr->${field}`,'value',`${amount} * sizeof(${type2})`]);
            }else{
                fun.statement("ptr->" + field + " = value");
            }
        }
        fun.returnExp("JS_UNDEFINED");
        return fun;
    }
    jsStructConstructor(structType, fields, classId) {
        //console.log('jsStructConstructor',structType, fields, classId, ids);
        const body = this.jsBindingFunction(structType + "_constructor");
        let r1=body.if('argc==0');
            r1.declare(structType + "*", 'ptr__return', false, `(${structType}*)js_calloc(ctx, 1, sizeof(${structType}))`);
            r1.declare("JSValue", '_return', false, `JS_NewObjectClass(ctx, ${classId})`);
            r1.call("JS_SetOpaque", ['_return', "ptr__return"]);
            r1.returnExp("_return");
        for(let i = 0; i < fields.length; i++) {
            const para = fields[i];
            body.jsToC(para.type, para.name, "argv[" + i + "]");
        }
        body.declareStruct(structType, "_struct", fields.map(x => x.name));
        body.jsStructToOpq(structType, "_return", "_struct", classId);
        body.returnExp("_return");
        return body;
    }
}