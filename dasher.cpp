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

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height; 

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
        if (scarfyPos.y >= windowHeight - scarfyRec.height) 
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
        scarfyPos.y += velocity;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        

        ClearBackground(WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();
}