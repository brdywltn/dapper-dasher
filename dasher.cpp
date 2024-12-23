#include "raylib.h"

struct AnimationData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main() {

    // Window dimensions
    const int windowDimensions[] = { 450, 800 };
    const char windowTitle[] {"Dapper Dasher"};
    // Initialise the window
    InitWindow(windowDimensions[1], windowDimensions[0], windowTitle);

    // Acceleration due to gravity (pixels/s)/s
    const int gravity { 1'000 };

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimationData scarfyData
    {
        { 0.0, 0.0, scarfy.width / 6, scarfy.height },
        { windowDimensions[1] / 2 - (scarfy.width / 6) / 2, windowDimensions[0] - scarfy.height },
        0,
        1.0 / 12.0,
        0
    };
 
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");                                                
    AnimationData nebulae[3] {};

    for (int i = 0; i < 3; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;

        nebulae[i].pos.y = windowDimensions[0] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].runningTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[1];
    nebulae[1].pos.x = windowDimensions[1] + 300;
    nebulae[2].pos.x = windowDimensions[1] + 600;
   
    int nebulaVelocity { -200 }; // (pixels/second)
    int velocity { 0 };

    // Is the rectangle in the air?
    bool isInAir { false };
    // Jump velocity (pixels/s)
    const int jumpVelocity { -600 };

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float deltaTime {GetFrameTime()};

        // Start drawing
        BeginDrawing();
    
        // Apply gravity
        if (scarfyData.pos.y >= windowDimensions[0] - scarfyData.rec.height) 
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

        for (int i = 0; i < 3; i ++) {
            nebulae[i].pos.x += nebulaVelocity * deltaTime;

            // if (nebulae[i].pos.x + (nebula.width / 8) < 0) 
            // {
            //     nebulae[i].pos.x = windowDimensions[1];
            // };
        }

        // Update Scarfy position
        scarfyData.pos.y += velocity * deltaTime;

        // Update running time
        scarfyData.runningTime += deltaTime;
        // Update Scarfy animation frame
        if (scarfyData.runningTime >= scarfyData.updateTime && !isInAir)
        {
            scarfyData.runningTime = 0.0;

            // Update animation frame
            scarfyData.rec.x = (scarfyData.frame * scarfyData.rec.width);
            scarfyData.frame++;
            if (scarfyData.frame > 5)
            {
                scarfyData.frame = 0;
            }
        }
        
        for (int i = 0; i < 3; i++)
        {
           // Update Neb running time
            nebulae[i].runningTime += deltaTime;

            // Update Nebula animation frames
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;

                nebulae[i].rec.x = (nebulae[i].frame * nebulae[i].rec.width);
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            } 
        }

        // Draw Nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        // Draw 2nd Nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
        // Draw 2nd Nebula
        DrawTextureRec(nebula, nebulae[2].rec, nebulae[2].pos, BLUE);
        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        

        ClearBackground(WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}