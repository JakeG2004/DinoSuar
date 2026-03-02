#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <nds.h>

class Dino;
class Cactus;

class GameManager {
private:
    // The static instance pointer
    static GameManager* instance;

    // Private constructor: Prevents other classes from "newing" this up
    GameManager(Dino* td, Dino* bd, Cactus* tc, Cactus* bc);

public:
    // Static method to access the instance
    static GameManager* getInstance();
    
    // Optional: Setup method to initialize the singleton with the dinos/cacti
    static void Create(Dino* td, Dino* bd, Cactus* tc, Cactus* bc);

    Dino* topDino;
    Dino* botDino;
    Cactus* topCactus;
    Cactus* botCactus;

    float gameSpeed;
    int gameOver;

    void IncrementSpeed();
    void GameOver(Dino* player);
    void Reset();
    void Update(int keys);
};

#endif