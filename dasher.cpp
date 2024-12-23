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
    AnimationData nebulaData 
    {
        { 0.0, 0.0, nebula.width / 8, nebula.height / 8 },                      // Neb Rectangle rec
        { windowDimensions[1], windowDimensions[0] - nebula.height / 8 },       // Neb Vec2 Pos
        0,                                                                      // Neb int Frame
        1.0 / 12.0,                                                             // Neb float update time
        0                                                                       // Neb float running time
    };

    // Nebula 2 variables
    AnimationData nebula2Data
    {
        { 0.0, 0.0, nebula.width / 8, nebula.height / 8 },                      // Neb Rectangle rec
        { windowDimensions[1] + 300, windowDimensions[0] - nebula.height / 8 }, // Neb Vec2 Pos
        0,                                                                      // Neb int Frame
        1.0 / 16.0,                                                             // Neb float update time
        0                                                                       // Neb float running time
    };                                                      
    
    AnimationData nebulae[2] = { nebulaData, nebula2Data };
   
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
        
        // Update Nebula position
        nebulae[0].pos.x += nebulaVelocity * deltaTime;

        // loop the first nebula
        if (nebulae[0].pos.x + (nebula.width / 8) < 0) 
        {
            nebulae[0].pos.x = windowDimensions[1];
        };

        // Update 2nd Nebula position
        nebulae[1].pos.x += nebulaVelocity * deltaTime;

        // Loop the 2nd nebula
        if (nebulae[1].pos.x + (nebula.width / 8) < 0) 
        {
            nebulae[1].pos.x = windowDimensions[1];
        };

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

        // Update Neb running time
        nebulae[0].runningTime += deltaTime;

        // Update Nebula animation frames
        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0;

            nebulae[0].rec.x = (nebulae[0].frame * nebulae[0].rec.width);
            nebulae[0].frame++;
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        // Update Neb2 running time
        nebulae[1].runningTime += deltaTime;

        // Update Nebula animation frames
        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;

            nebulae[1].rec.x = (nebulae[1].frame * nebulae[1].rec.width);
            nebulae[1].frame++;
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        // Draw Nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        // Draw 2nd Nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);
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