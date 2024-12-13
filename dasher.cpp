#include "raylib.h"

int main() {

    // Window dimensions
    const int windowHeight {450};
    const int windowWidth {800};
    const char windowTitle[] {"Dapper Dasher"};

    InitWindow(windowWidth, windowHeight, windowTitle);


    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RED);

        EndDrawing();
    }
}