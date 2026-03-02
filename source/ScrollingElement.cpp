#include "ScrollingElement.h"
#include "GameManager.h"

ScrollingElement::ScrollingElement(OamState* newOam, SpriteSize size, SpriteColorFormat format, int priority) : Sprite(newOam, size, format, priority)
{ }

void ScrollingElement::Update()
{
    posX -= GameManager::getInstance() -> gameSpeed;

    if (posX <= -64.0f) {
        posX = 312.0f + (rand() % 64);
        OnReset();
    }

    x = (int)posX;
}