#include "raylib.h"
struct AnimData
    {
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
    };

    bool isOnGround(AnimData data, int windowHeight)
    {
        return data.pos.y >= windowHeight - data.rec.height;
    }

    AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
    {
        //update running time
        data.runningTime += deltaTime;

        if (data.runningTime >= data.updateTime)
        {
            data.runningTime = 0.0;
            // Update animation frame
            data.rec.x = data.frame * data.rec.width;
            data.frame++;
            if (data.frame > maxFrame)
            {
                data.frame = 0;
            }
        }
        
        return data;
    }

int main()
{
    int windowDimensions[2]{512, 380};    

    // Window Properties
    //const int windowWidth = 512;
    //const int windowHeight = 380;

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

    bool collision{};

    // NOTE: InitWindow has to be called before Texture2D set up
    //InitWindow(windowWidth, windowHeight, "Dash Game");
    InitWindow(windowDimensions[0], windowDimensions[1], "Dash Game");

 Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

 Texture2D backGround = LoadTexture("textures/far-buildings.png");
 float bgXPos{0.0};

 Texture2D midGround = LoadTexture("textures/back-buildings.png");
 float mgXPos{0.0};

 Texture2D foreGround = LoadTexture("textures/foreground.png");
 float fgXPos{0.0};

/*   // Before struct
     // Nebula/Hazard 
    Rectangle nebulaRec{0, 0, nebula.width/8.0, nebula.height/8.0 };

      // Nebula animation frame
    int nebFrame = 0;
    const float nebUpdateTime = 1.0 / 12.0;
    float nebRunningTime =0;
    */


/* After struct, before for loop
    // AnimData struct for Nebula/Hazard
    AnimData nebulaData{ {0, 0, nebula.width/8.0, nebula.height/8.0}, {windowWidth,
        windowHeight-nebula.height/8.0}, 0, 1.0/16.0, 0.0 };

// AnimData struct for 2nd Nebula/Hazard
    AnimData nebula2Data{ {0, 0, nebula.width/8.0, nebula.height/8.0}, {windowWidth + 300,
        windowHeight-nebula.height/8.0}, 0, 1.0/12.0, 0.0 };
*/

const int nebulaCount{3};
AnimData nebulaDataArray[nebulaCount]{};

for (int i = 0; i < nebulaCount; i++)
{
    nebulaDataArray[i].rec.x = 0.0;
    nebulaDataArray[i].rec.y = 0.0;
    nebulaDataArray[i].rec.width = nebula.width/8.0;
    nebulaDataArray[i].rec.height = nebula.height/8.0;
    nebulaDataArray[i].pos.x = windowDimensions[0] + (300 * i);
    nebulaDataArray[i].pos.y = windowDimensions[1] - nebula.height/8.0;
    nebulaDataArray[i].frame = 0;
    nebulaDataArray[i].updateTime = 1.0/16.0;
    nebulaDataArray[i].runningTime = 0.0;
}

float finishLine{nebulaDataArray[nebulaCount-1].pos.x};


  
//    Before Struct
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
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;    
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
        // Delta time (Time since last frame)
            const float dT{ GetFrameTime()};

            BeginDrawing();
            ClearBackground(WHITE);

            // Scroll Background
            bgXPos -= 20.0 * dT;
            if (bgXPos <= -backGround.width*2)
            {
                bgXPos = 0.0;
            }

            // Scroll Midground
            mgXPos -= 40.0 * dT;
            if (mgXPos <= -midGround.width*2)
            {
                mgXPos = 0.0;
            }

            // Scroll Foreground
            fgXPos -= 80.0 * dT;
            if (fgXPos <= -foreGround.width*2)
            {
                fgXPos = 0.0;
            }

            // Draw Background
            Vector2 bg1Pos{bgXPos, 0.0};
            DrawTextureEx(backGround, bg1Pos, 0.0, 2.0, WHITE);
            Vector2 bg2Pos{bgXPos + (backGround.width*2), 0.0};
            DrawTextureEx(backGround, bg2Pos, 0.0, 2.0, WHITE);

            // Draw Midground
            Vector2 mg1Pos{mgXPos, 0.0};
            DrawTextureEx(midGround, mg1Pos, 0.0, 2.0, WHITE);
            Vector2 mg2Pos{mgXPos + (midGround.width*2), 0.0};
            DrawTextureEx(midGround, mg2Pos, 0.0, 2.0, WHITE);

            // Draw Foreground
            Vector2 fg1Pos{fgXPos, 0.0};
            DrawTextureEx(foreGround, fg1Pos, 0.0, 2.0, WHITE);
            Vector2 fg2Pos{fgXPos + (foreGround.width*2), 0.0};
            DrawTextureEx(foreGround, fg2Pos, 0.0, 2.0, WHITE);



            // Ground check
            // /* Before struct */ if (scarfyPos.y >= windowHeight - scarfyRec.height)
            if (isOnGround(scarfyData, windowDimensions[1]))
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
            
            // Before for loop
            // nebulaDataArray[0].pos.x += nebulaVel * dT;
            // nebulaDataArray[1].pos.x += nebulaVel * dT;

            for (int i = 0; i < nebulaCount; i++)
            {
                   nebulaDataArray[i].pos.x += nebulaVel * dT;
            }
                
            finishLine += nebulaVel * dT;

            /* Before Array
            // Nebula/Hazard update
            //nebulaPos.x += nebulaVel * dT;
            nebulaData.pos.x += nebulaVel * dT;
            nebula2Data.pos.x += nebulaVel * dT;
            */

            // Scarfy jump - Update Scarfy pos
            //scarfyPos.y += velocity * dT;
            scarfyData.pos.y += velocity * dT;
           

           // DrawRectangle(windowWidth/2, posY, rectangleWidth, rectangleHeight, BLUE);
            
            // Animating Scarfy
            if (!isInAir)
            {
                scarfyData = updateAnimData(scarfyData, dT, 5);
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


             for (int i = 0; i < nebulaCount; i++)
             {
                nebulaDataArray[i] = updateAnimData(nebulaDataArray[i], dT, 7);
             }


           /* //Before for loop
            if(nebulaDataArray[0].runningTime >= nebulaDataArray[0].updateTime)
            {
                nebulaDataArray[0].runningTime = 0.0;
                // Update hazard animation frame
                nebulaDataArray[0].rec.x = nebulaDataArray[0].frame * nebulaDataArray[0].rec.width;
                nebulaDataArray[0].frame++;
                if (nebulaDataArray[0].frame > 8)
                {
                    nebulaDataArray[0].frame = 0;
                }
            }
            
            if(nebulaDataArray[1].runningTime >= nebulaDataArray[1].updateTime)
            {
                nebulaDataArray[1].runningTime = 0.0;
                // Update hazard animation frame
                nebulaDataArray[1].rec.x = nebulaDataArray[1].frame * nebulaDataArray[1].rec.width;
                nebulaDataArray[1].frame++;
                if (nebulaDataArray[1].frame > 8)
                {
                    nebulaDataArray[1].frame = 0;
                }
            }
            */

            //Draw Nebula
           // DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

            /* Before for loop
           // DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
            DrawTextureRec(nebula, nebulaDataArray[0].rec, nebulaDataArray[0].pos, WHITE);
           // DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
            DrawTextureRec(nebula, nebulaDataArray[1].rec, nebulaDataArray[1].pos, WHITE);
            */

            
            for(AnimData nebula : nebulaDataArray)
            {
                float pad{50};
                Rectangle nebRec{
                    nebula.pos.x + pad,
                    nebula.pos.y + pad,
                    nebula.rec.width - 2*pad,
                    nebula.rec.height - 2*pad
                };

                Rectangle scarfyRec{
                    scarfyData.pos.x,
                    scarfyData.pos.y,
                    scarfyData.rec.width,
                    scarfyData.rec.height
                };

                if (CheckCollisionRecs(nebRec, scarfyRec))
                {
                    collision = true;
                    break;
                }
                
            }

            if(collision)
            {
                DrawText("Game Over!", 200, 200, 20, RED);
            }
            else if (scarfyData.pos.x >= finishLine)
            {
                DrawText("You Win!", 200, 200, 20, GREEN);
            }
            else
            {
            // Draw Nebula
            for (int i = 0; i < nebulaCount; i++)
            {
                DrawTextureRec(nebula, nebulaDataArray[i].rec, nebulaDataArray[i].pos, WHITE);
            }
            
            // Draw Scarfy
            //DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
            }
            
            EndDrawing();

    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(backGround);
    UnloadTexture(foreGround);
    UnloadTexture(midGround);
    CloseWindow();

}
