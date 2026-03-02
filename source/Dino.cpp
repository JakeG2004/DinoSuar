#include "Dino.h"
#include "Dino_Walk.h"
#include "GameManager.h"
#include <maxmod9.h>    // Required for mmEffectEx 
#include "soundbank.h" // Required for SFX_HIT ID 
#include "soundbank_bin.h"

Dino::Dino(OamState* newOam, int newJumpKey, int newCrouchKey) : Sprite(newOam, SpriteSize_64x64, SpriteColorFormat_256Color, 6) 
{
    jumpKey = newJumpKey;
    crouchKey = newCrouchKey;
    x = 16;
    y = 110;
    originalY = y;

    for(int i = 0; i < numSprites; i++) {
        u8* sourceFrame = (u8*)Dino_WalkTiles + (i * 4096); 
        dmaCopy(sourceFrame, gfx[i], 4096);
    }

    mmInitDefaultMem((mm_addr)soundbank_bin);

    // 2. Load the specific sound effect into memory
    // (Ensure SFX_HIT is defined in your soundbank.h)
    mmLoadEffect( SFX_JUMP );
}

void Dino::Update(int keys) 
{
    if((GameManager::getInstance() -> singlePlayer == 1) && this == GameManager::getInstance() -> botDino)
    {
        this -> isHidden = true;
        render(curFrame, 64, 64);
        return;
    } else {
        this -> isHidden = false;
    }

    // Use keysDown from your main loop or check for the specific frame 
    // to prevent the sound from spamming every frame.
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
    if(GameManager::getInstance()->gameOver != 0) return;

    vy = -jumpForce; 

    // --- PLAY JUMP SOUND ---
    // We define the sound effect inline here so it triggers on jump
    mm_sound_effect jump_sfx = {
        { SFX_JUMP },             // id from soundbank.h 
        (int)(1.0f * (1<<10)),   // rate (normal speed) 
        0,                       // handle 
        255,                     // volume (max) 
        128,                     // panning (center) 
    };
    
    mmEffectEx(&jump_sfx);      // Play the effect 
}

void Dino::Crouch()
{
    isCrouching = 1;
}

void Dino::ApplyPhysics() 
{
    y += (int)vy;
    vy += gravity;

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
                if(curFrame >= 2) curFrame = 0;

                if(++frameTimer > 5) 
                {
                    frameTimer = 0;
                    curFrame ^= 1;
                }
            } else {
                if(++frameTimer > 5) 
                {
                    frameTimer = 0;
                    curFrame = (curFrame == 4) ? 5 : 4; 
                }
            }
            break;
        }
        case 1:
        {
            if(gm -> topDino == this) { curFrame = 2; return; }
            curFrame = 3;
            return;
        }
        case 2:
        {
            if(gm -> botDino == this) { curFrame = 2; return; }
            curFrame = 3;
            return;
        }
    }
}