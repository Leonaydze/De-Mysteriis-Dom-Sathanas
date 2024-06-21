#pragma once
#include <raylib.h>

enum GameScreen { MAIN_MENU, SETTINGS, LEVEL_1, LEVEL_2, LEVEL_3 };

bool GetExitWindow();
void SetExitWindow(bool exitWindow);

bool GetExitWindowRequest();
void SetExitWindowRequest(bool exitWindowRequest);

void Init();

void MapLogic();

void DrawMap();

int GetCurrentMap();

void Update();

void Quit();