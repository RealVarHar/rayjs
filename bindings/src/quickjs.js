import { CodeWriter, CodeGenerator } from "./generation.js"
import * as fs from "./fs.js";
import { source_parser } from "./source_parser.js";
export class QuickJsHeader {
    parent;root;name='';
    structLookup = {};
    callbackLookup = {};
    body;
    includeGen;
    structGen;structArgs={};
    functionGen;functionArgs={};
    callbackGen;callbackArgs={};
    moduleFunctionList;
    moduleInit;
    moduleEntry;
    constructor(parent,name='',structLookup,callbackLookup) {
        if(parent!==undefined){
            this.parent=parent;
            this.structLookup = structLookup;
            this.callbackLookup = callbackLookup;
        }
        this.name = name;
        if(structLookup!==undefined)this.structLookup = structLookup;
        if(callbackLookup!==undefined)this.callbackLookup = callbackLookup;
        this.root = new QuickJsGenerator(this);
        this.body = this.root.header("JS_" + this.name + "_GUARD");
        this.includeGen = this.body.child();
        //TODO: move includes upstream so generation could be split to modules
        this.includeGen.include("stdio.h");
        this.includeGen.include("stdlib.h");
        this.includeGen.include("string.h");
        this.includeGen.breakLine();
        this.includeGen.include("quickjs.h");
        this.body.breakLine();
        this.body.line("#ifndef countof");
        this.body.line("#define countof(x) (sizeof(x) / sizeof((x)[0]))");
        this.body.line("#endif");
        this.body.line("#ifndef dynamidMemoryAlloc");
        this.body.line("#define dynamidMemoryAlloc");
        this.includeText(this.body);
        this.body.line("#endif");
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
    }
    includeText(body){
        //define an allocation linked list
        //define struct
        body.line('typedef struct memoryNode{');
        body.indent();
        body.declare('int', 'length');
        body.declare('void *','pointers[6]');
        body.declare('struct memoryNode *','next');
        body.unindent();
        body.line('} memoryNode;');
        //define store function
        body.line(`memoryNode* memoryStore(memoryNode *current, void * clarfunc, void * memoryptr) {
   // Saves memory fo de-allocation
   if(current->length < 6) {
        current->pointers[current->length] = clarfunc;
        current->pointers[current->length + 1] = memoryptr;
        current->length += 2;
        return current;
   } else {
        // This one is full, write to a new one
        memoryNode *new_node = (memoryNode *)malloc(sizeof(memoryNode));
        new_node->length = 2;
        new_node->pointers[0] = clarfunc;
        new_node->pointers[1] = memoryptr;
        new_node->next = NULL;
        current->next = new_node;
        return new_node;
   }
}`);
        //define clear function
        body.line(`void memoryClear(JSContext * ctx, memoryNode *head) {
    memoryNode * prev_node;
    while (head != NULL) {
        for (int i = 0; i < head->length; i += 2) {
            void (*free_func) (JSContext *,void *) = head->pointers[i];
            void * ptr_to_free = head->pointers[i + 1];
            free_func(ctx, ptr_to_free);
        }
        prev_node = head;
        head = head->next;
        free(prev_node);
    }
}`);
        //define a proxy for FreeValue
        body.line(`void JS_FreeValuePtr(JSContext *ctx, JSValue * v){
    JS_FreeValue(ctx,*v);
}`);
        //Define a struct to store in a trampoline
        //TODO: check if it may be sane to keep one global JSContext instead
        body.line(`typedef struct trampolineContext {
    JSContext * ctx;
    JSValue func_obj;
} trampolineContext;`);
        // quickjs.c has the typename enum we need
        let quickjsSource=new source_parser(fs.readFileSync("thirdparty/quickjs/quickjs.c", "utf8"));
        let classEnum=quickjsSource.enums.find(a=>a.name===''&&a.values.some(b=>b.name==='JS_CLASS_OBJECT'));
        let classEnumLine="enum {\n";
        for(let value of classEnum.values){
            classEnumLine+=value.name+' = '+value.value+',';
        }
        classEnumLine+="\n};";
        body.line(classEnumLine);
        body.line(`char * asnprintf(JSContext * ctx, char * buffer, size_t * maxsize, const char * format, ...){
    va_list args;
    va_start(args, format);
    int len=vsnprintf(buffer,*maxsize,format,args);
    if(len>*maxsize){
        len++;
        buffer=js_realloc(ctx,buffer,len * sizeof(char));
        memset(buffer+*maxsize,0,len-*maxsize);
        maxsize[0]=len;
        len=vsnprintf(buffer,len,format,args);
    }
    va_end(args);
    return buffer;
};`);
    }
    writeTo(filename) {
        const writer = new CodeWriter();
        writer.writeGenerator(this.root);
        fs.writeFileSync(filename, writer.toString());
    }
}
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
    jsToC(type, name, src,flags={},depth=0,errorCleanupFn=((ctx)=>{})) {
        //needs to return flags
        //TODO: cache functions to limit js_raylib_core.h size
        function getArray(ctx,type,name,src,srclen,overrideElse=false){
            //define
            if(!flags.supressDeclaration){
                ctx.declare(type,name);
            }
            let tmpname=name.replace(/[^\w]/g,'');
            let ctxif='if';

            let typedClassIds=ctx.getTypedArray(getsubtype(type));
            let addBuffer=!getsubtype(type).includes('*');
            let addTypedArray=typedClassIds!==false;
            let topDefineJs=!flags.dynamicAlloc && (addBuffer||addTypedArray);
            if( topDefineJs ){
                ctx.declare('JSValue',`da_${tmpname}`);//for de-allocation
            }

            //Check if NULL
            if(flags.allowNull){
                ctx[ctxif](`JS_IsNull(${src}) || JS_IsUndefined(${src})`).statement(`${name} = NULL`);
                ctxif='elsif';
            }

            //TODO: (out of spec) allow bidirectional auto casting of vec2,vec3,vec4

            //Check if Array
            let arr;
            if( !['void','char'].includes(getsubtype(type)) ) {//Dont allow dumb usecases: Array of direct opaque data, array of char
                //TODO: allow dynamic binding of array properties
                arr = ctx[ctxif](`JS_IsArray(ctx,${src}) == 1`);
                let size=srclen;
                if (srclen == undefined) {
                    size="size_" + tmpname;
                    arr.declare("int64_t","size_" + tmpname);
                    let fi = arr.if(`JS_GetLength(ctx,${src},&size_${tmpname})==-1`);
                    errorCleanupFn(fi);
                    fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                }
                let subtype=getsubtype(type);
                arr.declare(type,name,false,`(${type})js_malloc(ctx, ${size} * sizeof(${subtype}))`,true);
                if (flags.dynamicAlloc) {
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, ${name})`);
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
            if(getsubtype(type)=='char') {
                arr = ctx[ctxif](`JS_IsString(${src}) == 1`);
                arr.statement(`${name} = (${type})JS_ToCString(ctx, ${src})`);
                if(flags.dynamicAlloc){
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, ${name})`);
                }
                ctxif='elsif';
            }

            //Check if Buffer
            if(addBuffer) {//check for arrayBuffer only if [] but not [][]
                arr = ctx[ctxif](`JS_IsArrayBuffer(${src}) == 1`);
                arr.declare('JSValue',`da_${tmpname}`,false,`JS_DupValue(ctx,${src})`,!flags.dynamicAlloc);
                if(flags.dynamicAlloc){
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_${tmpname})`);
                }
                arr.declare("size_t","size_" + tmpname);
                arr.declare(type,name, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, da_${tmpname})`,true);
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
                if(flags.dynamicAlloc){
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_${tmpname})`);
                }
                //TODO: respect buffer offset
                arr.declare(type, name, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, da_${tmpname})`,true);
                ctxif='elsif';
            }
            const fi=ctx.else();
            if(overrideElse){
                return fi;
            }
            errorCleanupFn(fi);
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
            f.jsToC(type,`${name}[${iter}]`,`${src}[${iter}${plusstr}]`,ids,{supressDeclaration:true,dynamicAlloc:true,allowNull:flags.allowNull,altReturn:flags.altReturn},depth+1);
            //Arrays
        }else if(type.endsWith(']')){
            const stpos=type.indexOf('[');
            let len=type.substring(stpos+1,type.length-1).trim();
            getArray(this,getsubtype(type)+' *',name,src,len);
        }else if(type.endsWith('*')){
            getArray(this,type,name,src);
        }else if(type.endsWith('&')){
            let subtype=getsubtype(type);

            const classId = this.root.structLookup[subtype];
            //functions must be a pointer, dont check for them
            if (classId){
                this.declare(subtype+' *', name, false, `(${subtype} *)JS_GetOpaque(${src}, ${classId})`,flags.supressDeclaration);
                const fi=this.if(`${name} == NULL`);
                errorCleanupFn(fi);
                fi.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${subtype}"`]);
                fi.returnExp(flags.altReturn||"JS_EXCEPTION");
            }else{
                //A pointer may be declared as [el]
                let els;
                if(subtype.endsWith('*')){
                    getArray(this,subtype,name,src,undefined);
                }else{
                    els = getArray(this,subtype+' *',name,src,1,true);
                    //Or direct
                    els.jsToC(subtype,'js_'+tmpname,src,flags,depth,errorCleanupFn);
                    els.declare(subtype+' *', name,false,'&js_'+tmpname,true);
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
                        allocName=allocName+`_${tmpname}`;
                        this.declare('trampolineContext',`ctx_${tmpname}`);
                        this.statement(`ctx_${tmpname}.ctx = ctx`);
                        this.statement(`ctx_${tmpname}.func_obj = ${src}`);//store as whole, but compare as ${src}.u.ptr
                        if(attachmode==='set'){
                            this.root.addCallback(callbackId,allocName,false);
                            let fi = this.if(`JS_IsUndefined(${src}) || JS_IsNull(${src})`);
                                fi.declare('trampolineContext *',`${allocName}_arr`,false,`NULL`,true);
                            fi = this.elsif(`JS_IsFunction(ctx,${src})==1`);
                                fi.declare('trampolineContext *',`${allocName}_arr`,false,`&ctx_${tmpname}`,true);
                            fi = this.else();
                                fi.returnExp(flags.altReturn||"JS_EXCEPTION");
                            if(!flags.supressDeclaration) this.declare('void *',name,false);
                            fi = this.if(`${allocName}_arr == NULL`);
                                fi.declare('void *',name,false,'NULL',true);
                            fi = this.else();
                                fi.declare('void *',name,false,allocName+'_c',true);

                        }else
                        if(attachmode==='attach'){
                            this.root.addCallback(callbackId,allocName,true);
                            this.declare('void *',name,false,allocName+'_c',flags.supressDeclaration);
                            let fi = this.if(`JS_IsFunction(ctx,${src})==0`);
                                fi.returnExp(flags.altReturn||"JS_EXCEPTION");

                            fi.declare('void *',name,false,allocName+'_c',flags.supressDeclaration);

                            //Attaching functions is infrequent, no realloc optimization
                            fi=this.if(`${allocName}_size==0`);
                                fi.call('js_malloc',['ctx',`sizeof(void *) * 3`],{name:`${allocName}_arr`});
                                fi.declare('trampolineContext *',`${allocName}_arr[${allocName}_size]`,false,`ctx_${tmpname}`,true);
                                fi.statement(`${allocName}_size++`);
                            fi=this.else();
                                fi.call('js_realloc',['ctx',`${allocName}_arr`,`sizeof(void *) * ${allocName}_size`],{name:`${allocName}_arr`});
                                fi.declare('trampolineContext *',`${allocName}_arr[${allocName}_size]`,false,`ctx_${tmpname}`,true);
                                fi.statement(`${allocName}_size++`);
                                fi.returnExp(flags.altReturn||"JS_UNDEFINED");//Dont call the real attach
                        }else if(attachmode==='detach'){
                            //find in ffiAllocName the pointer and remove it
                            this.declare('int',`${tmpname}_pos`);
                            let iter='i'+depth;
                            this.declare('void *',name,false,allocName+'_c',flags.supressDeclaration);
                            this.declare('void *',`${tmpname}_ptr`,false,`${src}.u.ptr`);
                            let fi;
                            let fo = this.for(0, `${allocName}_size`, iter,'++');
                                fi = fo.if(`${allocName}_arr[${iter}].func_obj.u.ptr == ${tmpname}_ptr`);
                                    let fi2 = fi.for(undefined, `${allocName}_size-1`, iter,'++');
                                        fi2.statement(`${allocName}_arr[${iter}]=${allocName}_arr[${iter}+1]`);
                                    fi.statement(`${allocName}_size--`);
                                    fi.call('js_realloc',['ctx',`${allocName}_arr`,`sizeof(void *) * ${allocName}_size`],{name:`${allocName}_arr`});
                                    fi.statement(`break`);
                            fi= this.if(`${allocName}_size!=0`);
                                fi.returnExp(flags.altReturn||"JS_UNDEFINED");
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

            const subtype=getsubtype(type);
            //Check if String
            if(getsubtype(type)=='char') {
                ctx.statement(`${name} = JS_NewString(ctx, ${src})`);
                return;
            }

            //Check if Array
            if(subtype=='void'){
                console.log('At: '+type,name);
                throw new Error('Cannot convert void array type');
                return;
            }
            //Dont allow dumb usecases: Array of direct opaque data, array of char
            let srclen=sizeVars.pop();
            if(srclen==undefined){
                //TODO: remove sizeof() based length
                console.log("WARNING: sizeof length is deprecated, at"+type+name);
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
                if(srclen=='1&'){
                    ctx.cToJs(subtype,'js_'+tmpname,`${src}[0]`,{},depth+1,sizeVars);
                    ctx.statement(`JS_DefinePropertyValueUint32(ctx,${name},0,js_${tmpname},JS_PROP_C_W_E)`);
                    return;
                }else if(srclen=='&'){
                    sizeVars.push('&');
                    ctx.declare("size_t", "size_" + tmpname);
                    ctx.statement(`JS_GetLength(ctx, ${name},&size_${tmpname} )`);
                    child=ctx.for('0', "size_" + tmpname,'i'+depth);
                }else{
                    ctx.declare('JSValue', name, false, `JS_NewArray(ctx)`,true);
                    child=ctx.for('0', srclen,'i'+depth);
                }
                child.cToJs(subtype,'js_'+tmpname,`${src}[i${depth}]`,flags,depth+1,sizeVars);
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
                this.declare('JSValue', name+'['+len+']');
            }
            sizeVars.push(Number(len));
            setArray(this,type,name,src);
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
                arr = arr.if(`JS_IsArray(ctx,${name}) == 1`);
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
                arr=ctx[ctxif](`JS_IsArray(ctx,${src}) == 1`);
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
    jsFuncDef(jsName, numArgs, cName) {
        this.line(`JS_CFUNC_DEF("${jsName}",${numArgs},${cName}),`);
    }
    jsClassId(id) {
        this.declare("JSClassID", id, true);
        return id;
    }
    jsPropStringDef(key, value) {
        this.line(`JS_PROP_STRING_DEF("${key}","${value}", JS_PROP_CONFIGURABLE),`);
    }
    jsGetSetDef(key, getFunc, setFunc) {
        this.line(`JS_CGETSET_DEF("${key}",${getFunc || "NULL"},${setFunc || "NULL"}),`);
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
    jsStructGetter(structName, classId, field, type, element) {
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }];
        const fun = this.function(`js_${structName}_get_${field}`, "JSValue", args, true);
        fun.declare(structName + "*", "ptr", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
        if (element.overrideRead) {
            element.overrideRead(fun);
        } else {
            if(type.endsWith(']')){
                let type2=type.split('[');
                let amount='['+type2[1];
                type2=type2[0];
                fun.declare(type2, field+amount, false, "ptr->" + field);
            }else{
                fun.declare(type, field, false, "ptr->" + field);
            }
        }
        let sizeVars=element.sizeVars||[];
        fun.cToJs(type, "ret", field,{allowNull:true},0,sizeVars);
        fun.returnExp("ret");
        return fun;
    }
    jsStructSetter(structName, classId, field, type, overrideWrite) {
        //console.log('jsStructSetter',structName, classId, field, type, ids, overrideWrite);
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }, { type: "JSValue", name: "v" }];
        const fun = this.function(`js_${structName}_set_${field}`, "JSValue", args, true);
        fun.declare(structName + "*", "ptr", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
        fun.jsToC(type, "value", "v");
        if (overrideWrite) {
            overrideWrite(fun);
        } else {
            if(type.endsWith('*')){
                fun.if(`ptr->${field}!=NULL`)
                .call('js_free',['ctx',"ptr->" + field]);
            }
            fun.statement("ptr->" + field + " = value");
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