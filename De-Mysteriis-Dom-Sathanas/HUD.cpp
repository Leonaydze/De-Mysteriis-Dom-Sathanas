#include "HUD.h"
	

void DrawHUD(Player player) {
	DrawRectangle(15, 60, 210, 30, DARKBROWN);
	DrawRectangle(20, 65, player.GetPlayerHealth() * 2, 20, RED);
}