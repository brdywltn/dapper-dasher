#include "raylib.h"

int main() {

    // Window dimensions
    const int windowHeight {450};
    const int windowWidth {800};
    const char windowTitle[] {"Dapper Dasher"};
    // Initialise the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // Acceleration due to gravity (pixels/s)/s
    const int gravity {1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // Track current animation frame
    int frame {};

    // Amount of time before we update the animation frame
    const float updateTime {1.0 / 12.0};
    float runningTime {};

    int velocity {0};

    // Is the rectangle in the air?
    bool isInAir {false};
    // Jump velocity (pixels/s)
    const int jumpVelocity {-600};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float deltaTime {GetFrameTime()};

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
            velocity += gravity * deltaTime;
            isInAir = true;
        }

        // Jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }
        
        

        // Update position
        scarfyPos.y += velocity * deltaTime;

        // Update running time
        runningTime += deltaTime;

        if (runningTime >= updateTime)
        {
            runningTime = 0.0;

            // Update animation frame
            scarfyRec.x = (frame * scarfyRec.width);
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }

        
        

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        

        ClearBackground(WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();
}