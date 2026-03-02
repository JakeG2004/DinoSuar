#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <nds.h>

class SpriteManager {
private:
    static int nextMainID;
    static int nextSubID;

public:
    static int CreateUniqueSpriteID(OamState* oam);
};

#endif