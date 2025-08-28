import {simpleregex, lookForward, azZ0, azZ, defaultTypeParts, source_parser} from "./source_parser.js";

//The purpose of this file is to create a code generator that:
//- Can be tree-walkable
//- Can have easy code inserting
//- Will keep track of variables and parent scopes
//- Will keep track of dependencies

let globalTokenId=0;
const numMantissa = {
    "unsigned char":[8,0],
    "int_least8_t":[8,0],
    "signed char":[8,0],
    "int_fast8_t":[8,0],
    "uint8_t":[8,0],
    "int8_t":[8,0],
    "char":[8,0],
    "unsigned short int":[16,0],
    "signed short int":[16,0],
    "unsigned short":[16,0],
    "int_least16_t":[16,0],
    "signed short":[16,0],
    "unsigned int":[16,0],
    "int_fast16_t":[16,0],
    "signed int":[16,0],
    "short int":[16,0],
    "unsigned":[16,0],
    "uint16_t":[16,0],
    "int16_t":[16,0],
    "signed":[16,0],
    "short":[16,0],
    "int":[16,0],
    "unsigned long int":[32,0],
    "signed long int":[32,0],
    "unsigned long":[32,0],
    "int_least32_t":[32,0],
    "int_fast32_t":[32,0],
    "signed long":[32,0],
    "uint32_t":[32,0],
    "long int":[32,0],
    "int32_t":[32,0],
    "wchar_t":[32,0],
    "long":[32,0],
    "float":[32,16],
    "unsigned long long int":[64,0],
    "signed long long int":[64,0],
    "unsigned long long":[64,0],
    "signed long long":[64,0],
    "long long int":[64,0],
    "int_least64_t":[64,0],
    "int_fast64_t":[64,0],
    "long long":[64,0],
    "uintmax_t":[64,0],
    "uintptr_t":[64,0],
    "uint64_t":[64,0],
    "intmax_t":[64,0],
    "intptr_t":[64,0],
    "int64_t":[64,0],
    "size_t":[64,0],
    "double":[64,32],
    "long double":[64,64]
};
const mantisaNum=Object.fromEntries(Object.entries(numMantissa).map(a=>[JSON.stringify(a[1]),a[0]]));//inverse

//This class represents metadata of a single part of gen text
//This includes: comment, variable [declaration, assignment, call], if, loop
class CodeToken {
    constructor(type,text) {
        this.type=type;
        this.text=text;
        this.tokenId=globalTokenId;
        globalTokenId++;
    }
    _getVariables(into,sources){
        if(this.type=='declare'){
            into[this.text.name]=this.text;
        }else if(this.type=='function'){
            into[this.text.name]=this.text;
        }else if(this.type=='include'){
            let args=this.text.vars;
            for(let i=0;i<args.length;i++){
                into[args[i].name]=args[i];//{{char} *} {} => char *
            }
        }
    }
}

/**
 * TOOL: subset removes from Array<string> strings included in toRemove
 * @param {Array<string>} source
 * @param {Array<string>} toRemove
 * @param {boolean} [leavegaps] return unchanged array with removed strings as (true=>'', false=>not existing)
 * @return {Array<string>} reminder
 */
