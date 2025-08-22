
#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <string> 
using namespace std;


#define CELL_SIZE 10
#define CELL_COLOR DARKGRAY
#define LINE_COLOR WHITE

#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 600
#define GRID_WIDTH SCREEN_WIDTH / CELL_SIZE
#define GRID_HEIGHT SCREEN_HEIGHT / CELL_SIZE

#define TOP_BAR_WIDTH SCREEN_WIDTH
#define TOP_BAR_HEIGHT 100

static const Color DRY_SAND  = {194, 164, 108, 255}; // ochre
static const Color WET_SAND  = {150, 125,  85, 255};
static const Color ASH       = { 70,  70,  70, 255};
static const Color GLASS     = {190, 230, 230, 200};

Color COLORS[] = {DRY_SAND, WET_SAND, ASH, GLASS};

class Cell {       
    public:
        Vector2 pos;
        Color color;  
        bool filled;
    
        Cell() = default;
        Cell(Vector2 v, Color c) { 
            pos = v;
            color = c;
            filled = false;
        }
};

int grid_filled[GRID_WIDTH][GRID_HEIGHT] = {0};
Cell grid[GRID_WIDTH][GRID_HEIGHT];

void InitializeGrid(){
    for (int r = 0; r < GRID_WIDTH; r++){
        for (int c = 0; c < GRID_WIDTH; c++){
            Vector2 vec;
            vec.x = r;
            vec.y = c;
            grid[r][c] = Cell(vec, BLUE);
        }
    }
}

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
            if (grid[x][y].filled){
                FillCell(x, y, grid[x][y].color);
                printf("%d, %d filled\n", x, y);
            } else {
                FillCell(x, y, BLACK);
                printf("%d, %d not filled\n", x, y);
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
    
    // printf("x: %f - y: %f\n", mouse_pos.x, mouse_pos.y);

    int cell_x = mouse_pos.x / CELL_SIZE;
    int cell_y = mouse_pos.y / CELL_SIZE;

    // printf("CELL = %d - %d\n", cell_x, cell_y);
    
    // Show currently selected cell
    FillCell(cell_x, cell_y, WHITE);

    // Store clicked cell
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if ((mouse_pos.x < 0 || mouse_pos.x > SCREEN_WIDTH) || (mouse_pos.y < 0 || mouse_pos.y > SCREEN_HEIGHT)){
            printf("Clicking out of bounds...\n");
            return;
        }
        printf("Placed on cell %d-%d\n", cell_x, cell_y);
        grid[cell_x][cell_y].filled = true;
        cout << "x: " << cell_x << "y: " << cell_y << " is filled : " << grid[cell_x][cell_y].filled << endl;
    }
}

void MoveSand() {
    // Iterate from bottom to top to avoid moving the same sand multiple times
    for (int y = GRID_HEIGHT - 2; y >= 0; y--) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[x][y].filled) {
                // Try to move down
                if (!grid[x][y + 1].filled) {
                    grid[x][y + 1].filled = true;
                    grid[x][y].filled = false;
                }
                else if (x > 0 && !grid[x - 1][y + 1].filled) {
                    grid[x - 1][y + 1].filled = true;
                    grid[x][y].filled = false;
                }
                else if (x < GRID_WIDTH - 1 && !grid[x + 1][y + 1].filled) {
                    grid[x + 1][y + 1].filled = true;
                    grid[x][y].filled = false;
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

    printf("%d\n", COLORS[0].r);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT+TOP_BAR_HEIGHT, "Sand Simulation");
    SetWindowPosition(400, 100);
    
    int frameCounter = 30;
    char buff[100]; 
    SetTargetFPS(frameCounter);      
    Color sandColor;         
    int i = 0;
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);
        DrawGrid();
        DrawSelection();

        sandColor.r = i;
        sandColor.g = 0;
        sandColor.b = 0;
        sandColor.a = 255;
        i++;

        snprintf(buff, sizeof(buff), "Frame count: %d (change with up/down arrows)", frameCounter);
        DrawText(buff, 10, SCREEN_HEIGHT+10, 12, WHITE);

        EndDrawing();

        MoveSand();   
        if (IsKeyDown(KEY_UP)){
            frameCounter++;
            SetTargetFPS(frameCounter);               

        }
        if (IsKeyDown(KEY_DOWN)){
            frameCounter--;
            SetTargetFPS(frameCounter);               
        }     

        cout << boolalpha; 
        // printf("GRID: %.f-%.f is filled: ", grid[0][0].pos.x, grid[0][0].pos.y);
        // cout << "flag1: " << grid[0][0].filled << endl;
    }


    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}