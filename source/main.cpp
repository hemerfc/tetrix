/*
	Simple demo of sprites using citro3d, lodepng and immediate mode.
	Citra doesn't yet emulate immediate mode so this is hw only.
*/

#include <3ds.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// These headers are generated by the build process
#include "gfx.h"
#include "game.h"

#define TICKS_PER_SEC 268111856.0

int main(int argc, char **argv) {
  // init timer system
  u64	initialTime = svcGetSystemTick();

	Gfx gfx;
  gfx.Init();

	Game game;
	game.Init();

	// Main loop
	while (aptMainLoop()) {
		hidScanInput();

		// User input
		u32 kDown = hidKeysDown();
		u32 kUp = hidKeysUp();
		u32 kHeld = hidKeysHeld();

		if (kDown & KEY_START)
			break;  // break here to return to hbmenu

		/*

		if (kDown & KEY_DLEFT)  // KEY_START, KEY_Y, KEY_UP, KEY_DOWN
			game.Left();
    if (kDown & KEY_DRIGHT)  // KEY_START, KEY_Y, KEY_UP, KEY_DOWN
			game.Right();
		*/

    // calc elapsed time
		double elapsed = (svcGetSystemTick() - initialTime)/TICKS_PER_SEC;
		// printf("\x1b[4;1Helapsed: %.2f", (float)elapsed);

		// update game state
		game.Update(elapsed, kDown, kUp, kHeld);

		// render the graphics
		game.Render(gfx);

		printf("\x1b[10;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[11;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[12;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);
	}

	gfx.Destroy();
	return 0;
}
