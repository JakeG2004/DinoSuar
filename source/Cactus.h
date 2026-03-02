#ifndef CACTUS_H
#define CACTUS_H

#include "ScrollingElement.h"
#include "Dino.h"

class Cactus : public ScrollingElement {
public:
    Cactus(OamState* newOam, Dino* player);

    // We override Update to call the base movement AND then render
    void Update() override;

protected:
    // This is called by ScrollingElement when the cactus goes off-screen
    void OnReset() override;
    void CalculateCollision();

private:
    Dino* dino;
    int curFrame = 0;
    int collisionRadius = 150;
};

#endif