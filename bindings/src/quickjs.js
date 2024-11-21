import { CodeWriter, GenericCodeGenerator } from "./generation.js"
import * as fs from "./fs.js";
const config=JSON.parse(fs.readFileSync('bindings/config/buildFlags.json','utf8'));
export class QuickJsHeader {
    constructor(name) {
        this.name = name;
        this.structLookup = {};
        const root = this.root = new QuickJsGenerator();
        const body = this.body = root.header("JS_" + this.name + "_GUARD");
        const includes = this.includes = body.child();
        includes.include("stdio.h");
        includes.include("stdlib.h");
        includes.include("string.h");
        includes.breakLine();
        includes.include("quickjs.h");
        body.breakLine();
        body.line("#ifndef countof");
        body.line("#define countof(x) (sizeof(x) / sizeof((x)[0]))");
        body.line("#endif");
        body.line("#ifndef dynamidMemoryAlloc");
        body.line("#define dynamidMemoryAlloc");
        this.includeText(body);
        body.line("#endif");
        body.breakLine();
        this.definitions = body.child();
        body.breakLine();
        this.structs = body.child();
        this.functions = body.child();
        this.moduleFunctionList = body.jsFunctionList("js_" + name + "_funcs");
        const moduleInitFunc = body.function("js_" + this.name + "_init", "int", [{ type: "JSContext *", name: "ctx" }, { type: "JSModuleDef *", name: "m" }], true);
        const moduleInit = this.moduleInit = moduleInitFunc.child();
        moduleInit.statement(`JS_SetModuleExportList(ctx, m,${this.moduleFunctionList.getTag("_name")},countof(${this.moduleFunctionList.getTag("_name")}))`);
        moduleInitFunc.returnExp("0");
        const moduleEntryFunc = body.function("js_init_module_" + this.name, "JSModuleDef *", [{ type: "JSContext *", name: "ctx" }, { type: "const char *", name: "module_name" }], false);
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

        //TODO: Should be dynamicly taken from quickjs.c
        body.line(`enum {
    /* classid tag        */    /* union usage   | properties */
    JS_CLASS_OBJECT = 1,        /* must be first */
    JS_CLASS_ARRAY,             /* u.array       | length */
    JS_CLASS_ERROR,
    JS_CLASS_NUMBER,            /* u.object_data */
    JS_CLASS_STRING,            /* u.object_data */
    JS_CLASS_BOOLEAN,           /* u.object_data */
    JS_CLASS_SYMBOL,            /* u.object_data */
    JS_CLASS_ARGUMENTS,         /* u.array       | length */
    JS_CLASS_MAPPED_ARGUMENTS,  /*               | length */
    JS_CLASS_DATE,              /* u.object_data */
    JS_CLASS_MODULE_NS,
    JS_CLASS_C_FUNCTION,        /* u.cfunc */
    JS_CLASS_BYTECODE_FUNCTION, /* u.func */
    JS_CLASS_BOUND_FUNCTION,    /* u.bound_function */
    JS_CLASS_C_FUNCTION_DATA,   /* u.c_function_data_record */
    JS_CLASS_GENERATOR_FUNCTION, /* u.func */
    JS_CLASS_FOR_IN_ITERATOR,   /* u.for_in_iterator */
    JS_CLASS_REGEXP,            /* u.regexp */
    JS_CLASS_ARRAY_BUFFER,      /* u.array_buffer */
    JS_CLASS_SHARED_ARRAY_BUFFER, /* u.array_buffer */
    JS_CLASS_UINT8C_ARRAY,      /* u.array (typed_array) */
    JS_CLASS_INT8_ARRAY,        /* u.array (typed_array) */
    JS_CLASS_UINT8_ARRAY,       /* u.array (typed_array) */
    JS_CLASS_INT16_ARRAY,       /* u.array (typed_array) */
    JS_CLASS_UINT16_ARRAY,      /* u.array (typed_array) */
    JS_CLASS_INT32_ARRAY,       /* u.array (typed_array) */
    JS_CLASS_UINT32_ARRAY,      /* u.array (typed_array) */
    JS_CLASS_BIG_INT64_ARRAY,   /* u.array (typed_array) */
    JS_CLASS_BIG_UINT64_ARRAY,  /* u.array (typed_array) */
    JS_CLASS_FLOAT16_ARRAY,     /* u.array (typed_array) */
    JS_CLASS_FLOAT32_ARRAY,     /* u.array (typed_array) */
    JS_CLASS_FLOAT64_ARRAY,     /* u.array (typed_array) */
    JS_CLASS_DATAVIEW,          /* u.typed_array */
    JS_CLASS_BIG_INT,           /* u.object_data */
    JS_CLASS_MAP,               /* u.map_state */
    JS_CLASS_SET,               /* u.map_state */
    JS_CLASS_WEAKMAP,           /* u.map_state */
    JS_CLASS_WEAKSET,           /* u.map_state */
    JS_CLASS_ITERATOR,
    JS_CLASS_MAP_ITERATOR,      /* u.map_iterator_data */
    JS_CLASS_SET_ITERATOR,      /* u.map_iterator_data */
    JS_CLASS_ARRAY_ITERATOR,    /* u.array_iterator_data */
    JS_CLASS_STRING_ITERATOR,   /* u.array_iterator_data */
    JS_CLASS_REGEXP_STRING_ITERATOR,   /* u.regexp_string_iterator_data */
    JS_CLASS_GENERATOR,         /* u.generator_data */
    JS_CLASS_PROXY,             /* u.proxy_data */
    JS_CLASS_PROMISE,           /* u.promise_data */
    JS_CLASS_PROMISE_RESOLVE_FUNCTION,  /* u.promise_function_data */
    JS_CLASS_PROMISE_REJECT_FUNCTION,   /* u.promise_function_data */
    JS_CLASS_ASYNC_FUNCTION,            /* u.func */
    JS_CLASS_ASYNC_FUNCTION_RESOLVE,    /* u.async_function_data */
    JS_CLASS_ASYNC_FUNCTION_REJECT,     /* u.async_function_data */
    JS_CLASS_ASYNC_FROM_SYNC_ITERATOR,  /* u.async_from_sync_iterator_data */
    JS_CLASS_ASYNC_GENERATOR_FUNCTION,  /* u.func */
    JS_CLASS_ASYNC_GENERATOR,   /* u.async_generator_data */
    JS_CLASS_WEAK_REF,
    JS_CLASS_FINALIZATION_REGISTRY,
    JS_CLASS_CALL_SITE,

    JS_CLASS_INIT_COUNT, /* last entry for predefined classes */
};`);
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
    registerStruct(struct, classId) {
        this.structLookup[struct] = classId;
    }
    writeTo(filename) {
        const writer = new CodeWriter();
        writer.writeGenerator(this.root);
        (0, fs.writeFileSync)(filename, writer.toString());
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
export class GenericQuickJsGenerator extends GenericCodeGenerator {
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
    jsToC(type, name, src, classIds = {},flags={},depth=0,errorCleanupFn=((ctx)=>{})) {
        //needs to return flags
        //TODO: cache functions to limit js_raylib_core.h size
        function getArray(ctx,type,name,src,srclen,overrideElse=false){
            //define
            if(!flags.supressDeclaration){
                ctx.declare(type,name);
            }
            let tmpname=name.replace(/[[\]]/g,'');
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
                    arr.declare("size_t","size_" + tmpname);
                    let fi = arr.if(`JS_GetLength(ctx,${src},&size_${tmpname})==-1`);
                    errorCleanupFn(fi);
                    fi.returnExp("JS_EXCEPTION");
                }
                let subtype=getsubtype(type);
                arr.declare(type,name,false,`(${type})js_malloc(ctx, ${size} * sizeof(${subtype}))`,true);
                if (flags.dynamicAlloc) {
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, ${name})`);
                }
                let iter = 'i' + depth;
                let arrf = arr.for('0', size, iter);//TODO: fastpath if size==1
                arrf.declare('JSValue',`js_${tmpname}`, false, `JS_GetPropertyUint32(ctx,${src},${iter})`);
                arrf.jsToC(subtype, `${name}[${iter}]`, `js_${tmpname}`, classIds, {
                    supressDeclaration: true,
                    dynamicAlloc: true
                }, depth + 1);
                arrf.statement(`JS_FreeValue(ctx, js_${tmpname})`);//There is no reason for us to keep every value out of scope
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
            fi.returnExp("JS_EXCEPTION");
            //return exception
        }
        //normalize type
        type=type.replace('const ','');
        let tmpname=name.replace(/[[\]]/g,'');

        //spread
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
            this.statement(`if(size_${tmpname}>${config.spreadSize})size_${tmpname}=${config.spreadSize}`);
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
            f.jsToC(type,`${name}[${iter}]`,`${src}[${iter}${plusstr}]`,classIds,{supressDeclaration:true,dynamicAlloc:true,allowNull:flags.allowNull},depth+1);
            //Arrays
        }else if(type.endsWith(']')){
            const stpos=type.indexOf('[');
            let len=type.substring(stpos+1,type.length-1).trim();
            getArray(this,getsubtype(type)+' *',name,src,len);
        }else if(type.endsWith('*')){
            getArray(this,type,name,src);
        }else if(type.endsWith('&')){
            let subtype=getsubtype(type);

            const classId = classIds[subtype];
            if (classId){
                if(!flags.supressDeclaration){
                    this.declare(subtype+' *', name);
                }
                this.declare(subtype+' *', name, false, `(${subtype} *)JS_GetOpaque(${src}, ${classId})`,true);
                const fi=this.if(`${name} == NULL`);
                errorCleanupFn(fi);
                fi.call('JS_ThrowTypeError',['ctx',`"${src} does not match type ${subtype}"`]);
                fi.returnExp("JS_EXCEPTION");
            }else{
                //A pointer may be declared as [el]
                let els;
                if(subtype.endsWith('*')){
                    getArray(this,subtype,name,src,undefined);
                }else{
                    els = getArray(this,subtype+' *',name,src,1,true);
                    //Or direct
                    els.jsToC(subtype,'js_'+tmpname,src,classIds,flags,depth,errorCleanupFn);
                    els.declare(subtype+' *', name,false,'&js_'+tmpname,true);
                }
            }
        }else{
            switch (type) {
                case "bool": {
                    this.declare(type, name, false, `JS_ToBool(ctx, ${src})`, flags.supressDeclaration);
                    const fi = this.if(`${name}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not a bool"`]);
                    fi.returnExp("JS_EXCEPTION");
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
                    fi.returnExp("JS_EXCEPTION");
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
                    fi.returnExp("JS_EXCEPTION");
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
                    fi.returnExp("JS_EXCEPTION");
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
                    fi.returnExp("JS_EXCEPTION");
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
                    fi.returnExp("JS_EXCEPTION");
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
                    fi.returnExp("JS_EXCEPTION");
                    this.declare(type, name, false, `(${type})long_${tmpname}`, flags.supressDeclaration);
                    break;
                case "float": {
                    this.statement("double double_" + tmpname);
                    this.declare('int', 'err_' + tmpname, false, `JS_ToFloat64(ctx, &double_${tmpname}, ${src})`);
                    const fi = this.if(`err_${tmpname}<0`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} is not numeric"`]);
                    fi.returnExp("JS_EXCEPTION");
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
                    fi.returnExp("JS_EXCEPTION");
                    break;
                }
                default: {
                    const classId = classIds[type];
                    if (!classId) throw new Error("Cannot convert into parameter type: " + type);
                    this.declare(type + "*", 'ptr_'+tmpname, false, `(${type}*)JS_GetOpaque(${src}, ${classId})`);
                    //AllowNull unsupported for direct types
                    const fi = this.if(`ptr_${tmpname} == NULL`);
                    errorCleanupFn(fi);
                    fi.call('JS_ThrowTypeError',['ctx',`"${src} does not allow null"`]);
                    fi.returnExp("JS_EXCEPTION");
                    this.declare(type, name, false, `*ptr_${tmpname}`,flags.supressDeclaration);
                }
            }
        }
    }
    cToJs(type,name,src,classIds = {},flags={},depth=0,sizeVars=[]){
        //normalize type
        type=type.replace('const ','');
        let tmpname=name.replace(/[[\]]/g,'');
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
            if( !['void','char'].includes(getsubtype(type))) {//Dont allow dumb usecases: Array of direct opaque data, array of char
                let srclen=sizeVars.pop();
                if(srclen==undefined){
                    //TODO: remove sizeof() based length
                    ctx.declare('JSValue', name, false, `JS_NewArray(ctx)`,true);
                    ctx.declare('size_t','size_'+name,false,`sizeof(${src})/sizeof(${subtype})`);
                    let child=ctx.for('0', 'size_'+name,'i'+depth);
                    child.cToJs(subtype,'js_'+tmpname,`${src}[i${depth}]`,classIds,flags,depth+1,sizeVars);
                    child.statement(`JS_DefinePropertyValueUint32(ctx,${name},i${depth},js_${tmpname},JS_PROP_C_W_E)`);

                }else if(typeof(srclen)=="number"){
                    ctx.declare('JSValue', name, false, `JS_NewArray(ctx)`,true);
                    for(let i=0;i<srclen;i++){
                        ctx.cToJs(subtype,'js_'+tmpname,src+'['+i+']',classIds,flags,depth+1,sizeVars);
                        ctx.statement(`JS_DefinePropertyValueUint32(ctx,${name},${i},js_${tmpname},JS_PROP_C_W_E)`);
                    }
                }else if(typeof(srclen)=="string"){
                    let child=ctx;
                    if(srclen=='1&'){
                        ctx.cToJs(subtype,'js_'+tmpname,`${src}[0]`,classIds,flags,depth+1,sizeVars);
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
                    child.cToJs(subtype,'js_'+tmpname,`${src}[i${depth}]`,classIds,flags,depth+1,sizeVars);
                    child.statement(`JS_DefinePropertyValueUint32(ctx,${name},i${depth},js_${tmpname},JS_PROP_C_W_E)`);
                }
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
            if(classIds[subtype]){
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
            arr = arr.if(`JS_IsArray(ctx,${name}) == 1`);
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
                default: {
                    const classId = classIds[type];
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
    jsCleanUpParameter(type, name, src, classIds = {}, flags = {}) {
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
            let tmpname=name.replace(/[[\]]/g,'');
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
            const classId = classIds[type.replace(" &", "")];
            if (!classId){
                getArray(this,type,name,src);
            }
        }
    }
    jsFunctionList(name) {
        this.line("static const JSCFunctionListEntry " + name + "[] = {");
        this.indent();
        const sub = this.createGenerator();
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
    jsStructGetter(structName, classId, field, type, classIds, overrideRead) {
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }];
        const fun = this.function(`js_${structName}_get_${field}`, "JSValue", args, true);
        fun.declare(structName + "*", "ptr", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
        if (overrideRead) {
            overrideRead(fun);
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
        fun.cToJs(type, "ret", field, classIds);
        fun.returnExp("ret");
        return fun;
    }
    jsStructSetter(structName, classId, field, type, classIds, overrideWrite) {
        //console.log('jsStructSetter',structName, classId, field, type, classIds, overrideWrite);
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }, { type: "JSValue", name: "v" }];
        const fun = this.function(`js_${structName}_set_${field}`, "JSValue", args, true);
        fun.declare(structName + "*", "ptr", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
        fun.jsToC(type, "value", "v", classIds);
        if (overrideWrite) {
            overrideWrite(fun);
        }
        else {
            fun.statement("ptr->" + field + " = value");
        }
        fun.returnExp("JS_UNDEFINED");
        return fun;
    }
    jsStructConstructor(structType, fields, classId, classIds) {
        //console.log('jsStructConstructor',structType, fields, classId, classIds);
        const body = this.jsBindingFunction(structType + "_constructor");
        let r1=body.if('argc==0');
            r1.declare(structType + "*", 'ptr__return', false, `(${structType}*)js_calloc(ctx, 1, sizeof(${structType}))`);
            r1.declare("JSValue", '_return', false, `JS_NewObjectClass(ctx, ${classId})`);
            r1.call("JS_SetOpaque", ['_return', "ptr__return"]);
            r1.returnExp("_return");
        for(let i = 0; i < fields.length; i++) {
            const para = fields[i];
            body.jsToC(para.type, para.name, "argv[" + i + "]", classIds);
        }
        body.declareStruct(structType, "_struct", fields.map(x => x.name));
        body.jsStructToOpq(structType, "_return", "_struct", classId);
        body.returnExp("_return");
        return body;
    }
}
export class QuickJsGenerator extends GenericQuickJsGenerator {
    createGenerator() {
        return new QuickJsGenerator();
    }
}