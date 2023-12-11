#include "raylib.h"

int main()
{
    struct AnimData
    {
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
    };

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

 Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

/*   // Before struct
     // Nebula/Hazard 
    Rectangle nebulaRec{0, 0, nebula.width/8.0, nebula.height/8.0 };

      // Nebula animation frame
    int nebFrame = 0;
    const float nebUpdateTime = 1.0 / 12.0;
    float nebRunningTime =0;
    */

    // AnimData struct for Nebula/Hazard
    AnimData nebulaData{ {0, 0, nebula.width/8.0, nebula.height/8.0}, {windowWidth,
        windowHeight-nebula.height/8.0}, 0, 1.0/16.0, 0.0 };

// AnimData struct for 2nd Nebula/Hazard
    AnimData nebula2Data{ {0, 0, nebula.width/8.0, nebula.height/8.0}, {windowWidth + 300,
        windowHeight-nebula.height/8.0}, 0, 1.0/12.0, 0.0 };

  
//    
//     Vector2 nebulaPos;
//     nebulaPos.x = windowWidth;
//     nebulaPos.y = windowHeight - nebulaRec.height;
    

    // Nebula x velocity (pixels/per second)
    int nebulaVel{-200};

    // AnimData struct for Scarfy 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;   
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;    
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    /*  // Before struct
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

       // Scarfy animation frame
    int frame = 0; 
    const float updateTime = 1.0 / 12.0;
    float runningTime = 0;
    */

//    InitWindow(windowWidth, windowHeight, "Dash Game");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
            BeginDrawing();
            ClearBackground(WHITE);

            // Delta time (Time since last frame)
            const float dT{ GetFrameTime()};
  
            // Ground check
            // /* Before struct */ if (scarfyPos.y >= windowHeight - scarfyRec.height)
            if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
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
            //nebulaPos.x += nebulaVel * dT;
            nebulaData.pos.x += nebulaVel * dT;
            nebula2Data.pos.x += nebulaVel * dT;

            // Scarfy jump - Update Scarfy pos
            //scarfyPos.y += velocity * dT;
            scarfyData.pos.y += velocity * dT;
           

           // DrawRectangle(windowWidth/2, posY, rectangleWidth, rectangleHeight, BLUE);
            
            // Animating Scarfy
            //runningTime += dT;
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime && !isInAir)
            {
                //runningTime = 0.0;
                scarfyData.runningTime = 0.0;   
                // Update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }

            // Animating Nebula/Hazard
           // nebRunningTime += dT;

            //if (nebRunningTime >= nebUpdateTime)
            // {
            //     nebRunningTime = 0.0;
            //     // Update hazard animation frame
            //     nebulaRec.x = nebFrame * nebulaRec.width;
            //     nebFrame++;
            //     if (nebFrame > 8)
            //     {
            //         nebFrame = 0;
            //     }
            // }

            if(nebulaData.runningTime >= nebulaData.updateTime)
            {
                nebulaData.runningTime = 0.0;
                // Update hazard animation frame
                nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
                nebulaData.frame++;
                if (nebulaData.frame > 8)
                {
                    nebulaData.frame = 0;
                }
            }
            
            if(nebula2Data.runningTime >= nebula2Data.updateTime)
            {
                nebula2Data.runningTime = 0.0;
                // Update hazard animation frame
                nebula2Data.rec.x = nebula2Data.frame * nebula2Data.rec.width;
                nebula2Data.frame++;
                if (nebula2Data.frame > 8)
                {
                    nebula2Data.frame = 0;
                }
            }

            //Draw Nebula
           // DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

           // DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
            DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
            
            
           // DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
            DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, WHITE);
  
            // Draw Scarfy
            //DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

            EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}
