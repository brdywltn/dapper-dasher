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
    const int windowHeight { 450 };
    const int windowWidth { 800 };
    const char windowTitle[] {"Dapper Dasher"};
    // Initialise the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // Acceleration due to gravity (pixels/s)/s
    const int gravity { 1'000 };

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimationData scarfyData
    {
        { 0.0, 0.0, scarfy.width / 6, scarfy.height },
        { windowWidth / 2 - (scarfy.width / 6) / 2, windowHeight - scarfy.height },
        0,
        1.0 / 12.0,
        0
    };
 
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimationData nebulaData 
    {
        { 0.0, 0.0, nebula.width / 8, nebula.height / 8 },      // Neb Rectangle rec
        { windowWidth, windowHeight - nebula.height / 8 },      // Neb Vec2 Pos
        0,                                                      // Neb int Frame
        1.0 / 12.0,                                             // Neb float update time
        0                                                       // Neb float running time
    };

    // Nebula 2 variables
    AnimationData nebula2Data
    {
        { 0.0, 0.0, nebula.width / 8, nebula.height / 8 },       // Neb Rectangle rec
        { windowWidth + 300, windowHeight - nebula.height / 8 }, // Neb Vec2 Pos
        0,                                                       // Neb int Frame
        1.0 / 16.0,                                              // Neb float update time
        0                                                        // Neb float running time
    };                                                      
    
   
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
        if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height) 
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
        nebulaData.pos.x += nebulaVelocity * deltaTime;

        // loop the first nebula
        if (nebulaData.pos.x + (nebula.width / 8) < 0) 
        {
            nebulaData.pos.x = windowWidth;
        };

        // Update 2nd Nebula position
        nebula2Data.pos.x += nebulaVelocity * deltaTime;

        // Loop the 2nd nebula
        if (nebula2Data.pos.x + (nebula.width / 8) < 0) 
        {
            nebula2Data.pos.x = windowWidth;
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
        nebulaData.runningTime += deltaTime;

        // Update Nebula animation frames
        if (nebulaData.runningTime >= nebulaData.updateTime)
        {
            nebulaData.runningTime = 0.0;

            nebulaData.rec.x = (nebulaData.frame * nebulaData.rec.width);
            nebulaData.frame++;
            if (nebulaData.frame > 7)
            {
                nebulaData.frame = 0;
            }
        }

        // Update Neb running time
        nebula2Data.runningTime += deltaTime;

        // Update Nebula animation frames
        if (nebula2Data.runningTime >= nebula2Data.updateTime)
        {
            nebula2Data.runningTime = 0.0;

            nebula2Data.rec.x = (nebula2Data.frame * nebula2Data.rec.width);
            nebula2Data.frame++;
            if (nebula2Data.frame > 7)
            {
                nebula2Data.frame = 0;
            }
        }

        // Draw Nebula
        DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
        // Draw 2nd Nebula
        DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, RED);
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