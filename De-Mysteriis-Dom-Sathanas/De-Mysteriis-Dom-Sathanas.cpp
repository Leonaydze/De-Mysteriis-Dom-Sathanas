#include <iostream>
#include "Game.h"

int main()
{
	InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "AAA");

	InitAudioDevice();

	SetExitKey(KEY_NULL);       // Disable KEY_ESCAPE to close window, X-button still works
	
	bool exitWindowRequested = false;
	bool exitWindow = false;
	
	SetTargetFPS(60);

	while (!exitWindow) {
		if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;
		
		if (exitWindowRequested)
		{
			if (IsKeyPressed(KEY_Y)) {
				exitWindow = true;
			}
			else if (IsKeyPressed(KEY_N)){
				exitWindowRequested = false;
			}
		}
		
		BeginDrawing();
		ClearBackground(DARKGRAY);

		if (exitWindowRequested)
			{
				DrawRectangle(GetMonitorWidth(GetCurrentMonitor()) / 2 - 360, GetMonitorHeight(GetCurrentMonitor()) / 2 - 20, 750, 50, WHITE);
				DrawText("Are you sure you want to quit the game? [Y/N]", GetMonitorWidth(GetCurrentMonitor()) / 2 - 350, GetMonitorHeight(GetCurrentMonitor()) / 2 - 10, 30, BLACK);
			}
		
		MapLogic();
		DrawMap();

		if (GetCurrentMap() != 0 && GetCurrentMap() != 1 ) {
			Update();
		}

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}
