/*******************************************************************************************
*
*   raylib [core] example - Custom logging
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example contributed by Pablo Marcos Oltra (@pamarcos) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Pablo Marcos Oltra (@pamarcos) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as rl from 'rayjs:raylib';
import {
    BeginDrawing, ClearBackground, CloseWindow, DrawText, EndDrawing,
    InitWindow, LIGHTGRAY,
    LOG_DEBUG,
    LOG_ERROR,
    LOG_INFO,
    LOG_WARNING, RAYWHITE,
    SetTargetFPS,
    TextFormat,
    WindowShouldClose
} from "rayjs:raylib";
for (const key in rl) { globalThis[key] = rl[key] };

function strftime(format,date,lang='en-US'){
    //Short strftime implementation to make the main code simpler
    let i=0;
    let output="";
    while(i<format.length){
        if(format[i]!='%'){
            output+=format[i];
            i++;
            continue;
        }
        function getYearDay(date){
            const year=date.getFullYear();
            let month=date.getMonth();
            let days=date.getDate();
            while(month>0){
                days+=(new Date(year,month,0)).getDate();
                month--;
            }
            return days;
        }
        switch(format[i+1]){
            case "a":output+=date.toLocaleString(lang,{weekday:'short'});break;
            case "A":output+=date.toLocaleString(lang,{weekday:'long'});break;
            case "b":output+=date.toLocaleString(lang,{month:'short'});break;
            case "B":output+=date.toLocaleString(lang,{month:'long'});break;
            case "c":output+=strftime('%a %b %w %x %Y',date);break;
            case "d":output+=String(date.getMonth()).padStart(2,'0');break;
            case "H":output+=String(date.getHours()).padStart(2,'0');break;
            case "I":
                const hours=date.getHours();
                output+=String(hours>12?hours:hours-12).padStart(2,'0');break;
            case "j":output+=getYearDay(date);break;
            case "m":output+=String(date.getMonth()+1).padStart(2,'0');break;
            case "M":output+=String(date.getMinutes()).padStart(2,'0');break;
            case "p":output+=String(date.getHours()>12?"AM":"PM").padStart(2,'0');break;
            case "S":output+=String(date.getSeconds()).padStart(2,'0');break;
            case "U":output+=String(date.getSeconds()).padStart(2,'0');break;
            case "w":output+=date.getDay();break;
            case "W":
                const first=(new Date(date.getFullYear(),0,1)).getDay();
                output+=(getYearDay(date)+first-2)/7;break;
            case "x":output+=strftime('%d/%m/%Y',date);break;
            case "X":output+=strftime('%H:%M:%S',date);break;
            case "y":output+=String(date.getFullYear()).substring(2);break;
            case "Y":output+=date.getFullYear();break;
            case "Z":output+=date.toLocaleDateString(lang, { timeZoneName: 'short' });break;
            case "%":output+='%';break;
            default:i++;continue;
        }
        i+=2;
    }
    return format;
}

// Custom logging function
function CustomLog(msgType, text, args){
    let timeStr = "";
    let now = new Date();

    timeStr = strftime("%Y-%m-%d %H:%M:%S",now);
    console.log(`[${timeStr}]`);

    switch (msgType) {
        case LOG_INFO: console.log("[INFO] : "); break;
        case LOG_ERROR: console.log("[ERROR]: "); break;
        case LOG_WARNING: console.log("[WARN] : "); break;
        case LOG_DEBUG: console.log("[DEBUG]: "); break;
        default: break;
    }

    console.log(TextFormat(text, args));
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    // Set custom logger
    SetTraceLogCallback(CustomLog);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom logging");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Check out the console output to see the custom logger in action!", 60, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
