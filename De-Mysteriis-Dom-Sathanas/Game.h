#pragma once
#include <raylib.h>

enum GameScreen { MAIN_MENU, SETTINGS, LEVEL_1, LEVEL_2, LEVEL_3 };

void Init();

void MapLogic();

void DrawMap();

int GetCurrentMap();

void Update();