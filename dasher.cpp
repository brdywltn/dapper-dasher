#include "raylib.h"

int main() {

    // Window dimensions
    const int windowHeight {450};
    const int windowWidth {800};
    const char windowTitle[] {"Dapper Dasher"};
    // Initialise the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // Acceleration due to gravity (pixels/frame)/frame
    const int gravity {1};

    // Rectangle dimensions
    const int width {50};
    const int height {80};

    int posY {windowHeight - height};
    int velocity {0};

    // Is the rectangle in the air?
    bool isInAir {false};
    // Jump velocity
    const int jumpVelocity {-22};
    
   

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();

        // Apply gravity
        if (posY >= windowHeight - height) 
        {
            // Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // Rectangle is in the air
            // Apply gravity
            velocity += gravity;
            isInAir = true;
        }

        // Jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }
        
        

        // Update position
        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        

        ClearBackground(WHITE);

        // End drawing
        EndDrawing();
    }

    CloseWindow();
}