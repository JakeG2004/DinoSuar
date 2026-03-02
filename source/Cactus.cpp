#include "Cactus.h"
#include "Cacti.h"
#include "Dino.h"
#include "GameManager.h"
#include <maxmod9.h>    // Required for mmEffectEx 
#include "soundbank.h" // Required for SFX_HIT ID 
#include "soundbank_bin.h"

Cactus::Cactus(OamState* newOam, Dino* player) : ScrollingElement(newOam, SpriteSize_64x64, SpriteColorFormat_256Color, 6)
{

    y = 110;
    posX = 230.0f; 

    dino = player;
    
    // Inside Dino constructor
    for(int i = 0; i < numSprites; i++) {
        // Calculate where this frame starts in the source Tiles array
        // 64x64 at 8bpp (256 colors) is 4096 bytes per frame
        u8* sourceFrame = (u8*)CactiTiles + (i * 4096); 
        
        dmaCopy(sourceFrame, gfx[i], 4096);
    }

    mmInitDefaultMem((mm_addr)soundbank_bin);

    // 2. Load the specific sound effect into memory
    // (Ensure SFX_HIT is defined in your soundbank.h)
    mmLoadEffect( SFX_HIT );
}

void Cactus::Update()
{
    ScrollingElement::Update();

    CalculateCollision();

    render(curFrame, 64, 64);
}

void Cactus::OnReset()
{
    curFrame = rand() % 2;
    GameManager::getInstance() -> IncrementSpeed();
}

void Cactus::CalculateCollision()
{
    if((GameManager::getInstance() -> singlePlayer == 1) && this == GameManager::getInstance() -> botCactus)
    {
        return;
    }

    int dx = abs(x - dino -> x);
    int dy = abs(y - dino -> y);

    if(((dx * dx) + (dy * dy)) < collisionRadius)
    {
        if(GameManager::getInstance() -> gameOver == 0)
        {
            // --- PLAY JUMP SOUND ---
            // We define the sound effect inline here so it triggers on jump
            mm_sound_effect hit_sfx = {
                { SFX_HIT },             // id from soundbank.h 
                (int)(1.0f * (1<<10)),   // rate (normal speed) 
                0,                       // handle 
                255,                     // volume (max) 
                128,                     // panning (center) 
            };

            mmEffectEx(&hit_sfx);      // Play the effect 
        }
        GameManager::getInstance() -> GameOver(dino);
    }
}