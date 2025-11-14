import { writeFileSync } from "./fs.js";

export class TypeScriptDeclaration {
    constructor(modulename) {
        this.root = new TypescriptGenerator();
        this.module = this.root;
        if(modulename!='' && modulename!='global'){
            this.module = this.root.tsDeclareModule(modulename);
            this.module.name = modulename;
        }
        this.defined={};
        this.functions=[];
        this.structs=[];
        this.callbacks=[];
        this.aliases=[];
        this.constants=[];
    }
    addConstant(name, type, comment){
        this.defined[name]=true;
        this.constants.push([name, type, comment]);
    }
    addFunction(api) {
        this.defined[api.name]=true;
        this.functions.push(api);
    }
    addStruct(api) {
        this.defined[api.name]=true;
        if(api.fields==undefined)debugger;
        this.structs.push(api);
    }
    addCallback(name, parameters, comment){
        if(this.defined[name])return;
        this.defined[name]=true;
        this.callbacks.push({name, parameters, comment});
    }
    addAlias(name, aliasof){
        this.defined[name]=true;
        this.aliases.push({name, aliasof});
    }
    toJsType(type,lookups) {
        if(type.startsWith('const ')){
            type = type.substring('const '.length);
        }
        if(lookups!=undefined){
            let variable=lookups.variables[type];
            if(variable){
                //custom type
                let sourceModule=lookups.includegen.tokenList.find(a=>a.type=='include'&&a.text.vars.find(b=>b.name==type)!=undefined).text.name;
                let moduletypingName;
                for(let key in lookups.modules){
                    const module=lookups.modules[key];
                    if(module.gen.c_source==sourceModule){
                        moduletypingName='rayjs:'+module.gen.name;
                        break;
                    }
                }
                if(moduletypingName != this.module.name){
                    if(this.includeList[moduletypingName]==undefined)this.includeList[moduletypingName]={};
                    this.includeList[moduletypingName][type]=true;
                }
            }
        }
        if(type.endsWith('&')){
            const subtype = type.substring(0,type.length-1).trim();
            if(lookups!=undefined){
                //No need to wrap in array custom objects
                if(lookups.variables[subtype]){
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
    writeTo(filename, lookups) {
        //reset includes
        this.includeList={};//{key=>{value:true}}
        this.includesGen = this.module.child();
        this.includesGen.tags.module=this.module.tags.module;
        this.structsGen = this.module.child();
        this.structsGen.tags.module=this.module.tags.module;
        this.functionsGen = this.module.child();
        this.functionsGen.tags.module=this.module.tags.module;
        this.constantsGen = this.module.child();
        this.constantsGen.tags.module=this.module.tags.module;

        //Structs
        for(let struct of this.structs){
            const options = struct.binding || {};
            var fields = struct.fields.filter(x => x.binding.get).map(x => ({ name: x.name, comment: x.comment, type: this.toJsType(x.type) }));
            this.structsGen.tsDeclareInterface(struct.name, fields);
            this.structsGen.tsDeclareType(struct.name, !!(options.createConstructor), fields);
        }
        //Callbacks
        for(let callback of this.callbacks){
            let ret = callback.parameters.returnType;
            if(ret==undefined) {
                ret=='void';
            }else{
                ret = this.toJsType(ret,lookups);
            }
            let inlinefn;
            if(callback.parameters.threaded){
                //when inside of a worker, we pass the indentyfier that will be caught by onmessage
                inlinefn = 'string | number';
            }else{
                inlinefn = `(${callback.parameters.map(a=>`${a.name}:${this.toJsType(a.type.replaceAll('&', '*'),lookups)}`).join(',')})=>${ret}`;
            }
            this.structsGen.tsAliasType(callback.name, inlinefn, callback.comment);
        }
        //Aliases
        for(let alias of this.aliases){
            const aliasof = this.toJsType(alias.aliasof,lookups);
            this.structsGen.tsAliasType(alias.name, aliasof);
        }
        //Constants
        for(let constant of this.constants){
            this.constantsGen.tsDeclareConstant(...constant);
        }
        //Functions
        for(let fn of this.functions){
            const options = fn.binding || {};
            const arg = fn.args.filter(x => !x.binding.ignore).map(x => ({ name: (x.type=='...'?'...':'')+x.name, type: x.binding.jsType ?? this.toJsType(x.type,lookups) }));
            const returnType = options.jsReturns ?? this.toJsType(fn.returnType,lookups);
            this.functionsGen.tsDeclareFunction(fn.name, arg, returnType, fn.binding.comment);
        }

        for(let key in this.includeList){
            let toload = this.includeList[key];
            this.includesGen.tsImportTypes(key,Object.keys(toload));
        }
        //generate code
        writeFileSync(filename, this.root.toString());
    }
}
class TypescriptGenerator {
    /**
     * @type {[TypescriptGenerator|int|string]}
     */
    tokenList=[];
    initdepth=0;
    tags={};
    toString(){
        let ret="";
        let depth=this.initdepth;
        for(let token of this.tokenList){
            switch(typeof(token)){
                case "object":ret+=token.toString();break;
                case "number":depth+=token;break;
                case "string":{
                    let indent=" ".repeat(depth);
                    if(token[token.length-1]=="\n"){
                        token=indent+token.substring(0,token.length-1).replaceAll("\n","\n"+indent)+"\n";
                    }else{
                        token=indent+token.replaceAll("\n","\n"+indent)
                    }
                    ret+=token;
                }break;
            }
        }
        return ret;
    }
    line(text){this.tokenList.push(text);}
    child(){const c=new TypescriptGenerator();c.initdepth=this.depth;this.tokenList.push(c);return c;}
    indent(){this.tokenList.push(1);}
    unindent(){this.tokenList.push(-1);}
    tsDeclareFunction(name, parameters, returnType, comment) {
        let declare =this.tags.module?'':'declare ';
        this.tsDocComment(comment);
        this.line(`${declare}function ${name}(${parameters.map(x => x.name + ': ' + x.type).join(', ')}): ${returnType}`);
    }
    tsDeclareConstant(name, type, comment) {
        let declare =this.tags.module?'':'declare ';
        this.tsDocComment(comment);
        this.line(`${declare}var ${name}: ${type}`);
    }
    tsDeclareType(name, hasConstructor, parameters) {
        let declare =this.tags.module?'':'declare ';
        this.line(`${declare}var ${name}: {\n`);
        this.indent();
        this.line(`prototype: ${name}\n`);
        if (hasConstructor)
            this.line(`new(${parameters.map(x => x.name + "?: " + x.type).join(', ')}): ${name}\n`);
        this.unindent();
        this.line("}\n");
    }
    //Class should have constructor and notify that this module allows its creation
    tsDeclareClass(name, fileds) {

    }
    //Interfaces should define only class parameters
    tsDeclareInterface(name, fields) {
        this.line(`interface ${name} {\n`);
        this.indent();
        for (const field of fields) {
            if (field.comment)
                this.tsDocComment(field.comment);
            this.line(field.name + ": " + field.type + ",\n");
        }
        this.unindent();
        this.line("}\n");
    }
    tsImportTypes(module,types){
        this.line(`import type {${types.join(',')}} from '${module}';\n`);
    }
    tsDeclareModule(name){
        this.line(`declare module "${name}" {\n`);
        this.indent();
        let child=this.child();
        child.tags.module=true;
        this.unindent();
        this.line("}\n");
        return child;
    }
    tsAliasType(name, aliasof,comment){
        if (comment)
            this.tsDocComment(comment);
        this.line(`type ${name} = ${aliasof};\n`);
    }
    tsDocComment(comment) {
        this.line(`/** ${comment} */\n`);
    }
}