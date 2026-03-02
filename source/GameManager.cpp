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
    gameSpeed += 0.1f;
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

    DrawGameOver();

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

void GameManager::DrawGameOver()
{
    // --- NEW: TOP INSTRUCTIONS ---
    // Position at Row 2, Column 5
    iprintf("\x1b[2;5HUP / X to JUMP");
    // Position at Row 3, Column 5
    iprintf("\x1b[3;5HDOWN / B to CROUCH");
    iprintf("\x1b[4;5HSelect for solo / co-op");
    iprintf("\x1b[5;5HCurrent: ");
    iprintf("\x1b[5;14H%s", singlePlayer == 1 ? "Single Player" : "  Multiplayer");

    // --- WINNER TEXT ---
    iprintf("\x1b[10;7H"); // Moved column slightly for centering
    if (gameOver == 1) {
        iprintf("BOTTOM PLAYER WINS!");
    } else {
        iprintf("TOP PLAYER WINS!");
    }
    
    // --- RESTART TEXT ---
    // Using \n for a new line instead of complex escape codes can be cleaner
    iprintf("\x1b[12;5HPRESS START TO RESTART");
}

void GameManager::DrawScore(int newScore)
{
    iprintf("\x1b[0;1HSCORE: %i", newScore);
}