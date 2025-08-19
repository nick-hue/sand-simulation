
#include "raylib.h"

#define CELL_SIZE 20

void draw_grid()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    for (int x = 0; x < screenWidth; x += CELL_SIZE)
    {
        DrawLine(x, 0, x, screenHeight, DARKGRAY);
    }

    for (int y = 0; y < screenHeight; y += CELL_SIZE)
    {
        DrawLine(0, y, screenWidth, y, DARKGRAY);
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        BeginDrawing();

            ClearBackground(BLACK);

            draw_grid();
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}