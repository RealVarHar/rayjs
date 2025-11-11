import { CodeScope, getsubtype, resolveVariable, getVariableParts } from "./cgen.js";
import * as fs from "./fs.js";
import {simpleregex, source_parser, a0, azZ0} from "./source_parser.js";

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
export function subrepeat(fieldname,sizevars){
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
        case "JSValue":
            return "JS_EXCEPTION";
        default:
            return `(${type}){0}`;
    }
}
export function getStaticArrayLen(type){
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
        case "void":
            return ["any"];
        default:
            if(typeof(type)=='object'){
                if(type.type=='type' && type.subtype=='struct' && type.props.isSympleType){
                    return getTypedArray(type.fields[0].type);
                }
            }
            return false;
    }
}

/** return closest c type for jstype
 * @param {string} jsType
 * @return {string} ctype
 */
function jsTypeToC(jsType){
    switch(jsType){
        case "string":return "char";
        case "char":return "char";
        case "bool":return "bool";
        case "int8":return "int";
        case "uint8":return "unsigned int";
        case "int32":return "long";
        case "uint32":return "unsigned long";
        case "int64":return "long long";
        case "uint64":return "unsigned long long";
        case "float":return "float";
        case "double":return "double";
        default:{
            if(typeof(jsType)=='object'){
                return jsType;
            }
            return false;
        }
    }
}
export function getaliasedVariable(variable){
    if(variable==undefined)return;
    while(variable.aliased_types&&variable.aliased_types.length==1){
        variable=variable.aliased_types[0];
    }
    return variable;
}
export function ctojsType(variables,ctype){
    //This splitting logic would have to be implemented many times, this condences it into one space
    //a depth can be made by doing [arr,arr,bool]
    //switch can be reached by: passthrough
    // passthrough: [arr,[arr,ptr,string],char] //Good balance
    // pathing: [arr,[arr,ptr,string],[char,char,null]] //multi level chice is hard
    // digging: [arr,[[arr,char],[ptr,char],[string]]] //not easily extensible by external scripts


    //the 'goal' is to reach an ability to edit the type logic without code rewrites, so we can hot swap ["string"] for ["utf8string"]
    //or add/remove alt container paths so that [arr|buffer|null] is fine
    //Special rules:
    // null can be only on top level so [[null,arr],char] but never [arr,[arr,null]]
    //buffer and typed buffer bust be near last, so [arr,buffer,char] but never [buffer,arr,char]
    ctype=ctype.replace('const ','');
    let typeParts=[];
    //typeparts are not just split by ' '
    let jsType=[];
    let capture=[];
    let pos=simpleregex(ctype,["bos",' &','br*',' *'],ctype.length-1,capture);
    let pointers=capture[1].replaceAll(' ','').split('');
    while(ctype[pos]==']'){
        let capture2=[];
        pos=simpleregex(ctype,['br*',azZ0+' +*/','bs','[','br*',' '],pos-1,capture2);
        pointers.unshift(capture2[0]);
    }
    let maintype=ctype.substring(0,pos+1);
    if(capture[0]==' &'){
        //if aref of simpleType, use arr* otherwise arr1
        jsType[0]=['arr|1','ptr|1'];
    }
    for(let i=0;i<pointers.length;i++){
        let t=[];
        if(i==pointers.length-1){
            let variable=getaliasedVariable(variables[maintype]);
            if(variable!=undefined && variable.type=='type' && variable.subtype=='struct' && variable.props.bound_name){
                t.push('arrayProxy');
                t.push('arr|'+pointers[i]);
                //Arrays here are wierd, we know that * object was requested so we get from js [obj,obj] getting [*obj,*obj] to repackage them manually as *(obj,obj)

                //buffers and arrays can have [4float]
                if(getTypedArray(variable)!=false){
                    t.push('typedbuffer');
                }
                if(variable.props.isSympleType){
                    t.push('buffer');
                }
                if(pointers[i]=='*'||pointers[i]==1){
                    t.push('ptr');//ptr shall always be pushed last
                }
            }else{
                t.push('buffer');
                if(maintype!='void'){
                    t.push('arrayProxy');
                    t.push('arr|'+pointers[i]);
                }else{
                    t.push('string');
                }
                if(getTypedArray(maintype)!=false){
                    t.push('typedbuffer');
                }
                if(maintype=='char'){
                    t.push('string');
                }
            }
        }else{
            t=['arrayProxy','arr|'+pointers[i]];
        }
        if(t.length==1){
            jsType.push(t[0]);
        }else{
            jsType.push(t);
        }
    }
    switch (maintype) {
        case "bool": {
            jsType.push('bool');break;
        }
        case "char":{
            jsType.push("char");break;
        }
        case "int8_t":
        case "int":
        case "signed":
        case "signed int":
        case "short":
        case "short int":
        case "signed short":
        case "signed short int":
        case "signed char":{
            jsType.push("int8");break;
        }
        case "uint8_t":
        case 'wchar_t':
        case "unsigned char":
        case "unsigned short":
        case "unsigned short int":
        case "unsigned":
        case "unsigned int":{
            jsType.push("uint8");break;
        }
        case "int32_t":
        case "long":
        case "long int":
        case "signed long":
        case "signed long int": {
            jsType.push("int32");break;
        }
        case "uint32_t":
        case "unsigned long":
        case "unsigned long int": {
            jsType.push("uint32");break;
        }
        case "int64_t":
        case "long long":
        case "long long int":
        case "signed long long":
        case "signed long long int":{
            jsType.push("int64");break;
        }
        case "uint64_t":
        case "unsigned long long":
        case "unsigned long long int":
            jsType.push("uint64");break;
        case "float": {
            jsType.push("float");break;
        }
        case "double":
        case "long double":{
            jsType.push("double");break;
        }
        case "void":break;
        default:{
            let variable=getaliasedVariable(variables[maintype]);
            if(variable==undefined){
                throw new Error("Requred type is not found: " + maintype);
            }
            if(variable.type!='type'){
                throw new Error("Requred type is not found: " + maintype);
            }
            if (variable.subtype=='function' || variable.subtype=='struct'){
                jsType.push(variable);
                //issimpletype is not resolved here due to ptr->object being ptr->4*float that is not correct
            }else{
                throw new Error("Requred variable is not a type" + JSON.stringify(variable));
            }
        }
    }
    return jsType;
}
function jscheck(jsType,nextjsType,src){
    //return appropirate check for that jsType
    if(Array.isArray(jsType)){
        let ret=jsType.map(a=>jscheck(a,nextjsType,src)).filter(a=>a!='').join(' || ');
        if(ret=='')return 'false';
        return ret;
    }
    if(typeof(jsType)=='string'){
        jsType=jsType.split('|');
    }
    //TODO: detection can be more accurate
    switch(jsType[0]){
        case "arrayProxy":return `JS_GetClassID(${src}) == js_ArrayProxy_class_id`;
        case "bool":return`JS_IsBool(${src})`;
        case "char":return `JS_IsString(${src})`;
        case "string":return `JS_IsString(${src})`;
        case "int8":
        case "uint8":
        case "int32":
        case "uint32":
        case "int64":
        case "uint64":
        case "float":
        case "double":return `JS_IsNumber(${src})`;
        case "ptr":return jscheck(nextjsType,undefined,src);
        case "buffer":return`JS_IsArrayBuffer(${src})`;
        case "null":return`JS_IsNull(${src}) || JS_IsUndefined(${src})`;
        case "arr":{
            if(jsType[1]!='*'){
                return `js_IsArrayLength(ctx,${src},${jsType[1]})`;
            }
            return `JS_IsArray(${src})`;
        }
        case "typedbuffer":
            let typedClassIds;
            if(nextjsType==undefined){
                return `JS_GetTypedArrayType(${src})!=-1`//any
            }else
            if(Array.isArray(nextjsType)){
                typedClassIds=[];
                for(let i=0;i<nextjsType.length;i++){
                    let tmp=getTypedArray(jsTypeToC(nextjsType[i]));
                    if(tmp!==false){
                        typedClassIds.push(...tmp);
                    }
                }
                if(typedClassIds.length==0)break;
            }else{
                typedClassIds=getTypedArray(nextjsType);
                if(typedClassIds==false)break;
            }

            return typedClassIds.map(clas=>`JS_GetClassID(${src}) == ${clas}`).join(' || ');
        default:{
            if(typeof(jsType)=='object'){
                //check if struct or function
                if(typeof(jsType)=='object' && jsType.type=='type' && jsType.subtype=='struct' && jsType.props.bound_name){
                    return `JS_GetClassID(${src}) == ${jsType.props.bound_name}`;
                }
            }
        }
    }
    return undefined;
}
export function resolveSizeVar(ctx,sizeVar,sizevarName){
    //Resolvers sizevar iftrees (arrays)
    if(!Array.isArray(sizeVar))return sizeVar;
    if(sizevarName==undefined){
        sizevarName=ctx.allocVariable('size');
    }
    let branches=[[ctx,sizeVar]];
    while(branches.length>0){
        let [fn,branch]=branches.pop();
        let ifbodies=[];
        for(let result of branch.slice(branch.length/2)){
            ifbodies.push((fn2)=>{
                if(Array.isArray(result)){
                    branches.push([fn2,result]);
                }else{
                    fn2.assign(sizevarName,result);
                }
            })
        }
        fn.declare('size_t',sizevarName);
        fn.if(branch.slice(0,branch.length/2),...ifbodies);
    }
    return sizevarName;
}
export function deepCCopy(ctx,ctype,name,src,variables,deepCCopyBox,testShallow=false){
    //generates code that creates name as ptr to a full copy
    let variable=variables[ctype];
    if(variable==undefined)return false;
    variable=getaliasedVariable(variable);
    if(!testShallow)ctx.declare(ctype,name,src);
    for(let i=0;i<variable.fields.length;i++){
        let field=variable.fields[i];
        let capture=[];
        simpleregex(field.type,['r+',azZ0+' ','r*',' *','os','[','r*',a0+' '],0,capture);
        let arrsize=capture[1].replaceAll(' ','').length;
        if(field.type.startsWith('char *'))arrsize--;
        capture[3]=Number.parseInt(capture[3]);
        let sizeVars=field.binding.sizeVars||[];
        let type=field.type;
        let fn=ctx;
        let rowsrc=`${src}.${field.name}`;
        let rowtarget=`${name}.${field.name}`;
        let iter=0;
        if(!isNaN(capture[3])){
            type=capture[0]+capture[1]+'*';
            if(arrsize>0){
                fn.for(0,capture[3],(fn2,iter2)=>{fn=fn2;iter=iter2});
                rowsrc=`${rowsrc}[${iter}]`;
                rowtarget=`${rowtarget}[${iter}]`;
            }
        }
        if(arrsize>0){
            if(testShallow)return false;
            for(let i=0;i<arrsize;i++){
                if(sizeVars[i]==undefined){
                    throw new Error(`size of ${ctype}.${field.name} is undefined`);
                }
                fn.call('jsc_malloc',['ctx',`sizeof(${type})${sizeVars[i]!=1?('*'+sizeVars[i]):''}`],{type,name:rowtarget});
                let size=resolveSizeVar(fn,sizeVars[i],fn.allocVariable(`size${i}`));

                fn.for(0,size,(fn2,iter2)=>{fn=fn2;iter=iter2});
                type=getsubtype(type);

                rowsrc=`${rowsrc}[${iter}]`;
                rowtarget=`${rowtarget}[${iter}]`;

                if(i==arrsize-1){
                    deepCCopyBox.deepCCopy(fn,type,rowtarget,rowsrc,variables);
                }else{
                    let newrowsrc=fn.allocVariable(`${field.name}_src${i+1}`);
                    fn.declare(type,newrowsrc,rowsrc);
                    rowsrc=newrowsrc;
                    let newrowtarget=fn.allocVariable(`${field.name}_target${i+1}`);
                    fn.declare(type,newrowtarget,rowtarget);
                    rowtarget=newrowtarget;
                }
            }
        }
    }
    return true;
}
export function deepCFree(ctx,ctype,name,src){
    //generates code that frees deeply the whole struct but not the top level pointer (ctype is 'struct' not 'struct *')

}
export function jsToC(topctx,topjsType,toptype,topname,topsrc,flags={},variables){
    if(variables==undefined){
        variables=topctx.getVariables();
    }
    if(topjsType==undefined){
        topjsType=ctojsType(variables,toptype);
    }
    if(flags.onError==undefined){
        flags.onError=(fn=>{
            fn.return("JS_EXCEPTION");
        });
    }
    if(flags.onEmpty==undefined)flags.onEmpty=flags.onError;
    topjsType=topjsType.map(a=>{if(!Array.isArray(a))return [a];return a;});
    let allowNull=topjsType[0].find(a=>a=='null')!=undefined;
    //Allowed flags:
    //nocontextAlloc: own all internal memory for compatibility
    //altReturn: replace JS_EXCEPTION on error
    //The purpose of this function is co write correctly to $name based on jsType
    //It is prefferable to implement some sort of stack instead of relying on self-calling that could be too limiting
    //jsType often shows multiple paths, explode them as we go
    let jsc={'free':'js_free','malloc':'js_malloc','calloc':'js_calloc','realloc':'js_realloc'};
    if(flags.noContextAlloc){
        jsc={'free':'jsc_free','malloc':'jsc_malloc','calloc':'jsc_calloc','realloc':'jsc_realloc'};
    }
    topctx.declare(toptype,topname);
    let paths=[{ctx:topctx,src:topsrc,jsType:topjsType,name:topname,type:toptype}];
    while(paths.length>0){
        let currentPath=paths.pop();
        let currentTypes=currentPath.jsType[0];
        let nextTypes=currentPath.jsType[1];
        const ctx=currentPath.ctx;
        const src=currentPath.src;
        const name=currentPath.name;
        const type=currentPath.type;
        const subtype=getsubtype(type);
        //We need a way to check for any type in a list
        //Implementing a whole router for this is silly, a is<thing> shall always be provided
        let overrodeElse=false;
        let is_arrayProxy=undefined;
        if(currentTypes.includes('arrayProxy')){
            is_arrayProxy=ctx.allocVariable('is_arrayProxy');
            currentTypes.splice(currentTypes.indexOf('arrayProxy'),1);
            ctx.declare('bool',is_arrayProxy,0);
            ctx.if(`JS_GetClassID(${src}) == js_ArrayProxy_class_id`,(fn)=>{
                let AP_opaque=ctx.allocVariable('AP_opaque');
                let AP_fn=ctx.allocVariable('AP_fn');
                fn.declare('bool',is_arrayProxy,1);
                fn.call('JS_GetOpaque',[src, 'js_ArrayProxy_class_id'],{type:'void *',name:AP_opaque});
                fn.declare('ArrayProxy_class',AP_fn,`${AP_opaque}(ArrayProxy_class *)[0]`);
                fn.call(`${AP_fn}.values`,['ctx',src,`${AP_fn}.opaque`,0,false],{type:'JSValue',name:src});
            });
        }
        ctx.if([]);
        let tmpname=name.replace(/[^\w]/g,'');
        for(let i=0;i<currentTypes.length;i++){
            let currentTypeLen;
            let currentType=currentTypes[i];
            if(typeof(currentType[i])=='string'){
                currentType=currentType.split('|');
                currentTypeLen=currentType[1];
                currentType=currentType[0];
            }
            switch(currentType){
                case "arrayProxy":break;
                case "bool":
                    ctx.elsif(`JS_IsBool(${src})`,(fn)=>{
                        fn.call('JS_ToBool',['ctx',src],{type:'int',name:'js_'+tmpname});
                        fn.declare('bool', name, 'js_'+tmpname);
                    });
                    break;
                case "char":
                    ctx.elsif(`JS_IsString(${src})`,(fn)=>{
                        fn.call('JS_ToCString',['ctx', src],{type:"char *",name:'js_' + tmpname});
                        fn.declare("char", name, `js_${tmpname}[0](char)`);
                        fn.call('JS_FreeCString', ['ctx', 'js_' + tmpname]);
                    });
                    break;
                case "int8":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare('int32_t',`long_${tmpname}`);
                        fn.call('JS_ToInt32',['ctx', `long_${tmpname}`, src]);
                        fn.declare(type, name, `long_${tmpname}(${type})`);
                    });
                    break;
                case "uint8":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare('uint32_t',`long_${tmpname}`);
                        fn.call('JS_ToUint32',['ctx', `long_${tmpname}`, src]);
                        fn.declare(type, name, `long_${tmpname}(${type})`);
                    });
                    break;
                case "int32":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare(type, name);
                        fn.call('JS_ToInt32',['ctx',`${name}`,src]);
                    });
                    break;
                case "uint32":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare(type,name);
                        fn.call('JS_ToUint32',['ctx', `${name}`, src]);
                    });
                    break;
                case "int64":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare(type, name);
                        fn.call('JS_ToInt64',['ctx', `${name}`, src]);
                    });
                    break;
                case "uint64":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare('uint64_t',` long_${tmpname}`);
                        fn.call('JS_ToInt64',['ctx', `long_${tmpname}`, src]);
                        fn.declare(type, name, `long_${tmpname}(${type})`);
                    });
                    break;
                case "float":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare("double","double_" + tmpname);
                        fn.call('JS_ToFloat64',['ctx', `double_${tmpname}`, src]);
                        fn.declare(type, name, `double_${tmpname}(${type})`);
                    });
                    break;
                case "double":
                    ctx.elsif(`JS_IsNumber(${src})`,(fn)=>{
                        fn.declare(type,name);
                        fn.call('JS_ToFloat64',['ctx',`${name}`,src],{type:'int',name:'err_'+tmpname});
                    });
                    break;
                case "null":
                    ctx.elsif(`JS_IsNull(${src}) || JS_IsUndefined(${src})`,(fn)=>{
                        fn.declare(type,name,'NULL');
                    });
                    break;
                case "string":
                    ctx.elsif(`JS_IsString(${src})`,(fn)=>{
                        if(flags.noContextAlloc){
                            //The static memory version
                            let size_name=fn.allocVariable(`size_${name}`);
                            let tmp_name=fn.allocVariable('js_'+name);
                            fn.declare('int64_t',size_name);
                            fn.call('JS_ToCStringLen',['ctx', size_name,src],{name:tmp_name,type:"char *"});
                            let tmp2_name=fn.allocVariable('js2_'+name);
                            fn.call(jsc.malloc,['ctx', `${size_name}+1`],{type:'char *',name:tmp2_name});
                            fn.call(`memcpy`,[tmp2_name,tmp_name,size_name]);
                            fn.assign(`${tmp2_name}[${size_name}]`,0);
                            fn.assign(name,tmp2_name);
                            fn.call('JS_FreeCString',['ctx',tmp_name]);
                        }else{
                            fn.call('JS_ToCStringLen',['ctx', 'NULL',src],{name:name,type:"char *"});
                            fn.call('memoryStore',['JS_FreeCString', name]);
                            flags.dynamicAlloc=true;
                        }
                    });
                    break;
                case "arr":
                    //There is an issue with known sizes, if size must be 2 but it can be 2*16 (simpletype)
                    //Then 2 separate checks must happen:
                    //1) is it 2 withour simpletype
                    //2) is it 32 with only simpletype

                    //Check what subchecks have to be done
                    //is array of objects? if so, do some re-packaging
                    let checks=[];
                    for(let nextType of nextTypes){
                        let newjsType=currentPath.jsType.slice(1).map((a,j)=>{if(j==0)return [nextType];return a;});
                        if(typeof(nextType)=='object' && nextType.type=='type' && nextType.subtype=='struct' && nextType.props.bound_name){
                            checks.push({type:'obj',len:currentTypeLen,mod:1,ctype:nextType.name,jsType:newjsType,convert:false});
                            if(nextType.props.isSympleType){
                                newjsType=currentPath.jsType.slice(1).map((a,j)=>{if(j==0)return ctojsType(variables,nextType.fields[0].type);return a;});
                                if(currentTypeLen!='*'){
                                    if(isNaN(currentTypeLen)){
                                        currentTypeLen=`${currentTypeLen}*${nextType.fields.length}`;
                                    }else{
                                        currentTypeLen=currentTypeLen*nextType.fields.length;
                                    }
                                }
                                checks.push({type:'arr',len:currentTypeLen,mod:nextType.fields.length,ctype:nextType.fields[0].type,jsType:newjsType,convert:nextType});
                            }
                        }else{
                            checks.push({type:'arr',len:currentTypeLen,mod:1,ctype:subtype,jsType:newjsType,convert:false});
                        }
                    }
                    let checks_map={};
                    for(let check of checks){
                        let key='arr|'+check.len;
                        if(checks_map[key]==undefined){
                            checks_map[key]=[check];
                        }else{
                            checks_map[key].push(check);
                        }
                    }
                    for(let checkKey in checks_map){
                        let validTypes=checks_map[checkKey];
                        ctx.elsif(jscheck(checkKey,nextTypes,src),(fn)=>{
                            let size_name=fn.allocVariable(`size_${name}`);
                            if(currentTypeLen=='*'){
                                fn.declare('int64_t',size_name);
                                fn.if(`JS_GetLength(ctx,${src},${size_name})==-1`,(fn2)=>{
                                    flags.onError(fn2);
                                });
                            }else{
                                fn.declare('int64_t',size_name,currentTypeLen);
                            }


                            let nextType;
                            let subsrc=fn.allocVariable(`${src}0`);
                            function bindArr(fn2){
                                if(nextType.len!='*'){//"arr|2" - with known size
                                    if(nextType.len>1){
                                        fn2.declare('int64_t',size_name,nextType.len);
                                    }
                                }else{
                                    fn2.if(`${size_name}==0`,(fn3)=>{
                                        if(allowNull){
                                            flags.onEmpty(fn3);
                                        }else{
                                            fn3.call('JS_ThrowTypeError',['ctx',`"Received empty array"`]);
                                            flags.onError(fn3);
                                        }
                                    });
                                }
                                if(nextType.mod!=1){//"arr%2" - must be divisible by n
                                    fn2.declare('int64_t',size_name,`${size_name}-${size_name}%${nextType.mod}`);
                                }
                                let foreach=(fn3,iter,name2)=>{
                                    name2=name2||name;
                                    let subname=`${name2}[${iter}]`;
                                    if(iter==undefined){
                                        subname=name2;
                                        iter=0;
                                    }
                                    fn3.call('JS_GetPropertyUint32',['ctx',src,iter],{type:'JSValue',name:subsrc});
                                    fn3.call('JS_FreeValue',['ctx',subsrc]);
                                    if(nextType.jsType[0][0]=='arrayProxy'){
                                        nextType.jsType[0].push('arr|*');
                                    }
                                    paths.push({ctx:fn3,src:subsrc,jsType:nextType.jsType,name:subname,type:nextType.ctype});
                                }
                                if(nextType.type=='obj' && nextType.len==1 ){
                                    foreach(fn2,undefined);
                                }else
                                if(nextType.len!=1){
                                    fn2.call(jsc.malloc,['ctx',`${size_name} * sizeof(${nextType.ctype})`],{type,name});
                                    if(!nextType.convert){
                                        fn2.for(0,size_name,foreach);
                                    }else{
                                        fn2.for(0,size_name,(fn3,iter)=>{
                                            let tmp_obj=fn3.allocVariable('tmp_obj');
                                            fn3.declare(`${nextType.ctype} *`,tmp_obj,name);//cast
                                            fn3.for(0,nextType.convert.fields.length,(fn4,iter2)=>{
                                                foreach(fn4,`${iter}+${iter2}`,tmp_obj);
                                            });
                                            fn3.add('int',iter,nextType.convert.fields.length-1);
                                        });
                                    }
                                }else{
                                    fn2.call(jsc.malloc,['ctx',`sizeof(${nextType.ctype})`],{type,name});
                                    foreach(fn2,0);
                                }
                                fn2.call('memoryStore',[jsc.free, name]);
                                flags.dynamicAlloc=true;
                            }
                            if(validTypes.length>1){
                                fn.call('JS_GetPropertyUint32',['ctx',src,0],{type:'JSValue',name:subsrc});
                                fn.call('JS_FreeValue',['ctx',subsrc]);
                                fn.if([]);
                                for(let i=0;i<validTypes.length;i++){
                                    nextType=validTypes[i];
                                    const check=jscheck(nextType.jsType[0],nextType.jsType[1],subsrc);
                                    if(check!=false){
                                        fn.elsif(check,bindArr);
                                    }
                                }
                                fn.elsif('',(fn2)=>{
                                    fn2.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${toptype}"`]);
                                    flags.onError(fn2);
                                });
                            }else{
                                nextType=validTypes[0];
                                bindArr(fn);
                            }
                        });
                    }


                    break;
                case "ptr":
                    //A noop, only advance and add (array key -1 for struct)
                    //overrodeElse=true;
                    ctx.elsif(jscheck(nextTypes,currentPath.jsType[2],src),(fn)=>{
                        if(currentTypeLen==1)fn.assign('isptr[0]',true);
                        let requiresMalloc=false;
                        for(let i=0;i<currentPath.jsType[1].length;i++){
                            let newjsType=currentPath.jsType.slice(1).map((a,j)=>{if(j==0)return [a[i]];return a;});
                            let nextType=currentPath.jsType[1][i];
                            if(typeof(nextType)=='object' && nextType.type=='type' && nextType.subtype=='struct' && nextType.props.bound_name){
                                paths.push({ctx:fn,src:src,jsType:newjsType,name:name,type:subtype});
                            }else{
                                requiresMalloc=true;
                                let subname=`${name}[0]`;
                                paths.push({ctx:fn,src:src,jsType:newjsType,name:subname,type:subtype});
                            }
                        }
                        if(requiresMalloc){
                            fn.call(jsc.malloc,['ctx',`sizeof(${subtype})`],{type,name});//if we are on top, malloc can be skipped
                            fn.call('memoryStore',[jsc.free, name]);
                            flags.dynamicAlloc=true;
                        }
                    });
                    break;
                case "buffer":
                    ctx.elsif(`JS_IsArrayBuffer(${src})`,(fn)=>{
                        let size_name=fn.allocVariable(`size_${name}`);
                        let tmp_name=fn.allocVariable('js_'+name);
                        fn.declare('int64_t',size_name);

                        if(flags.noContextAlloc){
                            fn.call('JS_GetArrayBuffer',['ctx', size_name, src],{type,name:tmp_name});
                            fn.call(jsc.malloc,['ctx', size_name],{type,name});
                            fn.call(`memcpy`,[name,tmp_name,size_name]);
                            fn.call('memoryStore',[jsc.free, name]);
                            flags.dynamicAlloc=true;
                        }else{
                            fn.call('JS_GetArrayBuffer',['ctx',size_name,src],{type:`${subtype} *`,name});
                        }
                    });
                    break;
                case "typedbuffer":
                    //typedClassIds.map(clas=>`JS_GetClassID(${src}) == ${clas}`).join(' || ')
                    ctx.elsif(jscheck('typedbuffer',nextTypes,src),(fn)=>{
                        let offset_name=fn.allocVariable(`offset_${name}`);
                        let size_name=fn.allocVariable(`size_${name}`);
                        let da_name=fn.allocVariable(`da_${name}`);
                        let tmp_name=fn.allocVariable('js_'+name);
                        fn.declare('size_t','offset_'+tmpname);
                        fn.declare('size_t',size_name);
                        fn.call('JS_GetTypedArrayBuffer',['ctx',src,offset_name,size_name,'NULL'],{type:'JSValue',name:da_name});

                        if(flags.noContextAlloc){
                            fn.call('JS_GetArrayBuffer',['ctx', size_name, da_name],{type,name:tmp_name});
                            fn.call(jsc.malloc,['ctx', size_name],{type,name});
                            fn.call(`memcpy`,[name,tmp_name,size_name]);
                            fn.call('memoryStore',[jsc.free, name]);
                            flags.dynamicAlloc=true;
                        }else{
                            fn.call('JS_GetArrayBuffer',['ctx',size_name,src],{type:`${subtype} *`,name});
                        }
                        fn.add(subtype,name,offset_name);
                        fn.sub('size_t',size_name,offset_name);
                        fn.call('JS_FreeValuePtr',['ctx',da_name]);
                    });
                    break;
                default:{
                    if(typeof(currentType)=='object'){
                        //check if struct or function
                        if(typeof(currentType)=='object' && currentType.type=='type'){
                            if( currentType.subtype=='struct' && currentType.props.bound_name ){
                                ctx.elsif(`JS_GetClassID(${src}) == ${currentType.props.bound_name}`,(fn)=>{
                                    let class_id=currentType.props.bound_name;
                                    if(class_id.startsWith('js_')&&class_id!='js_ArrayProxy_class_id'){
                                        let tmpshadow=fn.allocVariable('tmpshadow');
                                        fn.call('JS_GetOpaque',[src,class_id],{type:'opaqueShadow *',name:tmpshadow});
                                        fn.declare(type,name,`${tmpshadow}[0].ptr`);
                                    }else{
                                        fn.call('JS_GetOpaque',[src,class_id],{type:type,name});
                                    }
                                });
                            }else
                            if(currentType.subtype=='function'){
                                ctx.elsif(`JS_IsFunction(ctx,${src})`,(fn)=>{
                                    fn.declare(type,name,src);
                                });
                            }
                        }
                    }else{
                        throw new Error(`unsupported jsType ${currentType}`);
                    }
                    break;
                }
            }
        }
        if(!overrodeElse){
            ctx.elsif('',(fn)=>{
                fn.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${toptype}"`]);
                flags.onError(fn);
            });
        }
        if(is_arrayProxy!=undefined){
            ctx.if(is_arrayProxy,(ctx)=>{
                ctx.call('JS_FreeValue',['ctx',src]);
            });
        }
    }
}
export function isobject(name,variables){
    let variable=variables[name];
    if(variable==undefined)return false;
    variable=getaliasedVariable(variables[name]);
    return typeof(variable)=='object' && variable.type=='type';
}
export function cToJs(topctx,ctype,name,src,flags={},variables){
    if(variables==undefined){
        variables=topctx.getVariables();
    }
    let ctx=topctx;
    if(ctype.endsWith(']'))debugger;
    let capture=[];
    simpleregex(ctype,['br*',' *','br*',azZ0+' '],ctype.length-1,capture);
    let arrsize=capture[0].replaceAll(' ','').length;
    let variable;
    let isstring=false;
    if(flags.sizeVars==undefined)flags.sizeVars=[];
    if(capture[1]=='char'&&arrsize>0){
        isstring=true;
        arrsize--;
    }else{
        variable=getaliasedVariable(variables[capture[1]]);
        if(typeof(variable)=='object' && variable.type=='type'){
            if(arrsize>flags.sizeVars.length){
                arrsize--;
            }
        }else{
            variable=undefined;
        }
    }
    if(arrsize>0){
        for(let i=0;i<arrsize;i++){
            let namei=i==0?name:`${name}${i}`;
            let namei1=`${name}${i+1}`;
            if(i!=0||ctx.getVariables()[name]==undefined){
                ctx.call('JS_NewArray',['ctx'],{type:'JSValue',name:namei});
            }
            let sizeVar=flags.sizeVars[i];
            if(sizeVar==undefined){
                throw new Error(`sizeVars are now required, at: ${src} depth ${i}`);
            }
            sizeVar=resolveSizeVar(ctx,sizeVar,ctx.allocVariable('size'+i));
            ctx.for('0',sizeVar,(fn,iter)=>{
                if(variable!=undefined && i==arrsize-1 && flags.anchor){
                    fn.declare(ctype,`src${i}`,`(${src}+${iter})`);
                }else{
                    ctype=getsubtype(ctype);
                    fn.declare(ctype,`src${i}`,`${src}[${iter}]`);
                }
                src=`src${i}`;
                let innerctx;
                fn.section((fn2)=>{innerctx=fn2});
                fn.call('JS_DefinePropertyValueUint32',['ctx',namei,iter,namei1,'JS_PROP_C_W_E']);
                ctx=innerctx;
            });
        }
        name=`${name}${arrsize}`;
    }
    if(isstring){
        ctx.call('JS_NewString',['ctx',src],{type:'JSValue',name});
        return;
    }
    if(variable!=undefined){
        if(flags.anchor){
            //TODO: where is case with JS_NULL (extern data but no anchor) used?
            ctx.call('JS_DupValue',['ctx',flags.anchor]);
            ctx.call('create_shadow_with_external',[src,flags.anchor],{type:'opaqueShadow *',name:"ptr_"+name});
        }else{
            ctx.call('create_shadow_with_data',[`sizeof(${ctype})`],{type:`opaqueShadow *`,name:'ptr_'+name});
            ctx.declare(`${ctype} *`,'ptr2_'+name,`(ptr_${name}+1)(${ctype} *)`);
            ctx.assign(`ptr2_${name}[0]`,src);
        }
        ctx.call('JS_NewObjectClass',['ctx', variable.props.bound_name],{type:"JSValue", name});
        ctx.call("JS_SetOpaque", [name, "ptr_"+name]);
        return;
    }
    switch(ctype){
        case "bool":return ctx.call('JS_NewBool',['ctx',src],{type:'JSValue',name});
        case "char":return ctx.call('JS_NewStringLen',['ctx',`${src}`,1],{type:'JSValue',name});
        case "int8_t":
        case "int":
        case "signed":
        case "signed int":
        case "short":
        case "short int":
        case "signed short":
        case "signed short int":
        case "signed char"://too small, needs to be cast
            return ctx.call('JS_NewInt32',['ctx',`${src}(long)`],{type:'JSValue',name});
        case "int32_t":
        case "long":
        case "long int":
        case "signed long":
        case "signed long int":
            return ctx.call('JS_NewInt32',['ctx',src],{type:'JSValue',name});
        case "uint8_t":
        case "unsigned char":
        case "unsigned short":
        case "unsigned short int":
        case "unsigned":
        case "unsigned int"://too small, needs to be cast
            return ctx.call('JS_NewUint32',['ctx',`${src}(unsigned long)`],{type:'JSValue',name});
        case "uint32_t":
        case "unsigned long":
        case "unsigned long int":
            return ctx.call('JS_NewUint32',['ctx',src],{type:'JSValue',name});
        case "int64_t":
        case "long long":
        case "long long int":
        case "signed long long":
        case "signed long long int":
            return ctx.call('JS_NewInt64',['ctx',src],{type:'JSValue',name});
        case "uint64_t":
        case "unsigned long long":
        case "unsigned long long int":
            return ctx.call('JS_NewInt64',['ctx',`${src}(long long)`],{type:'JSValue',name});
        case "float":
        case "long double":
            return ctx.call('JS_NewFloat64',['ctx',`${src}(double)`],{type:'JSValue',name});
        case "double":
            return ctx.call('JS_NewFloat64',['ctx',src],{type:'JSValue',name});
        //va_list can not be generic
        //case "va_list"
    }
    throw new Error("Requred type is not found: " + ctype);

}
export function jsToCallback(topctx,topjsType,topname,src,mode,flags={}){
    let toptype=`${topjsType.name} *`;
    let allocName=topjsType.name;
    const threaded = flags.threaded==true;
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
    switch(mode){
        case "set":{
            topctx.declare('trampolineContext',`ctx_${topname}`);
            topctx.assign(`ctx_${topname}.ctx`,'ctx');
            topctx.assign(`ctx_${topname}.func_obj`,src);//store as whole, but compare as ${src}.u.ptr (in threaded, use js_isequal)
            topctx.if([`JS_IsUndefined(${src}) || JS_IsNull(${src})`,`JS_IsFunction(ctx,${src})==1`,''],(ctx)=>{
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
                ctx.declare('trampolineContext *',`${allocName}_arr`,`ctx_${topname}`);
            },(ctx)=>{
                ctx.return(flags.altReturn||"JS_EXCEPTION");
            });
            if(threaded){
                topctx.call('js_copyWorker',['ctx',`${allocName}_ctx`],{name:'ctx_processor.thread_id',type:'JSValue'});
            }
            //prepare for call
            topctx.declare('void *',topname);
            topctx.if([`${allocName}_arr == NULL`,''],(ctx)=>{
                ctx.declare('void *',topname,'NULL');
            },(ctx)=>{
                ctx.declare('void *',topname,topjsType.callback);
            });
            topctx.call('JS_DupValue',['ctx',src]);
            break;
        }
        case "attach":{
            topctx.declare('trampolineContext',`ctx_${topname}`);
            topctx.assign(`ctx_${topname}.ctx`,'ctx');
            topctx.assign(`ctx_${topname}.func_obj`,src);//store as whole, but compare as ${src}.u.ptr (in threaded, use js_isequal)
            topctx.declare('void *',topname,topjsType.callback);
            let fi;
            if(threaded){
                //threaded does not support direct calls yet
                topctx.if([`argc==0 || (JS_IsString(${src}) == 0 && JS_IsNumber(${src}) == 0)`],(ctx)=>{
                    ctx.call('JS_ThrowTypeError',['ctx',`"${src} must be string or number"`]);
                    ctx.return(flags.altReturn||"JS_EXCEPTION");
                });
            }else{
                topctx.if([`JS_IsFunction(ctx,${src})==0`],(ctx)=>{
                    ctx.call('JS_ThrowTypeError',['ctx',`"${src} must be a function"`]);
                    ctx.return(flags.altReturn||"JS_EXCEPTION");
                });
            }
            //Attaching functions is infrequent, no realloc optimization
            topctx.if([`${allocName}_size==0`,''],(ctx)=>{
                if(threaded)addrt(ctx);
                ctx.call('js_malloc',['ctx',`sizeof(trampolineContext)`],{type:'trampolineContext *',name:`${allocName}_arr`});
            },(ctx)=>{
                ctx.call('js_realloc',['ctx',`${allocName}_arr`,`sizeof(trampolineContext) * ${allocName}_size`],{type:'trampolineContext *',name:`${allocName}_arr`});
            });
            topctx.call('JS_DupValue',['ctx',src]);
            if(threaded){
                this.cgen.call('js_copyWorker',['ctx',`${allocName}_ctx`],{name:'ctx_processor.thread_id'});
            }
            topctx.declare('trampolineContext *',`${allocName}_arr[${allocName}_size]`,`ctx_${topname}`);
            topctx.add('size_t',`${allocName}_size`,1);
            topctx.if(`${allocName}_size>1`,(ctx)=>{
                ctx.return(flags.altReturn||"JS_UNDEFINED");//Dont call the real attach
            });
            break;
        }
        case "deattach":
        case "detach":{
            //find in ffiAllocName the pointer and remove it
            topctx.declare('int',`${topname}_pos`);
            topctx.declare('void *',topname,topjsType.callback);
            let fi;
            topctx.for(0, `${allocName}_size`, (ctx,iter)=>{
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
            topctx.if([`${allocName}_size!=0`],(ctx)=>{
                ctx.return(flags.altReturn||"JS_UNDEFINED");
            });
            if(threaded)freert(this.cgen);
            break;
        }
        default:{
            throw new Error("Cannot convert into parameter type: " + toptype.name);
        }
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
    jsGet(type,name){

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
                variable=getaliasedVariable(variable);
                if(variable.props.bound_name==undefined){
                    throw new Error("struct must have been bound to exist as opaque");
                }
                //class by pointer
                this.jsStructToOpq(subtype, name, src, variable.props.bound_name, flags.supressDeclaration);
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
                    variable=getaliasedVariable(variable);
                    if(variable.props.bound_name==undefined){
                        throw new Error("struct must have been bound to exist as opaque");
                    }
                    this.jsStructToOpq(type, name, src, variable.props.bound_name);
                }
            }
        }
    }
    jsStructToOpq(structType, jsVar, srcVar, classId, supressDeclaration=false) {
        //TODO: just check if already defined
        if(!supressDeclaration){
            this.cgen.call('js_malloc',['ctx', `sizeof(${structType})`],{type:`${structType} *`,name:'ptr_'+jsVar});
            this.cgen.assign(`ptr_${jsVar}[0]`,srcVar);
            debugger;
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
                    ctx.call('js_free',['ctx',name]);
                });
            }
            let tmpname=name.replace(/[^\w]/g,'');
            //metacheck if could be arrayBuffer (is a simple int* or int{} )
            let typedClassIds=getTypedArray(getsubtype(type));
            if(typedClassIds!==false){
                ctx.elsif('',(ctx)=>{
                    ctx.call('JS_GetClassID',[src],{type:'JSClassID',name:'classid_'+tmpname});
                    ctx.if('classid_'+tmpname+'=='+typedClassIds.join(' && classid_'+tmpname+'=='),ctx=>{
                        let variables=ctx.getVariables();
                        if(variables[`da_${tmpname}`]==undefined)debugger;
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
            let mainstruct=structName;
            if(classId.startsWith('js_')&&classId!='js_ArrayProxy_class_id'){
                mainstruct='opaqueShadow';
            }
            ctx.call('JS_GetOpaque',['val',classId],{type:`${mainstruct} *`,name:'shadow'});
            if (onFinalize){
                onFinalize(ctx, "shadow[0].ptr");
            }
            ctx.call('deallocate_shadow',['rt',"shadow"]);//TODO: test if runtime dealloc is correct
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
}