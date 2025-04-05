import * as os from "qjs:os";
import * as rl from 'rayjs:raylib';
{
    for (const key in rl) { globalThis[key] = rl[key] };

    // Initialization
    //--------------------------------------------------------------------------------------
    var exponent = 1;
    var averageVolume = new Float32Array(400);   // Average volume history
    const screenWidth = 800;
    const screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [audio] example - processing mixed output");
    InitAudioDevice();              // Initialize audio device
    let myWorker = new os.Worker("./audio_mixed_processor_worker.js");
    myWorker.onmessage = function(e){
        //called as an asynchronous responce to postMessage
        averageVolume=e.data;
    };
    let music = LoadMusicStream("resources/country.mp3");
    let sound = LoadSound("resources/coin.wav");

    PlayMusicStream(music);

    SetTargetFPS(600);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);   // Update music buffer with new stream data
        // Modify processing variables
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_LEFT)) exponent -= 0.05;
        if (IsKeyPressed(KEY_RIGHT)) exponent += 0.05;

        if (exponent <= 0.5) exponent = 0.5;
        if (exponent >= 3) exponent = 3;
        myWorker.postMessage(exponent);// Ask worker to print its data and update exponent
        if (IsKeyPressed(KEY_SPACE)) PlaySound(sound);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("MUSIC SHOULD BE PLAYING!", 255, 150, 20, LIGHTGRAY);

            DrawText(TextFormat("EXPONENT = %.2f", exponent), 215, 180, 20, LIGHTGRAY);
            DrawRectangle(199, 199, 402, 34, LIGHTGRAY);
            for (let i = 0; i < 400; i++){
                DrawLine(201 + i, 232 - Math.floor(averageVolume[i] * 32), 201 + i, 232, MAROON);
            }
            DrawRectangleLines(199, 199, 402, 34, GRAY);
            DrawText("PRESS SPACE TO PLAY OTHER SOUND", 200, 250, 20, LIGHTGRAY);
            DrawText("USE LEFT AND RIGHT ARROWS TO ALTER DISTORTION", 140, 280, 20, LIGHTGRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    StopMusicStream(music);
    await new Promise(r=>{
        myWorker.onmessage = function(e){
            if(e.data===0)r();//answered, dead
        };
        myWorker.postMessage(0);// Ask worker to die
    });
    myWorker=undefined; // unasigning worker closes it

    UnloadSound(sound);   // Unload music stream buffers from RAM
    UnloadMusicStream(music);   // Unload music stream buffers from RAM

    CloseAudioDevice();         // Close audio device

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------*/
}