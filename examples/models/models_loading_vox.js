/*******************************************************************************************
*
*   raylib [models] example - Load models vox (MagicaVoxel)
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 4.0, last time updated with raylib 4.0
*
*   Example contributed by Johann Nadalutti (@procfxgen) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Johann Nadalutti (@procfxgen) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, GetTime, LoadModel, TraceLog, LOG_WARNING, TextFormat, GetModelBoundingBox, LoadShader, SHADER_LOC_VECTOR_VIEW, GetShaderLocation, SetShaderValue, SHADER_UNIFORM_VEC4, GRAY, SetTargetFPS, WindowShouldClose, IsMouseButtonDown, MOUSE_BUTTON_MIDDLE, GetMouseDelta, UpdateCameraPro, IsKeyDown, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_W, KEY_S, KEY_D, KEY_A, GetMouseWheelMove, IsMouseButtonPressed, MOUSE_BUTTON_LEFT, SHADER_UNIFORM_VEC3, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawModel, DrawGrid, WHITE, DrawSphereWires, DrawSphereEx, ColorAlpha, EndMode3D, DrawRectangle, DrawRectangleLines, DrawText, Fade, SKYBLUE, DARKBLUE, BLUE, GetFileName, EndDrawing, UnloadModel, CloseWindow } from 'rayjs:raylib';
import * as os from 'qjs:os';
import * as rm from 'rayjs:raymath';
import * as rli from 'rayjs:rlights';

const MAX_VOX_FILES = 4;

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
	GLSL_VERSION = 100;
}else{
	GLSL_VERSION = 330;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const screenWidth = 800;
	const screenHeight = 450;

	const voxFileNames = [
		"resources/models/vox/chr_knight.vox",
		"resources/models/vox/chr_sword.vox",
		"resources/models/vox/monu9.vox",
		"resources/models/vox/fez.vox"
	];

	InitWindow(screenWidth, screenHeight, "raylib [models] example - magicavoxel loading");

	// Define the camera to look into our 3d world
	let camera = new Camera();
	camera.position = new Vector3( 10, 10, 10 ); // Camera position
	camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
	camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
	camera.fovy = 45;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	//--------------------------------------------------------------------------------------
	// Load MagicaVoxel files
	let models = new Array(MAX_VOX_FILES);

	for (let i = 0; i < MAX_VOX_FILES; i++){
		// Load VOX file and measure time
		let t0 = GetTime() * 1000.0;
		models[i] = LoadModel(voxFileNames[i]);
		let t1 = GetTime() * 1000.0;

		TraceLog(LOG_WARNING, TextFormat("[%s] File loaded in %.3f ms", voxFileNames[i], t1 - t0));

		// Compute model translation matrix to center model on draw position (0, 0 , 0)
		let bb = GetModelBoundingBox(models[i]);
		let center = new Vector3();
		center.x = bb.min.x + (((bb.max.x - bb.min.x) / 2));
		center.z = bb.min.z + (((bb.max.z - bb.min.z) / 2));

		let matTranslate = rm.MatrixTranslate(-center.x, 0, -center.z);
		models[i].transform = matTranslate;
	}

	let currentModel = 0;

	//--------------------------------------------------------------------------------------
	// Load voxel shader
	let shader = LoadShader(TextFormat("resources/shaders/glsl%i/voxel_lighting.vs", GLSL_VERSION),
		TextFormat("resources/shaders/glsl%i/voxel_lighting.fs", GLSL_VERSION));

	// Get some required shader locations
	shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
	// NOTE: "matModel" location name is automatically assigned on shader loading, 
	// no need to get the location again if using that uniform name
	//shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

	// Ambient light level (some basic lighting)
	let ambientLoc = GetShaderLocation(shader, "ambient");
	SetShaderValue(shader, ambientLoc, [0.1, 0.1, 0.1, 1], SHADER_UNIFORM_VEC4);

	// Assign out lighting shader to model
	for (let i = 0; i < MAX_VOX_FILES; i++) {
		let m = models[i];
		for (let j = 0; j < m.materialCount; j++) {
			m.materials[j].shader = shader;
		}
	}

	// Create lights
	let lights = new Array(rli.MAX_LIGHTS);
	lights[0] = rli.CreateLight(rli.LIGHT_POINT, new Vector3( -20, 20, -20 ), rm.Vector3Zero(), GRAY, shader);
	lights[1] = rli.CreateLight(rli.LIGHT_POINT, new Vector3( 20, -20, 20 ), rm.Vector3Zero(), GRAY, shader);
	lights[2] = rli.CreateLight(rli.LIGHT_POINT, new Vector3( -20, 20, 20 ), rm.Vector3Zero(), GRAY, shader);
	lights[3] = rli.CreateLight(rli.LIGHT_POINT, new Vector3( 20, -20, -20 ), rm.Vector3Zero(), GRAY, shader);


	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	//--------------------------------------------------------------------------------------
	let modelpos = new Vector3();
	let camerarot = new Vector3();

	// Main game loop
	while (!WindowShouldClose()) {   // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
			const mouseDelta = GetMouseDelta();
			camerarot.x = mouseDelta.x * 0.05;
			camerarot.y = mouseDelta.y * 0.05;
		} else {
			camerarot.x = 0;
			camerarot.y = 0;
		}

		UpdateCameraPro(camera,
			new Vector3(
				(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * 0.1 -      // Move forward-backward
				(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * 0.1,
				(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * 0.1 -   // Move right-left
				(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * 0.1,
				0.0                                                // Move up-down
			),
			camerarot,
			GetMouseWheelMove() * -2);                              // Move to target (zoom)

		// Cycle between models on mouse click
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentModel = (currentModel + 1) % MAX_VOX_FILES;

		// Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
		let cameraPos = [ camera.position.x, camera.position.y, camera.position.z ];
		SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

		// Update light values (actually, only enable/disable them)
		for (let i = 0; i < rli.MAX_LIGHTS; i++) rli.UpdateLightValues(shader, lights[i]);

		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// Draw 3D model
		BeginMode3D(camera);

		DrawModel(models[currentModel], modelpos, 1, WHITE);
		DrawGrid(10, 1.0);

		// Draw spheres to show where the lights are
		for (let i = 0; i < rli.MAX_LIGHTS; i++) {
			if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2, 8, 8, lights[i].color);
			else DrawSphereWires(lights[i].position, 0.2, 8, 8, ColorAlpha(lights[i].color, 0.3));
		}

		EndMode3D();

		// Display info
		DrawRectangle(10, 400, 340, 60, Fade(SKYBLUE, 0.5));
		DrawRectangleLines(10, 400, 340, 60, Fade(DARKBLUE, 0.5));
		DrawText("MOUSE LEFT BUTTON to CYCLE VOX MODELS", 40, 410, 10, BLUE);
		DrawText("MOUSE MIDDLE BUTTON to ZOOM OR ROTATE CAMERA", 40, 420, 10, BLUE);
		DrawText("UP-DOWN-LEFT-RIGHT KEYS to MOVE CAMERA", 40, 430, 10, BLUE);
		DrawText(TextFormat("File: %s", GetFileName(voxFileNames[currentModel])), 10, 10, 20, GRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	// Unload models data (GPU VRAM)
	for (let i = 0; i < MAX_VOX_FILES; i++) UnloadModel(models[i]);

	CloseWindow();          // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}


