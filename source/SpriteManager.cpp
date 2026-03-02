#include "SpriteManager.h"

// Initialize the static members here
int SpriteManager::nextMainID = 0;
int SpriteManager::nextSubID = 0;

int SpriteManager::CreateUniqueSpriteID(OamState* oam) {
    if (oam == &oamMain) {
        return nextMainID++; 
    } else {
        return nextSubID++;
    }
}