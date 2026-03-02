// #ifndef BG_H
// #define BG_H
// 
// #include "ScrollingElement.h"
// 
// class BG : public ScrollingElement {
// public:
//     BG(OamState* newOam, float* speedPtr);
// 
//     // We override Update to call the base movement AND then render
//     void Update() override;
// 
// protected:
//     // This is called by ScrollingElement when the cactus goes off-screen
//     void OnReset() override;
// 
// private:
//     int curFrame = 0;
// };
// 
// #endif