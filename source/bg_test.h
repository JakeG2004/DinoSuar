
//{{BLOCK(bg_test)

//======================================================================
//
//	bg_test, 512x256@8, 
//	+ palette 256 entries, not compressed
//	+ 40 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 2560 + 4096 = 7168
//
//	Time-stamp: 2026-03-01, 10:40:07
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BG_TEST_H
#define GRIT_BG_TEST_H

#define bg_testTilesLen 2560
extern const unsigned int bg_testTiles[640];

#define bg_testMapLen 4096
extern const unsigned short bg_testMap[2048];

#define bg_testPalLen 512
extern const unsigned short bg_testPal[256];

#endif // GRIT_BG_TEST_H

//}}BLOCK(bg_test)
