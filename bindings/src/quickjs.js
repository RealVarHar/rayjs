import { writeFileSync } from "./fs.js";
import { CodeWriter, GenericCodeGenerator } from "./generation.js"
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
        this.includeMemoryAlloc(body);
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
    includeMemoryAlloc(body){
        //define an allocation linked list
        //define struct
        body.line('typedef struct memoryNode{');
        body.indent();
        body.declare('length','int');
        body.declare('pointers[6]','void *');
        body.declare('next','struct memoryNode *');
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
        body.line(`void memoryClear(memoryNode *head) {
    memoryNode * prev_node;
    while (head != NULL) {
        for (int i = 0; i < head->length; i += 2) {
            void (*free_func) (void *) = head->pointers[i];
            void * ptr_to_free = head->pointers[i + 1];
            free_func(ptr_to_free);
        prev_node = head;
        head = head->next;
        free(prev_node);
        }
    }
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
    }
    registerStruct(struct, classId) {
        this.structLookup[struct] = classId;
    }
    writeTo(filename) {
        const writer = new CodeWriter();
        writer.writeGenerator(this.root);
        (0, writeFileSync)(filename, writer.toString());
    }
}
function getsubtype(type){
    if(type.endsWith(']')){
        return type.substring(0,type.lastIndexOf(' ['));
    }else if(type.endsWith('*')){
        return type.substring(0,type.lastIndexOf(' *'));
    }else{
        return type.substring(0,type.lastIndexOf(' '));
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
                return ["JS_CLASS_UINT8C_ARRAY"];
            case "unsigned short":
            case "unsigned short int":
                return ["JS_CLASS_UINT8C_ARRAY"];
            case "int":
            case "signed":
            case "signed int":
                return ["JS_CLASS_INT16_ARRAY"];
            case "unsigned":
            case "unsigned int":
                return ["JS_CLASS_UINT16_ARRAY"];
            case "long":
            case "long int":
            case "signed long":
            case "signed long int":
                return ["JS_CLASS_INT32_ARRAY"];
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
    jsToC(type, name, src, classIds = {},flags={},depth=0) {
        //needs to return flags
        function getArray(ctx,type,name,src,srclen){
            //console.log(type,'subtype',getsubtype(type));
            //define
            if(!flags.supressDeclaration){
                if(srclen != undefined){
                    ctx.declare(name+'['+srclen+']',getsubtype(type));
                }else{
                    ctx.declare(name,type);
                }
            }
            let tmpname=name.replace(/[[\]]/g,'');
            let ctxif='if';

            let typedClassIds=ctx.getTypedArray(getsubtype(type));
            let addBuffer=!getsubtype(type).includes('*');
            let addTypedArray=typedClassIds!==false;
            let topDefineJs=!flags.dynamicAlloc && (addBuffer||addTypedArray);
            if( topDefineJs ){
                ctx.declare(`js_${tmpname}`,'JSValue');//for de-allocation
            }

            //Check if NULL
            if(flags.allowNull){
                ctx[ctxif](`JS_IsNull(${src}) || JS_IsUndefined(${src})`).statement(`${name} = NULL`);
                ctxif='elsif';
            }

            //Check if Array
            let arr;
            if(getsubtype(type)!='void') {//TODO: allow dynamic binding of array properties
                arr = ctx[ctxif](`JS_IsArray(ctx,${src}) == 1`);
                if (srclen == undefined) {
                    arr.declare("size_" + tmpname, "size_t");
                    arr.if(`JS_GetLength(ctx,${src},&size_${tmpname})==-1`).returnExp("JS_EXCEPTION");
                } else {
                    arr.declare("size_" + tmpname, "size_t", false, srclen);
                }
                arr.statement(`${name} = js_malloc(ctx, size_${tmpname} * sizeof(${getsubtype(type)}))`);
                if (flags.dynamicAlloc) {
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, ${name})`);
                }
                let iter = 'i' + depth;
                let arrf = arr.for('0', `size_${tmpname}`, iter);
                arrf.declare(`js_${tmpname}`, 'JSValue', false, `JS_GetPropertyUint32(ctx,${src},${iter})`);
                arrf.jsToC(getsubtype(type), `${name}[${iter}]`, `js_${tmpname}`, classIds, {
                    supressDeclaration: true,
                    dynamicAlloc: true
                }, depth + 1);
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

            //Check id Buffer
            if(addBuffer) {//check for arrayBuffer only if [] but not [][]
                arr = ctx[ctxif](`JS_IsArrayBuffer(${src}) == 1`);
                arr.declare(`js_${tmpname}`,'JSValue',false,`JS_DupValue(ctx,${src})`,topDefineJs);
                if(flags.dynamicAlloc){
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, &js_${tmpname})`);
                }
                arr.declare("size_" + tmpname, "size_t");
                arr.declare(`${name}`, type, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, js_${tmpname})`,true);
                ctxif='elsif';
            }

            //Check if typed array like int8Array
            if(addTypedArray){
                if(ctxif!='if'){
                    ctx = ctx.else();
                }
                ctx.declare('classid_'+tmpname,'JSClassID',false,`JS_GetClassID(${src})`);
                arr = ctx.if('classid_'+tmpname+'=='+typedClassIds.join(' && classid_'+tmpname+'=='));
                arr.declare('offset_'+tmpname,'size_t',false);
                arr.declare('size_'+tmpname,'size_t',false);
                arr.declare('js_'+tmpname,'JSValue',false,`JS_GetTypedArrayBuffer(ctx,${src},&offset_${tmpname},&size_${tmpname},NULL)`,topDefineJs);//calls js_dup, free this
                if(flags.dynamicAlloc){
                    arr.statement(`memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, &js_${tmpname})`);
                }
                //TODO: respect buffer offset
                arr.declare(name, type, false, `(${type})JS_GetArrayBuffer(ctx, &size_${tmpname}, js_${tmpname})`,true);
                ctxif='elsif';
            }
            ctx.else().returnExp("JS_EXCEPTION");
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
            this.declare(`size_${tmpname}`, "size_t",false,initValue);
            let spreadsize=4;
            this.statement(`if(size_${tmpname}>${spreadsize})size_${tmpname}=${spreadsize}`);
            //[]=[].map()
            this.declare(name,type+' *',false,`js_malloc(ctx, size_` + tmpname + ` * sizeof(${type}))`,flags.supressDeclaration);
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
            getArray(this,type,name,src,len);
        }else if(type.endsWith('*')){
            const classId = classIds[type.replace(" *", "")];
            if (classId){
                this.jsOpqToStructPtr(type.replace(" *", ""), name, src, classId);
                if(!flags.allowNull) {
                    this.statement(`if(${name} == NULL) return JS_EXCEPTION`);
                }
            }else{
                getArray(this,type,name,src);
            }
        }else{
            switch (type) {
                case "char":
                    this.declare(name,type,false,`(${type})((${type} *)JS_ToCString(ctx, ${src}))[0]`,flags.supressDeclaration);
                    break;
                case "double":
                    if (!flags.supressDeclaration)
                        this.statement(`${type} ${name}`);
                    this.statement(`JS_ToFloat64(ctx, &${name}, ${src})`);
                    break;
                case "float":
                    this.statement("double double_" + name);
                    this.statement(`JS_ToFloat64(ctx, &double_${name}, ${src})`);
                    this.declare(name,type,false,`(${type})double_${name}`,flags.supressDeclaration);
                    break;
                case "int":
                    if (!flags.supressDeclaration)
                        this.statement(`${type} ${name}`);
                    this.statement(`JS_ToInt32(ctx, &${name}, ${src})`);
                    break;
                case "unsigned int":
                    if (!flags.supressDeclaration)
                        this.statement(`${type} ${name}`);
                    this.statement(`JS_ToUint32(ctx, &${name}, ${src})`);
                    break;
                case "short":
                    this.statement("unsigned int _int_" + name);
                    this.statement(`JS_ToInt32(ctx, &_int_${name}, ${src})`);
                    this.declare(name,type,false,`(${type})_int_${name}`,flags.supressDeclaration);
                    break;
                case "unsigned short":
                case "unsigned char":
                    this.statement("unsigned int _int_" + name);
                    this.statement(`JS_ToUint32(ctx, &_int_${name}, ${src})`);
                    this.declare(name,type,false,`(${type})_int_${name}`,flags.supressDeclaration);
                    break;
                case "bool":
                    this.declare(name,type,false,`JS_ToBool(ctx, ${src})`,flags.supressDeclaration);
                    break;
                default:
                    const classId = classIds[type];
                    if (!classId) throw new Error("Cannot convert into parameter type: " + type);
                    this.jsOpqToStructPtr(type, name+'_ptr', src, classId);
                    //AllowNull unsupported for direct types
                    this.statement(`if(${name}_ptr == NULL) return JS_EXCEPTION`);
                    this.declare(name, type, false, `*${name}_ptr`);
            }
        }
    }
    jsToJs(type, name, src, classIds = {}) {
        function arrayof(thiz,src,name,len,subtype){
            thiz.declare(name, 'JSValue', false, `JS_NewArray(ctx)`);
            if(typeof(len)=='number'){
                for(let i=0;i<len;i++){
                    let subname=name+i;
                    thiz.jsToJs(subtype,subname,src+'['+i+']',classIds);//TODO: get correct classId
                    thiz.statement(`JS_DefinePropertyValue(ctx,${name},${i},${subname},JS_PROP_C_W_E)`);//TODO: flags
                }
            }else{
                let child=thiz.for('0', len);
                let subname=name+'i';
                child.jsToJs(subtype,subname,src+'[i]',classIds);//TODO: get correct classId
                child.statement(`JS_DefinePropertyValue(ctx,${name},'i',${subname},JS_PROP_C_W_E)`);//TODO: flags
            }
        }
        switch (type) {
            case "int":
            case "long":
                this.declare(name, 'JSValue', false, `JS_NewInt32(ctx, ${src})`);
                break;
            case "long":
                this.declare(name, 'JSValue', false, `JS_NewInt64(ctx, ${src})`);
                break;
            case "unsigned int":
            case "unsigned char":
                this.declare(name, 'JSValue', false, `JS_NewUint32(ctx, ${src})`);
                break;
            case "bool":
                this.declare(name, 'JSValue', false, `JS_NewBool(ctx, ${src})`);
                break;
            case "float":
            case "double":
                this.declare(name, 'JSValue', false, `JS_NewFloat64(ctx, ${src})`);
                break;
            case "const void *":
            case "void *":
            case "int *":
            case "float *":
            case "unsigned short *":
            case "unsigned char *":
            case "const unsigned char *":
            case "const char **":
            case "char **":
                let subtype=type.substring(0,type.length-1).trim();
                this.declare(name+'_size','size_t',false,`sizeof(${src})`);
                arrayof(this,src,name,name+'_size',subtype);
                break;
            case "const char *":
            case "char *":
                this.declare(name, 'JSValue', false, `JS_NewString(ctx, ${src})`);
                break;
            // case "unsigned char *":
            //     this.declare(name, 'JSValue', false, `JS_NewString(ctx, ${src})`)
            //     break;
            default:
                if(type.startsWith("float[")&&type.endsWith(']')){
                    let subtype=type.split('[')[0];
                    let len=type.substring('float['.length,type.length-1);
                    arrayof(this,src,name,len,subtype);
                    break;
                }
                const classId = classIds[type];
                if (!classId)
                    throw new Error("Cannot convert parameter type to Javascript: " + type);
                this.jsStructToOpq(type, name, src, classId);
        }
    }
    jsStructToOpq(structType, jsVar, srcVar, classId) {
        this.declare(jsVar + "_ptr", structType + "*", false, `(${structType}*)js_malloc(ctx, sizeof(${structType}))`);
        this.statement("*" + jsVar + "_ptr = " + srcVar);
        this.declare(jsVar, "JSValue", false, `JS_NewObjectClass(ctx, ${classId})`);
        this.call("JS_SetOpaque", [jsVar, jsVar + "_ptr"]);
    }
    jsCleanUpParameter(type, name, src, classIds = {}, flags = {}) {
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
                arr.call('js_free',['ctx','&js_'+tmpname]);
                ctxif='elsif';
            }
            let typedClassIds=ctx.getTypedArray(getsubtype(type));
            if(typedClassIds!==false){
                if(ctxif!='if'){
                    ctx = ctx.else();
                }
                ctx.declare('classid_'+tmpname,'JSClassID',false,`JS_GetClassID(${src})`);
                arr = ctx.if('classid_'+tmpname+'=='+typedClassIds.join(' && classid_'+tmpname+'=='));
                arr.call('js_free',['ctx','&js_'+tmpname]);
                ctxif='elsif';
            }
        }
        //normalize type
        type=type.replace('const ','');
        if(type.startsWith('...')){
            this.call('js_free',['ctx',name]);
            //Arrays
        }else if(type.endsWith(']')){
            getArray(this,type,name,src);
        }else if(type.endsWith('*')){
            const classId = classIds[type.replace(" *", "")];
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
        this.declare(id, "JSClassID", true);
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
        const body = this.function("js_declare_" + structName, "int", [{ type: "JSContext *", name: "ctx" }, { type: "JSModuleDef *", name: "m" }], true);
        body.declare("rt","JSRuntime *",false,`JS_GetRuntime(ctx)`);
        body.call("JS_NewClassID", ["rt","&" + classId]);
        const classDefName = `js_${structName}_def`;
        body.declare(classDefName, "JSClassDef", false, `{ .class_name = "${structName}", .finalizer = ${finalizerName} }`);
        body.call("JS_NewClass", ["rt", classId, "&" + classDefName]);
        body.declare("proto", "JSValue", false, "JS_NewObject(ctx)");
        body.call("JS_SetPropertyFunctionList", ["ctx", "proto", funcListName, `countof(${funcListName})`]);
        body.call("JS_SetClassProto", ["ctx", classId, "proto"]);
        body.statement("return 0");
        return body;
    }
    jsStructGetter(structName, classId, field, type, classIds, overrideRead) {
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }];
        const fun = this.function(`js_${structName}_get_${field}`, "JSValue", args, true);
        fun.declare("ptr", structName + "*", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
        if (overrideRead) {
            overrideRead(fun);
        } else {
            if(type.endsWith(']')){
                let type2=type.split('[');
                let amount='['+type2[1];
                type2=type2[0];
                fun.declare(field+amount, type2, false, "ptr->" + field);
            }else{
                fun.declare(field, type, false, "ptr->" + field);
            }
        }
        fun.jsToJs(type, "ret", field, classIds);
        fun.returnExp("ret");
        return fun;
    }
    jsStructSetter(structName, classId, field, type, classIds, overrideWrite) {
        //console.log('jsStructSetter',structName, classId, field, type, classIds, overrideWrite);
        const args = [{ type: "JSContext*", name: "ctx" }, { type: "JSValue", name: "this_val" }, { type: "JSValue", name: "v" }];
        const fun = this.function(`js_${structName}_set_${field}`, "JSValue", args, true);
        fun.declare("ptr", structName + "*", false, `JS_GetOpaque2(ctx, this_val, ${classId})`);
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
    jsOpqToStructPtr(structType, structVar, srcVar, classId) {
        this.declare(structVar, structType + "*", false, `(${structType}*)JS_GetOpaque2(ctx, ${srcVar}, ${classId})`);
    }
    jsStructConstructor(structName, fields, classId, classIds) {
        //console.log('jsStructConstructor',structName, fields, classId, classIds);
        const body = this.jsBindingFunction(structName + "_constructor");
        for (let i = 0; i < fields.length; i++) {
            const para = fields[i];
            body.jsToC(para.type, para.name, "argv[" + i + "]", classIds);
        }
        body.declareStruct(structName, "_struct", fields.map(x => x.name));
        body.jsStructToOpq(structName, "_return", "_struct", classId);
        body.returnExp("_return");
        return body;
    }
}
export class QuickJsGenerator extends GenericQuickJsGenerator {
    createGenerator() {
        return new QuickJsGenerator();
    }
}