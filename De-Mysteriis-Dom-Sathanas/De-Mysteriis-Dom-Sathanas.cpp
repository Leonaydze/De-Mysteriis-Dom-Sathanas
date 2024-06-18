#include <iostream>
#include "Game.h";

int main()
{
	InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "AAA");

	InitAudioDevice();

	Init();

	SetExitKey(KEY_NULL);       // Disable KEY_ESCAPE to close window, X-button still works
	
	bool exitWindowRequested = false;
	bool exitWindow = false;
	
	SetTargetFPS(60);

	while (!exitWindow) {
		if (WindowShouldClose() && GetCurrentMap() != 0 || IsKeyPressed(KEY_ESCAPE) && GetCurrentMap() != 0){
			exitWindowRequested = true;
		}
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
				DrawRectangle(GetMonitorWidth(GetCurrentMonitor()) / 2 - 360, GetMonitorHeight(GetCurrentMonitor()) / 2 - 80, 750, 50, WHITE);
				DrawText("Are you sure you want to quit the game? [Y/N]", GetMonitorWidth(GetCurrentMonitor()) / 2 - 350 , GetMonitorHeight(GetCurrentMonitor()) / 2 - 70, 30, BLACK);
			}

		DrawMap();
		MapLogic();

		if (GetCurrentMap() != 0 && GetCurrentMap() != 1 ) {
			Update();
		}

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}
