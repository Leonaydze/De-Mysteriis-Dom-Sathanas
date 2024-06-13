#include "Game.h"
#include "Player.h"
#include "Pugalo.h"
#include "HUD.h"
#include "Ground.h"

Player player = Player();

Pugalo pugalo = Pugalo();

Ground mainGroundFloor = { { 0, 17 } , GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()) + 10, WHITE };
Ground g2, g3;

extern GameScreen _currentScreen = MAIN_MENU;

extern Sound touchButton = LoadSound("Resources\\UseButton.mp3");

void PlayerCanWalk(Player player, Ground ground) {
    if (player.GetPlayerPositionX() >= ground.GetGroundPositionX() && player.GetPlayerPositionX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
        && (player.GetPlayerPositionY() >= ground.GetGroundPositionY() && player.GetPlayerPositionY() <= ground.GetGroundPositionY() + ground.GetGroundHeight())) {
        player.SetBoolPlayerCanWalk(false);
    }
    else {
        player.SetBoolPlayerCanWalk(true);
    }
}


void MapLogic() {
    switch (_currentScreen)
    {
    case MAIN_MENU:
        if ((GetMouseX() >= GetScreenWidth() / 2 - 50 && GetMouseX() <= GetScreenWidth() / 2 + 50)
            && (GetMouseY() >= GetScreenHeight() / 2 - 25 && GetMouseY() <= GetScreenHeight() / 2 + 25)
            && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
            PlaySound(touchButton);
            _currentScreen = LEVEL_1;
            UnloadSound(touchButton);
        }
        break;
    case LEVEL_1:
        DrawHUD(player);
        break;
    }
}


void DrawMap() {
    BeginDrawing();

    ClearBackground(BLACK);

    switch (_currentScreen)
    {
    case MAIN_MENU:
        DrawText("MAIN_MENU", 20, 20, 40, WHITE);
        DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 25, 100, 50, WHITE);
        DrawText("Play", GetScreenWidth() / 2 - 40, GetScreenHeight() / 2 - 20, 40, BLACK);
        break;
    case LEVEL_1:
        DrawText("LEVEL_1", 20, 20, 40, WHITE);
        pugalo.Draw();
        break;
        EndDrawing();
    }
}

int GetCurrentMap() {
    return _currentScreen;
}

void Update() {
    player.PlayerController();
    player.Draw();
    mainGroundFloor.GroundDraw();

    if (player.IsPlayerJump()) {
        player.MoveVertically();
        player.SetPlayerCanJump(false);
    }
    if (player.PlayerMaxJump() && !player.GetPlayerCanJump() || (!player.IsPlayerJump() && player.GetJumpHeight() > 0)) {
        player.SetPlayerJump(false);
        player.MoveVerticallyDown();
    }
}

bool PlayerOnGround(Player& player, Ground& ground) {
    return (player.GetPlayerPositionX() >= ground.GetGroundPositionX() && player.GetPlayerPositionX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
        && player.GetPlayerPositionY() >= ground.GetGroundPositionY() && player.GetPlayerPositionY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}