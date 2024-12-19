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
    AnimationData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0.0;
    scarfyData.rec.y = 0.0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0;

    Rectangle scarfyRec { 0.0, 0.0, scarfy.width / 6, scarfy.height };
    Vector2 scarfyPos { windowWidth / 2 - scarfyRec.width / 2, windowHeight - scarfyRec.height };

  
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec { 0.0, 0.0, nebula.width / 8, nebula.height / 8 };
    Vector2 nebulaPos { windowWidth, windowHeight - nebulaRec.height };
    int nebulaVelocity { -200 }; // (pixels/second)

    Rectangle nebula2Rec { 0.0, 0.0, nebula.width / 8, nebula.height / 8 };
    Vector2 nebula2Pos { windowWidth + 300, windowHeight - nebulaRec.height };

    
    // Track current animation frame
    int frame {};

    // Amount of time before we update the animation frame
    const float updateTime { 1.0 / 12.0 };
    float runningTime {};

    // Track animation frame for the nebula
    int nebFrame {};
    // Amount of time before we update the animation frame for the 2nd nebula
    const float nebUpdateTime { 1.0 / 16.0 };
    float nebRunningTime {};

    // Track animation frame for the 2nd nebula
    int neb2Frame {};
    // Amount of time before we update the animation frame for the nebula
    const float neb2UpdateTime { 1.0 / 12.0 };
    float neb2RunningTime {};

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

        // loop the first nebula
        if (nebulaPos.x + (nebula.width / 8) < 0) 
        {
            nebulaPos.x = windowWidth;
        };

        // Update 2nd Nebula position
        nebula2Pos.x += nebulaVelocity * deltaTime;

        // Loop the 2nd nebula
        if (nebula2Pos.x + (nebula.width / 8) < 0) 
        {
            nebula2Pos.x = windowWidth;
        };

        // Update Scarfy position
        scarfyPos.y += velocity * deltaTime;

        // Update running time
        runningTime += deltaTime;
        // Update Scarfy animation frame
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

        // Update Neb running time
        nebRunningTime += deltaTime;

        // Update Nebula animation frames
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;

            nebulaRec.x = (nebFrame * nebulaRec.width);
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        // Update Neb running time
        neb2RunningTime += deltaTime;

        // Update Nebula animation frames
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;

            nebula2Rec.x = (neb2Frame * nebula2Rec.width);
            neb2Frame++;
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
        }

        // Draw Nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        // Draw 2nd Nebula
        DrawTextureRec(nebula, nebula2Rec, nebula2Pos, RED);
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