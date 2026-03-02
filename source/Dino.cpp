#include "Dino.h"
#include "Dino_Walk.h"
#include "GameManager.h"

Dino::Dino(OamState* newOam, int newJumpKey, int newCrouchKey) : Sprite(newOam, SpriteSize_64x64, SpriteColorFormat_256Color, 6) 
{
    jumpKey = newJumpKey;
    crouchKey = newCrouchKey;
    x = 16;
    y = 110;
    originalY = y;

    // Inside Dino constructor
    for(int i = 0; i < numSprites; i++) {
        // Calculate where this frame starts in the source Tiles array
        // 64x64 at 8bpp (256 colors) is 4096 bytes per frame
        u8* sourceFrame = (u8*)Dino_WalkTiles + (i * 4096); 
        
        dmaCopy(sourceFrame, gfx[i], 4096);
    }
}

void Dino::Update(int keys) 
{
    // Check For Jump
    if((keys & jumpKey) && y == originalY) 
    {
        Jump();
    }

    if((keys & crouchKey) && y == originalY)
    {
        Crouch();
    } else {
        isCrouching = 0;
    }
    
    ApplyPhysics();

    Animate();

    render(curFrame, 64, 64);
}

void Dino::Jump() 
{
    if(GameManager::getInstance() -> gameOver != 0)
    {
        return;
    }

    vy = -jumpForce; 
}

void Dino::Crouch()
{
    isCrouching = 1;
}

void Dino::ApplyPhysics() 
{
    y += (int)vy;
    vy += gravity;

    // Stop on ground
    if(y >= originalY) 
    {
        vy = 0;
        y = originalY;
    }
}

void Dino::Animate() 
{
    GameManager* gm = GameManager::getInstance();
    switch(gm -> gameOver)
    {
        case 0:
        {
            if(isCrouching == 0)
            {
                if(curFrame >= 2)
                {
                    curFrame = 0;
                }

                if(++frameTimer > 5) 
                {
                    frameTimer = 0;
                    curFrame ^= 1;
                }
            } else{
                if(++frameTimer > 5) 
                {
                    frameTimer = 0;
                    // Toggles between 0 and 1, then adds 4 to shift to the crouch frames
                    curFrame = (curFrame == 4) ? 5 : 4; 
                }
            }
            break;
        }

        case 1:
        {
            if(gm -> topDino == this)
            {
                curFrame = 2;
                return;
            }

            curFrame = 3;
            return;
        }

        case 2:
        {
            if(gm -> gameOver == 2)
            {
                if(gm -> botDino == this)
                {
                    curFrame = 2;
                    return;
                }

                curFrame = 3;
                return;
            }
        }
    }
}