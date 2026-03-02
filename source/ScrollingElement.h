#ifndef SCROLLING_ELEMENT_H
#define SCROLLING_ELEMENT_H

#include "Sprite.h"

class ScrollingElement : public Sprite {
public:
    ScrollingElement(OamState* newOam, SpriteSize size, SpriteColorFormat format, int priority);

    // Common movement logic for all scrolling objects
    virtual void Update();
    int posX;

protected:
    float* gameSpeed;
    
    // Virtual function so Cactus can define what happens when it resets
    virtual void OnReset() = 0; 
};

#endif