export class StringWriter {
    constructor() {
        this.buffer = '';
    }
    write(value) {
        this.buffer += value;
    }
    writeLine(value = '') {
        this.buffer += value + '\n';
    }
    toString() {
        return this.buffer;
    }
}
export class CodeWriter extends StringWriter {
    constructor() {
        super(...arguments);
        this.indent = 0;
        this.needsIndent = true;
    }
    writeGenerator(generator) {
        const tokens = generator.iterateTokens();
        const text = generator.iterateText();
        const children = generator.iterateChildren();
        let result = tokens.next();
        while (!result.done) {
            switch (result.value) {
                case Token.STRING:
                    const str = text.next().value;
                    if (this.needsIndent) {
                        this.write("    ".repeat(this.indent));
                        this.needsIndent = false;
                    }
                    this.write(str);
                    break;
                case Token.GOSUB:
                    const sub = children.next().value;
                    this.writeGenerator(sub);
                    break;
                case Token.INDENT:
                    this.indent++;
                    break;
                case Token.UNINDENT:
                    this.indent = this.indent > 0 ? this.indent - 1 : 0;
                    break;
                case Token.NEWLINE:
                    this.write("\n");
                    this.needsIndent = true;
                    break;
                default:
                    break;
            }
            result = tokens.next();
        }
    }
}
const Token={
    "STRING":0,
    "NEWLINE":1,
    "INDENT":2,
    "UNINDENT":3,
    "GOSUB":4
};
export class CodeGenerator {
    constructor(parent) {
        this.parent=parent;
        if(parent){
            this.root=parent.root || parent;
        }
        this.children = [];
        this.text = [];
        this.tokens = [];
        this.tags = {};
    }
    getTag(key) {
        return this.tags[key];
    }
    setTag(key, value) {
        this.tags[key] = value;
    }
    iterateTokens() {
        return this.tokens[Symbol.iterator]();
    }
    iterateText() {
        return this.text[Symbol.iterator]();
    }
    iterateChildren() {
        return this.children[Symbol.iterator]();
    }
    line(text) {
        this.tokens.push(Token.STRING, Token.NEWLINE);
        this.text.push(text);
    }
    comment(text) {
        this.line("// " + text);
    }
    call(name, params, returnVal = null) {
        if (returnVal){
            if(returnVal.type){
                this.inline(`${returnVal.type} `);
            }
            this.inline(`${returnVal.name} = `);
        }
        this.inline(name + "(");
        this.inline(params.join(", "));
        this.statement(")");
    }
    declare(type, name, isStatic = false, initValue = undefined, supressDeclaration = false) {
        if(!supressDeclaration){
            if (isStatic)
                this.inline("static ");
            this.inline(type + " " + name);
        }else{
            this.inline(name);
        }
        if (initValue!==undefined)
            this.inline(" = " + initValue);
        this.statement("");
    }
    child(sub) {
        if (!sub)
            sub = new this.constructor(this);
        this.tokens.push(Token.GOSUB);
        this.children.push(sub);
        return sub;
    }
    inlineBefore(str,i){
        let n=this.tokens.length;
        this.tokens=this.tokens.slice(0, n-i).concat(Token.STRING,this.tokens.slice(n-i, n));
        i=this.tokens.slice(n-i, n).filter(a=> a==Token.STRING).length;
        n=this.text.length;
        this.text=this.text.slice(0, n-i).concat(str,this.text.slice(n-i, n));
    }
    inline(str) {
        this.tokens.push(Token.STRING);
        this.text.push(str);
    }
    statement(str) {
        this.line(str + ";");
    }
    breakLine() {
        this.tokens.push(Token.NEWLINE);
    }
    indent() {
        this.tokens.push(Token.INDENT);
    }
    unindent() {
        this.tokens.push(Token.UNINDENT);
    }
    function(name, returnType, args, isStatic, func) {
        const sub = new this.constructor(this);
        sub.setTag("_type", "function-body");
        sub.setTag("_name", name);
        sub.setTag("_isStatic", isStatic);
        sub.setTag("_returnType", returnType);
        let cstatic='';
        if (isStatic){
            cstatic='static '
        }
        this.inline(cstatic+returnType + " " + name + "(");
        this.inline(args.map(x => x.type.replaceAll('* &','*').replaceAll(' &',' *') + " " + x.name).join(", "));
        this.inline(") {");
        this.breakLine();
        this.indent();
        this.child(sub);
        this.unindent();
        this.line("}");
        this.breakLine();
        if (func)
            func(sub);
        return sub;
    }
    if(condition, funIf) {
        this.line("if(" + condition + ") {");
        this.indent();
        const sub = new this.constructor(this);
        sub.setTag("_type", "if-body");
        sub.setTag("_condition", condition);
        this.child(sub);
        this.unindent();
        this.line("}");
        if (funIf)
            funIf(sub);
        return sub;
    }
    elsif(condition, funIf){
        this.line("else if(" + condition + ") {");
        this.indent();
        const sub = new this.constructor(this);
        sub.setTag("_type", "if-body");
        sub.setTag("_condition", condition);
        this.child(sub);
        this.unindent();
        this.line("}");
        if (funIf)
            funIf(sub);
        return sub;
    }
    else(funElse) {
        this.line("else {");
        this.indent();
        const sub = new this.constructor(this);
        sub.setTag("_type", "else-body");
        this.child(sub);
        this.unindent();
        this.line("}");
        if (funElse)
            funElse(sub);
        return sub;
    }
    returnExp(exp) {
        this.statement("return " + exp);
    }
    include(name) {
        this.line("#include <" + name + ">");
    }
    for(indexVar, lengthVar, iter='i',increase='++') {
        let start=``;
        if(indexVar!=undefined)start=`int ${iter}=${indexVar}`;
        this.line(`for(${start}; ${iter} < ${lengthVar}; ${iter}${increase}){`);
        this.indent();
        const child = this.child();
        this.unindent();
        this.line("}");
        return child;
    }
    while(statement){
        this.line(`while(${statement}){`);
        this.indent();
        const child = this.child();
        this.unindent();
        this.line("}");
        return child;
    }
    header(guard, fun) {
        this.line("#ifndef " + guard);
        this.line("#define " + guard);
        this.breakLine();
        const sub = this.child();
        sub.setTag("_type", "header-body");
        sub.setTag("_guardName", guard);
        this.line("#endif // " + guard);
        if (fun)
            fun(sub);
        return sub;
    }
    declareStruct(structName, varName, values, isStatic = false) {
        if (isStatic)
            this.inline("static ");
        this.statement(`${structName} ${varName} = { ${values.join(', ')} }`);
    }
    switch(switchVar) {
        this.line(`switch(${switchVar}) {`);
        this.indent();
        const body = this.child();
        this.unindent();
        this.line("}");
        return body;
    }
    case(value) {
        this.line(`case ${value}:`);
    }
    defaultBreak() {
        this.line("default:{");
        this.indent();
        const body = this.child();
        this.statement("break");
        this.unindent();
        this.line("}");
        return body;
    }
    caseBreak(value) {
        this.line(`case ${value}:{`);
        this.indent();
        const body = this.child();
        this.statement("break");
        this.unindent();
        this.line("}");
        return body;
    }
}