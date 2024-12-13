#include "raylib.h"

int main() {

    int windowHeight {450};
    int windowWidth {800};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RED);

        EndDrawing();
    }
}