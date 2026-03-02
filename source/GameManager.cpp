#include "GameManager.h"
#include "Dino.h"
#include "Cactus.h"
#include <stdio.h>

// Initialize the static member to null
GameManager* GameManager::instance = nullptr;

GameManager::GameManager(Dino* td, Dino* bd, Cactus* tc, Cactus* bc)
    : topDino(td), botDino(bd), topCactus(tc), botCactus(bc), 
      gameSpeed(3.0f), gameOver(0) {}

void GameManager::Create(Dino* td, Dino* bd, Cactus* tc, Cactus* bc) {
    if (instance == nullptr) {
        instance = new GameManager(td, bd, tc, bc);
    }
}

GameManager* GameManager::getInstance() {
    return instance;
}

void GameManager::IncrementSpeed() {
    gameSpeed += 0.05f;
}

void GameManager::GameOver(Dino* player) 
{
    gameSpeed = 0;
    if (gameOver != 0) return;
    
    if (player == topDino) 
    {
        gameOver = 1; // Top player hit a cactus, Bottom player wins
    } else {
        gameOver = 2; // Bottom player hit a cactus, Top player wins
    }

    iprintf("\x1b[10;10H"); // ANSI escape code: Row 10, Col 10

    if (gameOver == 1) {
        iprintf("BOTTOM PLAYER WINS!");
    } else {
        iprintf("TOP PLAYER WINS!");
    }
    
    iprintf("\x1b[12;8HPRESS START TO RESTART");
}

void GameManager::Reset()
{
    iprintf("\x1b[2J");
    gameOver = 0;
    topCactus -> posX = 230;
    botCactus -> posX = 230;
    gameSpeed = 3;
}

void GameManager::Update(int keys)
{
    if(keys & KEY_START)
    {
        GameManager::Reset();
    }
}