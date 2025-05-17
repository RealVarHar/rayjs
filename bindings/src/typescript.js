import { CodeGenerator, CodeWriter } from "./generation.js"
import { writeFileSync } from "./fs.js";

export class TypeScriptDeclaration {
    constructor(modulename) {
        this.root = new TypescriptGenerator();
        this.module = this.root;
        if(modulename!='' && modulename!='global'){
            this.module = this.root.tsDeclareModule(modulename);
            this.module.name = modulename;
        }

        this.includeList={};//{key=>{value:true}}
        this.includes = this.module.child();
        this.includes.tags.module=this.module.tags.module;
        this.structs = this.module.child();
        this.structs.tags.module=this.module.tags.module;
        this.functions = this.module.child();
        this.functions.tags.module=this.module.tags.module;
        this.constants = this.module.child();
        this.constants.tags.module=this.module.tags.module;
    }
    addFunction(name, api, lookups) {
        const options = api.binding || {};
        const para = (api.params || []).filter(x => !x.binding.ignore).map(x => ({ name: (x.type=='...'||x.binding.jsType=='...'?'...':'')+x.name, type: x.binding.jsType ?? this.toJsType(x.type,lookups) }));
        const returnType = options.jsReturns ?? this.toJsType(api.returnType,lookups);
        this.functions.tsDeclareFunction(name, para, returnType, api.description);
    }
    addStruct(api) {
        const options = api.binding || {};
        var fields = api.fields.filter(x => !!(options.properties || {})[x.name]).map(x => ({ name: x.name, description: x.description, type: this.toJsType(x.type) }));
        this.structs.tsDeclareInterface(api.name, fields);
        this.structs.tsDeclareType(api.name, !!(options.createConstructor), fields);
    }
    addCallback(name, parameters, lookups){
        let ret = parameters.returnType;
        if(ret==undefined) {
            ret=='void';
        }else{
            ret = this.toJsType(ret,lookups);
        }
        let inlinefn;
        if(parameters.threaded){
            //when inside of a worker, we pass the indentyfier that will be caught by onmessage
            inlinefn = 'string | number';
        }else{
            inlinefn = `(${parameters.map(a=>`${a.name}:${this.toJsType(a.type.replaceAll('&', '*'),lookups)}`).join(',')})=>${ret}`;
        }
        this.structs.tsAliasType(name, inlinefn);
    }
    addAlias(name, aliasof, lookups){
        aliasof = this.toJsType(aliasof,lookups);
        this.structs.tsAliasType(name, aliasof);
    }
    toJsType(type,lookups) {
        if(type.startsWith('const ')){
            type = type.substring('const '.length);
        }
        if(lookups!=undefined){
            if(lookups.struct[type] || lookups.callback[type]){
                //custom type
                let sourceModule = lookups.includeDictionary.lookup[type];
                sourceModule = lookups.includeDictionary.moduleNames[sourceModule];
                if(sourceModule != this.module.name){
                    if(this.includeList[sourceModule]==undefined)this.includeList[sourceModule]=[];
                    this.includeList[sourceModule][type]=true;
                }
            }
        }
        if(type.endsWith('&')){
            const subtype = type.substring(0,type.length-1).trim();
            if(lookups!=undefined){
                //No need to wrap in array custom objects
                if(lookups.struct[subtype] || lookups.callback[subtype]){
                    return this.toJsType(subtype,lookups);
                }
            }
            return `${this.toJsType(subtype,lookups)} | ${this.toJsType(subtype,lookups)}[]`;
        }
        if(type.endsWith(']')){
            const index = type.lastIndexOf('[');
            const subtype = this.toJsType(type.substring(0,index).trim());
            const length = Number(type.substring(index+1,type.length-1).trim());
            if(subtype=='string' && type.substring(0,index).trim()=='char'){
                //char array is string, but allow for [string]
                return 'string';
            }
            return `[${new Array(length).fill(subtype).join(',')}]`;//return touple
        }
        switch (type) {
            case '...':
                return "any";
            case "bool":
                return "boolean";
            case "int8_t":
            case "int":
            case "signed":
            case "signed int":
            case "short":
            case "short int":
            case "signed short":
            case "signed short int":
            case "signed char":
            case "int32_t":
            case "long":
            case "long int":
            case "signed long":
            case "signed long int":
            case "uint8_t":
            case 'wchar_t':
            case "unsigned char":
            case "unsigned short":
            case "unsigned short int":
            case "unsigned":
            case "unsigned int":
            case "uint32_t":
            case "unsigned long":
            case "unsigned long int":
            case "int64_t":
            case "long long":
            case "long long int":
            case "signed long long":
            case "signed long long int":
            case "uint64_t":
            case "unsigned long long":
            case "unsigned long long int":
            case "float":
            case "double":
            case "long double":
                return "number";
            case "char":
            case "char *":
                return "string";
            case "void *":
                return "ArrayBuffer";
            default:
                if(type.endsWith('*')){
                    const subtype = type.substring(0,type.length-1).trim();
                    return this.toJsType(subtype,lookups)+'[]';
                }
                return type.replace(" *", "").replace("const ", "");
        }
    }
    writeTo(filename) {
        //reset includes
        this.includes.clear();
        for(let key in this.includeList){
            let toload = this.includeList[key];
            this.includes.tsImportTypes(key,Object.keys(toload));
        }
        //generate code
        const writer = new CodeWriter();
        writer.writeGenerator(this.root);
        writeFileSync(filename, writer.toString());
    }
}
class TypescriptGenerator extends CodeGenerator {
    tsDeclareFunction(name, parameters, returnType, description) {
        let declare =this.tags.module?'':'declare ';
        this.tsDocComment(description);
        this.statement(`${declare}function ${name}(${parameters.map(x => x.name + ': ' + x.type).join(', ')}): ${returnType}`);
    }
    tsDeclareConstant(name, type, description) {
        let declare =this.tags.module?'':'declare ';
        this.tsDocComment(description);
        this.statement(`${declare}var ${name}: ${type}`);
    }
    tsDeclareType(name, hasConstructor, parameters) {
        let declare =this.tags.module?'':'declare ';
        this.line(`${declare}var ${name}: {`);
        this.indent();
        this.statement("prototype: " + name);
        if (hasConstructor)
            this.statement(`new(${parameters.map(x => x.name + "?: " + x.type).join(', ')}): ${name}`);
        this.unindent();
        this.line("}");
    }
    //Class should have constructor and notify that this module allows its creation
    tsDeclareClass(name, fileds) {

    }
    //Interfaces should define only class parameters
    tsDeclareInterface(name, fields) {
        this.line(`interface ${name} {`);
        this.indent();
        for (const field of fields) {
            if (field.description)
                this.tsDocComment(field.description);
            this.line(field.name + ": " + field.type + ",");
        }
        this.unindent();
        this.line("}");
    }
    tsImportTypes(module,types){
        this.statement(`import type {${types.join(',')}} from '${module}'`);
    }
    tsDeclareModule(name){
        this.line(`declare module "${name}" {`);
        this.indent();
        let child=this.child();
        child.tags.module=true;
        this.unindent();
        this.line("}");
        return child;
    }
    tsAliasType(name, aliasof){
        this.statement(`type ${name} = ${aliasof}`);
    }
    tsDocComment(comment) {
        this.line(`/** ${comment} */`);
    }
}