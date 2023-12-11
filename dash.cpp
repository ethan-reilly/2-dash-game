#include "raylib.h"

int main()
{
    // Window Properties
    const int windowWidth = 512;
    const int windowHeight = 380;

    // Rectangle Prop
   /* const int rectangleWidth{50};
    const int rectangleHeight{80};

    int posY{windowHeight - rectangleHeight};*/
    int velocity = 1; // pixels per frame
    
    // Acceleration due to gravity
    //const int gravity = 1; // (p/f)/f
    // We want gravity per second, not per frame
    const int gravity{1'000};

    //const int jumpHeight = -22;
    // Again, we want per second, not per frame
    const int jumpHeight = -600;

    bool isInAir = false;

    // NOTE: InitWindow has to be called before Texture2D set up
    InitWindow(windowWidth, windowHeight, "Dash Game");

    
    
    // Scarfy animation frame
    int frame = 0; 
    const float updateTime = 1.0 / 12.0;
    float runningTime = 0;

    // Nebula animation frame
    int nebFrame = 0;
    const float nebUpdateTime = 1.0 / 12.0;
    float nebRunningTime =0;

    // Nebula/Hazard 
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0, 0, nebula.width/8.0, nebula.height/8.0, };
    
    Vector2 nebulaPos;
    nebulaPos.x = windowWidth;
    nebulaPos.y = windowHeight - nebulaRec.height;
    // Nebula x velocity (pixels/per second)
    int nebulaVel{-200};

    // Scarfy 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

//    InitWindow(windowWidth, windowHeight, "Dash Game");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
            BeginDrawing();
            ClearBackground(WHITE);

            // Delta time (Time since last frame)
            const float dT{ GetFrameTime()};
  
            // Ground check
            if (scarfyPos.y >= windowHeight - scarfyRec.height)
            {
                // Rectangle is on ground
                velocity = 0;
                isInAir = false;
            }
            else
            {
                // Rectangle is in air
                isInAir = true;

                // Apply Gravity
                velocity += gravity * dT;
            }

            // Jumping 
            if (IsKeyPressed(KEY_SPACE) && !isInAir)
            {
                velocity += jumpHeight;
            }
            
            // Nebula/Hazard update
            nebulaPos.x += nebulaVel * dT;

            // Scarfy jump - Update Scarfy pos
            scarfyPos.y += velocity * dT;

           

           // DrawRectangle(windowWidth/2, posY, rectangleWidth, rectangleHeight, BLUE);
            
            // Animating Scarfy
            runningTime += dT;
            if (runningTime >= updateTime && !isInAir)
            {
                runningTime = 0.0;
                // Update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }

            // Animating Nebula/Hazard
            nebRunningTime += dT;
            if (nebRunningTime >= nebUpdateTime)
            {
                nebRunningTime = 0.0;
                // Update hazard animation frame
                nebulaRec.x = nebFrame * nebulaRec.width;
                nebFrame++;
                if (nebFrame > 8)
                {
                    nebFrame = 0;
                }
            }
            
            //Draw Nebula
            DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

            // Draw Scarfy
            DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

            EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}
