import * as std from "std";
import * as os from "os";
class Buffer{
	bufferhistory=[];
	currentbufer;
	currentLength=0;
	length=0;
	alloc=0;

	constructor(alloc){
		this.alloc=alloc;
		this.currentbufer=new Uint8Array(alloc);
	}
	get(index){
		const alloc=this.alloc;
		const currentLength=this.currentLength;
		if(index>currentLength)return 0;
		let i=Math.floor(index/alloc);
		if(i==0){
			const currentbufer=this.currentbufer;
			return currentbufer[index];
		}else{
			const bufferhistory=this.bufferhistory;
			return bufferhistory[bufferhistory.length-i][index-i*alloc];
		}
	}
	set(index,value){
		const alloc=this.alloc;
		const bufferhistory=this.bufferhistory;
		if(index>this.length)return;
		let i=Math.floor(index/alloc);
		if(i==bufferhistory.length){
			const currentbufer=this.currentbufer;
			currentbufer[index-i*alloc]=value;
		}else{
			bufferhistory[i][index-i*alloc]=value;
		}
	}
	append(value){
		const alloc=this.alloc;
		const bufferhistory=this.bufferhistory;
		if(this.currentLength==alloc){
			bufferhistory.push(this.currentbufer);
			this.currentbufer=new Uint8Array(alloc);
			this.currentLength=0;
		}
		this.currentbufer[this.currentLength]=value;
		this.currentLength++;
		this.length++;
	}
	toString(){
		const alloc=this.alloc;
		let ret=String.fromCharCode(...(this.bufferhistory[0]));
		let n=0;
		for(let i=1;i<this.bufferhistory.length;i++){
			ret+=String.fromCharCode(...(this.bufferhistory[i]));
		}
		let currentbufer=this.currentbufer;
		if(this.currentLength<this.alloc){
			currentbufer=new Uint8Array(buffer, 0, this.currentLength);
		}
		ret+=String.fromCharCode(...currentbufer);
		return ret;
	}
	resolve(){
		const alloc=this.alloc;
		let ret=new Uint8Array(this.length);
		let n=0;
		for(let i=0;i<this.bufferhistory.length;i++){
			let buffer=this.bufferhistory[i];
			for(let j=0;j<alloc;j++){
				ret[n]=buffer[j];
				n++;
			}
		}
		const currentbufer=this.currentbufer;
		for(let j=0;j<alloc;j++){
			ret[n]=currentbufer[j];
			n++;
		}
		return ret;
	}
}
class Buffer16{
	bufferhistory=[];
	currentbufer;
	currentLength=0;
	length=0;
	alloc=0;

