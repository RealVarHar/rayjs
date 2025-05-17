import * as fs from "./fs.js";
globalThis.config=JSON.parse(fs.readFileSync('bindings/config/buildFlags.json','utf8'));
const rayjs_header = (await import("./raylib-header.js")).RayJsHeader;
const source_parser = (await import("./source_parser.js")).source_parser;

// @ts-ignore
String.prototype.replaceAt = function(index, replacement) {
    return this.substr(0, index) + replacement + this.substr(index+1);
};
if(globalThis.structuredClone==undefined){
    globalThis.structuredClone=(obj)=>{
        if(typeof(obj)=='object'){
            let obj2;
            if(Array.isArray(obj)){
                obj2=[];
            }else{
                obj2={};
            }
            for(let key in obj){
                obj2[key]=globalThis.structuredClone(obj[key]);
            }
            return obj2;
        }
        return obj;
    }
}
let modules= {};//name=>api
let ignored=0;
function attachGetters(api){
    api.getFunction=(name)=> api.functions.find(x => x.name === name);
    api.getStruct=(name)=> api.structs.find(x => x.name === name);
    api.getCallback=(name)=> api.callbacks.find(x => x.name === name);
    api.getEnum=(name)=> api.enums.find(x => x.name === name);
    api.ignore=(name)=>{
        let obj=api.getFunction(name);
        if(!obj)obj=api.getStruct(name);
        if(!obj)obj=api.getCallback(name);
        if(!obj)obj=api.getEnum(name);
        if(obj){
            obj.binding = { ignore: true };
            ignored++;
        }
    };
}
function normalizeType(type=''){
    return type.replaceAll("*", " * ").replaceAll('[',' [').replace(new RegExp("\\s+",'g'),' ').trim();
}
function removeDuplicates(module,key,names){
    let j=0;
    for(let i=0;i<module[key].length;i++){
        if(!names.has(module[key][i].name)){
            module[key][j]=module[key][i];
            j++;
        }
    }
    if(j<module[key].length)module[key]=module[key].slice(0,j);
}
const includeDictionary={lookup:{},contents:[],moduleNames:[]};
function addModuleToDictionary(module,name,include){
    let id=includeDictionary.contents.length;
    let contents={include};
    contents.structLookup={};
    contents.callbackLookup={};
    contents.enumLookup={};
    contents.functionLookup={};
    includeDictionary.contents[id]=contents;
    includeDictionary.moduleNames[id]='rayjs:'+name;
    return id;
}
function main() {
    new source_parser(fs.readFileSync("thirdparty/raylib/src/config.h", "utf8"));//only parse to add #defined
    let att,cb;
    // load quickjs.c since it has the enum we need
    let quickjsSource=new source_parser(fs.readFileSync("thirdparty/quickjs/quickjs.c", "utf8"));
    let classEnum=quickjsSource.enums.find(a=>a.name===''&&a.values.some(b=>b.name==='JS_CLASS_OBJECT'));
    let classEnumLine="enum {\n";
    for(let value of classEnum.values){
        classEnumLine+=value.name+' = '+value.value+',';
    }
    classEnumLine+="\n};";
    fs.writeFileSync("src/rayjs_generated.c",classEnumLine);
    // Load the pre-generated raylib api
    let once={};
    modules['core'] = new source_parser(fs.readFileSync("thirdparty/raylib/src/raylib.h", "utf8"));
    addModuleToDictionary(modules['core'],"raylib",(gen)=>{
        gen.includeGen.include("raylib.h");
    });
    modules['core'].gen = new rayjs_header("raylib",includeDictionary);
    modules['raymath']=new source_parser(fs.readFileSync("thirdparty/raylib/src/raymath.h", "utf8"));
    addModuleToDictionary(modules['raymath'],"raymath",(gen)=>{
        gen.includeGen.include("raymath.h");
    });
    modules['raymath'].gen = new rayjs_header("raymath",includeDictionary);
    modules['rcamera']=new source_parser(fs.readFileSync("thirdparty/raylib/src/rcamera.h", "utf8"));
    addModuleToDictionary(modules['rcamera'],"rcamera",(gen)=>{
        gen.includeGen.include("rcamera.h");
    });
    modules['rcamera'].gen = new rayjs_header("rcamera",includeDictionary);
    modules['raygui']=new source_parser(fs.readFileSync("thirdparty/raygui/src/raygui.h", "utf8"));
    addModuleToDictionary(modules['raygui'],"raygui",(gen)=>{
        if(!once['raygui']){
            once['raygui']=true;
            gen.includeGen.line("#define RAYGUI_IMPLEMENTATION");
        }
        gen.includeGen.include("raygui.h");
    });
    modules['raygui'].gen = new rayjs_header("raygui",includeDictionary);
    modules['rlights']=new source_parser(fs.readFileSync("thirdparty/raylib/examples/shaders/rlights.h", "utf8"));
    addModuleToDictionary(modules['rlights'],"rlights", (gen)=>{
        if(!once['rlights']){
            once['rlights']=true;
            gen.includeGen.line("#define RLIGHTS_IMPLEMENTATION");
        }
        gen.includeGen.include("rlights.h");
    });
    modules['rlights'].gen = new rayjs_header("rlights",includeDictionary);
    modules['reasings']=new source_parser(fs.readFileSync("thirdparty/raylib/examples/others/reasings.h", "utf8"));
    addModuleToDictionary(modules['reasings'],"reasings", (gen)=>{
        gen.includeGen.include("reasings.h");
    });
    modules['reasings'].gen = new rayjs_header("reasings",includeDictionary);
    modules['rlgl']=new source_parser(fs.readFileSync("thirdparty/raylib/src/rlgl.h", "utf8"));
    addModuleToDictionary(modules['rlgl'],"rlgl", (gen)=>{
        gen.includeGen.include("rlgl.h");
    });
    modules['rlgl'].gen = new rayjs_header("rlgl",includeDictionary);
    modules['rlightmapper']=new source_parser(fs.readFileSync("src/rlightmapper.h", "utf8"));
    addModuleToDictionary(modules['rlightmapper'],'rlightmapper',(gen)=>{
        if(!once['rlightmapper']){
            once['rlightmapper']=true;
            gen.includeGen.line("#define RLIGHTMAPPER_IMPLEMENTATION");
        }
        gen.includeGen.include("rlightmapper.h");
    });
    modules['rlightmapper'].gen = new rayjs_header("rlightmapper",includeDictionary);
    for(let key in modules)attachGetters(modules[key]);

    // Remove duplicate structs and functions from modules
    let dedup=new Set();
    for(let i=0;i<modules['core'].functions.length;i++){dedup.add(modules['core'].functions[i].name);}
    for(let i=0;i<modules['core'].structs.length;i++){dedup.add(modules['core'].structs[i].name);}
    for(let i=0;i<modules['core'].enums.length;i++){dedup.add(modules['core'].enums[i].name);}
    for(let i=0;i<modules['core'].aliases.length;i++){dedup.add(modules['core'].aliases[i].name);}
    for(let name in modules){
        //set access all fields by default
        for(let struct of modules[name].structs){
            struct.binding={createConstructor: true,properties:{}};
            const binding=struct.binding;
            for(let field of struct.fields){
                binding.properties[field.name]={get: true, set: true};
            }
        }
        if(name=='core')continue;
        removeDuplicates(modules[name],'functions',dedup);
        removeDuplicates(modules[name],'structs',dedup);
        removeDuplicates(modules[name],'enums',dedup);
        removeDuplicates(modules[name],'aliases',dedup);
    }
    modules['rlights'].getStruct('Light').binding = {
        properties: {
            type: { get: true, set: true },
            enabled: { get: true, set: true },
            position: { get: true, set: true },
            target: { get: true, set: true },
            color: { get: true, set: true },
            attenuation: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['rlightmapper'].getStruct('Lightmapper').binding.properties.data.sizeVars=['ptr->w * ptr->h * 4'];
    modules['rlightmapper'].getStruct('Lightmapper');
    modules['rlightmapper'].getStruct('Lightmapper').binding.properties['lm_handle']={};//Internal lightmapper context, no reason to bind this
    modules['rlightmapper'].getStruct('LightmapperConfig').binding = {
        properties: {
            hemisphereSize: { get: true, set: true },
            zNear: { get: true, set: true },
            zFar: { get: true, set: true },
            backgroundColor: { get: true, set: true },
            interpolationPasses: { get: true, set: true },
            interpolationThreshold: { get: true, set: true },
            cameraToSurfaceDistanceModifier: { get: true, set: true },
        },
        createConstructor: true
    };

    modules['core'].getStruct("Color").binding = {
        properties: {
            r: { get: true, set: true },
            g: { get: true, set: true },
            b: { get: true, set: true },
            a: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Rectangle").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
            width: { get: true, set: true },
            height: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Vector2").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Vector3").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
            z: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Vector4").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
            z: { get: true, set: true },
            w: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Ray").binding = {
        properties: {
            position: { get: false, set: true },
            direction: { get: false, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Camera2D").binding = {
        properties: {
            offset: { get: true, set: true },
            target: { get: true, set: true },
            rotation: { get: true, set: true },
            zoom: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Camera3D").binding = {
        properties: {
            position: { get: true, set: true },
            target: { get: true, set: true },
            up: { get: false, set: true },
            fovy: { get: true, set: true },
            projection: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("BoundingBox").binding = {
        properties: {
            min: { get: true, set: true },
            max: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Matrix").binding = {
        properties: {},
        createConstructor: false
    };
    modules['core'].getStruct("NPatchInfo").binding = {
        properties: {
            source: { get: true, set: true },
            left: { get: true, set: true },
            top: { get: true, set: true },
            right: { get: true, set: true },
            bottom: { get: true, set: true },
            layout: { get: true, set: true },
        },
        createConstructor: true
    };
    modules['core'].getStruct("Image").binding = {
        properties: {
            data: { set: true },
            width: { get: true, set: true },
            height: { get: true, set: true },
            mipmaps: { get: true, set: true },
            format: { get: true, set: true }
        },
        createConstructor: true
        //destructor: "UnloadImage"
    };
    modules['core'].getStruct("Wave").binding = {
        properties: {
            frameCount: { get: true },
            sampleRate: { get: true },
            sampleSize: { get: true },
            channels: { get: true }
        },
        createConstructor: true
        //destructor: "UnloadWave"
    };
    modules['core'].getStruct("Sound").binding = {
        properties: {
            frameCount: { get: true }
        },
        createConstructor: true
        //destructor: "UnloadSound"
    };
    modules['core'].getStruct("Music").binding = {
        properties: {
            stream: { get: true },
            frameCount: { get: true },
            looping: { get: true, set: true },
            ctxType: { get: true },
        },
        createConstructor: true
        //destructor: "UnloadMusicStream"
    };
    modules['core'].getStruct("Model").binding = {
        properties: {
            transform: { get: true, set: true },
            meshCount: { get: true },
            materialCount: { get: true },
            meshes: { get: true, set: true, sizeVars:['ptr->meshCount']},
            materials: { get: true, set: true, sizeVars:['ptr->materialCount'] },
            meshMaterial: { get: true, sizeVars:['ptr->meshCount'] },
            boneCount: { get: true },
            bones: { get: true, sizeVars:['ptr->boneCount'] },//TODO: check if there is a valid reason why we are disallowing set bones
            bindPose: { get: true, sizeVars:['ptr->boneCount'] }
        },
        createConstructor: true
        //destructor: "UnloadModel"
    };
    modules['core'].getStruct("ModelAnimation").binding.properties.bones.sizeVars=['ptr->boneCount'];
    modules['core'].getStruct("ModelAnimation").binding.properties.framePoses.sizeVars=['ptr->frameCount','ptr->boneCount'];
    modules['core'].getStruct("Mesh").binding = {
        properties: {
            vertexCount: { get: true, set: true },
            triangleCount: { get: true, set: true },
            vertices: { get: true, set: true, sizeVars:['ptr->vertexCount*3'] },
            texcoords: { get:true, set: true, sizeVars:['ptr->vertexCount*2'] },
            texcoords2: { set: true, sizeVars:['ptr->vertexCount*2'] },
            normals: { get:true, set: true, sizeVars:['ptr->vertexCount*3'] },
            tangents: { get: true, set: true, sizeVars:['ptr->vertexCount*4'] },
            colors: { get: true, set: true, sizeVars:['ptr->vertexCount*4'] },
            indices: { get: true, set: true, sizeVars:['ptr->vertexCount'] },
            animVertices: { get: true, set: true, sizeVars:['ptr->vertexCount*3'] },
            animNormals: { get: true, set: true, sizeVars:['ptr->vertexCount*3'] },
            boneIds: { get: true, set: true, sizeVars:['ptr->vertexCount*4'] },
            boneWeights: { get: true, set: true, sizeVars:['ptr->vertexCount*4'] },
        },
        createConstructor: true
        //destructor: "UnloadMesh"
    };
    modules['core'].getStruct("Shader").binding = {
        properties: {
            id: { get: true }
        },
        createConstructor: true
        //destructor: "UnloadShader"
    };
    modules['core'].getStruct("Texture").binding = {
        properties: {
            width: { get: true },
            height: { get: true },
            mipmaps: { get: true },
            format: { get: true },
        },
        createConstructor: true
        //destructor: "UnloadTexture"
    };
    modules['core'].getStruct("Font").binding = {
        properties: {
            baseSize: { get: true },
            glyphCount: { get: true },
            glyphPadding: { get: true },
			texture: { get: true },
        },
        createConstructor: true
        //destructor: "UnloadFont"
    };
    modules['core'].getStruct("RenderTexture").binding = {
        properties: {
            id: { get: true },
            texture: { get: true },
            depth: { get: true },
        },
        createConstructor: true
        //destructor: "UnloadRenderTexture"
    };
    modules['core'].getStruct("MaterialMap").binding = {
        properties: {
            texture: { set: true },
            color: { set: true, get: true },
            value: { get: true, set: true }
        },
        createConstructor: true
        //destructor: "UnloadMaterialMap"
    };
    modules['core'].getStruct("Material").binding = {
        properties: {
            shader: { get: true, set: true },
            maps: { get: true, sizeVars:[config.defined['MAX_MATERIAL_MAPS']] }
        },
        createConstructor: true
        //destructor: "UnloadMaterial"
    };
    modules['core'].getStruct("FilePathList").binding.properties.paths.sizeVars=["ptr->count"];
    modules['core'].getStruct("AutomationEventList").binding.properties.events.sizeVars=["ptr->count"];
    att = modules['rlgl'].getStruct("rlVertexBuffer").binding.properties;
    att.vertices.sizeVars=["ptr->elementCount*3*4"];
    att.texcoords.sizeVars=["ptr->elementCount*2*4"];
    att.normals.sizeVars=["ptr->elementCount*3*4"];
    att.colors.sizeVars=["ptr->elementCount*4*4"];
    if(att.indices!==undefined)att.indices.sizeVars=["ptr->elementCount*6"];
    att = modules['rlgl'].getStruct("rlRenderBatch").binding.properties;
    att.vertexBuffer.sizeVars=["ptr->bufferCount"];
    att.draws.sizeVars=["RL_DEFAULT_BATCH_DRAWCALLS"];
    const structDI = modules['core'].getStruct("VrDeviceInfo");
    structDI.binding = {
        properties: {
            hResolution: { set: true, get: true },
            vResolution: { set: true, get: true },
            hScreenSize: { set: true, get: true },
            vScreenSize: { set: true, get: true },
            eyeToScreenDistance: { set: true, get: true },
            lensSeparationDistance: { set: true, get: true },
            interpupillaryDistance: { set: true, get: true },
            lensDistortionValues: { set: true, get: true },
			chromaAbCorrection : { set: true, get: true }
        },
        createConstructor: true
    };
    modules['core'].getFunction("EndDrawing").binding = { after: gen => gen.call("app_update_quickjs", ['ctx']) };
    // Custom frame control functions
    // NOT SUPPORTED BECAUSE NEEDS COMPILER FLAG
    modules['core'].ignore("SwapScreenBuffer");
    modules['core'].ignore("PollInputEvents");
    modules['core'].getFunction("SetShaderValue").binding = { body: (gen) => {
        gen.jsToC("Shader", "shader", "argv[0]");
        gen.jsToC("int", "locIndex", "argv[1]");
        gen.declare("void *", "value", false, "NULL");
        gen.declare("JSValue", "da_value");
        gen.jsToC("int", "uniformType", "argv[3]");
        const sw = gen.switch("uniformType");
        //Named VEC but examples and inner code use (float *) technically the same
        let b = sw.caseBreak("SHADER_UNIFORM_FLOAT");
            b.jsToC("float &", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_VEC2");
            b.jsToC("float [2]", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_VEC3");
            b.jsToC("float [3]", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_VEC4");
            b.jsToC("float [4]", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        sw.case("SHADER_UNIFORM_INT");
        b = sw.caseBreak("SHADER_UNIFORM_SAMPLER2D");
            b.jsToC("int &", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_IVEC2");
            b.jsToC("int [2]", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_IVEC3");
            b.jsToC("int [3]", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_IVEC4");
            b.jsToC("int [4]", "val", "argv[2]");
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.defaultBreak();
            b.call('JS_ThrowTypeError',['ctx',`"unknown uniformType"`]);
            b.returnExp("JS_EXCEPTION");
        gen.call("SetShaderValue", ["shader", "locIndex", "value", "uniformType"]);
        gen.jsCleanUpParameter("void *", 'value', "argv[2]");
        gen.returnExp("JS_UNDEFINED");
    } };
    modules['core'].getFunction("SetShaderValueV").binding = { body: (gen) => {
            gen.jsToC("Shader", "shader", "argv[0]");
            gen.jsToC("int", "locIndex", "argv[1]");
            gen.jsToC("int", "uniformType", "argv[3]");
            gen.jsToC("int", "count", "argv[4]");
            gen.declare("void *", "value", false, "NULL");
            gen.declare("JSValue", "da_value");
            const sw = gen.switch("uniformType");
            //Named VEC but examples and inner code use (float *) technically the same
            let b;
            sw.case("SHADER_UNIFORM_FLOAT");
            sw.case("SHADER_UNIFORM_VEC2");
            sw.case("SHADER_UNIFORM_VEC3");
            b = sw.caseBreak("SHADER_UNIFORM_VEC4");
                b.jsToC("float *", "val", "argv[2]");
                b.statement("value = (void *)val");b.statement("da_value = da_val");
            sw.case("SHADER_UNIFORM_INT");
            sw.case("SHADER_UNIFORM_SAMPLER2D");
            sw.case("SHADER_UNIFORM_IVEC2");
            sw.case("SHADER_UNIFORM_IVEC3");
            b = sw.caseBreak("SHADER_UNIFORM_IVEC4");
                b.jsToC("int *", "val", "argv[2]");
                b.statement("value = (void*)val");b.statement("da_value = da_val");
            b = sw.defaultBreak();
                b.call('JS_ThrowTypeError',['ctx',`"unknown uniformType"`]);
                b.returnExp("JS_EXCEPTION");
            gen.call("SetShaderValueV", ["shader", "locIndex", "value", "uniformType",'count']);
            gen.jsCleanUpParameter("void *", 'value', "argv[2]");
            gen.returnExp("JS_UNDEFINED");
        } };
    modules['core'].getFunction("SetShaderValueV").params.find(a=>a.name=='value').name='values';


    /*******OPINION*********/
    //Opinion sections exist due to developer opinion and shall be accessable behind a config flag (TODO)
    // JS User has no need to raw allocate memory
    modules['core'].ignore("MemAlloc");
    modules['core'].ignore("MemRealloc");
    modules['core'].ignore("MemFree");
    // JS User should never freeze process using sleep (no async will fire)
    modules['core'].ignore("WaitTime");
    // Right now, it is not usefull to users to get native window handler address
    modules['core'].ignore("GetWindowHandle");
    /*******OPINION*********/

    // SetTraceLogCallback uses va_list and as such needs custom any[] implementation
    modules['core'].getFunction("ComputeMD5").returnSizeVars = [4];
    modules['core'].getFunction("ComputeSHA1").returnSizeVars = [5];
    modules['core'].ignore("TraceLogCallback");
    modules['core'].ignore("SetTraceLogCallback");
    // Files management functions
    att = modules['core'].getFunction("LoadFileData");
    //att.params.find(a=>a.name=='dataSize').type='int &';
    att.returnSizeVars = ['dataSize[0]'];
    att.returnType = "void *";//casting to void* is an estetic choice to use buffer like SaveFileData
    att.binding.after = gen => gen.call("UnloadFileData", ["returnVal"]);
    modules['core'].ignore("UnloadFileData");
    att = modules['core'].getFunction("ExportImageToMemory");
    att.returnSizeVars = ['fileSize[0]'];
    // TODO: SaveFileData works but unnecessary makes copy of memory
    modules['core'].getFunction("SaveFileData").binding = {};
    modules['core'].getFunction("LoadFileText").binding.after = gen => gen.call("UnloadFileText", ["returnVal"]);
    modules['core'].ignore("UnloadFileText");
    const createFileList = (gen, loadName, unloadName, args) => {
        gen.call(loadName, args, { type: "FilePathList", name: "files" });
        gen.call("JS_NewArray", ["ctx"], { type: "JSValue", name: "ret" });
        const f = gen.for("0", "files.count");
        f.call("JS_SetPropertyUint32", ["ctx", "ret", "i", "JS_NewString(ctx,files.paths[i])"]);
        gen.call(unloadName, ["files"]);
    };
    modules['core'].getFunction("LoadDirectoryFiles").binding = {
        jsReturns: "string[]",
        body: gen => {
            gen.jsToC("const char *", "dirPath", "argv[0]");
            createFileList(gen, "LoadDirectoryFiles", "UnloadDirectoryFiles", ["dirPath"]);
            gen.statement(`JS_FreeCString(ctx, dirPath)`);
            gen.returnExp("ret");
        }
    };
    modules['core'].getFunction("LoadDirectoryFilesEx").binding = {
        jsReturns: "string[]",
        body: gen => {
            gen.jsToC("const char *", "basePath", "argv[0]");
            gen.jsToC("const char *", "filter", "argv[1]");
            gen.jsToC("bool", "scanSubdirs", "argv[2]");
            createFileList(gen, "LoadDirectoryFilesEx", "UnloadDirectoryFiles", ["basePath", "filter", "scanSubdirs"]);
            gen.statement(`JS_FreeCString(ctx, basePath)`);
            gen.statement(`JS_FreeCString(ctx, filter)`);
            gen.returnExp("ret");
        }
    };
    modules['core'].ignore("UnloadDirectoryFiles");
    modules['core'].getFunction("LoadDroppedFiles").binding = {
        jsReturns: "string[]",
        body: gen => {
            createFileList(gen, "LoadDroppedFiles", "UnloadDroppedFiles", []);
            gen.returnExp("ret");
        }
    };
    modules['core'].ignore("UnloadDroppedFiles");
    modules['core'].getFunction("LoadImageColors").binding = {
        jsReturns: "ArrayBuffer",
        body: gen => {
            gen.jsToC("Image", "image", "argv[0]");
            gen.call("LoadImageColors", ["image"], { name: "colors", type: "Color *" });
            gen.statement("JSValue retVal = JS_NewArrayBufferCopy(ctx, (const uint8_t*)colors, image.width*image.height*sizeof(Color))");
            gen.call("UnloadImageColors", ["colors"]);
            gen.returnExp("retVal");
        }
    };
    let applyffix=false;
    const lfx = modules['core'].getFunction("LoadFontEx");
    if(applyffix){
        lfx.params[2].binding = { ignore: true };
        lfx.params[3].binding = { ignore: true };
        lfx.binding = { customizeCall: "Font returnVal = LoadFontEx(fileName, fontSize, NULL, 0);" };
    }else{
        lfx.params[2].binding = { allowNull: true };
    }
    if(!config.bindText){
        //Text functions are enabled for compatibility
        modules['core'].functions.filter(x => x.name.startsWith("Text")).forEach(x => modules['core'].ignore(x.name));
    }else{
        /*******OPINION*********/
        //Using textCopy is more cumbersome than doing it natively, due to not supporting C string offsets
        modules['core'].ignore("TextCopy");
        /*******OPINION*********/
        //modules['core'].getFunction("TextCopy").params.find(parm => parm.name === 'dst').type='char * &';
        modules['core'].getFunction("TextFormat").binding.body=(gen)=>{
            //TODO: Can improve performance by reusing buffers (static)
            let bufferdefined=false;
            const errorCleanupFn =(ctx)=>{
                ctx.call('memoryClear',['ctx','memoryHead']);
                ctx.call('js_free',['ctx','char_ptr']);
                if(bufferdefined)ctx.call('js_free',['ctx','buffer']);
            };
            let flags={dynamicAlloc:true};//reduces code size
            gen.declare('memoryNode *', 'memoryHead',false,`(memoryNode *)calloc(1,sizeof(memoryNode))`);
            gen.declare('memoryNode *', 'memoryCurrent',false,'memoryHead');

            gen.declare('size_t','char_ptrlen',false,10);
            gen.declare('char *','char_ptr',false,'(char *)js_calloc(ctx, char_ptrlen, sizeof(char))');
            gen.declare("int64_t","formatlen");
            let fi = gen.if('JS_GetLength(ctx,argv[0],&formatlen)==-1');
            errorCleanupFn(fi);
            fi.returnExp("JS_EXCEPTION");
            gen.jsToC('char *','format','argv[0]',flags);
            gen.declare('char *','subformat',false,`format`);
            gen.declare('size_t','subformatlen',false,0);
            gen.declare('char','subformatlenh');
            gen.declare('size_t','bufferlen',false,'formatlen*2');
            gen.declare('char *','buffer',false,'(char *)js_calloc(ctx, bufferlen, sizeof(char))');
            bufferdefined=true;
            gen.declare('int','l',false,0);
            gen.declare('int','c',false,1);
            gen.declare('int','ilen',false,0);
            let t0,t1,t2,t3,t4,t5,t6;
            t0=gen.for(0, 'formatlen');
                t0.declare('int','n',false,2);
                t0.declare('int','w',false,0);
                t0.declare('int','p',false,0);
                t1=t0.if("format[i]!='%'");
                    t1.statement('buffer[l]=format[i]');
                    t1.statement('l++');
                t1=t0.else();
                    t1.declare('int','firsth',false,'i+1');
                    t1.declare('char','har',false,'format[firsth]');
                        t2=t1.if('har==0');
                        t2.cToJs('char *','ret','buffer',{},0,['l']);
                        errorCleanupFn(t2);
                        t2.returnExp('ret');
                    t2=t1.while("!(har>=97&&har<=122)&&!(har>=65&&har<=90)&&har!='%'");
                        t2.statement('firsth++');
                        t2.statement('har=format[firsth]');
                        t3=t2.if('har==0');
                            t3.cToJs('char *','ret','buffer',{},0,['l']);
                            errorCleanupFn(t3);
                            t3.returnExp('ret');
                    t1.declare('int','lasth',false,'firsth');
                    t1.statement('har=format[lasth]');
                    t2=t1.while('strchr("diuoxXfFeEfFeEgGaAcspn%", har)==NULL');
                        t3=t2.if("har=='*'");
                            t4=t3.if("n==1");
                                t4.declare('int','w',false,'p',true);
                            t3.jsToC('int','p','argv[c]',flags,0,errorCleanupFn);
                            t3.statement('c++');
                            t3.statement('n--');
                        t2.statement('lasth++');
                        t2.declare('char','har',false,'format[lasth]',true);
                        t3=t2.if('har==0');
                            t3.cToJs('char *','ret','buffer',{},0,['l']);
                            errorCleanupFn(t3);
                            t3.returnExp('ret');
                    t1.declare('size_t','subformatlen',false,'lasth-i+1',true);
                    t1.declare('char','subformatlenh',false,'format[lasth+1]',true);
                    t1.declare('char *','subformat',false,'format+i',true);
                    t1.statement('subformat[subformatlen]=0');
                    t2=t1.if("format[lasth]=='%'");
                        t2.declare('int','i',false,'lasth',true);
                        t2.statement("buffer[l]='%'");
                        t2.statement("l++");
                        t2.statement("continue");
                    t1.statement('memset(char_ptr,0,ilen * sizeof(char))');
                    t2=t1.switch('har');
                        t2.case("'d'");
                        t3=t2.caseBreak("'i'");
                            t3.jsToC('int64_t','a','argv[c]',flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(int)a'],{name:'char_ptr'});
                            t4=t3.else().switch('format[lasth-1]');
                                t5=t4.caseBreak("'h'");
                                    t6=t5.if("subformat[lasth-i-2]=='h'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(signed char)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(short int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'l'");
                                    t6=t5.if("subformat[lasth-i-2]=='l'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(long long int)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(long int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'j'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(intmax_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'z'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(size_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'t'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(ptrdiff_t)a'],{name:'char_ptr'});
                                //Dont do anything on default, if this is a broken format, let it be skipped
                        t2.case("'u'");
                        t2.case("'o'");
                        t2.case("'x'");
                        t3=t2.caseBreak("'X'");
                            t3.jsToC('uint32_t','a','argv[c]',flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(unsigned int)a'],{name:'char_ptr'});
                            t4=t3.else().switch('subformat[lasth-i-1]');
                                t5=t4.caseBreak("'h'");
                                    t6=t5.if("subformat[lasth-i-2]=='h'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(unsigned char)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(unsigned short int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'l'");
                                    t6=t5.if("subformat[lasth-i-2]=='l'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(unsigned long long int)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(unsigned long int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'j'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(uintmax_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'z'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(size_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'t'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(ptrdiff_t)a'],{name:'char_ptr'});
                                //Dont do anything on default, if this is a broken format, let it be skipped
                        t2.case("'f'");
                        t2.case("'F'");
                        t2.case("'e'");
                        t2.case("'E'");
                        t2.case("'g'");
                        t2.case("'G'");
                        t2.case("'a'");
                        t3=t2.caseBreak("'A'");
                            t3.jsToC('double','a','argv[c]',flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(double)a'],{name:'char_ptr'});
                            t4=t3.else();
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(long double)a'],{name:'char_ptr'});
                        t3=t2.caseBreak("'c'");
                            t3.jsToC('int','a','argv[c]',flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(int)a'],{name:'char_ptr'});
                            t4=t3.else();
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(wint_t)a'],{name:'char_ptr'});
                        t3=t2.caseBreak("'s'");
                            t4=t3.if('firsth==lasth');
                                t4.jsToC('char *','a','argv[c]',flags,0,errorCleanupFn);
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','a'],{name:'char_ptr'});
                            t4=t3.else();
                                t4.jsToC('wchar_t *','a','argv[c]',flags,0,errorCleanupFn);
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','a'],{name:'char_ptr'});
                        t3=t2.caseBreak("'p'");
                            t3.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','n','w','p','(void *)&argv[c]'],{name:'char_ptr'});
                        t3=t2.caseBreak("'n'");
                            t3.cToJs('int &','argv[c]','(&l)',{dynamicAlloc:true,supressDeclaration:true});
                    t1.statement('subformat[subformatlen]=subformatlenh');
                    t1.statement('c++');
                    t1.declare('int','ilen',false,'strlen(char_ptr)',true);
                    t1.declare('int','maxstrlen',false,'formatlen+l+ilen-lasth');
                    t2=t1.if('bufferlen<maxstrlen');
                        t2.declare('char *','buffer',false,'js_realloc(ctx,buffer,maxstrlen)',true);
                        t2.call('memset',['buffer+bufferlen',0,'maxstrlen-bufferlen']);
                        t2.declare('int','bufferlen',false,'maxstrlen',true);
                    t1.call('strncpy',['buffer+l','char_ptr','ilen']);
                    t1.statement('l+=ilen');
                    t1.declare('int','i',false,'lasth',true);
            gen.cToJs('char *','js_buffer','buffer');
            errorCleanupFn(gen);
            gen.returnExp('js_buffer');
        };
    }
    att = modules['core'].getFunction("LoadWaveSamples");
    att.returnSizeVars = ['wave.frameCount*wave.channels'];
    att.binding.after = gen => gen.call("UnloadWaveSamples", ["returnVal"]);
    // requires returning pointer
    att = modules['rlgl'].getFunction("rlReadTexturePixels");
    if(config.defined['GRAPHICS_API_OPENGL_11'] || config.defined['GRAPHICS_API_OPENGL_33']){
        att.returnSizeVars = ['GetPixelDataSize(width, height, format)'];
    }else if(config.defined['GRAPHICS_API_OPENGL_ES2']){
        att.returnSizeVars = ['GetPixelDataSize(width, height, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)'];
    }else{
        modules['rlgl'].ignore("rlReadTexturePixels");
    }
    att = modules['rlgl'].getFunction("rlGetShaderLocsDefault");
    att.returnSizeVars = [String(config.defined['RL_MAX_SHADER_LOCATIONS'])];
    // Wave/Sound management functions
    modules['core'].ignore("SetAudioStreamCallback");
    modules['core'].ignore("AttachAudioStreamProcessor");
    modules['core'].ignore("DetachAudioStreamProcessor");
    att = modules['core'].getCallback("AudioCallback");
    att.params[0].type='float *';
    att.binding.threaded = true;
    //audioCallback has different sizes depending on what called it
    cb = structuredClone(att);
    cb.name='AudioStreamCallback';
    cb.params[0].sizeVars = ['arg_frames*2'];
    modules['core'].callbacks.push(cb);
    modules['core'].getFunction('SetAudioStreamCallback').params[1].type='AudioStreamCallback';
    cb = structuredClone(att);
    cb.name='AudioMixedProcessor';
    cb.params[0].type += ' &';
    cb.params[0].sizeVars = [`arg_frames*${config.defined['AUDIO_DEVICE_CHANNELS']}`];
    modules['core'].callbacks.push(cb);
    modules['core'].getFunction('AttachAudioMixedProcessor').params[0].type='AudioMixedProcessor';
    att = modules['core'].getCallback("SaveFileDataCallback");
    att.params[1].type='unsigned char *';
    att.params[1].sizeVars=['arg_dataSize'];
    // Requires fixes to void* parameters
    modules['rlgl'].ignore("rlLoadExtensions");
    modules['rlgl'].ignore("rlSetVertexAttributeDefault");
    modules['rlgl'].ignore("rlSetUniform");
    att = modules['core'].getFunction("LoadRandomSequence");
    att.returnSizeVars = ['count'];
    att.binding = { after: gen => gen.call("UnloadRandomSequence", ['returnVal']) };
    att = modules['rlgl'].getFunction("rlReadScreenPixels");
    att.returnSizeVars = ['width*height*4'];
    function detectPointer(fn){//A compressed way to separate pointers from arrays with the advantage of being somewhat generic
        for(let i=0;i<fn.params.length;i++){
            const parm=fn.params[i];
            if(parm.type.endsWith(' *')>0){
                if(fn.params.length==1 && !parm.type.endsWith('char *')){//Arrays tend to require length int but strings not
                    parm.type=parm.type.replaceAt(parm.type.length-1,'&');
                    continue;
                }
                const name=parm.name.toLowerCase();
                const subtype=parm.type.toLowerCase().substring(0,parm.type.length-2);
                //common names
                if(name==subtype || ['dst','texture','view','active','alpha','filesize','datasize','count','position','value','frames','lm','checked','scrollindex'].includes(name)){
                    parm.type=parm.type.replaceAt(parm.type.length-1,'&');
                }else
                if(name.endsWith('s')){
                    continue;
                }else
                if(subtype.startsWith('vector') || subtype.startsWith('quaternion')){
                    parm.type=parm.type.replaceAt(parm.type.length-1,'&');
                }
            }
        }
    }
    //manual reference assignment
    att = modules['raygui'].getFunction('GuiColorPicker').params[2];
    att.type = att.type.replaceAt(att.type.length-1,'&');
    for(let key in modules){
        modules[key].functions.forEach(detectPointer);
        modules[key].callbacks.forEach(detectPointer);
    }
    att = modules['raygui'].getFunction('GuiTextBox').params[1];
    att.type = att.type + ' &';
    cb = modules['core'].getStruct('AudioStream').fields;
    att = cb.find(field=>field.name=='buffer');
    att.type = att.type.replace(" *"," &");
    att = cb.find(field=>field.name=='processor');
    att.type = att.type.replace(" *"," &");
    //Dont allow using buffer (searching for typedef source is not supported yet)
    modules['core'].getStruct('AudioStream').binding.properties.buffer={};
    modules['core'].getStruct('AudioStream').binding.properties.processor={};
    modules['core'].getStruct('rAudioBuffer').binding.createConstructor=false;
    modules['core'].getStruct('rAudioProcessor').binding.createConstructor=false;

    modules['core'].getFunction('LoadShader').params[0].binding.allowNull=true;
    modules['raygui'].getFunction('GuiSpinner').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiValueBox').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiColorPicker').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiSlider').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiSliderBar').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiProgressBar').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiScrollPanel').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiGrid').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiColorBarAlpha').params[1].binding.allowNull=true;
    modules['raygui'].getFunction('GuiTextInputBox').params[6].binding.allowNull=true;
    modules['core'].getFunction('LoadAutomationEventList').params[0].binding.allowNull=true;

    modules['core'].ignore('bool');
    // Register types
    for(let key in modules){
        const module=modules[key];
        module.structs.forEach(x => module.gen.registerApiStruct(x));
        module.callbacks.forEach(x => module.gen.registerCallback(x));
    }
    for(let key in modules){
        const module=modules[key];
        module.aliases.forEach(x => module.gen.registerAlias(x));
    }
    //Generate Code
    for(let key in modules){
        const module=modules[key];
        module.structs.forEach(x => module.gen.addApiStruct_object(x));
        module.functions.forEach(x => module.gen.addApiFunction(x));
        module.enums.forEach(x => module.gen.addEnum(x));
        module.defines.forEach(x => {
            if(x.type=='bool' && x.name.endsWith('_H'))return;//GUARD
            if(x.type=='int'){
                module.gen.exportGlobalInt(x.name,x.description);
            }
            if(x.type=='float' || x.type=='double'){
                module.gen.exportGlobalDouble(x.name,x.description);
            }
            if(x.type=='struct'){
                let structId=module.gen.structLookup[x.content.type];
                if(structId!=undefined){
                    module.gen.exportGlobalStruct(x.content.type, x.name, x.content.values, x.description);
                }
            }
            if(x.type=='undefined' && module.gen.exported[x.content]!=undefined){
                const aliasof=module.gen.exported[x.content];
                if(aliasof=='int'){
                    module.gen.exportGlobalInt(x.name,x.description);
                }else if(aliasof=='float'){
                    module.gen.exportGlobalDouble(x.name,x.description);
                }
            }
        });
        module.gen.writeTo(`src/modules/${module.gen.name}.h`);
        module.gen.typings.writeTo(`bindings/typings/lib.${module.gen.name}.d.ts`);
    }
    const ignored = modules['core'].functions.filter(x => x.binding.ignore).length;
    console.log(`Converted ${modules['core'].functions.length+modules['core'].structs.length+modules['core'].callbacks.length - ignored}, ${ignored} ignored.`);
    console.log("Success!");
}
try{
    main();
}catch(e){
    console.log(e);
}
