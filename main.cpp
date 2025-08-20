
#include "raylib.h"
#include <iostream>
#include <cstdlib>

#define CELL_SIZE 15
#define CELL_COLOR DARKGRAY
#define LINE_COLOR WHITE

#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 900
#define GRID_WIDTH SCREEN_WIDTH / CELL_SIZE
#define GRID_HEIGHT SCREEN_HEIGHT / CELL_SIZE

int grid_filled[GRID_WIDTH][GRID_HEIGHT] = {0};

void DrawGridOutline(){
    // horizontal
    for (int x = 0; x < SCREEN_WIDTH; x += CELL_SIZE)
        DrawLine(x, 0, x, SCREEN_HEIGHT, LINE_COLOR);
    
    // vertical
    for (int y = 0; y < SCREEN_HEIGHT; y += CELL_SIZE)
        DrawLine(0, y, SCREEN_WIDTH, y, LINE_COLOR);

}

void FillCell(int x, int y, Color color){
    DrawRectangle(x * CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
}

void DrawFilledCells(){
    
    for (int x = 0; x < GRID_WIDTH; x++){
        for (int y = 0; y < GRID_HEIGHT; y++){
            if (grid_filled[x][y] == 0){
                FillCell(x, y, BLACK);
            } else {
                FillCell(x, y, WHITE);
            }
        }
    }
}

void DrawGrid()
{
    // Draw filled cells
    DrawFilledCells();
    // Draw grid outline
    DrawGridOutline();


}

void DrawSelection(){
    Vector2 mouse_pos = GetMousePosition();
    if ((mouse_pos.x < 0 || mouse_pos.x > SCREEN_WIDTH) || (mouse_pos.y < 0 || mouse_pos.y > SCREEN_HEIGHT)){
        printf("Clicking out of bounds...\n");
        return;
    }
    // printf("x: %f - y: %f\n", mouse_pos.x, mouse_pos.y);

    int cell_x = mouse_pos.x / CELL_SIZE;
    int cell_y = mouse_pos.y / CELL_SIZE;

    // printf("CELL = %d - %d\n", cell_x, cell_y);
    
    // Show currently selected cell
    FillCell(cell_x, cell_y, WHITE);

    // Store clicked cell
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        printf("Placed on cell %d-%d\n", cell_x, cell_y);
        grid_filled[cell_x][cell_y] = 1;
    }

    // printf("CELL x: %f - CELL y: %f\n", cell.x, cell.y);

}

void MoveSand() {
    // Iterate from bottom to top to avoid moving the same sand multiple times
    for (int y = GRID_HEIGHT - 2; y >= 0; y--) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid_filled[x][y] == 1) {
                // Try to move down
                if (grid_filled[x][y + 1] == 0) {
                    grid_filled[x][y + 1] = 1;
                    grid_filled[x][y] = 0;
                }
                else if (grid_filled[x - 1][y + 1] == 0) {
                    grid_filled[x - 1][y + 1] = 1;
                    grid_filled[x][y] = 0;
                }
                else if (grid_filled[x + 1][y + 1] == 0) {
                    grid_filled[x + 1][y + 1] = 1;
                    grid_filled[x][y] = 0;
                }
            }
        }
    }
}

// Copilot: Enable in Command Palette.

int main(void)
{
    printf("GRID WIDTH : %d\n", GRID_WIDTH);
    printf("GRID HEIGHT : %d\n", GRID_HEIGHT);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sand Simulation");
    SetWindowPosition(400, 100);
    
    SetTargetFPS(30);               
    
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);
        DrawGrid();
        DrawSelection();
            
        EndDrawing();

        MoveSand();        
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}