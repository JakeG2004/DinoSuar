#include "Cactus.h"
#include "Cacti.h"
#include "Dino.h"
#include "GameManager.h"

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
}

void Cactus::Update()
{
    ScrollingElement::Update();

    CalculateCollision();

    render(curFrame, 64, 64);
}

void Cactus::OnReset()
{
    curFrame = rand() % 5;
    GameManager::getInstance() -> IncrementSpeed();
}

void Cactus::CalculateCollision()
{
    int dx = abs(x - dino -> x);
    int dy = abs(y - dino -> y);

    if(((dx * dx) + (dy * dy)) < collisionRadius)
    {
        //GameManager::getInstance() -> GameOver(dino);
    }
}