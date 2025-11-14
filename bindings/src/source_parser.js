import * as fs from "./fs.js";
let defined=globalThis.config.defined;
export const az='abcdefghijklmnoprstuvqwxyz';
export const aZ='ABCDEFGHIJKLMNOPRSTUVQWXYZ';
export const a0='1234567890';
export const azZ=az+aZ;
export const azZ0=az+aZ+a0+'_-';
export const defaultTypeParts =['int_least16_t','int_fast16_t','int_least8_t','int_fast8_t','unsigned', 'uint64_t', 'uint32_t','volatile','restrict','uint16_t', 'int32_t', 'int64_t','wchar_t','int16_t','uint8_t','int8_t', 'signed', 'double', 'short', 'float', 'const', 'bool', 'char', 'long', 'int','*', '&', '...'];
const implicit_attrs=["unsigned","const","inline","static","_Thread_local"];
function isType(input){return input.split(' ').filter(a=>a!=''&&!defaultTypeParts.includes(a)).join('').length==0}
//text detection
export function lookBackward(input,str,pos=input.length){
    let i=str.length-1;
    while(i>=0){
        if(pos<0 || input[pos]!==str[i]){return false;}
        i--;pos--;
    }
    return true;
}
export function lookForward(input,str,pos=0){
    let i=0;
    while(i<str.length){
        if(pos>=input.length || input[pos]!==str[i]){return false;}
        i++;pos++;
    }
    return true;
}

/**
 * @param input
 * @param test
 * @param pos
 * @param capture
 * @return {number|false}
 */