function subset(source,toRemove, leavegaps=false){
    //start by sorting source and toremove
    toRemove=toRemove.sort((a,b)=>a.localeCompare(b));
    let numberedsource=Object.entries(source).sort((a,b)=>a[1].localeCompare(b[1]));
    let i=0;
    let j=0;
    let remainder=[];
    //a,b, ,d, ,f,f
    //a, ,c,d,e,f
    while(i<numberedsource.length){
        if(j>=toRemove.length){
            remainder.push(numberedsource[i]);
            i++;
            continue;
        }
        let cmp=numberedsource[i][1].localeCompare(toRemove[j]);
        if(cmp==0){
            i++;
        }else{
            if(cmp<0){
                remainder.push(numberedsource[i]);
                i++;
            }else{
                j++;
            }
        }
    }
    if(leavegaps){
        remainder=Object.fromEntries(remainder);
        for(let key in source){
            if(remainder[key]==undefined)source[key]='';
        }
        return source;
    }else{
        return remainder.sort((a,b)=>a[0]==b[0]?0:a[0]<b[0]?-1:1).map(a=>a[1]);
    }
}
export function getsubtype(type){
    if(type==undefined){
        debugger;
        return '';
    }
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

function cast(type,variable,targetType){
    //returns variable with castings to match type to targetType

    //handles numbers using casting
    //handles pointer differences
    targetType=targetType.replaceAll('[','*').split(' *');
    type=type.replaceAll('[','*').split(' *');
    let refcountOrig=targetType.length-1;
    let refcountNew=type.length-1;
    while(refcountNew<refcountOrig){
        variable='&'+variable;
        refcountNew++;
    }
    while(refcountNew>refcountOrig){
        variable='*'+variable;
        refcountNew--;
    }
    if(targetType[0]!=type[0]){
        return `(${targetType.join(' *')})${variable}`;
    }
    return variable;
}

/**
 * @param {Object} fn
 * @param {[string]} args
 * @param {{string:{}}} variableList
 */
function compilefunctionargs(fn,args,variables){
    let ret=[];
    for(let i=0;i<args.length;i++){
        //use resolveVariable to get implicit type if parameter is more complex
        let gettype=[];
        let arg=args[i];
        if(fn.args==undefined)console.log(fn);
        if(arg=='NULL'||fn.args[i].type=='any'){
            ret.push(arg);
            continue;
        }else if(fn.args[i].type=='...'){
            for(;i<args.length;i++){
                ret.push(args[i]);
            }
            break;
        }
        const parts=getVariableParts(arg,variables);
        arg = resolveVariable(parts,gettype,variables);
        //before casting, check if target type includes a function type (callback) and transform it
        let targettype=fn.args[i].type.split(' ');
        for(let i=0;i<targettype.length;i++){
            const word=targettype[i];
            const variable=variables[word];
            if(!variable||variable.type!='type'||variable.subtype!='function')continue;
            targettype[i]=variable.ptrtype;
        }
        arg = cast(gettype[0],arg,targettype.join(' ') );
        ret.push(arg);
    }
    return ret;
}
/**
 * @param {string} input of a.b[c][0]['ab']
 * @return {Array<{type:string,name:string}>} output of [{type:'string':name:'a'},{type:'string':name:'b'},{type:'variable',name:'c'},{type:'number':name:'0'},{type:'string':name:'ab'}]
 */
export function getVariableParts(input,variables){
    switch(typeof(input)){
        case "number":return [{type:'number',name:String(input)}];
        case "boolean":return [{type:'string',name:String(input)}];
    }
    //TODO: direct string
    let pos= 0;
    let parts= [];
    while(pos<input.length){
        let capture;
        while(input[pos]=='('){
            pos=simpleregex(input,["nr*",")"],pos+1,capture=[]);
            if(capture[0]!=''){
                //First, check if last token was a function, actually
                let lastpart=parts[parts.length-1];
                let inner=capture[0].trim();
                if(parts.length>0&&lastpart.type=='string'){
                    let variable=variables[lastpart.name];
                    if(variable!=undefined&&variable.type=='function'){
                        lastpart.type='function';
                        lastpart.args=inner.split(',').map(a=>a.trim());
                        inner='';
                    }
                }else if(inner[inner.length-1]=='*'){//cast
                }else if(simpleregex(inner,["nr*","+-*/^%"],0)!=inner.length){ //Is this a math stm?
                    parts.push({type:'child',name:getVariableParts(inner,variables)});
                    inner='';
                }
                if(inner!=''){
                    parts.push({type:'cast',name:inner});
                }
            }
            if(input[pos]==')')pos++;
        }
        capture=[];
        pos=simpleregex(input,["nr*","*/+-([{.'\""],pos,capture);
        let str=capture[0].trim();
        if(str!=''){
            if(isNaN(str)){
                parts.push({type:'string',name:str});
            }else{
                if(parts.length==1&&parts[0].type=='math'&&parts[0].name=='-'){
                    parts.pop();
                    str='-'+str;
                }
                parts.push({type:'number',name:str});
            }
        }
        capture=[];
        if(input[pos]=='{'){
            let lastpart=parts[parts.length-1];
            if(lastpart!=undefined&&lastpart.type=='cast'){
                //inline struct creation
                lastpart.type="struct";
                let skip=(new source_parser('')).skipDepthf(input,pos);
                lastpart.args=input.substring(pos+1,skip);
                pos=skip+1;
            }
        }else if("'\"".includes(input[pos])){
            let parser=new source_parser('');
            let pos2=parser.parseString(input,pos);
            if(pos2==false)throw new Error();
            pos2++;
            parts.push({type:'string',name:input.substring(pos,pos2)});
            pos=pos2;
        }else if(input[pos]=='['){
            //check for string
            pos=simpleregex(input,["r*"," \t","r*","'\""],pos,capture);
            if(capture[1]!=""){
                pos=simpleregex(input,["nr*",capture[1]],pos,capture);
                if(capture[0]!='')parts.push({type:'string',name:capture[2].trim()});
            }
            //go to the end
            capture=[];
            if(input[pos]=='[')pos++;
            pos=simpleregex(input,["nr*","]"],pos,capture);
            if(capture[0]!=''){
                //test if is a number
                const variable=capture[0].trim();
                let i=0;
                i=simpleregex(variable,["r+",'0123456789','os','.','r*','0123456789'],i);
                if(i!=false&&i==variable.length){
                    if(variable.includes('.')){
                        throw new Error("Floats are incorrect in the context of a variable digging");
                    }
                    parts.push({type:'number',name:variable});
                }else{
                    parts.push({type:'variable',name:variable});
                }
                pos++;
            }
        }else if(input[pos]=='.'){
            pos++;
        }else if('*/+-'.includes(input[pos])){
            parts.push({type:'math',name:input[pos]});
            pos++;
        }
    }
    return parts;
}
function resolvetype(typename,variableList){
    let variable=variableList[typename];
    if(variable==undefined){
        if(defaultTypeParts.includes(typename)){
            return [typename,[]];
        }
        throw new Error("variable "+typename+" undefined");
    }
    while(variable.type=='alias'){
        variable=variable.aliasof;
    }
    let type;
    let fields=[];
    switch(variable.type){
        case "type":{
            switch(variable.subtype){
                case "enum":{
                    type='int';
                }break;
                case "struct":{
                    type=variable.name;
                    fields=variable.fields;
                }break;
                case "direct":{
                    type=variable.name;
                }break;
            }
        }break;
        case "value":{
            type=variable.subtype;
        }break;
        case "function":{
            type="void *";
        }break;
        default:{
            throw new Error("can not determine type string of "+JSON.stringify(variable)+' as requested by '+typename);
        }
    }
    return [type,fields];
}

/** compiles variable parts to a digging value
 * @param {string} variable
 * @param {string | []} targetType
 * @param {{string:{}}} [variableList]
 * @return {string}
 */
export function resolveVariable(variableParts,targetType,variableList){
    //first is always an existing variable
    //Then in loop eather: [0],[""],.asd,(cast)
    if(variableParts.length==0){
        return '';
    }
    let resolved=variableParts[0].name;
    let type,fields;
    let parti=0;
    function typeCompare(typeA,typeB){
        //Decides what the target type should be to compare variables
        let typeAParts=type.split(" ");
        let typeBParts=targetType.split(" ");
        let endA=typeAParts.length-1;
        let endB=typeBParts.length-1;
        //ignore type parts that are identical from back
        while(endA>=0&&endB>=0&&typeAParts[endA]==typeBParts[endB]){
            endA--;endB--;
        }
        if(endA==0&&endB==0){
            return targetType;
        }

        let startA=0;
        let startB=0;
        while(startA<endA&&startB<endB&&typeAParts[startA]==typeBParts[startB]){
            startA++;startB++;
        }
        typeAParts=typeAParts.slice(startA,endA);
        typeBParts=typeBParts.slice(startB,endB);


        //For now, handles only pointers
        let refcountA=0;
        startA=0;
        startB=0;
        while(typeAParts[startA]=='*')startA++;
        while(typeBParts[startB]=='*')startB++;
        //TODO: if beneficial, try to simplify types

    }
    function typeAdd(typeA,typeB){
        //Returns what type results from applying math operations to two variables
        //adding any number to a pointer results in that poiner shifted
        if(typeA.endsWith('*'))return typeA;
        if(typeB.endsWith('*'))return typeB;
        //every number type has some mantisa and reminder value
        //the idea is to collect both and find the most appropariate casting at the end
        let typeinfoA=numMantissa[typeA];
        if(typeinfoA==undefined)throw new Error("Unresolved numerical type "+typeA);//TODO: resolve more types
        let typeinfoB=numMantissa[typeB];
        if(typeinfoB==undefined)throw new Error("Unresolved numerical type "+typeB);
        typeinfoA[0]=Math.max(typeinfoA[0],typeinfoB[0]);
        typeinfoA[1]=Math.max(typeinfoA[1],typeinfoB[1]);
        return mantisaNum[JSON.stringify(typeinfoA)];
    }
    function init(){
        const part=variableParts[parti];
        if(part.type=='function'){
            const fn=variableList[part.name];
            const args = compilefunctionargs(fn,part.args,variableList);
            resolved=`${part.name}(${args.join(',')})`;
            parti++;
            if(fn.returnType.endsWith("*")){
                type=fn.returnType;
                fields=[];
            }
            [type,fields]=resolvetype(fn.returnType,variableList);
        }else if(part.type=='child'){
            let gettype=[];
            let res=resolveVariable(part.name,gettype,variableList);
            type=gettype[0];
            fields=[];
            resolved=`(${res})`;
            parti++;
        }else if(part.type=='struct'){
            type=part.name;
            fields=[];
            resolved=`(${part.name}){${part.args}}`;
            parti++;
        }else{
            resolved=part.name;
            parti++;
            if(variableParts.length==parti || part.type=='number'){
                //check for string
                if((resolved[0]=='"' || resolved[0]=="'") && resolved[0]==resolved[resolved.length-1]){
                    if(resolved.length<=3){//eg. 'c'
                        type='char';
                    }else{
                        type='char *';
                    }
                    fields=[];
                    return;
                }

                //check if a number and init type
                let i=0;
                i=simpleregex(resolved,["os",'-',"r+",'0123456789','os','.','r*','0123456789'],i);
                if(i!=false&&i==resolved.length){
                    if(resolved.includes('.')){
                        type='double';
                    }else{
                        type='long';
                    }
                    fields=[];
                    return;
                }
            }
            [type,fields]=resolvetype(resolved,variableList);
        }
    }
    init();
    let mathparts=[];

    function getarraytag(type,subtype){
        let arraytag=type.substring(subtype.length).trim();
        if(arraytag==''){
            return '';
        }
        if(arraytag=='&'){
            arraytag=1;
        }else
        if(arraytag!='*'){
            arraytag=Number(arraytag.substring(1,arraytag.length-1));//[1]
            if(isNaN(arraytag)){
                return '';
            }
        }
        return arraytag;
    }
    while(parti<variableParts.length){
        let part=variableParts[parti];
        parti++;
        //detect if the ending is a *, [], or direct type
        let subtype,arraytag='';
        //arraytag=int/*
        if(fields.length==0){
            subtype=getsubtype(type);
            if(subtype==''){
                //got to the end of type def, try resolving type before crashing
                if(type=='')debugger;
                let subresolve=resolvetype(type,variableList);
                type=subresolve[0];
                fields=subresolve[1];
                subtype=getsubtype(type);
            }
            arraytag=getarraytag(type,subtype);
        }
        switch(part.type){
            case "cast":{
                type=part.name;
                fields=[];
                resolved=`((${type})${resolved})`;
                break;
            }
            case "function":{
                const fn=variableList[part.name];
                const args = compilefunctionargs(fn,part.args,variableList);
                resolved=`${part.name}(${args.join(',')})`;
                parti++;
                if(fn.returnType.endsWith("*")){
                    type=fn.returnType;
                    fields=[];
                }
                [type,fields]=resolvetype(fn.returnType,variableList);
            }
            case "string":{
                //skip array notations to get to type by passing in [0]
                while(arraytag!=''){
                    resolved=resolved+`[0]`;
                    type=subtype;
                    subtype=getsubtype(type);
                    if(subtype==''){
                        //got to the end of type def, try resolving type before crashing
                        let subresolve=resolvetype(type,variableList);
                        type=subresolve[0];
                        subtype=getsubtype(type);
                        fields=subresolve[1];
                    }else{
                        debugger;
                    }
                    if(fields.length>0){
                        arraytag='';
                    }else{
                        arraytag=getarraytag(type,subtype);
                    }
                }
            }
            case "variable":{
                //get the variable directly
                if(part.type=='variable'){
                    resolved=resolved+`[${part.name}]`;
                    if(fields.length>0){
                        //TODO: implement field.child handling
                        type=fields[0].type;//Take first one since it is dynamic
                        fields=[];
                    }else{
                        type=subtype;
                    }
                }else{
                    let i=simpleregex(part.name,["r+",azZ,"r*",azZ0],0);
                    if(i==part.name.length){
                        resolved=resolved+`.${part.name}`;
                    }else{
                        resolved=resolved+`["${part.name}"]`;
                    }
                    let field=fields.find(a=>a.name==part.name);
                    if(field==undefined){
                        throw new Error(`field ${part.name} is not recognised`);
                    }
                    type=field.type;
                    fields=field.child||[];
                }
            }break;
            case "number":{
                if(fields.length>0){
                    throw new Error("Number as field param is not supported");
                }
                //check if we have either [4] or * at the end
                if(arraytag!='*' && part.name>=arraytag){
                    throw new Error("Array index exceeds definition");
                }
                resolved=resolved+`[${part.name}]`;
                type=subtype;
            }break;
            case "math":{
                mathparts.push({name:resolved,type,math:part.name});
                if(variableParts.length<=parti){
                    throw new Error("assignment can not end on "+part.name);
                }
                init();
            }break;
        }
    }
    //colapse math
    if(mathparts.length>0){
        for(let i=mathparts.length-1;i>=0;i--){
            const part=mathparts[i];
            resolved=part.name+part.math+resolved;
            type=typeAdd(part.type,type);
        }
    }

    //resolve type coalation
    //When we finished digging, its time to add some flavouring to allign with target type
    //In the future, look deeper to allow autocasts, but for now, user should have casted it
    //only try to * or & to get the same number of references
    if(Array.isArray(targetType)){
        targetType[0]=type;//what type is needed? you tell me!
        return resolved;
    }
    resolved=cast(type,resolved,targetType );
    return resolved;
}

//This class offers a scope that keeps track of multiple CodeToken's or CodeScope's and their variables
//Generation shall be context-aware!
//  [if,scope] should be inline
//  [if1,scope,if2,scope] should treat if2 as elseif/else if if2 it contains !f1.condition
//  [declaration,call] and [declaration,assignment] should be inlined
//  Call that saves to a variable is always [declaration,call]. The code generator handles when the declaration header is applied
export class CodeScope {
    type='scope';
    /** @type {[CodeToken|CodeScope]} */
    tokenList=[];
    constructor(parent,type='scope') {
        this.parent=parent;
        this.tokenId=globalTokenId;
        this.type=type;//scope or section
        globalTokenId++;
    }
    /**
     * @param {int} [tokennum]
     * @param {int} [indent]
     * @param {Object.<string, string>} [variables]
     */
    toStringToken(tokennum=0,indent=0,variables={}){
        let token=this.tokenList[tokennum];
        tokennum++;
        const txtIndend="\t".repeat(indent);
        let str;
        switch(token.type){
            case "if":{
                //must have variables: if,scope,scope..
                let ifchain=`${txtIndend}if`;
                str='';
                const conditions=token.text;
                for(let i=0;i<conditions.length;i++){
                    const nexttoken=this.tokenList[tokennum];
                    if(nexttoken.type!='scope')break;
                    tokennum++;
                    let condition='';
                    let pos=0;
                    while(pos!==false){
                        let capture=[];
                        pos=simpleregex(conditions[i],["nr*","<>!=|&",'r+','<>!=|&'],pos,capture);
                        condition+=resolveVariable(getVariableParts(capture[0],variables),[],variables);
                        if(pos!==false){
                            condition+=capture[1];
                        }
                    }
                    if(condition==''){
                        str+=`else{\n${nexttoken.toString(indent+1,variables)}${txtIndend}}`;
                        break;
                    }
                    str+=`${ifchain}(${condition}){\n${nexttoken.toString(indent+1,variables)}${txtIndend}}`;
                    ifchain='else if';
                }
                if(conditions.length!=0){
                    str+="\n";
                }
                break;
            }
            case "loop":{
                let nexttoken=this.tokenList[tokennum];
                if(nexttoken.type!=='scope')break;
                tokennum++;
                const t=token.text;
                if(t['var']==undefined){
                    //while
                    str=`${txtIndend}while(${t['to']}){\n${nexttoken.toString(indent+1,variables)}${txtIndend}}\n`;
                }else{
                    //for
                    const to=typeof(t['to'])!='string'?t['to']:resolveVariable(getVariableParts(t['to'],variables),[],variables);
                    str=`${txtIndend}for(${t['var']}=${t['from']};${t['var']}<${to};${t['var']}++){\n${nexttoken.toString(indent+1,variables)}${txtIndend}}\n`;
                }
                break;
            }
            case "guard":{
                let nexttoken=this.tokenList[tokennum];
                if(nexttoken.type!='scope')break;
                tokennum++;
                str =`${txtIndend}#ifndef ${token.text}\n${txtIndend}\t#define ${token.text}\n${nexttoken.toString(indent+1,variables)}\n${txtIndend}#endif //${token.text}`;
                break;
            }
            case "line":{
                str=token.text+";\n";
                break;
            }
            case "return":{
                let v=token.text.variable;
                if(v!=='' && v!=undefined)v=' '+String(v);
                str=`${txtIndend}${token.text.type}${v};\n`;
                break;
            }
            case "comment":{
                if(token.text.includes("\n")){
                    str='//'+token.text+"\n";
                }else{
                    str='/*'+token.text.replaceAll('*/','*\\/')+"*/\n";
                }
                break;
            }
            case "declare":{
                const t=token.text;
                let capture=[];
                simpleregex(t.name,['r*','* ()','r+',azZ0],0,capture);//TODO: check if capture[0] contains anything ever

                let rettype;//var is type but var[i].arg is rettype
                let retname;//name is var(Mesh *)[0] but retname is ((Mesh *)var)[0]
                const name_parts=getVariableParts(t.name,variables);
                if(name_parts.length==1){
                    retname=t.name;
                    rettype=t.subtype;
                }else{
                    //resolve call result output type
                    const subtype_box=[];
                    retname=resolveVariable(name_parts,subtype_box,variables);
                    rettype=subtype_box[0];
                }

                const name=capture[1];
                let doDefine=variables[name]==undefined;
                if(doDefine){
                    variables[name]=t;
                }
                if(t.implicit)break;
                let doAssign='';
                let nexttoken=this.tokenList[tokennum];
                if(nexttoken!==undefined && nexttoken.type=='assignlist'){
                    const nt=nexttoken.text;
                    doAssign=`={\n${txtIndend}\t${nt.initial.join(`,\n${txtIndend}\t`)}\n${txtIndend}}`;
                    tokennum++;
                }else if(nexttoken!==undefined && nexttoken.type=='assign'  && nexttoken.text.name==t.name){
                    const nt=nexttoken.text;
                    let capture=[];
                    const pos = simpleregex(nt.initial,["r*",' ',"s",nt.name,"r*",' ','os','-','os','+'],0,capture);//optimize +=,-=
                    const add = pos==false?'':capture[3]+capture[4];//- or +
                    let initial=add==''?nt.initial:nt.initial.substring(pos);
                    if(initial!==''){
                        if(initial=='NULL'||String(initial).includes('{')){
                            //TODO: handle classes
                            doAssign='='+add+initial;
                        }else{
                            if(add==''){
                                doAssign=add+'='+resolveVariable(getVariableParts(initial,variables),rettype,variables);
                            }else{
                                //Adding to (void *) should not cast int to pointer
                                doAssign=add+'='+resolveVariable(getVariableParts(initial,variables),[],variables);
                            }
                        }
                    }

                    tokennum++;
                }else if(nexttoken!==undefined && nexttoken.type=='call' && nexttoken.text.set==t.name){//call and name is correct
                    const nt=nexttoken.text;
                    let fn = variables[nt.name];
                    if(fn==undefined){
                        let gettype=[];
                        resolveVariable(getVariableParts(nt.name,variables),gettype,variables);
                        fn = variables[gettype[0]];
                        if(fn==undefined)throw Error("Function "+nt.name+" is not recognized");
                    }
                    //If defined name is something like arr[i] it will have multiple parts
                    //Name will not have casts or function calls so dont safeguard aganist that
                    const name_parts=getVariableParts(t.name,variables);
                    let cast=fn.returnType!=rettype?`(${rettype})`:'';
                    globalThis.fnc=globalThis.fnc!=undefined?globalThis.fnc+1:0;
                    //console.log(globalThis.fnc);
                    const args = compilefunctionargs(fn,nt.args,variables);
                    doAssign=`=${cast}${nt.name}(${args.join(',')})`;
                    tokennum++;
                }
                if(doDefine){
                    let size='';
                    while(rettype.endsWith(']')){
                        let pos=rettype.lastIndexOf('[',rettype.length);
                        size=size+rettype.substring(pos);
                        rettype=rettype.substring(0,pos).trim();
                    }
                    let isstatic=t.props.static==true?'static ':'';
                    str=`${txtIndend}${isstatic}${rettype} ${retname}${size}${doAssign};\n`;
                }else{
                    if(doAssign!==''){
                        str=`${txtIndend}${retname} ${doAssign};\n`;
                    }else{
                        str=undefined;
                    }
                }
                break;
            }
            case 'assign':{
                let parts=[getVariableParts(token.text.name,variables),getVariableParts(token.text.initial,variables)];
                let leftType=[];
                let left=resolveVariable(parts[0],leftType,variables);
                str=`${txtIndend}${left}=${resolveVariable(parts[1],leftType[0],variables)};\n`;
                break;
            }
            case "call":{
                const t=token.text;
                const fn = variables[t.name];
                globalThis.fnc=globalThis.fnc!=undefined?globalThis.fnc+1:0;
                //console.log(globalThis.fnc);
                if(t.args.includes('da_dataSize'))debugger;
                const args = compilefunctionargs(fn,t.args,variables);
                str=`${txtIndend}${t.name}(${args.join(',')});\n`;
                break;
            }
            case 'function':{
                const t=token.text;
                variables[t.name]=t;
                const statics=t.isStatic?'static ':'';
                const nexttoken=this.tokenList[tokennum];tokennum++;
                const args=[];
                for(let arg of t.args){
                    if(!arg.type.endsWith(']')){
                        args.push(arg.type+' '+arg.name);
                    }else{
                        const i=arg.type.indexOf('[');
                        args.push(arg.type.substring(0,i-1)+' '+arg.name+arg.type.substring(i));
                    }

                }
                str=`${txtIndend}\n${txtIndend}${statics}${t.returnType} ${t.name}(${args.join(',')}){\n${nexttoken.toString(indent+1,variables)}${txtIndend}}\n`;
                break;
            }
            case "scope":{
                str=`{\n${token.toString(indent+1,variables)}\n${txtIndend}}\n`;break;
            }
            case "section":{
                str=token.toString(indent,variables);break;
            }
            case "include":{
                if(token.text.implicit)break;
                if(token.text.name!=''){
                    str=`${txtIndend}#include <${token.text.name}>\n`;
                }
                token._getVariables(variables);
            }break;
        }
        return [str,tokennum];
    }
    /**
     * @param {int} [indent]
     * @param {Object.<string, string>} [variables]
     */
    toString(indent=0,variables) {
        //Go through all tocens and call tostring with indent
        if(variables==undefined){
            variables={};
            this._getVariables(variables,0);
        }else if(this.type=='scope'){
            //variables from child scope dont leak upwards
            variables=structuredClone(variables);
            //but that does not apply to a code section
        }
        let str="";
        let tokennum=0;
        while(tokennum<this.tokenList.length){
            let v = this.toStringToken(tokennum,indent,variables);
            tokennum=v[1];
            if(v[0]!=undefined)str+=v[0];
        }

        return str;
    }
    /**
     * @param {CodeToken | CodeScope} token
     * @param {int} [offset]
     */
    addToken(token,offset){
        //insert token at the end
        if(token.type=='declare'&&typeof(token.text.type)!='string')debugger;
        if(offset==undefined){
            this.tokenList.push(token);
            return;
        }
        //(<0) insert token at end-offset
        while(offset<0)offset+=this.tokenList.length;
        //(>=0) insert token at offset
        let i=this.tokenList.length;
        while(i>offset){
            this.tokenList[i]=this.tokenList[i-1];
            i--;
        }
        this.tokenList[offset]=token;
    }

    /**
     * @param {int} tokenId
     */
    getTokenOffset(tokenId){
        for(let i=0;i<this.tokenList.length;i++){
            if(this.tokenList[i].tokenId==tokenId)return i;
        }
    }
    /**
     * @param {Object} into
     * @param {int} [offset]
     * @param {boolean} [backward]
     */
    _getVariables(into,offset,backward=true){
        //if index, go back in history
        if(offset==undefined)offset=this.tokenList.length;
        //(<0) insert token at end-offset
        while(offset<0)offset+=this.tokenList.length;
        //(>=0) insert token at offset
        if(backward&&this.parent!=undefined){
            this.parent._getVariables(into,this.parent.getTokenOffset(this.tokenId));
        }
        for(let i=0;i<offset;i++){
            const token=this.tokenList[i];
            if(token.type=='scope'){
                continue;
            }
            this.tokenList[i]._getVariables(into,undefined,false);
        }
    }
    getVariables(){
        const v={};
        this._getVariables(v);
        return v;
    }

    //creates variable name that is avaliable
    /**
     * @param {string} [hint]
     * @param {int} [offset]
     */
    allocVariable(hint='v',offset){
        const variables={};
        this._getVariables(variables,offset);
        if(variables[hint]==undefined)return hint;
        let i=0;
        while(variables[hint+i]!==undefined){
            i++;
        }
        return hint+i;
    }
    //if(i==0,(scope)=>{},(scope)=>{})
    /**
     * @param {string|Array<string>} conditions
     * @param {...(ctx:CodeScope)=>{}} fn
     */
    if(conditions,...fn){
        //tip: (empty conditions list is allowed)
        if(typeof(conditions)=='string')conditions=[conditions];
        if(conditions.length!=fn.length)debugger;
        let scope;
        let maxlength=Math.min(conditions.length,fn.length);
        for(let i=0;i<maxlength;i++){
            //else must be last
            if(conditions[i]==''){
                maxlength=i+1;
                break;
            }
        }
        if(maxlength<conditions.length){
            conditions=conditions.slice(0,maxlength);
        }
        const iftoken = new CodeToken('if',conditions);
        this.addToken(iftoken);
        for(let i=0;i<maxlength;i++){
            scope= new CodeScope(this);
            this.addToken(scope);
            fn[i](scope);
        }
        return iftoken.tokenId;
    }
    //This is a way to edit 'if' after the fact

    /**
     * @param {string} condition
     * @param {(ctx:CodeScope)=>{}} fn
     * @param {int} [tokenId]
     */
    elsif(condition,fn,tokenId){
        let tokennum;
        if(tokenId==undefined){
            //get last token, good enough most of the time
            tokennum=this.tokenList.length-1;
            let token=this.tokenList[tokennum];
            while(token.type=='scope'){
                tokennum--;
                token=this.tokenList[tokennum];
            }
            if(token.type!=='if')return false;
        }else{
            //id is provided
            for(let i=this.tokenList.length-1;i>=0;i--){
                let token=this.tokenList[i];
                if(token.type!=='function')continue;
                if(token.tokenId==tokenId){
                    tokennum=i;
                    break;
                }
            }
            if(tokennum==undefined){
                //failed? maybe in sub-scope?
                for(let i=this.tokenList.length-1;i>=0;i--){
                    let token=this.tokenList[i];
                    if(token.type!=='scope')continue;
                    let result =  token.elsif(condition,fn,tokenId);
                    if(result==true)return true;
                }
                return false;
            }
        }
        let token=this.tokenList[tokennum];
        token.text.push(condition);

        let scope= new CodeScope(this);
        this.addToken(scope,tokennum+token.text.length);
        fn(scope);
        return true;
    }
    //switch(i,[0,1,2],(case,scope)=>{})
    /**
     * @param {string|int} variable
     * @param {Array<string|int>} cases
     * @param {(ctx:CodeScope,i:string|int)=>{}} fn
     */
    switch(variable,cases=[],fn){
        let scope;
        let conditions=[];
        for(let i=0;i<cases.length;i++){
            if(cases[i]=='default'){
                conditions.push('');
            }else{
                conditions.push(String(cases[i]).split('||').map(c=>`${variable}==${c}`).join('||'));
            }
        }
        this.addToken(new CodeToken('if',conditions));
        for(let i=0;i<cases.length;i++){
            scope= new CodeScope(this);
            this.addToken(scope);
            fn(scope,cases[i]);
        }
    }
    /**
     * @param {string|int} from
     * @param {string|int} to
     * @param {(ctx:CodeScope,i:string)=>{}} fn
     */
    for(from,to,fn){
        let loopvariable=this.allocVariable('i');
        //TOOD: check type of from, to if they exist and auto-cast
        this.addToken(new CodeToken('declare',{type:'value',props:{},subtype:'int',name:loopvariable}));
        this.addToken(new CodeToken('loop',{var:loopvariable,from,to}));
        let scope= new CodeScope(this);
        this.addToken(scope);
        fn(scope,loopvariable);
    }
    /**
     * @param {string|int} to
     * @param {(ctx:CodeScope)=>{}} fn
     */
    while(to,fn){
        this.addToken(new CodeToken('loop',{to}));
        let scope= new CodeScope(this);
        this.addToken(scope);
        fn(scope);
    }
    /**
     * @param {string} guard
     * @param {(ctx:CodeScope)=>{}} [fn]
     * @return CodeScope
     */
    header(guard, fn) {
        this.addToken(new CodeToken('guard',guard));
        let scope= new CodeScope(this);
        this.addToken(scope);
        if(fn)fn(scope);
        return scope;
    }
    /** An invisible code separation that perserves varialbes
     * @param {(ctx:CodeScope)=>{}} [fn]
     * @return CodeScope
     */
    section(fn) {
        let scope= new CodeScope(this,'section');
        this.addToken(scope);
        if(fn)fn(scope);
        return scope;
    }
    /**
     * @param {string} [variable]
     */
    return(variable){
        this.addToken(new CodeToken('return',{type:'return',variable}));
    }
    break(){
        this.addToken(new CodeToken('return',{type:'break',variable:''}));
    }
    continue(){
        this.addToken(new CodeToken('return',{type:'continue',variable:''}));
    }
    /**
     * @param {string} text
     */
    comment(text){
        this.addToken(new CodeToken('comment',text));
    }
    /**
     * @param {string} name
     * @param {[{type:string,name:string,mode:'var'|'struct'|'function'|'enum'|'alias'|'define'}]} vars
     * @param {Array<string>} defines
     */
    include(name,vars,defines=[],implicit=false) {
        //TODO: we could track usages and remove include if unused
        for(let define of defines){
            this.addToken(new CodeToken('line',`#define ${define} `));
        }
        this.addToken(new CodeToken('include',{name,vars,implicit}));
        //After add token to allow for backwards resolve
        let varsmap={};
        this._getVariables(varsmap);
        let aliases={};
        let aliasesTODO=[];
        for(let key in varsmap){
            const v=varsmap[key];
            if(v.type=='alias'){
                aliasesTODO.push(v);
            }
        }
        let i=0;
        varsloop: while(i<aliasesTODO.length){
            let v =aliasesTODO[i];
            i++;
            //we have to resolve type alias here,
            //an alias will be a type pointing at another type or alias or combination
            let filtered_type=subset(v.aliasof.split(" "),defaultTypeParts,true);
            if(filtered_type.join('').length==0){
                //an easy direct type alias
                varsmap[v.name] = {type:'type',subtype:'direct',name:v.name,src:v.aliasof};
                aliases[v.name] = varsmap[v.name];
                continue;
            }
            let aliased_types=[];
            for(let keyword of filtered_type){
                if(keyword=='')continue;
                //if any keyword is not yet resolved, leave this as alias
                let keyvar=varsmap[keyword];
                if(keyvar==undefined){
                    continue varsloop;
                }
                if(keyvar.type=='alias'){
                    //alias of alias
                    if(aliasesTODO.length+1==v.lastlength){
                        continue varsloop;//safeguard aganist infinite loops
                    }
                    aliasesTODO.push({type:'alias',name:v.name,aliasof:v.aliasof,lastlength:aliasesTODO.length+1});
                    continue varsloop;
                }
                aliased_types.push(keyvar);
            }
            let newtype={type:'type',subtype:'direct',name:v.name,src:v.aliasof,props:{}, aliased_types};
            varsmap[v.name] = newtype;
            aliases[v.name] = varsmap[v.name];
        }
        //apply aliases
        for(let key in vars){
            let v=vars[key];
            let alias=aliases[v.name]
            if(alias!=undefined){
                vars[key]=alias;
            }
        }
    }
    /**
     * @param {string} name
     * @param {Array<string>} [args]
     * @param { {type:string,name:string} } [returnVal]
     */
    call(name,args=[],returnVal){
        let values={name,args};
        if(returnVal!=undefined){
            if(returnVal.type==undefined||returnVal.name==undefined)throw new Error("bad usage");
            this.addToken(new CodeToken('declare',{type:'value',subtype:returnVal.type,props:{},name:returnVal.name,implicit:false}));
            values.set=returnVal.name;
        }
        this.addToken(new CodeToken('call',values));
    }
    /**
     * @param {string} returnType
     * @param {string} name
     * @param {[{name:string,type:string}]} args
     * @param {boolean} isStatic
     * @param {(ctx:CodeScope)=>{}} fn
     */
    function(returnType,name,args,isStatic=false,fn){
        this.addToken(new CodeToken('function',{type:'function',returnType,name,args,isStatic}));
        let scope= new CodeScope(this,'scope');
        //Implicitly declare parameters as first tokens of its scope
        for(let arg of args){
            scope.addToken(new CodeToken('declare',{type:'value',subtype:arg.type,props:{},name:arg.name,implicit:true}));
        }
        this.addToken(scope);
        fn(scope);
    }
    /**
     * @param {string} type
     * @param {string} name
     * @param {string} initial
     */
    add(type,name,initial){if(arguments.length!=3)debugger;this.declare(type,name,`${name}+${initial}`)};
    /**
     * @param {string} type
     * @param {string} name
     * @param {string} initial
     */
    sub(type,name,initial){if(arguments.length!=3)debugger;this.declare(type,name,`${name}-${initial}`)};
    /**
     * @param {string} type
     * @param {string} name
     * @param {string|Array<string>} [initial]
     * @return {undefined|CodeToken}
     */
    declare(type,name,initial,props={}){
        if(String(initial).startsWith('*'))debugger;
        if(type.includes("*")&&!type.includes(" *"))debugger;
        if(type.startsWith('static ')){
            props.static=true;
            type=type.substring('static '.length).trim();
        }
        let token = this.addToken(new CodeToken('declare',{type:'value',subtype:type,name,props,implicit:false}));
        if(initial==undefined)return token;

        if(Array.isArray(initial)){
            token = new CodeToken('assignlist',{name,initial});
        }else{
            token = new CodeToken('assign',{name,initial});
        }
        this.addToken(token);
        return token;
    }
    /** use declare when possible, raw assign allows setting deep properties
     * @param {string} name dot(.) delimited nesting to the set property
     * @param {string} initial what to set property to
     */
    assign(name,initial){
        if(String(initial).startsWith('('))debugger;
        this.addToken(new CodeToken('assign',{name,initial}));
    }

    /** Get token before this one
     * @return {undefined|CodeToken|CodeScope}
     */
    previous(){
        if(this.parent==undefined)return undefined;
        return this.parent.tokenList[this.parent.getTokenOffset(this.tokenId)-1];
    }
}