	constructor(alloc){
		this.alloc=alloc;
		this.currentbufer=new Uint16Array(alloc);
	}
	get(index){
		const alloc=this.alloc;
		const currentLength=this.currentLength;
		if(index>currentLength)return 0;
		let i=Math.floor(index/alloc);
		if(i==0){
			const currentbufer=this.currentbufer;
			return currentbufer[index];
		}else{
			const bufferhistory=this.bufferhistory;
			return bufferhistory[bufferhistory.length-i][index-i*alloc];
		}
	}
	set(index,value){
		const alloc=this.alloc;
		const bufferhistory=this.bufferhistory;
		if(index>this.length)return;
		let i=Math.floor(index/alloc);
		if(i==bufferhistory.length){
			const currentbufer=this.currentbufer;
			currentbufer[index-i*alloc]=value;
		}else{
			bufferhistory[i][index-i*alloc]=value;
		}
	}
	append(value){
		const alloc=this.alloc;
		const bufferhistory=this.bufferhistory;
		if(this.currentLength==alloc){
			bufferhistory.push(this.currentbufer);
			this.currentbufer=new Uint8Array(alloc);
			this.currentLength=0;
		}
		this.currentbufer[this.currentLength]=value;
		this.currentLength++;
		this.length++;
	}
	toString(){
		const historylen=this.bufferhistory.length;
		let ret;
		let n=0;
		let currentbufer=this.currentbufer;
		if(this.currentLength<this.alloc){
			currentbufer=currentbufer.slice(0, this.currentLength);
		}
		if(historylen>0){
			ret=String.fromCharCode(...(this.bufferhistory[0]));
			for(let i=1;i<historylen;i++){
				ret+=String.fromCharCode(...(this.bufferhistory[i]));
			}
			return ret+String.fromCharCode(...currentbufer);
		}else{
			return String.fromCharCode(...currentbufer);
		}
	}
	resolve(){
		const alloc=this.alloc;
		let ret=new Uint16Array(this.length);
		let n=0;
		for(let i=0;i<this.bufferhistory.length;i++){
			let buffer=this.bufferhistory[i];
			for(let j=0;j<alloc;j++){
				ret[n]=buffer[j];
				n++;
			}
		}
		const currentbufer=this.currentbufer;
		for(let j=0;j<alloc;j++){
			ret[n]=currentbufer[j];
			n++;
		}
		return ret;
	}
}
function wlength(str){
	let srclen=str.length;
	let len=0;
	let high=str.charCodeAt(0);
	let i;
	for(i=1;i<srclen;i++){
		len++;
		let low=str.charCodeAt(i);
		if(high<0xD800||high>0xDBFF||low<0xDC00||low>0xDFFF){
			high=low;continue;
		}
		i++;
		high=str.charCodeAt(i);
	}
	if(i==srclen)len++;
	return len;
}
function tounicode(high,low){//utf16 to unicode
	//Always provide second character, if possible
	if(low==undefined){
		return high;
	}
	if(high<0xD800||high>0xDFFF){
		return high;
	}
	if(high>0xDBFF||low<0xDC00||low>0xDFFF){
		return 65533;//�
	}
	return ((high&1023)<<10|low&1023)+0x10000;
}
function fromunicode(i){//unicode to utf16
	//Always provide second character, if possible
	if(i<0x10000){
		return String.fromCharCode(i);
	}
	i-=0x10000;
	return String.fromCharCode(i>>10|0xD800)+String.fromCharCode(i&1023|0xDC00);
}
function toutf8(str=""){
	let srclen=str.length;
	let ret=new Buffer(str.length);
	let charlen=0;
	const dictheader=[0,192,224,240];
	const dictmask=[128,224,240,248];
	let tmp=new Uint8Array(4);
	for(let i=0;i<srclen;i++){
		let char=tounicode(str.charCodeAt(i),str.charCodeAt(i+1));
		if(char>0xFFFF)i++;
		//directwrite
		if(char<128){
			ret.append(char);
			continue;
		}
		//handle octet conversion
		charlen=0;
		while(char>63){
			tmp[charlen]=char&63|128;//%64+128
			char=char>>6;
			charlen++;
		}
		//handle header
		let mask=dictmask[charlen];
		if((char&mask)==0){
			ret.append(char&63|dictheader[charlen]);
		}else{
			ret.append(dictheader[charlen+1]);
			ret.append(char|128);
		}
		//write reversed octects
		for(let j=charlen-1;j>=0;j--){
			ret.append(tmp[j]);
		}
	}
	return ret.resolve();
}
function fromutf8(src=new Uint8Array(1),start=0){
	const srclen=src.length;
	let ret=new Buffer16(Math.min(srclen,4096));
	let i=start;
	while(i<srclen){
		const header=src[i];
		if(header<192){
			if(header<128){
				ret.append(header);
			}else{
				ret.append(65533);//�
			}
			i++
		}else{
			let codes;
			if(header<224){
				//len=2
				codes=(header&31)<<6;
				codes|=src[i+1]&63;
				i+=2;
				ret.append(codes);
				continue;
			}else if(header<240){
				//len=3
				codes=(header&15)<<12;
				codes|=(src[i+1]&63)<<6;
				codes|=(src[i+2]&63);
				i+=3;
				ret.append(codes);
				continue;
			}else if(header<248){
				//len=4
				codes=(header&7)<<18;
				codes|=(src[i+1]&63)<<12;
				codes|=(src[i+2]&63)<<6;
				codes|=(src[i+3]&63);
				i+=4;
			}else{
				ret.append(65533);//�
				i++;
				continue;
			}
			if(codes<0x10000){
				ret.append(codes);
			}else{
				codes-=0x10000;
				ret.append(codes>>10|0xD800);
				ret.append(codes&1023|0xDC00);
			}
		}
	}
	return ret.toString();
}
function readflags(flag){
	switch(flag){
		case 'a':{
			return os.O_WRONLY | os.O_APPEND | os.O_CREAT;
		}break;
		case 'ax':{
			return os.O_WRONLY | os.O_APPEND | os.O_CREAT | os.O_EXCL;
		}break;
		case 'a+':{
			return os.O_RDWR | os.O_APPEND | os.O_CREAT;
		}break;
		case 'ax+':{
			return os.O_RDWR | os.O_APPEND | os.O_CREAT | os.O_EXCL;
		}break;
		case 'as':{
			return os.O_WRONLY | os.O_APPEND | os.O_CREAT;
		}break;
		case 'as+':{
			return os.O_RDWR | os.O_APPEND | os.O_CREAT;
		}break;
		case 'r':{
			return os.O_RDONLY;
		}break;
		case 'rs':{
			return os.O_RDONLY;
		}break;
		case 'r+':{
			return os.O_RDWR;
		}break;
		case 'rs+':{
			return os.O_RDWR;
		}break;
		case 'w':{
			return os.O_WRONLY | os.O_CREAT | os.O_TRUNC;
		}break;
		case 'wx':{
			return os.O_WRONLY | os.O_CREAT | os.O_EXCL | os.O_TRUNC;
		}break;
		case 'w+':{
			return os.O_RDWR | os.O_CREAT | os.O_TRUNC;
		}break;
		case 'wx+':{
			return os.O_RDWR | os.O_CREAT | os.O_EXCL | os.O_TRUNC;
		}break;
	}
	return os.O_RDWR | os.O_CREAT;
}
export function readFileSync(path, options={}){
	if(typeof(options)=='string'){
		options={encoding:options};
	}
	if(options.flag==undefined){
		options.flag= os.O_RDONLY;
	}else{
		options.flag=readflags(options.flag);
	}
	let ret;
	const f = os.open(path, options.flag);
	if(f==null||f<0){
		console.log('ERROR: fs.read',path);
		return undefined;
	}

	let size = os.seek(f,0, std.SEEK_END);
	os.seek(f, 0, std.SEEK_SET);
	ret = new Uint8Array(size);
	os.read(f, ret.buffer, 0, size);
	if(options.encoding=='utf8'){
		//utf8 does not support BOM, but it can be present
		if(size>=3 && ret[0]==0xEF && ret[1]==0xBB && ret[2]==0xBF){
			ret=fromutf8(ret,3);
		}else{
			ret=fromutf8(ret);
		}
	}
	//TODO: more encodings
	os.close(f);
	return ret;
}
export function writeFileSync(path, data, options={}){
	if(options.mode==undefined){
		options.mode=0o666;
	}
	if(options.flag==undefined){
		options.flag= os.O_WRONLY | os.O_CREAT | os.O_TRUNC;
	}else{
		options.flag=readflags(options.flag);
	}
	if(options.flush==undefined){
		options.flush=true;
	}
	if(options.encoding==undefined||options.encoding=='utf8'){
		data=toutf8(data);
	}
	const f = os.open(path, options.flag);
	if(f==null){
		console.log('ERROR: fs.write');
		return false;//not up to spec, throw error
	}

	let written=os.write(f,data.buffer,0,data.length);
	os.close(f);
	if(written<0)return false;
	return true;
}