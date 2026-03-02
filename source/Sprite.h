#ifndef SPRITE_H
#define SPRITE_H

#include <nds.h>
#include "SpriteManager.h"

class Sprite {
public:
    // Position variables
    int x; 
    int y;

    // Graphics variables
    int numSprites;
    u16** gfx;
    OamState* oam;

    // Sprite variables
    SpriteSize size;
    SpriteColorFormat colorFormat;
    int spriteID;
    bool isHidden = false;

    Sprite(OamState* objOam, SpriteSize objSize, SpriteColorFormat objFormat, int newNumSprites)
    {
        oam = objOam;
        size = objSize;
        colorFormat = objFormat;
        numSprites = newNumSprites;
        gfx = (u16**)malloc(sizeof(u16*) * numSprites);

        for(int i = 0; i < numSprites; i++)
        {
            gfx[i] = oamAllocateGfx(oam, size, colorFormat);
        }
        
        // Automatically grab the next available ID for this specific OAM engine
        spriteID = SpriteManager::CreateUniqueSpriteID(objOam);
    }

    void render(int frame, int width, int height) 
    {
        // Safety check to ensure we don't go out of bounds of our gfx array
        if (frame < 0 || frame >= numSprites) frame = 0;

        // Directly use the pointer we allocated for this specific frame
        u16* framePtr = gfx[frame];

        // Use the internal spriteID instead of passing one in
        oamSet(oam, spriteID, x, y, 0, 0, size, colorFormat, 
            framePtr, -1, false, isHidden, false, false, false);
    }

    void SetPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
    }
};

#endif