export function simpleregex(input='',test=[],pos=0,capture=[]){
    //very simple regex replacement for long text, since regex always starts with begining of string
    let i=0;
    let tmp;
    while(input.length>pos && test.length>i){
        let format=test[i];
        let opt=test[i+1];
        let back=1;
        if(format[0]==='b'){
            back=-1;
            format=format.substring(1);
        }
        let start=pos;
        switch (format) {
            case 's':{
                if(back===1?lookForward(input,opt,pos):lookBackward(input,opt,pos)){
                    tmp=pos+opt.length*back;
                    if(back==1){
                        capture.push(input.substring(pos,tmp));
                    }else{
                        capture.push(input.substring(pos+1,tmp+1));
                    }
                    pos=tmp;
                    break;
                }else{return false;}
            }
            case 'os':{
                if(back===1?lookForward(input,opt,pos):lookBackward(input,opt,pos)){
                    tmp=pos+opt.length*back;
                    if(back==1){
                        capture.push(input.substring(pos,tmp));
                    }else{
                        capture.push(input.substring(pos+1,tmp+1));
                    }
                    pos=tmp;
                }else{
                    capture.push('');
                }
                break;
            }
            case 'ns':{
                let f=back===1?lookForward:lookBackward;
                let tmp=pos;
                while(input.length>tmp){
                    if(f(input,opt,tmp)){
                        if(back==1){
                            capture.push(input.substring(pos,tmp));
                        }else{
                            capture.push(input.substring(pos+1,tmp+1));
                        }
                        pos=tmp;
                        break;
                    }else{
                        tmp+=back;
                    }
                }
                break;
            }
            case 'r+':{
                if(opt.includes(input[pos])){
                    pos+=back;
                }else{return false;}
            }
            case 'r*':{
                while(input.length>pos && opt.includes(input[pos])){
                    pos+=back;
                }
                if(back==1){
                    capture.push(input.substring(start,pos));
                }else{
                    capture.push(input.substring(start+1,pos+1));
                }
                break;
            }
            case 'nr+':{
                if(!opt.includes(input[pos])){
                    pos+=back;
                }else{return false;}
            }
            case 'nr*':{
                while(input.length>pos && pos>=0 && !opt.includes(input[pos])){
                    pos+=back;
                }
                if(back==1){

                    capture.push(input.substring(start,pos));
                }else{
                    capture.push(input.substring(start+1,pos+1));
                }
                break;
            }
        }
        i+=2;
    }
    //EOS return
    while(test.length>i){
        let format=test[i];
        if(format[0]==='b'){
            format=format.substring(1);
        }
        switch (format) {
            case 's':return false;
            case 'os':capture.push('');break;
            case 'ns':capture.push('');break;
            case 'r+':return false;
            case 'r*':capture.push('');break;
            case 'nr+':return false;
            case 'nr*':capture.push('');break;
        }
        i+=2;
    }
    return pos;
}
export class source_parser {
    //sets (avoids re-declaration)
    nameSet={};
    //parsed
    functions=[];
    staticData=[];
    enums=[];
    structs=[];
    unions=[];
    callbacks=[];
    aliases=[];
    defines=[];
    //Raw detection
    comments=[];
    //define
    defineName(name,type,contents){
        if(name===''||name===undefined){
            this[type].push(contents);
            return;
        }
        let info=this.nameSet[name];
        if(info==undefined){
            if(contents==undefined)return;
            this[type].push(contents);
            this.nameSet[name]=[this[type].length-1,type];
            return;
        }
        if(info[1]==type && contents!=undefined){
            this[type][info[0]]=contents;
            return;
        }
        let oldid=info[0];
        let oldtype=info[1];
        this[oldtype].splice(oldid,1);
        for(let name in this.nameSet){
            if(this.nameSet[1]==oldtype && this.nameSet[0]>oldid){
                this.nameSet[0]--;//spliced aliases, so shift nameSet
            }
        }
        if(contents==undefined)return;
        this[type].push(contents);
        this.nameSet[name]=[this[type].length-1,type];
    }
    println(input,pos){
        //debugging function for printing lines
        if(input[pos]=="\n")pos++;
        let start=simpleregex(input,["bnr*","\n"],pos);
        let end=simpleregex(input,["nr*","\n"],pos);
        console.log(input.substring(start+1,pos)+'||'+input.substring(pos,end));
    }
    //Text filtration
    normalizeType(type=''){
        let ret=type.replaceAll("*", " * ").replaceAll('[',' [').replace(new RegExp("\\s+",'g'),' ').trim();
        if(ret.startsWith('struct ')){
            ret=ret.substring(7);
        }else
        if(ret.startsWith('enum ')){
            ret=ret.substring(7);
        }
        return ret;
    }
    removeTrap(input,removeString=true,removeComment=true,linecount=0){
        //Filter out strings or comments
        let ret='';
        let start=0;
        let pos=0;
        while(pos<input.length){
            let lastpos=pos;
            switch(input[pos]){
                case "'":
                case '"':{
                    let tmp=this.parseString(input,pos);
                    if(removeString){
                        ret+=input.substring(start,pos);
                    }else{
                        ret+=input.substring(start,tmp);
                    }
                    start=tmp;
                    pos=tmp;
                    break;
                }
                case "/":{
                    let tmp=this.parseComment(input,pos,true,linecount);
                    if(removeComment){
                        ret+=input.substring(start,pos);
                    }else{
                        ret+=input.substring(start,tmp);
                    }
                    start=tmp;
                    pos=tmp;
                    break;
                }
                case "\n":linecount++;break;
            }
            if(lastpos===pos)pos++;
        }
        ret+=input.substring(start,pos);
        return ret;
    }
    //deep text parsing
    /**
     * @param {string} word
     * @param {string[]} args
     * @param { {} } props
     * @return {string}
     */
    cleanword(word,args,props){
        if(word=='__attribute__'){
            let argtokens=[];
            let argspos=1;//enclosed in (()) instead of ()
            while(argspos<args.length-1){
                //attributes are a attr,attr() list
                argspos=simpleregex(args,['r*',' \t','r+',azZ0,'r*',' \t','os',"("],argspos,argtokens);
                if(argspos==false)return word;
                let attributes=true;
                //attributes can have parameters
                if(argtokens[3]=='('){
                    let argend=this.skipDepthf(args,argspos);
                    attributes=args.substring(argspos,argend).split(',').map(a=>a.trim());
                    argspos=argend+1;
                }
                props[argtokens[1]]=attributes;
                argspos=simpleregex(args,['r*',' \t','os',","],argspos);
            }
            return "";
        }
        if(args!=undefined){
            //word has to be a defined function!
            const def=defined[word];
            if(def==undefined)return `${word}(${args})`;
            if(def.type=='function'){
                args=args.split(',').map((a,i)=>{a=a.trim();return [def.content.args[i],a.trim()]});
                word = this.safeEval(def.content.body,Object.fromEntries(args));
            }else{
                return word;
            }
            let pos=word.length-1;
            let words=[];
            while(pos>0){
                const w=this.getwordb(word,pos,props);
                if(w==false)return word;
                pos=w[0];
                if(w[1].length>0)words.push(w[1]);
            }
            return words.join(' ');
        }
        if(implicit_attrs.includes(word)){
            props[word]=true;
            return "";
        }
        //last, the word may have been redefined earlier
        const def=defined[word];
        if(def==undefined)return word;
        if(def.type=='undefined'){
            word = def.content.body;
            let pos=word.length-1;
            let words=[];
            while(pos>0){
                const w=this.getwordb(word,pos,props);
                if(w==false)return word;
                pos=w[0];
                if(w[1].length>0)words.push(w[1]);
            }
            return words.join(' ');
        }
        return word;
    }
    /**
     * @param {string} input
     * @param {number} pos
     * @param { {} } props
     * @return {false | [number,string] }
     */
    getword(input,pos,props){
        while(true){
            pos=simpleregex(input,["r*"," \t"],pos);
            switch(input[pos]){
                case "/":{
                    if(input[pos+1]=='*'){
                        pos=simpleregex(input,['ns','*/'],pos-1);
                    }else{
                        return false;
                    }
                    break;
                }
                case "(":{
                    let pos2=this.skipDepthf(input,pos);
                    return [pos2,input.substring(pos,pos2)];
                }
                default:{
                    let pos2=simpleregex(input,["r+",azZ0],pos);
                    if(pos2==false)return false;
                    let pos3=pos2;
                    let args;
                    if(input[pos2]=='('){
                        pos3=this.skipDepthf(input,pos2);
                        args=input.substring(pos2+1,pos3);
                        pos3++;
                    }
                    const word=this.cleanword(input.substring(pos,pos2),args,props);
                    pos3=simpleregex(input,["r*"," \t"],pos3);
                    return [pos3,word];
                }
            }
        }
    }
    /**
     * @param {string} input
     * @param {number} pos
     * @param { {} } props
     * @return {false | [number,string] }
     */
    getwordb(input,pos,props){
        while(true){
            pos=simpleregex(input,["br*"," \t"],pos);
            switch(input[pos]){
                case "/":{
                    if(input[pos-1]=='*'){
                        pos=simpleregex(input,['bns','/*'],pos-1);
                    }else{
                        return false;
                    }
                    break;
                }
                case ")":{
                    let pos2=this.skipDepthfb(input,pos);
                    let pos3=simpleregex(input,["br+",azZ0],pos2);
                    if(pos3==false)return false;
                    const word=this.cleanword(input.substring(pos3+1,pos2+1),input.substring(pos2+2,pos),props);
                    pos3=simpleregex(input,["br*"," \t"],pos3);
                    return [pos3,word];
                }
                default:{
                    let pos2=simpleregex(input,["br+",azZ0],pos);
                    if(pos2==false)return false;
                    const word=this.cleanword(input.substring(pos2+1,pos+1),undefined,props);
                    pos2=simpleregex(input,["br*"," \t"],pos2);
                    return [pos2,word];
                }
            }
        }
        return false;
    }
    //Parsers
    parseES(input, pos=0, save=true,linecount=[0]){
        //Resolve Encountering enum or struct (not typedef)
        let mode=input[pos]=='e'?'enum':'struct';
        let capture=[];
        let ret=simpleregex(input,['s',mode,'r+',' \t\r\n','os','{'],pos,capture);
        if(ret==false)return pos;
        let namecapture=['r*',azZ0];
        let name='';
        if(capture[2]!='{'){
            let capture2=[];
            ret=simpleregex(input,['r+',azZ0,'r*',' \t\r\n','os','{'],ret,capture2);
            if(ret==false)return pos;
            name=capture2[0];
            namecapture=['os',name];
        }
        let tmp=this.skipDepth(input,ret-1)+1;
        capture.push(input.substring(ret,tmp-1));
        ret=simpleregex(input,['r*',' \t\r\n',...namecapture,'r*',' \t\r\n','s',';'],tmp,capture);
        if(ret===false)return pos;
        if(capture[5]!='')name=capture[5];
        if(save){
            let comment='';
            if(this.comments[linecount[0]-1]!=undefined)comment=this.comments[linecount[0]-1];
            if(mode=='struct'){
                this.defineName(name,'structs',{
                    name,
                    fields: this.parseStructValues(capture[3],linecount),
                    binding:{comment,line:linecount[0]}
                });
            }else{
                this.defineName(name,'enums',{
                    name,
                    values: this.parseEnumValues(capture[3],linecount),
                    binding:{comment,line:linecount[0]}
                });
            }
        }
        return ret;
    }
    parseEnumValues(input,linecount=[0]) {
        let lastNumber = 0;
        input=this.removeTrap(input,false,true,linecount[0]);
        let values = [];//{name: en[0].trim(),value: val}
        let start=0;
        while(start<input.length-1){
            let capture=[];
            let ret=simpleregex(input,['nr*','#,('],start,capture);
            if(ret===false)return values;
            linecount[0]+=capture[0].countChar("\n");
            if(input[ret]==','||ret==input.length){
                let v=capture[0].split('=');
                let val=lastNumber+1;
                if(v.length==2){
                    v[1]=v[1].trim();
                    val=Number(v[1]);
                    if(isNaN(val)){
                        let def=defined[v[1]];
                        if(def!=undefined){
                            val=def.content.body;
                        }else{
                            val=this.safeEval(v[1],{});
                        }
                    }
                }
                lastNumber=val;
                if(v[0].trim()==''){
                    start=ret+1;
                    continue;
                }
                const value={
                    name: v[0].trim(),
                    value: val
                }
                if(this.comments[linecount[0]]!==undefined){
                    value.comment=this.comments[linecount[0]];
                }
                values.push(value);
                defined[value.name]={type:'integer',content:{name:value.name,body:value.value}};
                start=ret+1;
            }else if(input[ret]=='('){
                //Maybe we deal with some inline macro?
                let name=input.substring(start,ret).trim();
                let def=defined[name];
                if(def!=undefined){
                    if(def.type=='function'){
                        let pos3=this.skipDepthf(input,ret);
                        let args=input.substring(ret+1,pos3).split(',').map((a,i)=>{a=a.trim();return [def.content.args[i],a.trim()]});
                        input=input.substring(0,start)+this.safeEval(def.content.body,Object.fromEntries(args))+input.substring(pos3+1);
                    }else{
                        throw new Error("Known definitions other than function are not yet supported");
                    }
                }else{
                    //Not a function so it must be direct math
                    let pos3=this.skipDepthf(input,ret);
                    input=input.substring(0,ret)+this.safeEval(input.substring(ret+1,pos3),{})+input.substring(pos3+1);
                }
                continue;
            }else if(input[ret]=='#'){
                //We dont have the whole information, parse if, replace, continue
                ret=this.ifselect(input,ret,linecount[0]);
                input=this.removeTrap(ret[1],false)+input.substring(ret[0]);
                start=0;
                continue;
            }
        }
        return values;
    }
    parseStructValues(input,linecount=[0]) {
        input=this.removeTrap(input,false,true,linecount[0]);
        let values = [];
        let start=0;
        while(start<input.length-1){
            let capture=[];
            let ret=simpleregex(input,['nr+','#{;'],start,capture);
            if(ret===false)return values;
            linecount[0]+=capture[0].countChar("\n");
            if(input[ret]=='{'){
                let end=this.skipDepth(input,ret);
                start=simpleregex(input,['nr+',';'],ret,capture);
                values.push({
                    type:'struct',
                    name: capture[1].trim(),
                    child:this.parseStructValues(input.substring(ret,end),linecount)
                });
                continue;
            }else if(lookForward(input,'#if',ret)){
                //We dont have the whole information, parse if, replace, continue
                ret=this.ifselect(input,ret,linecount[0]);
                input=ret[1]+input.substring(ret[0]);
                start=0;
                continue;
            }else if(input[ret]=='#'){
                debugger;
                ret=this.ifselect(input,ret,linecount[0]);
                input=ret[1]+input.substring(ret[0]);
                start=0;
                continue;
            }
            start=ret+1;
            let parts=capture[0].split(',').map(a=>a.trim());
            if(parts[0].endsWith(']')){
                ret=simpleregex(parts[0],['bs',']','br*','0123456789','bs','[','bos',' ','br+',azZ0],parts[0].length-1,capture);
                capture[1]=' ['+capture[2]+']';
                capture[2]=capture[5];
                capture=capture.slice(0,3);
            }else{
                capture.push('');
                ret=simpleregex(parts[0],['br+',azZ0],parts[0].length-1,capture);
            }
            if(ret===false)return values;
            let type=this.normalizeType(parts[0].substring(0,ret+1));
            let val={
                type:type+capture[1],
                name: capture[2],
                child:undefined
            };
            if(this.comments[linecount[0]]!==undefined){
                val.comment=this.comments[linecount[0]];
            }
            values.push(val);
            for(let i=1;i<parts.length;i++){
                let capture=[];
                if(parts[0].endsWith(']')){
                    ret=simpleregex(parts[i],['bs',']','br*','0123456789','bs','[','bos',' ','br+',azZ0],parts[i].length-1,capture);
                    capture[0]=' ['+capture[1]+']';
                    capture[1]=capture[4];
                    capture=capture.slice(0,2);
                }else{
                    capture.push('');
                    ret=simpleregex(parts[i],['br+',azZ0],parts[i].length-1,capture);
                }
                if(ret===false)return values;
                values.push({
                    type:type+capture[0],
                    name: capture[1],
                    child:undefined
                });
            }
        }
        return values;
    }
    parseTypedef(input, pos=0, save=true,linecount=[0]){
        //Resolve Encountering top level !typedef struct or !typedef enum
        let capture=[];
        let ret=simpleregex(input,['s','typedef ','os','const ','os','struct','os','enum','os','union','r*',' \t\r\n','r*',azZ0,'r*',' \t\r\n','os','{'],pos,capture);
        if(ret===false)return pos;
        let thiz=this;
        function enum_struct_union(){
            let structName=capture[6];
            if(capture[8]==='{'){
                let depthEnd=thiz.skipDepth(input,ret-1)+1;
                capture.push(input.substring(ret,depthEnd-1));
                ret=depthEnd;
            }else{
                capture.push('');
            }
            ret=simpleregex(input,['r*',' \t\r\n','os',structName],ret,capture);
            if(capture[11]!=''){
                //self-define
                ret=simpleregex(input,['r*',' \t\r\n','s',';'],ret,capture);
            }else{
                //alias
                capture.pop();
                ret=simpleregex(input,['r*','* &'],ret,capture);
                let ptr=capture.pop();
                ret=simpleregex(input,['r+',azZ0,'r*',' \t\r\n','s',';'],ret,capture);
                capture[11]=ptr+capture[11];
            }
            if(ret===false)return pos;
            if(structName==''){
                structName=capture[11];
            }
            if(save){
                let comment='';
                if(thiz.comments[linecount[0]-1]!=undefined)comment=thiz.comments[linecount[0]-1];
                if(capture[2]!==''){
                    thiz.defineName(structName,'structs',{
                        name: structName,
                        fields: thiz.parseStructValues(capture[9],linecount),
                        binding:{comment,line:linecount[0]}
                    });
                }else if(capture[3]!==''){
                    thiz.defineName(structName,'enums',{
                        name: structName,
                        values: thiz.parseEnumValues(capture[9],linecount),
                        binding:{comment,line:linecount[0]}
                    });
                }else if(capture[4]!==''){
                    thiz.defineName(structName,'unions',{
                        name: structName,
                        fields: thiz.parseStructValues(capture[9],linecount),
                        binding:{comment,line:linecount[0]}
                    });
                }
            }
            return ret;
        }
        function callback(){
            //example: typedef int (*someType)(char, int);
            // typedef void (*TraceLogCallback)(int logLevel, const char *text, va_list args);  // Logging: Redirect trace log messages
            // typedef unsigned char *(*LoadFileDataCallback)(const char *fileName, int *dataSize);    // FileIO: Load binary data
            // typedef bool (*SaveFileDataCallback)(const char *fileName, void *data, int dataSize);   // FileIO: Save binary data
            // typedef char *(*LoadFileTextCallback)(const char *fileName);            // FileIO: Load text data
            // typedef bool (*SaveFileTextCallback)(const char *fileName, char *text); // FileIO: Save text data
            // typedef JSValue JSCFunction(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
            if(capture[6]=='')return pos;
            ret=pos+'typedef '.length;
            ret=simpleregex(input,['os','static ','os','unsigned ','os','const ','r+',azZ0,'r*',' *'],ret,capture=[]);
            if(ret===false)return pos;
            ret=simpleregex(input,['os','(','r*',' *','r+',azZ0,'r*',' ','os',')','r*',' ','s','(','r+',', \n*[]'+azZ0,'os','...','r*',' ','s',')','r*',' ','s',';'],ret,capture);
            if(ret===false)return pos;
            if(save){
                let comment='';
                if(thiz.comments[linecount[0]-1]!=undefined)comment=thiz.comments[linecount[0]-1];
                const type=capture[6]==''?'void':'void *';
                thiz.defineName(capture[7],'callbacks',{
                    returnType: thiz.normalizeType(capture[1]+capture[2]+capture[3]+capture[4]),
                    name: capture[7],
                    args: thiz.parseFunctionArgs(capture[12]+capture[13]),
                    type,
                    binding:{comment,line:linecount[0]}
                });
            }
            return ret+1;//+1 to eat ;
        }
        if(capture[2]!=='' || capture[3]!=='' || capture[4]!==''){
            return enum_struct_union();
        }else{
            //check if is some simple alias
            if(capture[6]!==''){//type
                let alias_end=simpleregex(input,['r*',' \t\r\n','r*',azZ0+'*','r*',' \t\r\n','s',';'],ret,capture);
                if(alias_end!==false){
                    thiz.defineName(capture[10],'aliases',{
                        name: capture[10],
                        type: capture[6],
                        binding:{}
                    });
                    return alias_end;
                }
            }
            return callback();
        }
    }
    parseDefFunction(input, pos=0){
        let capture=[];
        let ret=simpleregex(input,['br+',azZ0,'r+',' \t\r\n'],pos-1,capture);
        if(ret==false)return false;
        let name=capture[0];
        let def=defined[name];
        if(def==undefined || def.type!='function'){
            return false;
        }
        let pos3=this.skipDepthf(input,pos);
        let args=input.substring(pos+1,pos3).split(',').map((a,i)=>{a=a.trim();return [def.content.args[i],a.trim()]});
        return {from:pos-name.length,to:pos3+1,replace:this.safeEval(def.content.body,Object.fromEntries(args))};
    }
    parseFunction(input, pos=0, save=true,linecount=[0]){
        if(lookBackward(input,'JS_IsModule',pos))debugger;
        //Resolve Encountering top level !(){
        //((?:\/\/.+\n)+)^[A-Z]+ (.+?)(\w+)\(([^\)]+)\)
        //Search argsStart,' (',name,' ',type
        let capture=[];
        //RLAPI should not be hard coded here, but the alternative is to translate every word according to defines
        let ret=simpleregex(input,['br+',azZ0,'br*',' *'],pos-1,capture);
        if(ret===false)return pos;
        let props={};
        let words=[];
        while(ret>0&&input[ret]!="\n"){
            const w=this.getwordb(input,ret,props);
            if(w==false)return pos;
            ret=w[0];
            if(w[1].length>0)words.push(w[1]);
        }
        words=words.join(' ');
        let wlen=simpleregex(words,['r+',azZ0],0,capture);
        if(wlen!=words.length)return pos;
        if(input[ret]!="\n")return pos;
        ret=simpleregex(input,['r*',', \r\n*[]'+azZ0,'os','...','r*',' ','s',')','r*'," \t\r\n",'os','/','os','{','os',';'],pos+1,capture);
        if(ret===false)return pos;
        if(capture[8]==='/'){//some comment, remove it
            ret=this.parseComment(input,ret-1);
            capture.splice(capture.length-4,4);
            ret=simpleregex(input,['r*'," \t\r\n",'os','/','os','{','os',';'],ret,capture);
            if(ret===false)return pos;
        }
        if(capture[9]!=='{'&&capture[10]!==';')return pos;
        if(capture[9]==='{'){
            let tmp=this.skipDepth(input,ret-1)+1;
            capture.push(input.substring(ret,tmp));
            ret=tmp;
        }

        if(save){
            console.log("defined fn "+capture[0]);
            let comment='';
            if(this.comments[linecount[0]-1]!=undefined)comment=this.comments[linecount[0]-1];
            if(capture[5]=="inline ")props.inline=true;
            if(capture[6]=="static ")props.static=true;
            this.defineName(capture[0],'functions',{
                returnType: this.normalizeType(capture[2]+capture[1]),
                name: capture[0],
                args: this.parseFunctionArgs(capture[3]+capture[4]),
                props,
                binding:{comment,line:linecount[0]}
            });
        }
        return ret;
    }
    parseFunctionArgs(input) {
        return input.split(',').filter(x => x !== 'void' && x !=='').map(arg => {
            let type = this.normalizeType(arg);
            if(type=='...'){
                return { name: 'args', type: '...', binding:{},sizeVars:[] };
            }
            let frags=type.split(' ');
            let name=frags[frags.length-1];
            if(name=='*'|| this.nameSet[name] || defaultTypeParts.includes(name) ){
                name='';
            }else{
                frags.pop();
            }
            let j=0;
            for(let i=0;i<frags.length;i++){
                const word=frags[i];
                const def=defined[word];
                if(def){
                    if(def.type=='undefined'){
                        frags[j]=def.content.body;
                    }
                }
            }
            return { name: name, type: frags.filter(a=>a!='').join(' '), binding:{},sizeVars:[] };
        });
    }
    parseComment(input,pos=0,save=true,linecount=0){
        //Resolve Encountering !// or !/*
        if(input.length<=pos+1)return false;
        let next=input[pos+1];
        let ret;
        if(next=='/'){
            ret=simpleregex(input,['ns',"\n"],pos+2);
        }else if(next=='*'){
            ret=simpleregex(input,['ns',"*/"],pos+2)+2;
        }else{
            return pos;
        }
        if(save){
            let comment=input.substring(pos+2,ret).trim();
            if(this.comments[linecount]){
                comment=this.comments[linecount]+input.substring(pos,ret);
            }
            //No real standard for comments, inline seem to be more direct than comment before
            let lastfn;
            if((lastfn=this.functions.at(-1))&&lastfn.binding.line==linecount){
                lastfn.binding.comment=comment;
            }else if((lastfn=this.callbacks.at(-1))&&lastfn.binding.line==linecount){
                lastfn.binding.comment=comment;
            }else{
                //Save comments only if not assigned, to not reuse inline comments
                this.comments[linecount]=comment;
            }
        }
        return ret;
    }
    parseString(input,pos=0){
        //Resolve Encountering " or '
        let endTag=input[pos];
        pos++;
        while(true){
            let ret=simpleregex(input,['ns',endTag],pos);
            if(ret===false)return input.length;
            //check for \" but ignore \\"
            let capture=[];
            simpleregex(input,['br*','\\'],ret,capture);
            pos=ret;
            if(capture[0].length%2==0)break;
            pos++;
        }
        return pos+1;
    }
    parseStringb(input,pos=0){
        //Resolve Encountering " or '
        let endTag=input[pos];
        pos--;
        while(true){
            let ret=simpleregex(input,['bns',endTag],pos);
            if(ret===false)return 0;
            //check for \" but ignore \\"
            let capture=[];
            simpleregex(input,['br*','\\'],ret,capture);
            pos=ret;
            if(capture[0].length%2==0)break;
            pos-=capture[0].length+1;
        }
        return pos-1;
    }
    parseIfHeader(input){
        //read header statement of #if and resolve to bool
        input=input.replace(/\s/g,'');
        if(input.startsWith('#ifdef')){
            return defined[input.slice(6)]!==undefined;
        }else if(input.startsWith('#ifndef')){
            return defined[input.slice(7)]===undefined;
        }
        let pos=0;
        let historytype=[];//stores type 'd','o','(' AKA digit,option,start of brackets
        let history=[];
        let historypos=0;
        function writedirect(start,end){
            if(start>=end)return false;
            if(azZ.includes(input[start])){
                history[historypos]=defined[input.substring(start,end)];
                historytype[historypos]='d';
                historypos++;
                return true;
            }else if('\'\"'.includes(input[start])){
                history[historypos]=input.substring(start+1,end-1);
                historytype[historypos]='d';
                historypos++;
                return true;
            }else if(a0.includes(input[start])){
                history[historypos]=Number(input.substring(start,end));
                historytype[historypos]='d';
                historypos++;
                return true;
            }
        }
        function compressHistory(){
            if(historytype[historypos-1]!='d')return;
            if(historytype[historypos-2]!='o')return;
            historypos--;
            let type=historytype[historypos-1];
            while(type=='o'){//isopt
                let res;let d=history[historypos];
                switch(history[historypos-1]){
                    case '<':res=history[historypos-2]<d;historypos-=2;break;
                    case '>':res=history[historypos-2]>d;historypos-=2;break;
                    case '<=':res=history[historypos-2]<=d;historypos-=2;break;
                    case '>=':res=history[historypos-2]>=d;historypos-=2;break;
                    case '==':res=history[historypos-2]==d;historypos-=2;break;
                    case '&':res=history[historypos-2]&&d;historypos-=2;break;
                    case '|':res=history[historypos-2]||d;historypos-=2;break;
                    case '!':res=!d;historypos--;break;
                }
                history[historypos]=res;
                historytype[historypos]='d';
                type=historytype[historypos-1];
            }
            historypos++;
        }
        while(pos<input.length){
            let end=simpleregex(input,['nr*','()><=&|!d'],pos);
            if(writedirect(pos,end)){
                compressHistory();
            }
            switch(input[end]){
                case "(":{
                    history[historypos]=0;
                    historytype[historypos]='(';
                    historypos++;
                    pos++;
                    break;
                }
                case ")":{
                    historypos-=2;
                    history[historypos]=history[historypos+1];
                    historytype[historypos]=historytype[historypos+1];
                    compressHistory();
                    pos++;
                    break;
                }
                case ">":
                case "<":
                case "=":{
                    let optend=simpleregex(input,['r*','='],end+1);
                    history[historypos]=input.substring(end,optend);
                    historytype[historypos]='o';
                    historypos++;pos=optend;
                    break;
                }
                case "&":{
                    history[historypos]='&';
                    historytype[historypos]='o';
                    historypos++;pos+=2;
                    break;
                }
                case "|":{
                    history[historypos]='|';
                    historytype[historypos]='o';
                    historypos++;pos+=2;
                    break;
                }
                case "!":{
                    history[historypos]='!';
                    historytype[historypos]='o';
                    historypos++;pos++;
                    break;
                }
                case "d":{
                    if(lookForward(input,'defined(',end)){
                        let s=input.indexOf(')',end+8);
                        if(s===-1)return '';
                        history[historypos]=defined[input.substring(end+8,s).trim()]!==undefined;
                        historytype[historypos]='d';
                        historypos++;pos=s+1;
                        compressHistory();
                        break;
                    }
                }
                default:{
                    pos++;
                }
            }
        }
        return history[0];
    }
    parseStaticVal(input,pos){
        //resolve static data definition, exaple:
        //static uint8_t const typed_array_size_log2[JS_TYPED_ARRAY_COUNT];
        //static JSClassID js_ArrayProxy_class_id;
        //static int qjs__argc;
        //static char **qjs__argv;
        //static int default_dump;
        if(!lookForward(input,'static ',pos))return pos;
        let ret=pos+'static '.length;
        let props={};
        let words=[];
        while(ret<input.length&&input[ret]!="\n"){
            const w=this.getword(input,ret,props);
            if(w==false)break;
            ret=w[0];
            if(w[1].length>0){
                if(w[1].includes('('))return pos;
                words.push(w[1]);
            }
            ret=simpleregex(input,['r*',' *\t'],ret,words);
            if(words[words.length-1].trimEnd()=='')words.pop();
        }
        let name=words.pop();
        let type=words.join(' ');
        if(input[ret]=='['){
            let capture=[];
            ret=simpleregex(input,['nr+',']'],ret,capture);
            if(ret==false||input[ret]!=']')return pos;
            ret++;
            type=type+`[${capture[0].trim()}]`;
        }
        let capture=[];
        ret=simpleregex(input,['r*',' \t','os',';','os','='],ret,capture);
        if(capture[1]==';'){
            this.defineName(name,'staticData',{name, type,initial:undefined,props});
            return ret;
        }else if(capture[2]=='='){
            ret=simpleregex(input,['nr+',';'],ret,capture);
            this.defineName(name,'staticData',{name, type,initial:capture[3],props});
            return ret;
        }
        return pos;
    }
    safeEval(input,args){
        //implement very limited definition code
        //It does things like concat string,add numbers required in code interpretation
        let ret=[];
        let capture;
        let pos=0;
        //Tokenizer
        while(pos<input.length){
            pos=simpleregex(input,['nr*','({-+*/^#<>,|&!'],pos,capture=[]);
            if(pos==input.length){
                ret.push(capture[0].trim());
                break;
            }
            switch(input[pos]){
                case "(":{
                    //if previous input is only text this is a function call
                    let pos2=simpleregex(capture[0],['r*',azZ+'_'],pos);
                    if(pos!=pos2&&pos2==capture[0].length){
                        let fn=defined[capture[0]];
                        let pos3=simpleregex(capture[0],['nr*',')'],pos,capture);
                        let localargs=capture[1].split(',').map((a,i)=>{a=a.trim();return [fn.args[i],args[a.trim()]];});
                        ret+=this.safeEval(fn.content,Object.fromEntries(localargs));
                        pos+=pos3;
                    }else{
                        let pos3=this.skipDepthf(input,pos);
                        let resolved=this.safeEval(input.substring(pos+1,pos3),args);
                        if(resolved!=''){
                            if(capture[0].trim()==''){
                                ret.push(`(${resolved})`);
                            }else{
                                ret.push(`${capture[0].trim()}(${resolved})`);
                            }
                        }else{
                            ret.push(capture[0].trim());
                        }
                        pos=pos3+1;
                    }
                }break;
                case "{":{
                    let pos3=this.skipDepth(input,pos);
                    ret.push(`{${this.safeEval(input.substring(pos+1,pos3),args)}}`);
                    if(pos==pos3){
                        pos++;
                    }else{
                        pos=pos3;
                    }
                }break;
                case "#":
                case "<":
                case ">": {
                    ret.push(capture[0].trim());
                    if(lookForward(input,'##',pos)){
                        ret.push('##');
                        pos+=2;
                    }else if(lookForward(input,'<<',pos)){
                        ret.push('<<');
                        pos+=2;
                    }else if(lookForward(input,'>>',pos)){
                        ret.push('>>');
                        pos+=2;
                    }else{
                        ret.push(input[pos]);
                        pos++;
                    }
                }break;
                case "!":{
                    ret.push(input[pos]);
                    pos++;
                }break;
                case "+":
                case "-":
                case "*":
                case "/":
                case "|":
                case "^":{
                    ret.push(capture[0].trim());
                    ret.push(input[pos]);
                    pos++;
                }break;

                case ",":{
                    ret.push(capture[0].trim());
                    ret.push(',');
                    pos++;
                }break;
            }
        }
        //resolver
        //filter out casts
        ret=ret.filter(a=>a!=''&&!isType(a));
        //pass 1: convert to numbers
        for(let i=0;i<ret.length;i+=2){
            let variable=ret[i];
            if(variable.startsWith('0x')){
                let j=2;
                j=simpleregex(variable,["r+",'0123456789abcdef'],j);
                if(j!=false&&j==variable.length){
                    ret[i]=Number(variable);
                }
                break;
            }
            let j=0;
            j=simpleregex(variable,["r+",'0123456789','os','.','r*','0123456789'],j);
            if(j!=false&&j==variable.length){
                ret[i]=Number(variable);
                break;
            }
        }
        function resolve(variable){
            if(typeof(variable)!='string')return variable;
            if(args[variable]!=undefined)return args[variable];
            if(defined[variable]!=undefined){
                return defined[variable].content.body;
            }
            return variable;
        }
        //Negation pass (!)
        for(let i=0;i<ret.length;i++){
            if(ret[i]!=='!')continue;
            if(i+1>=ret.length){
                ret[i-1]='!'+ret[i-1];
            }else{
                const right=resolve(ret[i+1]);
                ret[i]=(!Number(right))?1:0;
            }
            ret.splice(i+1,1);
            i--;
        }

        //implement 2arg passes
        let passes=[
            ['!',[(a,b)=>(!Number(b))?1:0]],
            [['##'],[(a,b)=>String(a)+String(b)]],
            [['<<','>>'],[(a,b)=>a<<b,(a,b)=>a>>b]],
            [['&','|'],[(a,b)=>a&b,(a,b)=>a|b]],
            ['^',[(a,b)=>a^b]],
            ['/*',[(a,b)=>a/b,(a,b)=>a*b]],
            ['+-',[(a,b)=>Number(a)+Number(b),(a,b)=>a-b]],
            [',',[(a,b)=>a+','+b]]
        ];
        for(let pass of passes){
            for(let tokenId in pass[0]){
                for(let i=1;i<ret.length;i++){
                    const variable=ret[i];
                    if(variable!==pass[0][tokenId])continue;
                    if(i+1>=ret.length){
                        ret[i-1]=ret[i-1]+variable;
                    }else{
                        const left=resolve(ret[i-1]);
                        const right=resolve(ret[i+1]);
                        ret[i-1]=pass[1][tokenId](left,right);
                    }
                    ret.splice(i,2);
                    i-=2;
                }
            }
        }
        return ret.length==1?ret[0]:ret.join('');
    }
    parseDefine(input,save,linecount=0){
        //Parse #define and register poperly
        let thiz=this;
        function getStack(input,pos,capture=[]){
            let stack_size=1;
            while(pos<input.length){
                pos=simpleregex(input,['nr*','(){}'],pos,capture);
                if(pos===false)return;
                if(input[pos]=='('||input[pos]=='{')stack_size++;
                if(input[pos]==')'||input[pos]=='}')stack_size--;
                capture.push(stack_size);
                if(pos>=input.length)break;
                capture[capture.length-2]+=input[pos];
                pos++;
            }
        }
        function setDefine(name,content){
            if(!save)return true;
            if(content!==undefined){
                content.binding={
                    comment:thiz.comments[linecount]||thiz.comments[linecount-1]||'',
                    line:linecount
                };
            }
            defined[name]=content;
            thiz.defineName(name,'defines',content);
            return true;
        }
        let capture=[];
        let pos=simpleregex(input,["os","define","os","undef","r*"," \t"],0,capture);
        let is_undefine=capture[1]!='';
        input=input.replace(/\\\r*\n/g,' ').trim().replace(/\s+/g,' ');
        capture=[];
        pos=simpleregex(input,['r+',azZ0],pos,capture);
        if(pos===false)return false;
        let name=capture[0];
        if(is_undefine){
            setDefine(name,undefined);
            if(save)delete defined[name];
            return true;
        }
        let body, type;
        pos=simpleregex(input,['r*',' \t','os','('],pos,capture=[]);
        if(capture[1]==='('){
            if(capture[0]==''){
                //function and has arguments
                type='function';
                let endpos=this.skipDepthf(input,pos);
                let args=input.substring(pos,endpos).split(',').map(a=>a.trim());
                body=input.substring(endpos+1);
                let content={name,args,body};
                return setDefine(name,{type,content});
            }else{
                //this is eval, probably needed
                body=this.safeEval(input.substring(pos,this.skipDepthf(input,pos)),{});
                let type;
                if(typeof(body)=='string'){
                    type='string';
                }else if(typeof(body)=='boolean'){
                    type='bool';
                }else if(typeof(body)=='number'){
                    if(Number.isInteger(body)){
                        type='int';
                    }else{
                        type='float';
                    }
                }
                return setDefine(name,{type,name,content:{body}});
            }
        }
        body=input.substring(pos,input.length).trim();
        if(body.at(-1)=='f' && !isNaN(body.substring(0,body.length-1))){
            body=Number(body.substring(0,body.length-1));
            return setDefine(name,{type:'float',name,content:{body}});
        }
        if(body.at(-1)=='d' && !isNaN(body.substring(0,body.length-1))){
            body=Number(body.substring(0,body.length-1));
            return setDefine(name,{type:'double',name,content:{body}});
        }
        type='undefined';
        if(body.startsWith('CLITERAL(')){
            getStack(input,pos,capture=[]);
            type="struct";
            //collect string
            let startDepth=capture[3];
            let str=capture[4];
            let i=5;
            while(i<capture.length && startDepth<capture[i]){
                str+=capture[i+1];i+=2;
            }
            str=str.substring(1,str.length-1)//remove {}
            body={
                type:capture[2].substring(0,capture[2].length-1),//remove last )
                values:str.split(',').map(a=>a.trim())
            }
        }else
        if(body.toLowerCase()=='true'){body=1;type='bool';}else
        if(body.toLowerCase()=='false'){body=0;type='bool';}else
        if(body!=''){
            if((body.startsWith('"')&&body.endsWith('"')) || (body.startsWith("'")&&body.endsWith("'"))){
                body=body.substring(1,body.length-1);type='string';
            }else
            if(!isNaN(body)){
                if(body.includes('.')){
                    type='double';
                }else{
                    type='int';
                }
                body=Number(body);
            }
        }
        return setDefine(name,{type,name,content:{body}});
    }
    ifselect(input,pos=0,linecount=0){
        //This function returns the processed code #if end where #if ends or handle random #declare

        let ifDepth=0;
        let ifStatement='';
        let ifBody=true;//0=definition, 1 block
        let inDefine=false;
        let ifOkDepth=0;//ifDepth==ifOkDepth => parse code
        let ifpassed=false;//in a if else chain, was a good chain executed
        let parseBody=false;
        let capture='';let log=[pos];
        function pushCapture(pos,index){
            log[index]=pos;
            if(log[1]!==undefined) {
                if (log[0] !== undefined) {
                    capture += input.substring(log[0], log[1]);
                }
                log = [];
            }
        }
        //This requires carefull management, but does not need a stack approach
        let start=pos;
        while(pos<input.length){
            //console.log(input.substring(pos-5,pos)+'|'+input.substring(pos,pos+10));
            let lastpos=pos;
            switch(input[pos]){
                case "#":{
                    if(ifBody && lookForward(input,'#define',pos)){
                        inDefine=true;
                        start=pos+7;pos+=7;
                        ifStatement='define';
                    }else if(lookForward(input,'#undef',pos)){
                        inDefine=true;
                        start=pos+6;pos+=6;
                        ifStatement='undef';
                    }else if(lookForward(input,'#if',pos)){
                        ifpassed=false;
                        parseBody=false;pushCapture(pos,1);
                        ifStatement='';
                        if(lookForward(input,'def',pos+3)){
                            start=pos+6;pos+=6;
                            ifStatement='#ifdef';
                        } else if(lookForward(input,'ndef',pos+3)){
                            start=pos+7;pos+=7;
                            ifStatement='#ifndef';
                        }else{
                            pos+=4;start=pos;
                        }
                        ifBody=false;
                    }else if(lookForward(input,'#elif',pos)){
                        parseBody=false;pushCapture(pos,1);
                        start=pos+6;pos+=5;
                        ifDepth--;
                        ifStatement='';
                        ifBody=false;
                    }else if(lookForward(input,'#else',pos)){
                        parseBody=false;pushCapture(pos,1);
                        start=pos+6;pos+=5;
                        ifDepth--;
                        if(!ifpassed && ifOkDepth===ifDepth){
                            ifOkDepth++;
                            ifpassed=true;
                            parseBody=true;pushCapture(start,0);
                        }
                        ifDepth++;
                        ifBody=true;
                    }else if(lookForward(input,'#endif',pos)){
                        parseBody=false;pushCapture(pos,1);
                        start=pos+7;pos+=6;
                        ifDepth--;
                        if(ifOkDepth>=ifDepth){
                            ifOkDepth=ifDepth;
                            parseBody=true;pushCapture(start,0);
                        }
                        ifBody=true;
                    }else if(lookForward(input,'#include',pos)){
                        let captureImport=[];
                        simpleregex(input,["r+"," \t","r+",'<"',"r*"," \t","r+",azZ+"-_.","r*"," \t","r+",'>"'],pos+8,captureImport);
                        let path=this.sourcefiles[captureImport[3]];
                        let imported;
                        if(path==undefined){
                            throw new Error(`File ${captureImport[3]} can not be included`);
                        }else if(path==false){
                            imported=''
                        }else{
                            imported=fs.readFileSync(path, "utf8");
                        }
                        pushCapture(pos,1);
                        start=pos+9+captureImport.join('').length;pos+=pos+8+captureImport.join('').length;
                        //The imput we have is a copy, so we need to edit capture directly
                        capture +=imported;
                        pushCapture(pos,0);
                        continue;
                    }
                    break;
                }
                case "\n":{
                    //For newline or comment, if in #if header, write this as 'if'
                    if(input[pos-1]=='\\')continue;//handle multiline if
                    if(inDefine){
                        ifStatement+=input.substring(start,pos);
                        this.parseDefine(ifStatement,ifOkDepth>=ifDepth);
                        inDefine=false;
                    }else
                    if(!ifBody){
                        ifStatement+=input.substring(start,pos);
                        if(!ifpassed && ifOkDepth===ifDepth &&this.parseIfHeader(ifStatement)){
                            ifOkDepth++;
                            ifpassed=true;
                            parseBody=true;pushCapture(pos,0);
                        }
                        ifBody=true;
                        start=pos+1;
                        ifDepth++;
                    }
                    linecount++;
                    break;
                }
                case "'":case '"':pos=this.parseString(input,pos);break;
                case "/":{
                    //For newline or comment, if in #if header, write this as 'if'
                    if(!ifBody || inDefine){
                        ifStatement+=input.substring(start,pos);
                    }
                    //Skip comments
                    pos=this.parseComment(input,pos);
                    start=pos;
                    break;
                }
            }
            if(lastpos===pos)pos++;
            if(ifDepth===0 && ifBody && !inDefine)return [pos,capture];
        }
        return [pos,capture];
    }
    skipDepth(input,pos=0){//skip {}
        let depth=1;
        pos++;
        while(pos<input.length && depth>0){
            let ret=pos;
            switch(input[pos]){
                case "{":depth++;break;
                case "}":depth--;break;
                case "'":case '"':ret=this.parseString(input,pos);break;
                case "/":ret=this.parseComment(input,pos);break;
            }
            if(ret==pos){
                pos++;
            }else{
                pos=ret;
            }
        }
        return pos-1;
    }
    skipDepthf(input,pos=0){//skip ()
        let depth=1;
        pos++;
        while(pos<input.length && depth>0){
            let ret=pos;
            switch(input[pos]){
                case "(":depth++;break;
                case ")":depth--;break;
                case "'":case '"':ret=this.parseString(input,pos);break;
                case "/":ret=this.parseComment(input,pos);break;
            }
            if(ret==pos){
                pos++;
            }else{
                pos=ret;
            }
        }
        return pos-1;
    }
    skipDepthfb(input,pos=0){//skip () backwards
        let depth=1;
        pos--;
        while(pos>=0 && depth>0){
            let ret=pos;
            switch(input[pos]){
                case "(":depth--;break;
                case ")":depth++;break;
                case "'":case '"':ret=this.parseStringb(input,pos);break;
                case "/"://NOTE: cant handle single line comments
                    if(input[pos-1]=='*'){
                        ret=simpleregex(input,['bns','/*'],pos-1);
                    }
                    pos--;
                    break;
            }
            if(ret==pos){
                pos--;
            }else{
                pos=ret;
            }
        }
        return pos;
    }
    constructor(input,sourcefiles={}){
        defined=globalThis.config.defined;//re-synchronize
        let ifDepth=0;
        let ifStatement='';
        let ifBody=true;//0=definition, 1 block
        let inDefine=false;
        let ifOkDepth=0;//ifDepth==ifOkDepth => parse code
        let ifpassed=false;//in a if else chain, was a good chain executed
        let parseBody=true;
        let start=0;
        let pos=0;
        let linecount=[0];//does not represent actual line in the file, just as much is convinient for comment parsing
        this.sourcefiles=sourcefiles;
        while(pos<input.length){
            let lastpos=pos;
            switch(input[pos]){
                case "#":{
                    if(ifBody && lookForward(input,'#define',pos)){
                        inDefine=true;
                        start=pos+7;pos+=7;
                        ifStatement='define';
                    }else if(lookForward(input,'#undef',pos)){
                        inDefine=true;
                        start=pos+6;pos+=6;
                        ifStatement='undef';
                    }else if(lookForward(input,'#if',pos)){
                        ifpassed=false;
                        parseBody=false;
                        ifBody=false;
                        ifStatement='';
                        if(lookForward(input,'def',pos+3)){
                            pos+=6;start=pos;
                            ifStatement='#ifdef';
                        } else if(lookForward(input,'ndef',pos+3)){
                            pos+=7;start=pos;
                            ifStatement='#ifndef';
                        }else{
                            pos+=4;start=pos;
                        }
                    }else if(lookForward(input,'#elif',pos)){
                        parseBody=false;
                        start=pos+6;pos+=5;
                        ifDepth--;
                        ifBody=false;
                        ifStatement='';
                    }else if(lookForward(input,'#else',pos)){
                        parseBody=false;
                        start=pos+6;pos+=5;
                        ifDepth--;
                        if(!ifpassed && ifOkDepth===ifDepth){
                            ifOkDepth++;
                            ifpassed=true;
                            parseBody=true;
                        }
                        ifDepth++;
                        ifBody=true;
                    }else if(lookForward(input,'#endif',pos)){
                        parseBody=false;
                        start=pos+7;pos+=6;
                        ifDepth--;
                        if(ifOkDepth>=ifDepth){
                            ifOkDepth=ifDepth;
                            parseBody=true;
                        }
                        ifBody=true;
                    }else if(lookForward(input,'#include',pos)){
                        let capture=[];
                        simpleregex(input,["r+"," \t","r+",'<"',"r*"," \t","r+",azZ0+"/.","r*"," \t","r+",'>"'],pos+8,capture);
                        let path=this.sourcefiles[capture[3]];
                        let imported;
                        if(path==undefined){
                            //this.sourcefiles[capture[3]]=false;
                            //pos=pos+8+capture.join('').length;
                            throw new Error(`File ${capture[3]} can not be included`);
                        }else if(path==false){
                            imported=''
                        }else{
                            imported=fs.readFileSync(path, "utf8");
                        }
                        input=input.substring(0,pos)+imported+input.substring(pos+8+capture.join('').length);
                        continue;
                    }
                    break;
                }
                case "\n":{
                    //For newline or comment, if in #if header, write this as 'if'
                    if(input[pos-1]=='\\'||input.substring(pos-2,pos)=="\\\r") break;//handle multiline if
                    if(inDefine){
                        ifStatement+=input.substring(start,pos);
                        if(this.parseDefine(ifStatement,parseBody,linecount[0])){
                            pos++;
                            start=pos;
                        }
                        inDefine=false;
                    }else
                    if(!ifBody){
                        ifStatement+=input.substring(start,pos);
                        if(!ifpassed && ifOkDepth===ifDepth &&this.parseIfHeader(ifStatement)){
                            ifOkDepth++;
                            ifpassed=true;
                            parseBody=true;
                        }
                        ifBody=true;
                        pos++;
                        start=pos;
                        ifDepth++;
                    }
                    linecount[0]++;
                    break;
                }
                case "'":case '"':
                    pos=this.parseString(input,pos);
                    break;
                case "t":{
                    //todo: handle callbacks
                    //example: raylib.h line 953
                    let pos2=this.parseTypedef(input,pos,parseBody,linecount);
                    if(pos2>pos){
                        pos=pos2;
                        start=pos;
                    }
                    break;
                }
                case "e":{
                    //skip extern "C" {
                    if(lookForward(input,'extern "C" {',pos)){
                        pos+=12;
                        start=pos;
                    }else if(!inDefine){
                        let pos2=this.parseES(input, pos,parseBody, linecount);
                        if(pos2>pos){
                            pos=pos2;
                            start=pos;
                        }
                    }
                    break;
                }
                case "s":{
                    if(inDefine)break;
                    let pos2=this.parseES(input, pos, parseBody, linecount);//struct
                    if(pos2==pos){
                        pos2=this.parseStaticVal(input, pos);//static
                    }
                    if(pos2!=pos){
                        pos=pos2;
                        start=pos;
                    }
                    break;
                }
                case "/":{
                    //For newline or comment, if in #if header, write this as 'if'
                    if(!ifBody || inDefine){
                        ifStatement+=input.substring(start,pos);
                    }
                    //Skip comments
                    let pos2=this.parseComment(input,pos,parseBody,linecount[0]);
                    if(pos2>pos){
                        pos=pos2;
                        start=pos;
                    }
                    break;
                }
                case "{":{
                    pos=this.skipDepth(input,pos);
                    break;
                }
                case "(":{
                    if(!ifBody || inDefine){pos=this.skipDepthf(input,pos);break;}
                    //before resolving function try to parse as definition
                    let ret=this.parseDefFunction(input, pos);
                    if(ret!==false){
                        input=input.substring(0,ret.from)+ret.replace+input.substring(ret.to);
                        pos=ret.to;
                        break;
                    }
                    if(input.substring(start,pos).trim().startsWith('JS_EXTERN JSValue JS_PRINTF_FORMAT_ATTR(2, 3)'))debugger;
                    let pos2=this.parseFunction(input,pos,parseBody,linecount);
                    if(pos2==pos){
                        pos=this.skipDepthf(input,pos);
                    }else{
                        pos=pos2;
                        start=pos;
                    }
                    break;
                }
            }
            if(lastpos===pos)pos++;
        }
    }
}