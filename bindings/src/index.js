import * as fs from "./fs.js";
import * as raylib_header from "./raylib-header.js";
import source_parser from "./source_parser.js";
const config=JSON.parse(fs.readFileSync('bindings/config/buildFlags.json','utf8'));

String.prototype.replaceAt = function(index, replacement) {
    return this.substr(0, index) + replacement + this.substr(index+1);
};

let api;
function getFunction(funList, name) {
    return funList.find(x => x.name === name);
}
function getStruct(strList, name) {
    return strList.find(x => x.name === name);
}
function getAliases(aliasList, name) {
    return aliasList.filter(x => x.type === name).map(x => x.name);
}
function ignore(name) {
    getFunction(api.functions, name).binding = { ignore: true };
}
function normalizeType(type=''){
    return type.replaceAll("*", " * ").replaceAll('[',' [').replace(new RegExp("\\s+",'g'),' ').trim();
}
function deduplicateName(arr){
    let dedup=new Set();let j=0;
    for(let i=0;i<arr.length;i++){
        let f=arr[i];
        if(dedup.has(f.name)){
            continue;
        }else{
            dedup.add(f.name);
            arr[j]=f;
            j++;
        }
    }
    arr.splice(j,arr.length-j);
    return arr;
}
function main() {
    // Load the pre-generated raylib api
    api = JSON.parse(fs.readFileSync("thirdparty/raylib/parser/output/raylib_api.json", 'utf8'));
    //make sure json structure is as expected
    api.functions=api.functions.map(fn=>{
        return {
            returnType: normalizeType(fn.returnType),
            name: fn.name,
            params: (fn.params||[]).map( parm =>{
                return {
                    name: parm.name || "",
                    type: normalizeType(parm.type),
                    binding:{}
                }
            }),
            description: fn.description || "",
            binding:{}
        };
    });
    let mathSource=new source_parser(fs.readFileSync("thirdparty/raylib/src/raymath.h", "utf8"));
    api.functions=api.functions.concat(mathSource.functions);
    let rlglSource=new source_parser(fs.readFileSync("thirdparty/raylib/src/rlgl.h", "utf8"));
    api.functions=api.functions.concat(rlglSource.functions);
    api.structs=api.structs.concat(rlglSource.structs);
    let rcameraSource=new source_parser(fs.readFileSync("thirdparty/raylib/src/rcamera.h", "utf8"));
    api.functions=api.functions.concat(rcameraSource.functions);
    api.structs=api.structs.concat(rcameraSource.structs);
    let rguiSource=new source_parser(fs.readFileSync("thirdparty/raygui/src/raygui.h", "utf8"));
    api.functions=api.functions.concat(rguiSource.functions);
    api.enums=api.enums.concat(rguiSource.enums);
    let rlightsSource=new source_parser(fs.readFileSync("thirdparty/raylib/examples/shaders/rlights.h", "utf8"));
    api.functions=api.functions.concat(rlightsSource.functions);
    api.enums=api.enums.concat(rlightsSource.enums);
    api.structs=api.structs.concat(rlightsSource.structs);
    api.structs.find(a=>a.name=='Light').binding = {
        properties: {
            type: { get: true, set: true },
            enabled: { get: true, set: true },
            position: { get: true, set: true },
            target: { get: true, set: true },
            color: { get: true, set: true },
            attenuation: { get: true, set: true },
        },
    };
    let reasingsSource=new source_parser(fs.readFileSync("thirdparty/raylib/examples/others/reasings.h", "utf8"));
    api.functions=api.functions.concat(reasingsSource.functions);
    let rlightmapperSource=new source_parser(fs.readFileSync("src/rlightmapper.h", "utf8"));
    api.functions=api.functions.concat(rlightmapperSource.functions);
    api.structs=api.structs.concat(rlightmapperSource.structs);
    api.structs.find(a=>a.name=='Lightmapper').binding = {
        properties: {
            w: { get: true },
            h: { get: true },
            progress: { get: true }
        }
    };
    api.structs.find(a=>a.name=='LightmapperConfig').binding = {
        properties: {
            hemisphereSize: { get: true, set: true },
            zNear: { get: true, set: true },
            zFar: { get: true, set: true },
            backgroundColor: { get: true, set: true },
            interpolationPasses: { get: true, set: true },
            interpolationThreshold: { get: true, set: true },
            cameraToSurfaceDistanceModifier: { get: true, set: true },
        }
    };
    let rextensionsSource=new source_parser(fs.readFileSync("src/rextensions.h", "utf8"));
    api.functions=api.functions.concat(rextensionsSource.functions);
    // Deduplicate functions and structs
    let dedup=new Set();let j=0;
    for(let i=0;i<api.functions.length;i++){
        let f=api.functions[i];
        if(dedup.has(f.name)){
            continue;
        }else{
            dedup.add(f.name);
            api.functions[j]=f;
            j++;
        }
    }
    api.functions=deduplicateName(api.functions);
    api.structs=deduplicateName(api.structs);
    api.enums=deduplicateName(api.enums);
    // Define a new header
    const core = new raylib_header.RayLibHeader("raylib_core");
    core.includes.include("raymath.h");
    core.includes.include("rcamera.h");
    core.includes.line("#define RAYGUI_IMPLEMENTATION");
    core.includes.include("raygui.h");
    core.includes.line("#define RLIGHTS_IMPLEMENTATION");
    core.includes.include("rlights.h");
    core.includes.include("reasings.h");
    core.includes.line("#define RLIGHTMAPPER_IMPLEMENTATION");
    core.includes.include("rlightmapper.h");
    //core.includes.line("#define RLGL_IMPLEMENTATION");
    core.includes.include("rlgl.h");
    getStruct(api.structs, "Color").binding = {
        properties: {
            r: { get: true, set: true },
            g: { get: true, set: true },
            b: { get: true, set: true },
            a: { get: true, set: true },
        },
        createConstructor: true
    };
    getStruct(api.structs, "Rectangle").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
            width: { get: true, set: true },
            height: { get: true, set: true },
        },
        createConstructor: true
    };
    getStruct(api.structs, "Vector2").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
        },
        createConstructor: true
    };
    getStruct(api.structs, "Vector3").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
            z: { get: true, set: true },
        },
        createConstructor: true
    };
    getStruct(api.structs, "Vector4").binding = {
        properties: {
            x: { get: true, set: true },
            y: { get: true, set: true },
            z: { get: true, set: true },
            w: { get: true, set: true },
        },
        createConstructor: true,
        aliases: getAliases(api.aliases, "Vector4")
    };
    getStruct(api.structs, "Ray").binding = {
        properties: {
            position: { get: false, set: true },
            direction: { get: false, set: true },
        },
        createConstructor: true
    };
    getStruct(api.structs, "RayCollision").binding = {
        properties: {
            hit: { get: true, set: false },
            distance: { get: true, set: false },
            point: { get: true, set: false },
            normal: { get: true, set: false },
        },
        createConstructor: false
    };
    getStruct(api.structs, "Camera2D").binding = {
        properties: {
            offset: { get: true, set: true },
            target: { get: true, set: true },
            rotation: { get: true, set: true },
            zoom: { get: true, set: true },
        },
        createConstructor: true
    };
    getStruct(api.structs, "Camera3D").binding = {
        properties: {
            position: { get: true, set: true },
            target: { get: true, set: true },
            up: { get: false, set: true },
            fovy: { get: true, set: true },
            projection: { get: true, set: true },
        },
        createConstructor: true,
        aliases: getAliases(api.aliases, "Camera3D")
    };
    getStruct(api.structs, "BoundingBox").binding = {
        properties: {
            min: { get: true, set: true },
            max: { get: true, set: true },
        },
        createConstructor: true
    };
    getStruct(api.structs, "Matrix").binding = {
        properties: {},
        createConstructor: false
    };
    getStruct(api.structs, "NPatchInfo").binding = {
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
    getStruct(api.structs, "Image").binding = {
        properties: {
            data: { set: true },
            width: { get: true, set: true },
            height: { get: true, set: true },
            mipmaps: { get: true, set: true },
            format: { get: true, set: true }
        },
        createEmptyConstructor: true
        //destructor: "UnloadImage"
    };
    getStruct(api.structs, "Wave").binding = {
        properties: {
            frameCount: { get: true },
            sampleRate: { get: true },
            sampleSize: { get: true },
            channels: { get: true }
        },
        //destructor: "UnloadWave"
    };
    getStruct(api.structs, "Sound").binding = {
        properties: {
            frameCount: { get: true }
        },
        //destructor: "UnloadSound"
    };
    getStruct(api.structs, "Music").binding = {
        properties: {
            frameCount: { get: true },
            looping: { get: true, set: true },
            ctxType: { get: true },
        },
        //destructor: "UnloadMusicStream"
    };
    getStruct(api.structs, "Model").binding = {
        properties: {
            transform: { get: true, set: true },
            meshCount: { get: true },
            materialCount: { get: true },
            meshes: { get: true },
            materials: { get: true },
            meshMaterial: { get: true },
            boneCount: { get: true },
            bones: { get: true },
            bindPose: { get: true }
        },
        //destructor: "UnloadModel"
    };
    getStruct(api.structs, "Mesh").binding = {
        properties: {
            vertexCount: { get: true, set: true },
            triangleCount: { get: true, set: true },
            // TODO: Free previous pointers before overwriting
            vertices: { get: true, set: true },
            texcoords: { get:true, set: true },
            texcoords2: { set: true },
            normals: { get:true, set: true },
            tangents: { set: true },
            colors: { set: true },
            indices: { set: true },
            animVertices: { set: true },
            animNormals: { set: true },
            boneIds: { set: true },
            boneWeights: { set: true },
        },
        createEmptyConstructor: true
        //destructor: "UnloadMesh"
    };
    getStruct(api.structs, "Shader").binding = {
        properties: {
            id: { get: true }
        },
        //destructor: "UnloadShader"
    };
    getStruct(api.structs, "Texture").binding = {
        properties: {
            width: { get: true },
            height: { get: true },
            mipmaps: { get: true },
            format: { get: true },
        },
        aliases: getAliases(api.aliases, "Texture")
        //destructor: "UnloadTexture"
    };
    getStruct(api.structs, "Font").binding = {
        properties: {
            baseSize: { get: true },
            glyphCount: { get: true },
            glyphPadding: { get: true },
			texture: { get: true },
        },
        //destructor: "UnloadFont"
    };
    getStruct(api.structs, "RenderTexture").binding = {
        properties: {
            id: { get: true },
            texture: { get: true },
            depth: { get: true },
        },
        aliases: getAliases(api.aliases, "RenderTexture")
        //destructor: "UnloadRenderTexture"
    };
    getStruct(api.structs, "MaterialMap").binding = {
        properties: {
            texture: { set: true },
            color: { set: true, get: true },
            value: { get: true, set: true }
        },
        //destructor: "UnloadMaterialMap"
    };
    getStruct(api.structs, "Material").binding = {
        properties: {
            shader: { get: true, set: true },
            maps: { get: true }
        },
        //destructor: "UnloadMaterial"
    };
    const structDI = getStruct(api.structs, "VrDeviceInfo");
    structDI.fields.filter(x => x.name === "lensDistortionValues")[0].type = "Vector4";
    structDI.binding = {
        createEmptyConstructor: true,
        properties: {
            hResolution: { set: true, get: true },
            vResolution: { set: true, get: true },
            hScreenSize: { set: true, get: true },
            vScreenSize: { set: true, get: true },
            eyeToScreenDistance: { set: true, get: true },
            lensSeparationDistance: { set: true, get: true },
            interpupillaryDistance: { set: true, get: true },
			//below are Vector4 and float[4] that need custom read/write
            //lensDistortionValues: { set: true, get: true },
			//chromaAbCorrection : { set: true, get: true }
        }
    };
    getFunction(api.functions, "EndDrawing").binding = { after: gen => gen.call("app_update_quickjs", ['ctx']) };
    ignore("SetWindowIcons");
    ignore("GetWindowHandle");
    // Custom frame control functions
    // NOT SUPPORTED BECAUSE NEEDS COMPILER FLAG
    ignore("SwapScreenBuffer");
    ignore("PollInputEvents");
    ignore("WaitTime");
    //ignore("BeginVrStereoMode")
    //ignore("EndVrStereoMode")
    //ignore("LoadVrStereoConfig")
    //ignore("UnloadVrStereoConfig")
    getFunction(api.functions, "SetShaderValue").binding = { body: (gen) => {
        gen.jsToC("Shader", "shader", "argv[0]", core.structLookup);
        gen.jsToC("int", "locIndex", "argv[1]", core.structLookup);
        gen.declare("void *", "value", false, "NULL");
        gen.declare("JSValue", "da_value");
        gen.jsToC("int", "uniformType", "argv[3]", core.structLookup);
        const sw = gen.switch("uniformType");
        //Named VEC but examples and inner code use (float *) technically the same
        let b = sw.caseBreak("SHADER_UNIFORM_FLOAT");
            b.jsToC("float &", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_VEC2");
            b.jsToC("float [2]", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_VEC3");
            b.jsToC("float [3]", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_VEC4");
            b.jsToC("float [4]", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        sw.case("SHADER_UNIFORM_INT");
        b = sw.caseBreak("SHADER_UNIFORM_SAMPLER2D");
            b.jsToC("int &", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_IVEC2");
            b.jsToC("int [2]", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_IVEC3");
            b.jsToC("int [3]", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.caseBreak("SHADER_UNIFORM_IVEC4");
            b.jsToC("int [4]", "val", "argv[2]", core.structLookup);
            b.statement("value = (void *)val");b.statement("da_value = da_val");
        b = sw.defaultBreak();
            b.call('JS_ThrowTypeError',['ctx',`"unknown uniformType"`]);
            b.returnExp("JS_EXCEPTION");
        gen.call("SetShaderValue", ["shader", "locIndex", "value", "uniformType"]);
        gen.jsCleanUpParameter("void *", 'value', "argv[2]", core.structLookup);
        gen.returnExp("JS_UNDEFINED");
    } };
    getFunction(api.functions, "SetShaderValueV").binding = { body: (gen) => {
            gen.jsToC("Shader", "shader", "argv[0]", core.structLookup);
            gen.jsToC("int", "locIndex", "argv[1]", core.structLookup);
            gen.jsToC("int", "uniformType", "argv[3]", core.structLookup);
            gen.jsToC("int", "count", "argv[4]", core.structLookup);
            gen.declare("void *", "value", false, "NULL");
            gen.declare("JSValue", "da_value");
            const sw = gen.switch("uniformType");
            //Named VEC but examples and inner code use (float *) technically the same
            let b;
            sw.case("SHADER_UNIFORM_FLOAT");
            sw.case("SHADER_UNIFORM_VEC2");
            sw.case("SHADER_UNIFORM_VEC3");
            b = sw.caseBreak("SHADER_UNIFORM_VEC4");
                b.jsToC("float *", "val", "argv[2]", core.structLookup);
                b.statement("value = (void *)val");b.statement("da_value = da_val");
            sw.case("SHADER_UNIFORM_INT");
            sw.case("SHADER_UNIFORM_SAMPLER2D");
            sw.case("SHADER_UNIFORM_IVEC2");
            sw.case("SHADER_UNIFORM_IVEC3");
            b = sw.caseBreak("SHADER_UNIFORM_IVEC4");
                b.jsToC("int *", "val", "argv[2]", core.structLookup);
                b.statement("value = (void*)val");b.statement("da_value = da_val");
            b = sw.defaultBreak();
                b.call('JS_ThrowTypeError',['ctx',`"unknown uniformType"`]);
                b.returnExp("JS_EXCEPTION");
            gen.call("SetShaderValueV", ["shader", "locIndex", "value", "uniformType",'count']);
            gen.jsCleanUpParameter("void *", 'value', "argv[2]", core.structLookup);
            gen.returnExp("JS_UNDEFINED");
        } };
    getFunction(api.functions, "SetShaderValueV").params.find(a=>a.name=='value').name='values';
    const traceLog = getFunction(api.functions, "TraceLog");
    traceLog.params?.pop();
    // JS User has no need to raw allocate memory
    ignore("MemAlloc");
    ignore("MemRealloc");
    ignore("MemFree");
    // Callbacks not yet implemented, qjs has calls, eval, interrupt needed for this
    ignore("SetTraceLogCallback");
    ignore("SetLoadFileDataCallback");
    ignore("SetSaveFileDataCallback");
    ignore("SetLoadFileTextCallback");
    ignore("SetSaveFileTextCallback");
    // Files management functions
    const lfd = getFunction(api.functions, "LoadFileData");
    lfd.params[lfd.params.length - 1].binding = { ignore: true };
    lfd.binding = {
        body: gen => {
            gen.jsToC("const char *", "fileName", "argv[0]");
            gen.declare("unsigned int", "bytesRead");
            gen.call("LoadFileData", ["fileName", "&bytesRead"], { type: "unsigned char *", name: "retVal" });
            gen.statement("JSValue buffer = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, bytesRead)");
            gen.call("UnloadFileData", ["retVal"]);
            gen.statement(`JS_FreeCString(ctx, fileName)`);
            gen.returnExp("buffer");
        }
    };
    ignore("UnloadFileData");
    // TODO: SaveFileData works but unnecessary makes copy of memory
    getFunction(api.functions, "SaveFileData").binding = {};
    ignore("ExportDataAsCode");
    getFunction(api.functions, "LoadFileText").binding = { after: gen => gen.call("UnloadFileText", ["returnVal"]) };
    ignore("UnloadFileText");
    const createFileList = (gen, loadName, unloadName, args) => {
        gen.call(loadName, args, { type: "FilePathList", name: "files" });
        gen.call("JS_NewArray", ["ctx"], { type: "JSValue", name: "ret" });
        const f = gen.for("0", "files.count");
        f.call("JS_SetPropertyUint32", ["ctx", "ret", "i", "JS_NewString(ctx,files.paths[i])"]);
        gen.call(unloadName, ["files"]);
    };
    getFunction(api.functions, "LoadDirectoryFiles").binding = {
        jsReturns: "string[]",
        body: gen => {
            gen.jsToC("const char *", "dirPath", "argv[0]");
            createFileList(gen, "LoadDirectoryFiles", "UnloadDirectoryFiles", ["dirPath"]);
            gen.statement(`JS_FreeCString(ctx, dirPath)`);
            gen.returnExp("ret");
        }
    };
    getFunction(api.functions, "LoadDirectoryFilesEx").binding = {
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
    ignore("UnloadDirectoryFiles");
    getFunction(api.functions, "LoadDroppedFiles").binding = {
        jsReturns: "string[]",
        body: gen => {
            createFileList(gen, "LoadDroppedFiles", "UnloadDroppedFiles", []);
            gen.returnExp("ret");
        }
    };
    ignore("UnloadDroppedFiles");
    // Compression/encoding functionality
    ignore("CompressData");
    ignore("DecompressData");
    ignore("EncodeDataBase64");
    ignore("DecodeDataBase64");
    ignore("DrawLineStrip");
    ignore("DrawTriangleFan");
    ignore("DrawTriangleStrip");
    ignore("CheckCollisionPointPoly");
    ignore("CheckCollisionLines");
    ignore("LoadImageAnim");
    ignore("ExportImageAsCode");
    getFunction(api.functions, "LoadImageColors").binding = {
        jsReturns: "ArrayBuffer",
        body: gen => {
            gen.jsToC("Image", "image", "argv[0]", core.structLookup);
            gen.call("LoadImageColors", ["image"], { name: "colors", type: "Color *" });
            gen.statement("JSValue retVal = JS_NewArrayBufferCopy(ctx, (const uint8_t*)colors, image.width*image.height*sizeof(Color))");
            gen.call("UnloadImageColors", ["colors"]);
            gen.returnExp("retVal");
        }
    };
    ignore("LoadImagePalette");
    ignore("UnloadImageColors");
    ignore("UnloadImagePalette");
    ignore("GetPixelColor");
    ignore("SetPixelColor");
    let applyffix=false;
    const lfx = getFunction(api.functions, "LoadFontEx");
    if(applyffix){
        lfx.params[2].binding = { ignore: true };
        lfx.params[3].binding = { ignore: true };
        lfx.binding = { customizeCall: "Font returnVal = LoadFontEx(fileName, fontSize, NULL, 0);" };
    }else{
        lfx.params[2].binding = { allowNull: true };
    }
    ignore("LoadFontFromMemory");
    ignore("LoadFontData");
    ignore("GenImageFontAtlas");
    ignore("UnloadFontData");
    ignore("ExportFontAsCode");
    ignore("DrawTextCodepoints");
    ignore("GetGlyphInfo");
    ignore("LoadUTF8");
    ignore("UnloadUTF8");
    ignore("LoadCodepoints");
    ignore("UnloadCodepoints");
    ignore("GetCodepointCount");
    ignore("GetCodepoint");
    ignore("GetCodepointNext");
    ignore("GetCodepointPrevious");
    ignore("CodepointToUTF8");
    if(!config.bindText){
        //Text functions are enabled for compatibility
        api.functions.filter(x => x.name.startsWith("Text")).forEach(x => ignore(x.name));
    }else{
        getFunction(api.functions, "TextCopy").params.find(parm => parm.name === 'dst').type='char * &';
        getFunction(api.functions, "TextFormat").binding.body=(gen)=>{
            //TODO: Can improve performance by reusing buffers (static)
            let bufferdefined=false;
            const errorCleanupFn =(ctx)=>{
                ctx.call('memoryClear',['ctx','memoryHead']);
                ctx.call('js_free',['ctx','char_ptr']);
                if(bufferdefined)ctx.call('js_free',['ctx','buffer']);
            };
            let flags={dynamicAlloc:true};//reduces code size
            gen.declare('memoryNode *', 'memoryHead',false,`(memoryNode *)calloc(1,sizeof(memoryNode))`);
            gen.declare('memoryNode *', 'memoryCurrent',false,'memoryHead;');

            gen.declare('size_t','char_ptrlen',false,10);
            gen.declare('char *','char_ptr',false,'(char *)js_calloc(ctx, char_ptrlen, sizeof(char))');
            gen.declare("size_t","formatlen");
            let fi = gen.if('JS_GetLength(ctx,argv[0],&formatlen)==-1');
            errorCleanupFn(fi);
            fi.returnExp("JS_EXCEPTION");
            gen.jsToC('char *','format','argv[0]',core.structLookup,flags);
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
                t1=t0.if("format[i]!='%'");
                    t1.statement('buffer[l]=format[i];');
                    t1.statement('i++');
                t1=t0.else();
                    t1.declare('int','firsth',false,'i+1');
                    t1.declare('char','har',false,'format[firsth]');
                        t2=t1.if('har==0');
                        t2.cToJs('char *','ret','buffer',core.structLookup,{},0,['l']);
                        errorCleanupFn(t2);
                        t2.returnExp('ret');
                    t2=t1.while("!(har>=97&&har<=122)&&!(har>=65&&har<=90)&&har!='%'");
                        t2.statement('firsth++');
                        t2.statement('har=format[firsth]');
                        t3=t2.if('har==0');
                            t3.cToJs('char *','ret','buffer',core.structLookup,{},0,['l']);
                            errorCleanupFn(t3);
                            t3.returnExp('ret');
                    t1.declare('int','lasth',false,'firsth');
                    t1.statement('har=format[lasth]');
                    t2=t1.while('strchr("diuoxXfFeEfFeEgGaAcspn%", har)==NULL');
                        t2.statement('lasth++');
                        t2.declare('char','har',false,'format[lasth]',true);
                        t3=t2.if('har==0');
                            t3.cToJs('char *','ret','buffer',core.structLookup,{},0,['l']);
                            errorCleanupFn(t3);
                            t3.returnExp('ret');
                    t1.declare('size_t','subformatlen',false,'lasth-i+1',true);
                    t1.declare('char','subformatlenh',false,'format[lasth+1]',true);
                    t1.declare('char *','subformat',false,'format+i',true);
                    t1.statement('subformat[subformatlen]=0');
                    t2=t1.if("format[lasth]=='%'");
                        t2.declare('int','i',false,'lasth',true);
                        t2.statement("buffer[l]='%';");
                        t2.statement("i++");
                        t2.statement("continue");
                    t1.statement('memset(char_ptr,0,ilen * sizeof(char))');
                    t2=t1.switch('har');
                        t2.case("'d'");
                        t3=t2.caseBreak("'i'");
                            t3.jsToC('int64_t','a','argv[c]',core.structLookup,flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(int)a'],{name:'char_ptr'});
                            t4=t3.else().switch('format[lasth-1]');
                                t5=t4.caseBreak("'h'");
                                    t6=t5.if("subformat[lasth-i-2]=='h'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(signed char)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(short int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'l'");
                                    t6=t5.if("subformat[lasth-i-2]=='l'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(long long int)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(long int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'j'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(intmax_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'z'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(size_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'t'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(ptrdiff_t)a'],{name:'char_ptr'});
                                //Dont do anything on default, if this is a broken format, let it be skipped
                        t2.case("'u'");
                        t2.case("'o'");
                        t2.case("'x'");
                        t3=t2.caseBreak("'X'");
                            t3.jsToC('uint32_t','a','argv[c]',core.structLookup,flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(unsigned int)a'],{name:'char_ptr'});
                            t4=t3.else().switch('subformat[lasth-i-1]');
                                t5=t4.caseBreak("'h'");
                                    t6=t5.if("subformat[lasth-i-2]=='h'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(unsigned char)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(unsigned short int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'l'");
                                    t6=t5.if("subformat[lasth-i-2]=='l'");
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(unsigned long long int)a'],{name:'char_ptr'});
                                    t6=t5.else();
                                        t6.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(unsigned long int)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'j'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(uintmax_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'z'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(size_t)a'],{name:'char_ptr'});
                                t5=t4.caseBreak("'t'");
                                    t5.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(ptrdiff_t)a'],{name:'char_ptr'});
                                //Dont do anything on default, if this is a broken format, let it be skipped
                        t2.case("'f'");
                        t2.case("'F'");
                        t2.case("'e'");
                        t2.case("'E'");
                        t2.case("'g'");
                        t2.case("'G'");
                        t2.case("'a'");
                        t3=t2.caseBreak("'A'");
                            t3.jsToC('double','a','argv[c]',core.structLookup,flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(double)a'],{name:'char_ptr'});
                            t4=t3.else();
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(long double)a'],{name:'char_ptr'});
                        t3=t2.caseBreak("'c'");
                            t3.jsToC('int','a','argv[c]',core.structLookup,flags,0,errorCleanupFn);
                            t4=t3.if('firsth==lasth');
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(int)a'],{name:'char_ptr'});
                            t4=t3.else();
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(wint_t)a'],{name:'char_ptr'});
                        t3=t2.caseBreak("'s'");
                            t4=t3.if('firsth==lasth');
                                t4.jsToC('char *','a','argv[c]',core.structLookup,flags,0,errorCleanupFn);
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','a'],{name:'char_ptr'});
                            t4=t3.else();
                                t4.jsToC('wchar_t *','a','argv[c]',core.structLookup,flags,0,errorCleanupFn);
                                t4.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','a'],{name:'char_ptr'});
                        t3=t2.caseBreak("'p'");
                            t3.call('asnprintf',['ctx','char_ptr','&char_ptrlen','subformat','(void *)&argv[c]'],{name:'char_ptr'});
                        t3=t2.caseBreak("'n'");
                            t3.cToJs('int &','argv[c]','(&l)',core.structLookup,flags);
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
            gen.cToJs('char *','js_buffer','buffer',core.structLookup);
            gen.returnExp('js_buffer');
        };
    }
    ignore("DrawTriangleStrip3D");
    ignore("LoadMaterials");
    ignore("LoadModelAnimations");
    ignore("UpdateModelAnimation");
    ignore("UnloadModelAnimation");
    ignore("UnloadModelAnimations");
    ignore("IsModelAnimationValid");
    ignore("ExportWaveAsCode");
    // Wave/Sound management functions
    ignore("SetAudioStreamCallback");
    ignore("AttachAudioStreamProcessor");
    ignore("DetachAudioStreamProcessor");
    ignore("AttachAudioMixedProcessor");
    ignore("DetachAudioMixedProcessor");
    ignore("Vector3ToFloatV");
    ignore("MatrixToFloatV");
    core.exportGlobalDouble("DEG2RAD", "(PI/180.0)");
    core.exportGlobalDouble("RAD2DEG", "(180.0/PI)");
    core.definitions.declare("char", "textbuffer[4096]", true);
    //ignore("GuiListViewEx");
    // needs string array
    ignore("GuiTabBar");
    ignore("GuiGetIcons");
    ignore("GuiLoadIcons");
    ignore("rlLoadExtensions");
    ignore("rlSetVertexAttributeDefault");
    ignore("rlSetUniform");
    api.structs.forEach(x => core.addApiStruct(x));
    api.functions.forEach(fn => {//A compressed way to separate pointers from arrays with the advantage of being somewhat generic
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
                if(name==subtype || ['dst','texture','view','active','alpha','filesize','count','position','value','frames','lm','checked','scrollindex'].includes(name)){
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
    });
    let f=getFunction(api.functions, "UnloadRandomSequence").params[0];f.type=f.type.replaceAt(f.type.length-1,'*');
    getFunction(api.functions,'LoadShader').params[0].binding.allowNull=true;
    getFunction(api.functions,'GuiSpinner').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiValueBox').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiColorPicker').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiSlider').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiSliderBar').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiProgressBar').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiScrollPanel').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiGrid').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiColorBarAlpha').params[1].binding.allowNull=true;
    getFunction(api.functions,'GuiTextInputBox').params[6].binding.allowNull=true;
    api.functions.forEach(x => core.addApiFunction(x));
    api.defines.filter(x => x.type === "COLOR").map(x => ({ name: x.name, description: x.description, values: (x.value.match(/\{([^}]+)\}/) || "")[1].split(',').map(x => x.trim()) })).forEach(x => {
        core.exportGlobalStruct("Color", x.name, x.values, x.description);
    });
    api.enums.forEach(x => core.addEnum(x));
    core.exportGlobalInt("MATERIAL_MAP_DIFFUSE", "Albedo material (same as: MATERIAL_MAP_DIFFUSE");
    core.exportGlobalInt("MATERIAL_MAP_SPECULAR", "Metalness material (same as: MATERIAL_MAP_SPECULAR)");
    core.writeTo("src/bindings/js_raylib_core.h");
    core.typings.writeTo("examples/lib.raylib.d.ts");
    const ignored = api.functions.filter(x => x.binding.ignore).length;
    console.log(`Converted ${api.functions.length - ignored} function. ${ignored} ignored`);
    console.log("Success!");
    // TODO: Expose PLatform defines
}
try{
    main();
}catch(e){
    console.log(e);
}
