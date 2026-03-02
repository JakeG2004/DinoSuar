#include <nds.h>
#include <maxmod9.h>
#include "Dino.h"
#include "Cactus.h"
#include "GameManager.h"
#include <maxmod9.h>    // Required for mmEffectEx 
#include "soundbank.h" // Required for SFX_HIT ID 
#include "soundbank_bin.h"

// Background
#include "bg_test.h"

// Sprites
#include "Dino_Walk.h"
#include "Cacti.h"

int bgMain;
int bgSub;

void InitScreens();

int main(void) 
{
    // Initialization, like Start()
    InitScreens();

    Dino topDino = Dino(&oamMain, KEY_X, KEY_B);
    Dino botDino = Dino(&oamSub, KEY_UP, KEY_DOWN);

    Cactus topCactus = Cactus(&oamMain, &topDino);
    Cactus bottomCactus = Cactus(&oamSub, &botDino);

    GameManager::Create(&topDino, &botDino, &topCactus, &bottomCactus);
    GameManager* gm = GameManager::getInstance();

    int bgScroll = 0;

    mmInitDefaultMem((mm_addr)soundbank_bin);
    
    int musicTimer = 0;
    int songLengthInFrames = 60 * 66;

    // Update loop
    while(1) 
    {
        if(musicTimer <= 0)
        {
            // --- PLAY JUMP SOUND ---
            // We define the sound effect inline here so it triggers on jump
            mm_sound_effect music_sfx = {
                { SFX_MUSIC },             // id from soundbank.h 
                (int)(1.0f * (1<<10)),   // rate (normal speed) 
                0,                       // handle 
                255,                     // volume (max) 
                128,                     // panning (center) 
            };
            mmEffectEx(&music_sfx);
            musicTimer = songLengthInFrames;
        }

        musicTimer--;

        // Get the keys
        scanKeys();
        int keys = keysHeld();

        gm -> Update(keys);

        // Update the dinos
        topDino.Update(keys);
        botDino.Update(keys);

        bgScroll = (int)(bgScroll + gm -> gameSpeed);
        bgSetScroll(bgMain, bgScroll, 0);
        bgSetScroll(bgSub, bgScroll, 0);

        bgUpdate();

        // Update the cacti
        topCactus.Update();
        bottomCactus.Update();

        // Wait for screen to finish drawing
        swiWaitForVBlank();

        // Commit the changes to hardware
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }
}

void InitScreens()
{
    // 1. Setup Video Modes for Tiled Graphics (Mode 0)
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    // 2. Map VRAM Banks
    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);
    vramSetBankB(VRAM_B_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    consoleDemoInit();

    // Initialize the scrolling tiled background
    bgMain = bgInit(3, BgType_Text8bpp, BgSize_T_512x256, 0, 1);
    bgSub = bgInitSub(3, BgType_Text8bpp, BgSize_T_512x256, 0, 1);

    // Copy tiles
    dmaCopy(bg_testTiles, bgGetGfxPtr(bgMain), bg_testTilesLen);
    dmaCopy(bg_testTiles, bgGetGfxPtr(bgSub), bg_testTilesLen);

    // Copy tilemap
    dmaCopy(bg_testMap, bgGetMapPtr(bgMain), bg_testMapLen);
    dmaCopy(bg_testMap, bgGetMapPtr(bgSub), bg_testMapLen);

    // Copy Palette
    dmaCopy(bg_testPal, BG_PALETTE, bg_testPalLen);
    dmaCopy(bg_testPal, BG_PALETTE_SUB, bg_testPalLen);

    // Initialize the OAM Engines
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    oamInit(&oamSub, SpriteMapping_1D_32, false);

    // Initialize sprites
    dmaCopy(CactiPal, SPRITE_PALETTE, CactiPalLen);
    dmaCopy(CactiPal, SPRITE_PALETTE_SUB, CactiPalLen);
    
    dmaCopy(Dino_WalkPal, SPRITE_PALETTE, Dino_WalkPalLen);
    dmaCopy(Dino_WalkPal, SPRITE_PALETTE_SUB, Dino_WalkPalLen);
}