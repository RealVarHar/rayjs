import * as rl from 'rayjs:raylib';

{
    for (const key in rl) {
        globalThis[key] = rl[key]
    }
    ;

// This is a texture generator that creates placeholder textures
// An example how to use rayjs for quick tool-scripts

    InitWindow(100, 100, "Gen")

    const input = [["orange", ORANGE], ["green", LIME], ["purple", PURPLE], ["red", MAROON], ["lightgrey", LIGHTGRAY], ["grey", GRAY], ["blue", BLUE]]

    const outDir = "out/"
    input.forEach(t => {
        const [name, color] = t
        createPlaceholder(128, 128, color, 64, 32, `${outDir}grid_128_${name}.png`)
        createPlaceholder(64, 64, color, 32, 16, `${outDir}grid_64_${name}.png`)
        createPlaceholder(32, 32, color, 16, 8, `${outDir}grid_32_${name}.png`)
        createDoor(128, 128, color, `${outDir}door_${name}.png`)
        createWindow(128, 128, color, `${outDir}window_${name}.png`)
        createStairs(128, 128, color, `${outDir}stairs_${name}.png`)
    });
    createSpecial("CLIP", new Color(255, 0, 255, 255), `${outDir}CLIP.png`)
    createSpecial("SKIP", new Color(255, 0, 255, 255), `${outDir}SKIP.png`)


    CloseWindow()

    function createSpecial(text, color, filename) {
        const img = GenImageColor(32, 32, color);
        ImageDrawText(img, text, 2, 1, 10, WHITE);
        ExportImage(img, filename);
        UnloadImage(img);
    }

    function createDoor(sizex, sizey, color, filename) {
        const img = GenImageColor(sizex, sizey, color);
        DrawGrid(img, sizex, sizey, 8, blend(color, WHITE, 0.12));
        DrawGrid(img, sizex, sizey, 16, blend(color, WHITE, 0.25));
        DrawGrid(img, sizex, sizey, 32, blend(color, WHITE, 0.5));
        ImageDrawLine(img, 0, 0, sizex, 0, WHITE);
        ImageDrawLine(img, 0, 0, 0, sizey, WHITE);
        ImageDrawText(img, `Door 48x64`, 2, 1, 10, WHITE);
        ImageDrawRectangle(img, 40, 64, 48, 64, blend(color, BLACK, 0.5));
        ImageDrawRectangleLines(img, new Rectangle(40, 64, 48, 64 + 1), 1, WHITE);
        ExportImage(img, filename);
        UnloadImage(img);
    }

    function createStairs(sizex, sizey, color, filename) {
        const img = GenImageColor(sizex, sizey, color)
        DrawGrid(img, sizex, sizey, 16, blend(color, WHITE, 0.25))
        DrawGrid(img, sizex, sizey, 32, blend(color, WHITE, 0.5))
        ImageDrawLine(img, 0, 0, sizex, 0, WHITE)
        ImageDrawLine(img, 0, 0, 0, sizey, WHITE)
        ImageDrawText(img, `Steps 16x16`, 2, 1, 10, WHITE)
        let x = 0;
        const colDark = blend(color, BLACK, 0.5)
        for (let y = 0; y < sizey / 16; y++) {
            const sx = x * 16
            const sy = sizey - ((y + 1) * 16)
            ImageDrawRectangle(img, sx, sy, sizex - (x * 16), 16, colDark)
            x++
            ImageDrawLine(img, sx, sy, sx + 16, sy, WHITE)
            ImageDrawLine(img, sx, sy, sx, sy + 16, WHITE)
        }
        ExportImage(img, filename)
        UnloadImage(img)
    }

    function createWindow(sizex, sizey, color, filename) {
        const img = GenImageColor(sizex, sizey, color)
        DrawGrid(img, sizex, sizey, 8, blend(color, WHITE, 0.12))
        DrawGrid(img, sizex, sizey, 16, blend(color, WHITE, 0.25))
        DrawGrid(img, sizex, sizey, 32, blend(color, WHITE, 0.5))
        ImageDrawLine(img, 0, 0, sizex, 0, WHITE)
        ImageDrawLine(img, 0, 0, 0, sizey, WHITE)
        ImageDrawText(img, `Window 32x48`, 2, 1, 10, WHITE)
        ImageDrawRectangle(img, 48, 48, 32, 48, blend(color, BLACK, 0.5))
        ImageDrawRectangleLines(img, new Rectangle(48, 48, 32, 48), 1, WHITE)
        console.log(filename);
        ExportImage(img, filename)
        console.log(filename, 2);
        UnloadImage(img)
    }

    function createPlaceholder(sizex, sizey, color, grid, subgrid, filename) {
        const img = GenImageColor(sizex, sizey, color)
        DrawGrid(img, sizex, sizey, subgrid, blend(color, WHITE, 0.25))
        DrawGrid(img, sizex, sizey, grid, blend(color, WHITE, 0.5))
        ImageDrawLine(img, 0, 0, sizex, 0, WHITE)
        ImageDrawLine(img, 0, 0, 0, sizey, WHITE)
        ImageDrawText(img, `${sizex}x${sizey}`, 2, 1, 10, WHITE)
        ExportImage(img, filename)
        UnloadImage(img)
    }

    function drawGrid(img, w, h, size, color) {
        for (let y = 0; y < h; y += size) {
            ImageDrawLine(img, 0, y, w, y, color)
        }
        for (let x = 0; x < w; x += size) {
            ImageDrawLine(img, x, 0, x, h, color)
        }
    }

    function blend(c1, c2, alpha) {
        const b = (v1, v2) => v1 * (1 - alpha) + v2 * alpha
        return new Color(b(c1.r, c2.r), b(c1.g, c2.g), b(c1.b, c2.b), c1.a)
    }
}