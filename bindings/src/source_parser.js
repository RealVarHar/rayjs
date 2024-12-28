let defined=globalThis.config.defined;
let az='abcdefghijklmnoprstuvqwxyz';
let aZ='ABCDEFGHIJKLMNOPRSTUVQWXYZ';
let a0='1234567890';
let azZ=az+aZ;
let azZ0=az+aZ+a0+'_-';
export class source_parser {
    //sets (avoids re-declaration)
    nameSet={};
    //parsed
    functions=[];
    enums=[];
    structs=[];
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
            this[type].push(contents);
            this.nameSet[name]=[this[type].length-1,type];
            return;
        }
        if(info[1]==type){
            this[type][info[0]]=contents;
            return;
        }
        let oldid=info[name][0];
        let oldtype=info[name][1];
        this[oldtype].splice(oldid,1);
        this[type].push(contents);
        this.nameSet[name]=[this[type].length-1,type];
    }
    //text detection
    lookBackward(input,str,pos=input.length){
        let i=str.length-1;
        while(i>=0){
            if(pos<0 || input[pos]!==str[i]){return false;}
            i--;pos--;
        }
        return true;
    }
    lookForward(input,str,pos=0){
        let i=0;
        while(i<str.length){
            if(pos>=input.length || input[pos]!==str[i]){return false;}
            i++;pos++;
        }
        return true;
    }
    simpleregex(input='',test=[],pos=0,capture=[]){
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
                    if(back===1?this.lookForward(input,opt,pos):this.lookBackward(input,opt,pos)){
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
                    if(back===1?this.lookForward(input,opt,pos):this.lookBackward(input,opt,pos)){
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
                    let f=back===1?this.lookForward:this.lookBackward;
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
                    while(input.length>pos && !opt.includes(input[pos])){
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
    removeTrap(input,removeString=true,removeComment=true){
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
                    let tmp=this.parseComment(input,pos);
                    if(removeComment){
                        ret+=input.substring(start,pos);
                    }else{
                        ret+=input.substring(start,tmp);
                    }
                    start=tmp;
                    pos=tmp;
                    break;
                }
            }
            if(lastpos===pos)pos++;
        }
        ret+=input.substring(start,pos);
        return ret;
    }
    //Parsers
    parseES(input, pos=0, save=true){
        //Resolve Encountering enum or struct (not typedef)
        let mode=input[pos]=='e'?'enum':'struct';
        let capture=[];
        let ret=this.simpleregex(input,['s',mode,'r*',' \t\n','s','{'],pos,capture);
        if(ret===false)return pos;
        let tmp=this.skipDepth(input,ret-1)+1;
        capture.push(input.substring(ret,tmp-1));
        ret=this.simpleregex(input,['r*',' \t\n','r*',azZ0,'r*',' \t\n','s',';'],tmp,capture);
        if(ret===false)return pos;
        if(save){
            if(mode=='struct'){
                this.defineName(capture[5],'structs',{
                    name: capture[5],
                    fields: this.parseStructValues(capture[3]),
                });
            }else{
                this.defineName(capture[5],'enums',{
                    name: capture[5],
                    values: this.parseEnumValues(capture[3]),
                });
            }
        }
        return ret;
    }
    parseEnumValues(input) {
        //TODO: can enum have #if?
        let lastNumber = 0;
        return this.removeTrap(input).split(',').map(en => {
            en=en.split('=');
            let val=lastNumber+1;
            if(en.length==2){
                val=Number(en[1].trim());
            }
            lastNumber=val;
            if(en[0].trim()=='')return;
            return {
                name: en[0].trim(),
                value: val
            };
        }).filter(a=>a!==undefined);
    }
    parseStructValues(input) {
        input=this.removeTrap(input);
        let values = [];
        let start=0;
        while(start<input.length-1){
            let capture=[];
            let ret=this.simpleregex(input,['nr+','#{;'],start,capture);
            if(ret===false)return values;
            if(input[ret]=='{'){
                let end=this.skipDepth(input,ret);
                start=this.simpleregex(input,['nr+',';'],ret,capture);
                values.push({
                    type:'struct',
                    name: capture[1].trim(),
                    child:this.parseStructValues(input.substring(ret,end))
                });
                continue;
            }else if(this.lookForward(input,'#if',ret)){
                //We dont have the whole information, parse if, replace, continue
                ret=this.ifselect(input,ret);
                input=ret[1]+input.substring(ret[0]);
                start=0;
                continue;
            }
            start=ret+1;
            let parts=capture[0].split(',').map(a=>a.trim());
            ret=this.simpleregex(parts[0],['br+',azZ0],parts[0].length-1,capture);
            if(ret===false)return values;
            let type=this.normalizeType(parts[0].substring(0,ret));
            values.push({
                type,
                name: capture[1],
                child:undefined
            });
            for(let i=1;i<parts.length;i++){
                values.push({
                    type,
                    name: parts[i],
                    child:undefined
                });
            }
        }
        return values;
    }
    parseTypedef(input, pos=0, save=true){
        //Resolve Encountering top level !typedef struct or !typedef enum
        let capture=[];
        let ret=this.simpleregex(input,['s','typedef ','os','struct','os','enum','r*',' \t\n','r*',azZ0,'r*',' \t\n','os','{'],pos,capture);
        if(ret===false)return pos;
        let capturename=['r+',azZ0];
        if(capture[4]!==''){
            capturename=['s',capture[4]];
        }
        if(capture[6]==='{'){
            let tmp=this.skipDepth(input,ret-1)+1;
            capture.push(input.substring(ret,tmp-1));
            ret=tmp;
        }
        ret=this.simpleregex(input,['r*',' \t\n',...capturename,'r*',' \t\n','s',';'],ret,capture);
        if(ret===false)return pos;
        let structName;
        if(capture[4]!==''){
            structName=capture[4]
        }else{
            structName=capture[capture.length-3];
        }
        if(save){
            if(capture[1]!==''){
                this.defineName(structName,'structs',{
                    name: structName,
                    fields: this.parseStructValues(capture[capture.length-5]),
                });
            }else if(capture[2]!==''){
                this.defineName(structName,'enums',{
                    name: structName,
                    values: this.parseEnumValues(capture[capture.length-5]),
                });
            }
        }
        return ret;
    }
    parseFunction(input, pos=0, save=true){
        //Resolve Encountering top level !(){
        //((?:\/\/.+\n)+)^[A-Z]+ (.+?)(\w+)\(([^\)]+)\)
        //Search argsStart,' (',name,' ',type
        let capture=[];
        let ret=this.simpleregex(input,['bos'," ",'br+',azZ0,'br*',' *','br+',azZ0,'bos',"unsigned ",'bos',"const ",'bos',"static ","br+","\n \t}"],pos-1,capture);
        if(ret===false)return pos;
        ret=this.simpleregex(input,['r*',', *[]'+azZ0,'s',')','r*'," \t\n",'os','/','os','{','os',';'],pos+1,capture);
        if(ret===false)return pos;
        if(capture[capture.length-3]==='/'){//some comment, remove it
            ret=this.parseComment(input,ret-1);
            capture.splice(capture.length-4,4);
            ret=this.simpleregex(input,['r*'," \t\n",'os','/','os','{','os',';'],ret,capture);
            if(ret===false)return pos;
        }
        if(capture[capture.length-2]!=='{'&&capture[capture.length-1]!==';')return pos;
        if(capture[capture.length-2]==='{'){
            let tmp=this.skipDepth(input,ret-1)+1;
            capture.push(input.substring(ret,tmp));
            ret=tmp;
        }
        if(save){
            this.defineName(capture[1],'functions',{
                returnType: this.normalizeType(capture[5]+capture[4]+capture[3]+capture[2]),
                name: capture[1],
                params: this.parseFunctionArgs(capture[8]),
                binding:{}
            });
        }
        return ret;
    }
    parseFunctionArgs(input) {
        return input.split(',').filter(x => x !== 'void' && x !=='').map(arg => {
            const frags = this.normalizeType(arg).split(' ');
            const name = frags.pop();
            const type = frags.join(' ');
            return { name: name || "", type: type.trim(), binding:{} };
        });
    }
    parseComment(input,pos=0,save=true){
        //Resolve Encountering !// or !/*
        if(input.length<=pos+1)return false;
        let next=input[pos+1];
        let ret;
        if(next=='/'){
            ret=this.simpleregex(input,['ns',"\n"],pos+2);
        }else if(next=='*'){
            ret=this.simpleregex(input,['ns',"*/"],pos+2)+2;
        }else{
            return pos;
        }
        if(save){
            this.comments.push(input.substring(pos,ret+1));
        }
        return ret;
    }
    parseString(input,pos=0){
        //Resolve Encountering " or '
        let endTag=input[pos];
        pos++;
        while(true){
            let ret=this.simpleregex(input,['ns',endTag],pos);
            if(ret===false)return input.length;
            //check for \" but ignore \\"
            let capture=[];
            this.simpleregex(input,['br*','\\'],ret,capture);
            pos=ret;
            if(capture[0].length%2==0)break;
            pos++;
        }
        return pos;
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
            let end=this.simpleregex(input,['nr*','()><=&|!d'],pos);
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
                    let optend=this.simpleregex(input,['r*','='],end+1);
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
                    if(this.lookForward(input,'defined(',end)){
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
    parseDefine(input){
        //Parse #define and register poperly
        let pos=0;
        if(input.startsWith('#define'))pos=8;
        input=input.trim().replace(/\s+/g,' ');
        let capture=[];
        pos=this.simpleregex(input,['r+',azZ0,'os','('],pos,capture);
        if(pos===false)return;
        let content;
        if(capture.pop()==='('){
            pos=this.simpleregex(input,['nr+',')'],pos,capture);
            if(pos===false)return;
            capture[1]=capture[1].replace(/[^a-zA-Z,0-9_-]+/g,'');//secure eval
            let argNames=capture[1].split(',');
            let argArray=argNames.map(a=>'"'+a+'"').join(',');
            content=eval(`(${capture[1]})=>{
            let a=${JSON.stringify(input.substring(pos+1,input.length))};
            let args=[${argArray}];
            for(let i=0;i<args.length;i++){
                a=a.replaceAll(args[i],arguments[i]);
            }
            return JSON.parse(a);}
            `);
        }else{
            content=input.substring(pos,input.length).trimStart();
            if(content.toLowerCase()=='true'){content=1;}else
            if(content.toLowerCase()=='false'){content=0;}else
            if(content==''){content=true;}else
            if(!isNaN(content)){content=Number(content);}
        }
        
        defined[capture[0]]=content;
    }
    ifselect(input,pos=0){
        //#if statements can exist inside structs.
        //This function returns the processed code #if end where #if ends

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
                    if(ifBody && this.lookForward(input,'#define',pos)){
                        inDefine=true;
                        pos+=7;start=pos;
                        ifStatement='';
                    }else if(this.lookForward(input,'#if',pos)){
                        ifpassed=false;
                        parseBody=false;pushCapture(pos,1);
                        ifStatement='';
                        if(this.lookForward(input,'def',pos+3)){
                            pos+=7;start=pos;
                            ifStatement='#ifdef';
                        } else if(this.lookForward(input,'ndef',pos+3)){
                            pos+=8;start=pos;
                            ifStatement='#ifndef';
                        }else{
                            pos+=4;start=pos;
                        }
                        ifBody=false;
                    }else if(this.lookForward(input,'#elif',pos)){
                        parseBody=false;pushCapture(pos,1);
                        pos+=5;start=pos;
                        ifDepth--;
                        ifBody=false;
                        ifStatement='';
                    }else if(this.lookForward(input,'#else',pos)){
                        parseBody=false;pushCapture(pos,1);
                        pos+=5;start=pos;
                        ifDepth--;
                        if(!ifpassed && ifOkDepth===ifDepth){
                            ifOkDepth++;
                            ifpassed=true;
                            parseBody=true;pushCapture(start,0);
                        }
                        ifDepth++;
                    }else if(this.lookForward(input,'#endif',pos)){
                        parseBody=false;pushCapture(pos,1);
                        pos+=6;start=pos;
                        ifDepth--;
                        if(ifOkDepth>=ifDepth){
                            ifOkDepth=ifDepth;
                            parseBody=true;pushCapture(start,0);
                        }
                        ifBody=true;
                    }
                    break;
                }
                case "\n":{
                    //For newline or comment, if in #if header, write this as 'if'
                    if(input[pos-1]=='\\')continue;//handle multiline if
                    if(inDefine){
                        ifStatement+=input.substring(start,pos);
                        this.parseDefine(ifStatement);
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
            if(ifDepth===0 && ifBody)return [pos,capture];
        }
        return [pos,capture];
    }
    skipDepth(input,pos=0){//skip {}
        let depth=1;
        pos++;
        while(pos<input.length && depth>0){
            switch(input[pos]){
                case "{":depth++;break;
                case "}":depth--;break;
                case "'":case '"':pos=this.parseString(input,pos);break;
                case "/":pos=this.parseComment(input,pos);break;
            }
            pos++;
        }
        return pos-1;
    }
    skipDepthf(input,pos=0){//skip ()
        let depth=1;
        pos++;
        while(pos<input.length && depth>0){
            switch(input[pos]){
                case "(":depth++;break;
                case ")":depth--;break;
                case "'":case '"':pos=this.parseString(input,pos);break;
                case "/":pos=this.parseComment(input,pos);break;
            }
            pos++;
        }
        return pos-1;
    }
    constructor(input){
        //TODO: if(parseBody) save data
        let ifDepth=0;
        let ifStatement='';
        let ifBody=true;//0=definition, 1 block
        let inDefine=false;
        let ifOkDepth=0;//ifDepth==ifOkDepth => parse code
        let ifpassed=false;//in a if else chain, was a good chain executed
        let parseBody=true;
        let start=0;
        let pos=0;
        while(pos<input.length){
            let lastpos=pos;
            switch(input[pos]){
                case "#":{
                    if(ifBody && this.lookForward(input,'#define',pos)){
                        inDefine=true;
                        pos+=7;start=pos;
                        ifStatement='';
                    }else if(this.lookForward(input,'#if',pos)){
                        ifpassed=false;
                        parseBody=false;
                        ifStatement='';
                        if(this.lookForward(input,'def',pos+3)){
                            pos+=7;start=pos;
                            ifStatement='#ifdef';
                        } else if(this.lookForward(input,'ndef',pos+3)){
                            start=pos+8;pos+=7;
                            ifStatement='#ifndef';
                        }else{
                            start=pos+4;pos+=3;
                        }
                        ifBody=false;
                    }else if(this.lookForward(input,'#elif',pos)){
                        parseBody=false;
                        pos+=4;start=pos+1;
                        ifDepth--;
                        ifBody=false;
                        ifStatement='';
                    }else if(this.lookForward(input,'#else',pos)){
                        parseBody=false;
                        pos+=4;start=pos+1;
                        ifDepth--;
                        if(!ifpassed && ifOkDepth===ifDepth){
                            ifOkDepth++;
                            ifpassed=true;
                            parseBody=true;
                        }
                        ifDepth++;
                    }else if(this.lookForward(input,'#endif',pos)){
                        parseBody=false;
                        pos+=5;start=pos+1;
                        ifDepth--;
                        if(ifOkDepth>=ifDepth){
                            ifOkDepth=ifDepth;
                            parseBody=true;
                        }
                        ifBody=true;
                    }
                    break;
                }
                case "\n":{
                    //For newline or comment, if in #if header, write this as 'if'
                    if(input[pos-1]!=='\\'){//handle multiline if
                        if(inDefine){
                            ifStatement+=input.substring(start,pos);
                            this.parseDefine(ifStatement);
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
                            start=pos+1;
                            ifDepth++;
                        }
                    }
                    break;
                }
                case "'":case "":pos=this.parseString(input,pos);break;
                case "t":{
                    pos=this.parseTypedef(input,pos,parseBody);
                    break;
                }
                case "e":{
                    //skip extern "C" {
                    if(this.lookForward(input,'extern "C" {',pos)){
                        pos+=12;
                    }else{
                        pos=this.parseES(input, pos,parseBody);
                    }
                    break;
                }
                case "s":{
                    pos=this.parseES(input, pos);break;
                }
                case "/":{
                    //For newline or comment, if in #if header, write this as 'if'
                    if(!ifBody || inDefine){
                        ifStatement+=input.substring(start,pos);
                    }
                    //Skip comments
                    pos=this.parseComment(input,pos,parseBody);
                    start=pos;
                    break;
                }
                case "{":{
                    pos=this.skipDepth(input,pos);
                    break;
                }
                case "(":{
                    let a=this.parseFunction(input,pos,parseBody);
                    if(a==pos){
                        pos=this.skipDepthf(input,pos);
                    }else{
                        pos=a;
                    }
                    break;
                }
            }
            if(lastpos===pos)pos++;
        }
    }
}