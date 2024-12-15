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

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec { 0.0, 0.0, scarfy.width / 6, scarfy.height };
    Vector2 scarfyPos { windowWidth / 2 - scarfyRec.width / 2, windowHeight - scarfyRec.height };
  
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec { 0.0, 0.0, nebula.width / 8, nebula.height / 8 };
    Vector2 nebulaPos { windowWidth, windowHeight - nebulaRec.height };
    int nebulaVelocity { -600 }; // (pixels/second)
    
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
        
        // Update Nebula position
        nebulaPos.x += nebulaVelocity * deltaTime;

        if (nebulaPos.x + (nebula.width / 8) < 0) 
        {
            nebulaPos.x = windowWidth;
        };

        // Update Scarfy position
        scarfyPos.y += velocity * deltaTime;

        // Update running time
        runningTime += deltaTime;

        if (runningTime >= updateTime && !isInAir)
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

        // Draw Nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        

        ClearBackground(WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}