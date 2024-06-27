#include <iostream>
#include "Game.h";

int main()
{
	InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "DE-MYSTERIIS-DOM-SATHANAS");

	InitAudioDevice();

	Init();

	SetExitKey(KEY_NULL);       // Disable KEY_ESCAPE to close window, X-button still works
	
	
	SetTargetFPS(60);

	Font mainFont = LoadFont("Resources\\KHTitle.otf");

	while (!GetExitWindow()) {
		if (WindowShouldClose() && GetCurrentMap() != 0 || IsKeyPressed(KEY_ESCAPE) && GetCurrentMap() != 0){
			SetExitWindowRequest(true);
		}
		if (GetExitWindowRequest)
		{
			if (IsKeyPressed(KEY_Y)) {
				SetExitWindow(true);
			}
			else if (IsKeyPressed(KEY_N)){
				SetExitWindowRequest(false);
			}
		}
		
		BeginDrawing();
		ClearBackground(DARKGRAY);
		
		DrawMap();
		MapLogic();

		if (GetExitWindowRequest()){
			Quit();
		}

		if (GetCurrentMap() != 0 && GetCurrentMap() != 1 ) {
			Update();
		}

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}
