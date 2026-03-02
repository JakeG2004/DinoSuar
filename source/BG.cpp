// #include "BG.h"
// #include "Ground.h"
// 
// BG::BG(OamState* newOam, float* speedPtr) : ScrollingElement(newOam, SpriteSize_64x64, SpriteColorFormat_256Color, 5, speedPtr)
// {
//     y = 110;
//     
//     dmaCopy(GroundTiles, *gfx, GroundTilesLen);
// }
// 
// void BG::Update()
// {
//     ScrollingElement::Update();
// 
//     render(curFrame, 64, 64);
// }
// 
// void BG::OnReset()
// {
//     curFrame = rand() % 5;
// }