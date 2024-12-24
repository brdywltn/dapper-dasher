#include "raylib.h"

struct AnimationData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimationData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimationData updateAnimationData(AnimationData data, float deltaTime, int maxFrameValue)
{
    // Update the running time
    data.runningTime += deltaTime;

    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // Update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;

        if (data.frame > maxFrameValue)
        {
            data.frame = 0;
        }
    }

    return data;
}

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
        1.0 / 7.0,
        0
    };
 
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int sizeOfNebulae {6};                                                
    AnimationData nebulae[sizeOfNebulae] {};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = windowDimensions[1] + i * 300; // Increase x_neb_pos to spawn next nebulae 300 pixels behind the previous one
        nebulae[i].pos.y = windowDimensions[0] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].runningTime = 0.0;
    }
   
    int nebulaVelocity { -200 }; // (pixels/second)
    int velocity { 0 };

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float background_x { 0.0 };
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float midground_x { 0.0 };
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float foreground_x { 0.0 };

    // Is the rectangle in the air?
    bool isInAir { false };
    // Jump velocity (pixels/s)
    const int jumpVelocity { -600 };

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float deltaTime { GetFrameTime() };

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Scroll background
        background_x -= 20 * deltaTime;
        if (background_x <= -background.width * 3.1)
        {
            background_x = 0.0;
        }

        // Scroll midground
        midground_x -= 40 * deltaTime;
        if (midground_x <= -midground.width * 3.1)
        {
            midground_x = 0.0;
        }

        // Scroll foreground
        foreground_x -= 80 * deltaTime;
        if (foreground_x <= -foreground.width * 3.1)
        {
            foreground_x = 0.0;
        }

        // Draw background
        Vector2 bg1Pos { background_x, 0.0 };
        DrawTextureEx(background, bg1Pos, 0.0, 3.1, WHITE);
        Vector2 bg2Pos { background_x + background.width * 3.1, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 3.1, WHITE);

        // Draw midground
        Vector2 mg1Pos { midground_x, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 3.1, WHITE);
        Vector2 mg2Pos { midground_x + midground.width * 3.1, 0.0 };
        DrawTextureEx(midground, mg2Pos, 0.0, 3.1, WHITE);

        // Draw foreground
        Vector2 fg1Pos { foreground_x, 0.0 };
        DrawTextureEx(foreground, fg1Pos, 0.0, 3.1, WHITE);
        Vector2 fg2Pos { foreground_x + foreground.width * 3.1, 0.0 };
        DrawTextureEx(foreground, fg2Pos, 0.0, 3.1, WHITE);

        // Apply gravity
        if (isOnGround(scarfyData, windowDimensions[0])) 
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


        // Update nebulae position
        for (int i = 0; i < sizeOfNebulae; i ++) 
        {
            nebulae[i].pos.x += nebulaVelocity * deltaTime;
        }

        // Update Scarfy position
        scarfyData.pos.y += velocity * deltaTime;

        // Update running time
        scarfyData.runningTime += deltaTime;
        // Update Scarfy animation frame


        if (!isInAir)
        {
            scarfyData = updateAnimationData(scarfyData, deltaTime, 5);
        }
        
        // Update nebulae animation frames
        for (int i = 0; i < sizeOfNebulae; i++)
        {
           nebulae[i] = updateAnimationData(nebulae[i], deltaTime, 7);
        }

        // Draw nebulae
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}