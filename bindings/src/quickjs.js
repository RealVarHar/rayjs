import { CodeScope, getsubtype, resolveVariable, getVariableParts } from "./cgen.js";
import * as fs from "./fs.js";
import { source_parser } from "./source_parser.js";

function getBoundName(variable){
    let bound_name=variable.props.bound_name;
    if(!variable.aliased_types)return bound_name;
    while(bound_name==undefined && variable.aliased_types.length==1){
        variable=variable.aliased_types[0];
        bound_name=variable.props.bound_name;
    }
    return bound_name;
}
function compileSrcLen(ctx0,srcLen0,writeto){
    //We get ['condition','variable'|object]
    ctx0.declare('int',writeto);
    let tasks=[[ctx0,srcLen0]];
    while(tasks.length>0){
        const [ctx1,srcLen1]=tasks.pop();
        ctx1.if([]);
        for(let i=0;i<srcLen1.length;i+=2){
            ctx1.elsif(srcLen1[i],(ctx2)=>{
                if(typeof(srcLen1[i+2])=="object"){
                    tasks.push([nested,srcLen1[i+1]]);
                }else{
                    ctx2.declare('int',writeto,srcLen1[i+1]);
                }
            })
        }
    }

}
function subrepeat(fieldname,sizevars){
    //converts 'type',[2,3] to {{type[0][0],type[0][1],type[0][2]},{type[1][0],type[1][1],type[1][2]}}
    if(sizevars.length==0)return fieldname;
    let structuredFields=new Array(sizevars[sizevars.length-1]).fill('');//contains elements in a desired structure
    //first pass, create structure
    for(let i=sizevars.length-2;i>=0;i--){
        let swapstructuredFields = [];
        for(let j=0;j<sizevars[i];j++){
            let cpy= structuredClone(structuredFields);
            swapstructuredFields.push(cpy);
        }
        structuredFields = swapstructuredFields;
    }
    //second pass, add numbering
    let unpacked=[[structuredFields,'']];
    let containers = [structuredFields];
    while(unpacked.length>0){
        let [item,size]=unpacked.pop();
        if(typeof(item[0])=='string'){
            for(let i=0;i<item.length;i++){
                item[i]=fieldname+size+`[${i}]`;
            }
        }else{
            for(let i=0;i<item.length;i++){
                unpacked.push([item[i],size+`[${i}]`]);
                if(typeof(item[0][0])!='string'){
                    containers.push(item[i]);
                }
            }
        }
    }
    //Third pass, stringify
    if(typeof(structuredFields[0])=='string'){
        //if only 1d, skip parsing containers
        return `{${structuredFields.join(',')}}`;
    }
    while(containers.length>0){
        let item=containers.pop();
        for(let i=0;i<item.length;i++){
            item[i]=`{${item[i].join(',')}}`;
        }
    }
    return `{${structuredFields.join(',')}}`;
}
export function getDefaultReturn(type){
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
function getStaticArrayLen(type){
    //converts "char[4][3][2]" to ["char",[4,3,2]]
    let sizevars=[];
    while(type.endsWith(']')) {
        const stpos = type.lastIndexOf(']');
        const st2pos = type.lastIndexOf('[', stpos);
        let len= type.substring(st2pos+1,stpos).trim();
        if(!isNaN(len))len=Number(len);
        sizevars.unshift(len);
        type = type.substring(0,st2pos).trim();
    }
    return {type,sizevars};
}
function getTypedArray(type){
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
export class QuickJsGenerator {
    cgen=new CodeScope();
    constructor(cgen){if(cgen!=undefined)this.cgen=cgen;}
    jsBindingFunction(jsName,fn) {
        const args = [
            { type: "JSContext *", name: "ctx" },
            { type: "JSValue", name: "this_val" },
            { type: "int", name: "argc" },
            { type: "JSValue *", name: "argv" },
        ];
        this.cgen.function("JSValue","js_" + jsName, args, true,fn);
    }
    jsToC(type, name, src,flags={},depth=0,errorCleanupFn=((ctx)=>{}),sizeVars=[]) {
        //needs to return flags
        let jsc={'free':'js_free','malloc':'js_malloc','calloc':'js_calloc','realloc':'js_realloc'};
        if(flags.noContextAlloc){
            jsc={'free':'jsc_free','malloc':'jsc_malloc','calloc':'jsc_calloc','realloc':'jsc_realloc'};
        }
        function getArray(ctx,type,name,src,overrideElse){
            //define
            ctx.declare(type,name);
            let tmpname=name.replace(/[^\w]/g,'');
            let ctxif='if';

            let allowArrayType=flags.jsType==undefined||flags.jsType=='array';
            let allowStringType=flags.jsType==undefined||flags.jsType=='string';
            let allowBufferType=flags.jsType==undefined||flags.jsType=='buffer';
            let allowTypedType=flags.jsType==undefined||flags.jsType=='typed';

            let typedClassIds= getTypedArray(getsubtype(type));
            let addArray = allowArrayType && !['void','char'].includes(getsubtype(type));
            let addString= allowStringType && getsubtype(type)=='char';
            let addBuffer= allowBufferType && !getsubtype(type).includes('*');
            let addTypedArray=allowTypedType && typedClassIds!==false;
            let topDefineJs=!flags.dynamicAlloc && (addTypedArray);

            //remember to free src if from external sources
            if(!flags.dynamicAlloc && addArray){
                ctx.declare('bool',`freesrc_${tmpname}`,'false');
            }

            if( topDefineJs ){
                ctx.declare('JSValue',`da_${tmpname}`);//for de-allocation
            }

            if(addArray || addString || addBuffer || addTypedArray){
                ctx.declare("int64_t","size_" + tmpname);
            }
            if(addArray){
                ctx.call('JS_GetClassID',[src],{type:'JSClassID',name:`${tmpname}_class`});
            }
            ctx.declare('JSValue','src',src);
            ctx.if([]);

            //TODO: (out of spec) allow bidirectional auto casting of vec2,vec3,vec4


            //Check if Array
            if(addArray) {
                //Is arrayProxy?
                ctx.elsif(`${tmpname}_class == js_ArrayProxy_class_id`,(ctx)=>{
                    //void * opaque = JS_GetOpaque(val, js_ArrayProxy_class_id);
                    ctx.call('JS_GetOpaque',['src', 'js_ArrayProxy_class_id'],{type:'void *',name:`opaque_${tmpname}`});
                    //ArrayProxy_class AP = *(ArrayProxy_class *)opaque;
                    ctx.declare('ArrayProxy_class',`AP_${tmpname}`,`opaque_${tmpname}(ArrayProxy_class *)[0]`);
                    //arr = AP.values(ctx,AP.opaque,JS_UNDEFINED,0,false);
                    ctx.call(`AP_${tmpname}.values`,['ctx',`AP_${tmpname}.opaque`,0,false],{type:'JSValue',name:'src'});
                    if(!flags.dynamicAlloc){
                        ctx.declare('bool',`freesrc_${tmpname}`,'true');
                    }else{
                        ctx.call('memoryStore',['memoryCurrent', 'JS_FreeValue', 'src'],{type:'memoryNode *',name:'memoryCurrent'});
                    }
                });

                //TODO: allow dynamic binding of array properties
                ctx.if(`JS_IsArray(src) == 1`,(ctx)=>{
                    let srclen = sizeVars.pop();
                    let size=srclen;
                    //get length from existing jsArray
                    if ( srclen == undefined ) {
                        ctx.if(`JS_GetLength(ctx,src,size_${tmpname})==-1`,(ctx)=>{
                            if(size==undefined){
                                size=`size_${tmpname}`;
                            }
                            errorCleanupFn(ctx);
                            ctx.return(flags.altReturn||"JS_EXCEPTION");
                        });
                    }
                    let subtype=getsubtype(type);
                    if(flags.supressAllocation){
                        if(srclen==undefined){
                            throw new Error("Missing array length with supressAllocation will cause out of bounds writes");
                        }
                        //check if ArrayLen is == srclen, otherwise return error
                        ctx.if(`${size}!=${srclen}`,(ctx)=>{
                            errorCleanupFn(ctx);
                            ctx.return(flags.altReturn||"JS_EXCEPTION");
                        });
                    }else{
                        ctx.call(jsc.malloc,['ctx',`${size} * sizeof(${subtype})`],{type,name});
                        if (flags.dynamicAlloc) {
                            ctx.call('memoryStore',['memoryCurrent', `${jsc.free}`,name],{type:'memoryNode *',name:'memoryCurrent'});
                        }
                    }
                    if(size==1){
                        ctx.call('JS_GetPropertyUint32',['ctx','src',0],{type:'JSValue',name:`js_${tmpname}`});
                        let gen=new QuickJsGenerator(ctx);
                        gen.jsToC(subtype, `${name}[0]`, `js_${tmpname}`, {
                            supressDeclaration: true, dynamicAlloc: true, altReturn:flags.altReturn
                        }, depth + 1);
                        ctx.call('JS_FreeValue',['ctx',`js_${tmpname}`]);
                    }else{
                        ctx.for(0,size,(ctx,iter)=>{
                            ctx.call('JS_GetPropertyUint32',['ctx','src',iter],{type:'JSValue',name:`js_${tmpname}`});
                            let gen=new QuickJsGenerator(ctx);
                            gen.jsToC(subtype, `${name}[${iter}]`, `js_${tmpname}`, {
                                supressDeclaration: true, dynamicAlloc: true, altReturn:flags.altReturn
                            }, depth + 1);
                            ctx.call('JS_FreeValue',['ctx',`js_${tmpname}`]);//There is no reason for us to keep every value out of scope
                        });
                    }
                });
            }

            //Check if NULL
            if(flags.allowNull){
                ctx.elsif(`JS_IsNull(${src}) || JS_IsUndefined(${src})`,(ctx)=>{
                    ctx.declare(type,name,'NULL');
                });
            }

            //Check if String
            if(addString) {
                ctx.elsif(`JS_IsString(${src}) == 1`,(ctx)=>{
                    if(flags.noContextAlloc){
                        ctx.call('JS_ToCStringLen',['ctx', `size_${tmpname}`,'src'],{name:`js_${name}`,type:"char *"});
                        ctx.call(jsc.malloc,['ctx', `size_${tmpname} * sizeof(char *)`],{type,name});
                        ctx.call(`memcpy`,[name,`js_${name}`,"size_" + tmpname]);
                        ctx.call('JS_FreeCString',['ctx',name]);
                        if(flags.dynamicAlloc){
                            ctx.call('memoryStore',['memoryCurrent', `${jsc.free}`, name],{type:'memoryNode *',name:'memoryCurrent'});
                        }
                    }else{
                        ctx.call('JS_ToCStringLen',['ctx', `size_${tmpname}`, 'src'],{type:"char *",name});
                        if(flags.dynamicAlloc){
                            ctx.call('memoryStore',['memoryCurrent', 'JS_FreeCString', name],{type:'memoryNode *',name:'memoryCurrent'});
                        }
                    }
                });
            }

            //Check if Buffer
            if(addBuffer) {//check for arrayBuffer only if [] but not [][]
                ctx.elsif(`JS_IsArrayBuffer(src) == 1`,(ctx)=>{
                    ctx.declare("size_t","size_" + tmpname);

                    if(flags.noContextAlloc){
                        ctx.call('JS_GetArrayBuffer',['ctx', `size_${tmpname}`, 'src'],{type,name:'js_'+name});
                        ctx.call(jsc.malloc,['ctx', `size_${tmpname} * sizeof(${type})`],{type,name});
                        ctx.call(`memcpy`,[name,`js_${name}`,"size_" + tmpname]);
                    }else{
                        //arr.declare('JSValue',`da_${tmpname}`,false,`JS_DupValue(ctx,${src})`,!flags.dynamicAlloc);
                        ctx.call('JS_GetArrayBuffer',['ctx',`size_${tmpname}`,'src'],{type,name});
                    }
                });
            }

            function onbadType(ctx){
                errorCleanupFn(ctx);
                if(!flags.dynamicAlloc && addArray){
                    ctx.if(`freesrc_${tmpname}`,(ctx)=>{
                        ctx.call('JS_FreeValue',['ctx','src']);
                    });
                }
                ctx.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${type}"`]);
                ctx.return(flags.altReturn||"JS_EXCEPTION");
            }

            //Check if typed array like int8Array
            if(addTypedArray){
                ctx.elsif('',(ctx)=>{
                    ctx.call('JS_GetClassID',['src'],{type:'JSClassID',name:'classid_'+tmpname});
                    ctx.if(['classid_'+tmpname+'=='+typedClassIds.join(' || classid_'+tmpname+'=='),''],(ctx)=>{
                        ctx.declare('size_t','offset_'+tmpname);
                        ctx.declare('size_t','size_'+tmpname);
                        ctx.call('JS_GetTypedArrayBuffer',['ctx','src',`offset_${tmpname}`,`size_${tmpname}`,'NULL'],{type:'JSValue',name:'da_'+tmpname});//calls js_dup, free this

                        if(flags.noContextAlloc){
                            ctx.call('JS_GetArrayBuffer',['ctx',`size_${tmpname}`,`da_${tmpname}`],{type,name:`js_${name}`});
                            ctx.add(type,`js_${name}`,`offset_${tmpname}`);
                            ctx.sub('size_t',`size_${tmpname}`,`offset_${tmpname}`);

                            ctx.call(jsc.malloc,['ctx', `size_${tmpname} * sizeof(${type})`],{type,name});
                            ctx.call(`memcpy`,[name,`js_${name}`,"size_" + tmpname]);
                            ctx.call('JS_FreeValuePtr',['ctx',`da_${tmpname}`]);
                            if(flags.dynamicAlloc){
                                ctx.call('memoryStore',['memoryCurrent', `${jsc.free}`, name],{type:'memoryNode *',name:'memoryCurrent'});
                            }
                        }else{
                            ctx.call('JS_GetArrayBuffer',['ctx', `size_${tmpname}`, `da_${tmpname}`],{type,name});
                            ctx.add(type,name,`offset_${tmpname}`);
                            ctx.sub('size_t',`size_${tmpname}`,`offset_${tmpname}`);
                            if(flags.dynamicAlloc){
                                ctx.call('memoryStore',['memoryCurrent', 'JS_FreeValuePtr', `da_${tmpname}`],{type:'memoryNode *',name:'memoryCurrent'});
                            }
                        }
                    },onbadType);
                });
            }else{
                if(overrideElse!==undefined){
                    ctx.elsif('',overrideElse);
                    return;
                }
                ctx.elsif('',onbadType);
                //return exception
            }
        }
        //normalize type
        type=type.replace('const ','');
        let tmpname=name.replace(/[^\w]/g,'');

        if(type.endsWith(']')){
            let arrayLen = getStaticArrayLen(type);
            sizeVars.push(...arrayLen.sizevars);
            getArray(this.cgen,arrayLen.type+" *".repeat(arrayLen.sizevars.length),name,src);
        }else if(type.endsWith('*')){
            getArray(this.cgen,type,name,src);
        }else if(type.endsWith('&')){
            let subtype=getsubtype(type);

            let variable=this.cgen.getVariables()[subtype];
            while(variable!=undefined && variable.type=='type' && variable.subtype=='direct'){
                variable=this.cgen.getVariables()[variable.src];
            }
            //functions must be a pointer, don't check for them
            if(subtype=='void'){
                let target=this.cgen.allocVariable('target');
                this.cgen.declare('void *',`target`);
                this.cgen.assign(name,`${target}&`);
                //same as: this.cgen.call('js_malloc',['ctx','sizeof(void *)'],{name,type:'void *'});
            }else if (variable!=undefined && variable.type=='type' && variable.subtype=='struct'){
                let bound_name=getBoundName(variable);
                if(bound_name==undefined){
                    throw new Error("struct must have been bound to exist as opaque");
                }
                this.cgen.call('JS_GetOpaque',[src,bound_name],{type:`${subtype} *`,name});
                this.cgen.if(`${name} == NULL`,(ctx)=>{
                    errorCleanupFn(ctx);
                    ctx.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${subtype}"`]);
                    ctx.return(flags.altReturn||"JS_EXCEPTION");
                });
            }else{
                //A pointer may be declared as [el]
                let els=this;
                if(subtype.endsWith('*')){
                    flags.jsType="array";
                    getArray(this.cgen,subtype+' *',name,src);
                }else{
                    //differrenciate between [a] and a
                    if(flags.jsType===undefined){
                        //detect array
                        flags.jsType="array";
                        //TODO: unnecesarly calls malloc
                        getArray(this.cgen,subtype+' *',name,src,(ctx)=>{
                            //or direct
                            let gen=new QuickJsGenerator(ctx);
                            gen.jsToC(subtype,'js_'+tmpname,src,flags,depth,errorCleanupFn);
                            ctx.declare(subtype+' *', name,'js_'+tmpname);
                        });
                    }else if(flags.jsType==='array'){
                        //TODO: unnecesarly calls malloc
                        getArray(this.cgen,subtype+' *',name,src);
                    }else{
                        //Or direct
                        this.jsToC(subtype,'js_'+tmpname,src,flags,depth,errorCleanupFn);
                        this.cgen.declare(subtype+' *', name,'js_'+tmpname);
                    }
                }
            }
        }else{
            switch (type) {
                case "bool": {
                    this.cgen.call('JS_ToBool',['ctx',src],{type:'int',name:'js_'+tmpname});
                    this.cgen.if(`${'js_'+tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not a bool"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    this.cgen.declare('bool', name, 'js_'+tmpname);
                    break;
                }
                case "char":{
                    this.cgen.call('JS_ToCString',['ctx', src],{type:"char *",name:'js_' + tmpname});
                    this.cgen.declare("char", name, `js_${tmpname}[0](char)`);
                    this.cgen.call('JS_FreeCString', ['ctx', 'js_' + tmpname]);
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
                    this.cgen.declare('int32_t',`long_${tmpname}`);
                    this.cgen.call('JS_ToInt32',['ctx', `long_${tmpname}`, src],{type:'int',name:'err_' + tmpname});
                    //let fnname=this.cgen.previous().text?.name;
                    //if(fnname=='js_DrawText')debugger;
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    this.cgen.declare(type, name, `long_${tmpname}(${type})`);
                    break;
                }
                case "int32_t":
                case "long":
                case "long int":
                case "signed long":
                case "signed long int": {
                    this.cgen.declare(type, name);
                    this.cgen.call('JS_ToInt32',['ctx',`${name}`,src],{type:'int',name:'err_' + tmpname});
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    break;
                }
                case "uint8_t":
                case 'wchar_t':
                case "unsigned char":
                case "unsigned short":
                case "unsigned short int":
                case "unsigned":
                case "unsigned int":{//too small, needs to be cast
                    this.cgen.declare('uint32_t',`long_${tmpname}`);
                    this.cgen.call('JS_ToUint32',['ctx', `long_${tmpname}`, src],{type:'int',name:'err_' + tmpname});
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    this.cgen.declare(type, name, `long_${tmpname}(${type})`);
                    break;
                }
                case "uint32_t":
                case "unsigned long":
                case "unsigned long int": {
                    this.cgen.declare(type,name);
                    this.cgen.call('JS_ToUint32',['ctx', `${name}`, src],{type:'int',name:'err_' + tmpname});
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    break;
                }
                case "int64_t":
                case "long long":
                case "long long int":
                case "signed long long":
                case "signed long long int":{
                    this.cgen.declare(type, name);
                    this.cgen.call('JS_ToInt64',['ctx', `${name}`, src],{type:'int',name:'err_' + tmpname});
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    break;
                }
                case "uint64_t":
                case "unsigned long long":
                case "unsigned long long int":
                    this.cgen.declare('uint64_t',` long_${tmpname}`);
                    this.cgen.call('JS_ToInt64',['ctx', `long_${tmpname}`, src],{type:'int',name:'err_' + tmpname });
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    this.cgen.declare(type, name, `long_${tmpname}(${type})`);
                    break;
                case "float": {
                    this.cgen.declare("double","double_" + tmpname);
                    this.cgen.call('JS_ToFloat64',['ctx', `double_${tmpname}`, src],{type:'int',name:'err_' + tmpname});
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    this.cgen.declare(type, name, `double_${tmpname}(${type})`);
                    break;
                }
                case "double":
                case "long double":{
                    this.cgen.declare(type,name);
                    this.cgen.call('JS_ToFloat64',['ctx',`${name}`,src],{type:'int',name:'err_'+tmpname});
                    this.cgen.if(`err_${tmpname}<0`,(ctx)=>{
                        errorCleanupFn(ctx);
                        ctx.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                        ctx.return(flags.altReturn||"JS_EXCEPTION");
                    });
                    break;
                }
                default: {
                    let variables=this.cgen.getVariables();
                    let variable=variables[type];
                    if(variable==undefined){
                        throw new Error("Requred type is not found: " + type);
                    }
                    if (variable.type=='type'&&variable.subtype=='function'){
                        //Input check
                        let functionHeader=this.cgen.previous();
                        let allocName=functionHeader.text.name.substring(3);//cut off 'js_'
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
                        const threaded = flags.threaded;
                        if(attachmode!=='detach'){
                            //Store function and give it new context (in case it is shared ans async)
                            this.cgen.declare('trampolineContext',`ctx_${tmpname}`);
                            this.cgen.assign(`ctx_${tmpname}.ctx`,'ctx');
                            this.cgen.assign(`ctx_${tmpname}.func_obj`,src);//store as whole, but compare as ${src}.u.ptr (in threaded, use js_isequal)
                        }
                        function addrt(ctx){
                            ctx.call('JS_NewRuntime3',[],{name:'rt',type:"JSRuntime*"});
                            ctx.if('!rt').return('JS_EXCEPTION');
                            ctx.call('JS_DupContext',['ctx']);
                            ctx.call('JS_SetMaxStackSize',['rt','0']);
                            ctx.call('js_std_init_handlers',['rt']);
                            ctx.call('JS_NewCustomContext',['rt'],{name:`${allocName}_ctx`});
                        }
                        function freert(ctx){
                            ctx.call('JS_GetRuntime',[`${allocName}_ctx`],{type:'JSRuntime*', name:'rt'});
                            ctx.call('JS_FreeContext',[`${allocName}_ctx`]);
                            ctx.call('JS_FreeContext',[`ctx`]);
                            ctx.call('js_std_free_handlers',[`rt`]);
                            ctx.call('JS_FreeRuntime',[`rt`]);
                        }
                        if(variables[`${allocName}_arr`]==undefined)debugger;
                        if(attachmode==='set'){
                            this.cgen.if([`JS_IsUndefined(${src}) || JS_IsNull(${src})`,`JS_IsFunction(ctx,${src})==1`,''],(ctx)=>{
                                //unset
                                ctx.call('JS_FreeValue',[`${allocName}_arr[0].ctx`,`${allocName}_arr[0].func_obj`]);
                                ctx.call('JS_FreeContext',[`${allocName}_arr[0].ctx`]);
                                ctx.declare('trampolineContext *',`${allocName}_arr`,`NULL`);
                                if(threaded)freert(ctx);
                            },(ctx)=>{
                                let fi2 = ctx.if(`${allocName}_arr != NULL`,(ctx)=>{
                                    //reset
                                    ctx.call('JS_FreeValue',[`${allocName}_arr[0].ctx`,`${allocName}_arr[0].func_obj`]);
                                    ctx.call('JS_FreeContext',[`${allocName}_arr[0].ctx`]);
                                });
                                if(threaded){
                                    ctx.elsif('',addrt);//set
                                }
                                ctx.declare('trampolineContext *',`${allocName}_arr`,`ctx_${tmpname}`);
                            },(ctx)=>{
                                ctx.return(flags.altReturn||"JS_EXCEPTION");
                            });
                            if(threaded){
                                this.cgen.call('js_copyWorker',['ctx',`${allocName}_ctx`],{name:'ctx_processor.thread_id',type:'JSValue'});
                            }

                            //prepare for call
                            this.cgen.declare('void *',name);
                            this.cgen.if([`${allocName}_arr == NULL`,''],(ctx)=>{
                                ctx.declare('void *',name,'NULL');
                            },(ctx)=>{
                                ctx.declare('void *',name,variable.callback);
                            });
                            this.cgen.call('JS_DupValue',['ctx',src]);

                        }else if(attachmode==='attach'){
                            this.cgen.declare('void *',name,variable.callback);
                            let fi;
                            if(threaded){
                                //threaded does not support direct calls yet
                                this.cgen.if([`argc==0 || (JS_IsString(${src}) == 0 && JS_IsNumber(${src}) == 0)`],(ctx)=>{
                                    ctx.call('JS_ThrowTypeError',['ctx',`"${src} must be string or number"`]);
                                    ctx.return(flags.altReturn||"JS_EXCEPTION");
                                });
                            }else{
                                this.cgen.if([`JS_IsFunction(ctx,${src})==0`],(ctx)=>{
                                    ctx.call('JS_ThrowTypeError',['ctx',`"${src} must be a function"`]);
                                    ctx.return(flags.altReturn||"JS_EXCEPTION");
                                });
                            }
                            //Attaching functions is infrequent, no realloc optimization
                            this.cgen.if([`${allocName}_size==0`,''],(ctx)=>{
                                if(threaded)addrt(ctx);
                                ctx.call('js_malloc',['ctx',`sizeof(trampolineContext)`],{type:'trampolineContext *',name:`${allocName}_arr`});
                            },(ctx)=>{
                                ctx.call('js_realloc',['ctx',`${allocName}_arr`,`sizeof(trampolineContext) * ${allocName}_size`],{type:'trampolineContext *',name:`${allocName}_arr`});
                            });
                            this.cgen.call('JS_DupValue',['ctx',src]);
                            if(threaded){
                                this.cgen.call('js_copyWorker',['ctx',`${allocName}_ctx`],{name:'ctx_processor.thread_id'});
                            }
                            this.cgen.declare('trampolineContext *',`${allocName}_arr[${allocName}_size]`,`ctx_${tmpname}`);
                            this.cgen.add('size_t',`${allocName}_size`,1);
                            this.cgen.if(`${allocName}_size>1`,(ctx)=>{
                                ctx.return(flags.altReturn||"JS_UNDEFINED");//Dont call the real attach
                            });
                        }else if(attachmode==='detach'){
                            //find in ffiAllocName the pointer and remove it
                            this.cgen.declare('int',`${tmpname}_pos`);
                            this.cgen.declare('void *',name,variable.callback);
                            let fi;
                            this.cgen.for(0, `${allocName}_size`, (ctx,iter)=>{
                                ctx.if([`JS_IsEqual(${allocName}_arr[${iter}].ctx, ${allocName}_arr[${iter}].func_obj, ${src})`],(ctx)=>{
                                    ctx.call('JS_FreeValue',[`ctx`,`${allocName}_arr[${iter}].func_obj`]);
                                    ctx.call('JS_FreeValue',[`${allocName}_arr[${iter}].ctx`,`${allocName}_arr[${iter}].func_obj`]);
                                    if(threaded)ctx.call('JS_FreeValue',[`${allocName}_arr[${iter}].ctx`,`${allocName}_arr[${iter}].thread_id`]);
                                    ctx.call('JS_FreeContext',[`${allocName}_arr[${iter}].ctx`]);
                                    ctx.for(iter, `${allocName}_size-1`, (ctx,iter)=>{
                                        ctx.assign(`${allocName}_arr[${iter}]`,`${allocName}_arr[${iter}+1]`);
                                    });
                                });
                                ctx.sub('size_t',`${allocName}_size`,1);
                                ctx.call('js_realloc',['ctx',`${allocName}_arr`,`sizeof(void *) * ${allocName}_size`],{type:'trampolineContext *',name:`${allocName}_arr`});
                                ctx.break();
                            });

                            this.cgen.if([`${allocName}_size!=0`],(ctx)=>{
                                ctx.return(flags.altReturn||"JS_UNDEFINED");
                            });

                            if(threaded)freert(this.cgen);
                        }else{
                            throw new Error("Cannot convert into parameter type: " + type);
                        }
                    }else if(variable.type=='type'){
                        const bound_name = getBoundName(variable);
                        if(bound_name==undefined){
                            throw new Error("struct must have been bound to exist as opaque");
                        }
                        this.cgen.call('JS_GetOpaque',[src,bound_name],{type:`${type} *`,name:'ptr_'+tmpname});
                        //AllowNull unsupported for direct types
                        this.cgen.if(`ptr_${tmpname} == NULL`,(ctx)=>{
                            errorCleanupFn(ctx);
                            ctx.call('JS_ThrowTypeError',['ctx',`"${src} does not allow null"`]);
                            ctx.return(flags.altReturn||"JS_EXCEPTION");
                        });

                        this.cgen.declare(type, name, `ptr_${tmpname}`);
                    }else{
                        throw new Error("Requred type is not a type: " + type);
                    }
                }
            }
        }
    }
    cToJs(type,name,src,flags={},depth=0,sizeVars=[]){
        let cgen=this.cgen;
        //normalize type
        type=type.replace('const ','');
        let tmpname=name.replace(/[^\w]/g,'');
        //We try to write return from c to js
        //This needs to work with any type, also returned by reference
        //This assumes no return int &
        function setArray(ctx,type,name,src,overrideElse=false){
            const subtype=getsubtype(type);
            //Check if String
            if(getsubtype(type)==='char') {
                ctx.call('JS_NewString',['ctx',src],{type:'JSValue',name});
                return;
            }

            //Dont allow dumb usecases: Array of direct opaque data, array of char
            let srclen=sizeVars.pop();

            //Check if Array
            if(subtype==='void'){
                if(srclen !== undefined){
                    ctx.call('JS_NewArrayBufferCopy',['ctx',src,srclen],{type:'JSValue',name});
                }else{
                    console.log('At: '+type,name);
                    throw new Error('Cannot convert void array type without length');
                }
                return;
            }
            if(srclen===undefined){
                //TODO: remove sizeof() based length
                console.log("WARNING: sizeof length is deprecated, at "+type+name);
                ctx.declare(type,`sizeref_${name}`,src);
                ctx.call('sizeof',[`sizeref_${name}`],{type:'size_t',name:'size_'+name});
                ctx.call('sizeof',[subtype],{type:'size_t',name:'size1_'+name});
                ctx.declare('size_t','size_'+name,`size_${name}/size1_${name}`);
                ctx.for('0', 'size_'+name,(ctx,loopvar)=>{
                    (new QuickJsGenerator(ctx)).cToJs(subtype,'js_'+tmpname,`${src}[${loopvar}]`,flags,depth+1,sizeVars);
                    ctx.call('JS_DefinePropertyValueUint32',['ctx',name,loopvar,`js_${tmpname}`,'JS_PROP_C_W_E']);
                });


            }else if(typeof(srclen)=="number"){
                for(let i=0;i<srclen;i++){
                    (new QuickJsGenerator(ctx)).cToJs(subtype,'js_'+tmpname+i,src+'['+i+']',flags,depth+1,sizeVars);
                    ctx.call('JS_DefinePropertyValueUint32',['ctx',name,i,`js_${tmpname}${i}`,'JS_PROP_C_W_E']);
                }
            }else if(typeof(srclen)=="object" || typeof(srclen)=="string"){
                if(typeof(srclen)=="object"){
                    compileSrcLen(ctx,srclen,'srclen');
                    srclen='srclen';
                }
                let child=ctx;
                ctx.for('0', srclen,(ctx,loopvar)=>{
                    let tmpflags=structuredClone(flags);
                    tmpflags.supressDeclaration=false;
                    (new QuickJsGenerator(ctx)).cToJs(subtype,'js_'+tmpname,`${src}[${loopvar}]`,tmpflags,depth+1,sizeVars);
                    ctx.call('JS_DefinePropertyValueUint32',['ctx',name,loopvar,`js_${tmpname}`,'JS_PROP_C_W_E']);
                });
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
            cgen.declare('JSValue', name);
            sizeVars.push(Number(len));
            cgen.call('JS_NewArray',['ctx'],{type:'JSValue',name});
            setArray(this.cgen,getsubtype(type)+' *',name,src);
            //define name as (any)[] using setArray
        }else if(type.endsWith('*')){
            //define name as (any)[] using setArray
            if(type!=='char *') {
                cgen.call('JS_NewArray',['ctx'],{type:'JSValue',name});
            }
            setArray(this.cgen,type,name,src);
        }else if(type.endsWith('&')){
            // set flag supressDeclaration=true (we already have JSValue) in the function ABOVE, for readability
            let variables = this.cgen.getVariables();
            let variable =  variables[subtype];
            if(variable !== undefined){
                const bound_name = getBoundName(variable);
                if(bound_name==undefined){
                    throw new Error("struct must have been bound to exist as opaque");
                }
                //class by pointer
                this.jsStructToOpq(subtype, name, src, bound_name, flags.supressDeclaration);
                return;
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
            let arr=this.cgen;
            if(flags.allowNull){
                arr.if(`${src} != NULL`,(fn=>{arr=fn;}));
            }
            let subsrc=src;
            if(subtype.endsWith(' *')){
                subsrc+='[0]';
            }else{
                sizeVars.push(1);
                subtype+=' *';
            }
            //if defined as a direct value previously in code, it is good to check
            let var_exists=false;
            try{
                resolveVariable(getVariableParts(name,variables),[],variables);
                var_exists=true;
            }catch(e){
                //If does not exist resolveVariable would throw an error
            }
            if(var_exists){
                //Check only supported if previously defined (AKA. returns by pointer)
                arr.if(`JS_IsArray(${name}) == 1`,(arr)=>{
                    setArray(arr,subtype,name,subsrc);
                });
            }else{
                arr.call('JS_NewArray',['ctx'],{type:'JSValue', name});
                setArray(arr,subtype,name,subsrc);
            }
        }else{
            //Normal type return
            switch (type) {
                case "bool": {
                    this.cgen.call('JS_NewBool',['ctx',src],{type:'JSValue',name});
                    break;
                }
                case "char":{
                    this.cgen.call('JS_NewStringLen',['ctx',`${src}`,1],{type:'JSValue',name});
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
                    this.cgen.call('JS_NewInt32',['ctx',`${src}(long)`],{type:'JSValue',name});
                    break;
                }
                case "int32_t":
                case "long":
                case "long int":
                case "signed long":
                case "signed long int": {
                    this.cgen.call('JS_NewInt32',['ctx',src],{type:'JSValue',name});
                    break;
                }
                case "uint8_t":
                case "unsigned char":
                case "unsigned short":
                case "unsigned short int":
                case "unsigned":
                case "unsigned int":{//too small, needs to be cast
                    this.cgen.call('JS_NewUint32',['ctx',`${src}(unsigned long)`],{type:'JSValue',name});
                    break;
                }
                case "uint32_t":
                case "unsigned long":
                case "unsigned long int": {
                    this.cgen.call('JS_NewUint32',['ctx',src],{type:'JSValue',name});
                    break;
                }
                case "int64_t":
                case "long long":
                case "long long int":
                case "signed long long":
                case "signed long long int":{
                    this.cgen.call('JS_NewInt64',['ctx',src],{type:'JSValue',name});
                    break;
                }
                case "uint64_t":
                case "unsigned long long":
                case "unsigned long long int":
                    this.cgen.call('JS_NewInt64',['ctx',`${src}(long long)`],{type:'JSValue',name});
                    break;
                case "float":
                case "long double":{
                    this.cgen.call('JS_NewFloat64',['ctx',`${src}(double)`],{type:'JSValue',name});
                    break;
                }
                case "double":{
                    this.cgen.call('JS_NewFloat64',['ctx',src],{type:'JSValue',name});
                    break;
                }
                //va_list can not be generic
                //case "va_list"
                default: {
                    if(type==''){
                        debugger;
                        return;
                    }
                    let variables=this.cgen.getVariables();
                    let variable=variables[type];
                    if(variable==undefined){
                        throw new Error("Requred type is not found: " + type);
                    }else if(variable.type!='type'){
                        throw new Error("Requred type is not a type: " + type);
                    }
                    const bound_name = getBoundName(variable);
                    if(bound_name==undefined){
                        throw new Error("struct must have been bound to exist as opaque");
                    }
                    this.jsStructToOpq(type, name, src, bound_name);
                }
            }
        }
    }
    jsStructToOpq(structType, jsVar, srcVar, classId, supressDeclaration=false) {
        //TODO: just check if already defined
        if(!supressDeclaration){
            this.cgen.call('js_malloc',['ctx', `sizeof(${structType})`],{type:`${structType} *`,name:'ptr_'+jsVar});
            this.cgen.assign(`ptr_${jsVar}[0]`,srcVar);
            this.cgen.call('JS_NewObjectClass',['ctx', classId],{type:"JSValue", name:jsVar});
            this.cgen.call("JS_SetOpaque", [jsVar, "ptr_"+jsVar]);
        }else{
            this.cgen.call("JS_SetOpaque", [jsVar, srcVar]);
        }
    }
    jsCleanUpParameter(type, name, src, flags = {}) {
        //Data clearing when not using dynamic Allocation
        function getArray(ctx,type,name,src,ref=false){
            //console.log(type,'subtype',getsubtype(type));
            //define
            let ctxif='if';
            //Check if NULL
            if(flags.allowNull){
                ctx[ctxif](`JS_IsNull(${src}) || JS_IsUndefined(${src})`,()=>{});
                ctxif='elsif';
            }
            //Check if IsArray
            ctx.if([]);//initialize if

            if(type!='void *'){
                ctx.elsif(`JS_IsArray(${src}) == 1`,ctx=>{
                    ctx.call('js_free',['ctx',name]);
                });
            }

            if(ref)return;

            //Check if IsString
            if(getsubtype(type)=='char') {
                ctx.elsif(`JS_IsString(${src}) == 1`,(ctx)=>{
                    ctx.call('JS_FreeCString',['ctx',name]);
                });
            }
            let tmpname=name.replace(/[^\w]/g,'');
            //metacheck if could be arrayBuffer (is a simple int* or int{} )
            let typedClassIds=getTypedArray(getsubtype(type));
            if(typedClassIds!==false){
                ctx.elsif('',(ctx)=>{
                    ctx.call('JS_GetClassID',[src],{type:'JSClassID',name:'classid_'+tmpname});
                    ctx.if('classid_'+tmpname+'=='+typedClassIds.join(' && classid_'+tmpname+'=='),ctx=>{
                        ctx.call('js_free',['ctx','da_'+tmpname]);
                    });
                });
            }
        }
        //normalize type
        type=type.replace('const ','');
        if(type.startsWith('...')){
            this.call('js_free',['ctx',name]);
            //Arrays
        }else if(type.endsWith(']')){
            getArray(this.cgen,getsubtype(type)+' *',name,src);
        }else if(type.endsWith('*')){
            getArray(this.cgen,type,name,src);
        }else if(type.endsWith('&')){
            const variables=this.cgen.getVariables();
            if (!variables[type.replace(" &", "")]){
                getArray(this.cgen,type,name,src,true);
            }
        }
    }
    jsClassId(id) {
        this.cgen.declare("static JSClassID", id);
        return id;
    }
    jsFuncDef(jsName, numArgs, cName, functype) {
        if(functype==undefined){
            return `JS_CFUNC_DEF("${jsName}",${numArgs},${cName})`;
        }else{
            return `JS_CFUNC_MAGIC_DEF("${jsName}",${numArgs},${cName},${functype})`;
        }
    }
    jsPropStringDef(key, value) {
        return `JS_PROP_STRING_DEF("${key}","${value}", JS_PROP_CONFIGURABLE)`;
    }
    jsGetSetDef(key, getFunc, setFunc) {
        return `JS_CGETSET_DEF("${key}",${getFunc || "NULL"},${setFunc || "NULL"})`;
    }
    jsAliasDef(key, aliasof) {
        return `JS_ALIAS_DEF("${key}",${aliasof || "NULL"}`;
    }
    jsStructFinalizer(classId, structName, onFinalize) {
        const args = [{ type: "JSRuntime *", name: "rt" }, { type: "JSValue", name: "val" }];
        this.cgen.function("void",`js_${structName}_finalizer`, args, true,(ctx)=>{
            ctx.call('JS_GetOpaque',['val',classId],{type:`${structName} *`,name:'ptr'});
            ctx.if(["ptr"], (cond) => {
                //cond.call("TraceLog", ["LOG_INFO",`"Finalize ${structName} %p"`,"ptr"])
                if (onFinalize)
                    onFinalize(cond, "ptr");
                cond.call("js_free_rt", ["rt", "ptr"]);
            });
        });
        return `js_${structName}_finalizer`;
    }
    jsClassDeclaration(structName, classId, finalizerName, funcListName) {
        this.cgen.function("int","js_declare_" + structName,  [{ type: "JSContext *", name: "ctx" }, { type: "JSModuleDef *", name: "m" }], true,(ctx)=>{
            ctx.call('JS_GetRuntime',['ctx'],{type:"JSRuntime *",name:'rt'});
            ctx.call("JS_NewClassID", ["rt",classId]);
            const classDefName = `js_${structName}_def`;
            ctx.declare("JSClassDef", classDefName, `{ .class_name = "${structName}", .finalizer = ${finalizerName} }`);
            ctx.call("JS_NewClass", ["rt", classId, classDefName]);
            ctx.call('JS_NewObject',['ctx'],{type:'JSValue',name:'proto'});
            ctx.call("JS_SetPropertyFunctionList", ["ctx", "proto", funcListName, `countof(${funcListName})`]);
            ctx.call("JS_SetClassProto", ["ctx", classId, "proto"]);
            ctx.return(0);
        });
        return "js_declare_" + structName;//function name
    }
    jsStructIterator(structName, classId, field, type, element, nested) {
        //not yet known what to do here,
        //We do need some function JS_CFunc_Def refers to

        return fun;
    }
    jsStructConstructor(structType, fields, classId) {
        //console.log('jsStructConstructor',structType, fields, classId, ids);
        let functionName;
        this.jsBindingFunction(structType + "_constructor",(body)=>{
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
            for(let i = 0; i < fields.length; i++) {
                const para = fields[i];
                (new QuickJsGenerator(body)).jsToC(para.type, para.name, "argv[" + i + "]",flags);
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
}