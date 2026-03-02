#ifndef DINO_H
#define DINO_H

#include "Sprite.h"

// Dino inherits from Sprite
class Dino : public Sprite {
public:
    // Constructor
    Dino(OamState* newOam, int newJumpKey, int newCrouchKey);

    void Update(int keys);

private:
    // Physics and Movement (Specific to Dino)
    float vy = 0;
    int originalY;
    int jumpForce = 10;
    int jumpKey;
    int crouchKey;
    float gravity = 0.6;
    int isCrouching = 0;

    // Animation Variables
    int curFrame = 0;
    int frameTimer = 0;
    int frameRate = 5;

    // Other
    int* gameOver = 0;

    // Dino-specific logic
    void Jump();
    void Crouch();
    void ApplyPhysics();
    void Animate();
};

#endif