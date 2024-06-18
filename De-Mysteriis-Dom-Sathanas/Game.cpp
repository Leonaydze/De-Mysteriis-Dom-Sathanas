#include "Game.h"
#include "Player.h"
#include "Pugalo.h"
#include "Ground.h"
#include "Door.h"
#include "Enemy.h"

Player player = Player({ 50.0f , 950.0f });
Camera2D _playerCamera;

Pugalo pugalo = Pugalo();

Ground mainGroundFloor = { { 0, 1000 } , 1920, 150, DARKGRAY };

Door door = Door({1700, 900});

Enemy enemy = { { 1488.0f, 950.0f}, 100, 5 };

extern GameScreen _currentScreen = LEVEL_1;

extern Sound touchButton = LoadSound("Resources\\UseButton.mp3");

bool PlayerOnGround(Player& player, Ground& ground) {
    player.SetPlayerCanJump(true);
    return (player.GetPlayerPositionX() + 64 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
        && player.GetPlayerPositionY() + 64 >= ground.GetGroundPositionY() && player.GetPlayerPositionY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

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
        _playerCamera.target = player.GetPlayerPosition();
        _playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
        _playerCamera.zoom = 1.0f;
        _playerCamera.rotation = 0.0f;
        if (player.GetPlayerPositionX() + 64 >= door.DoorPositionX() && player.GetPlayerPositionX() - 64 <= door.DoorPositionX() + 128 &&
            player.GetPlayerPositionY() + 64 >= door.DoorPositionY() && player.GetPlayerPositionY() <= door.DoorPositionY() + 128){
            _currentScreen = LEVEL_2;
            player.SetPlayerPosition({ 50.0f , 950.0f });
        }
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
        BeginMode2D(_playerCamera);
        mainGroundFloor.GroundDraw();
        DrawText("LEVEL_1", 20, 20, 40, WHITE);
        pugalo.Draw();
        door.DrawDoor();
        break;
    case LEVEL_2:
        mainGroundFloor.GroundDraw();
        DrawText("LEVEL_2", 20, 20, 40, WHITE);
        enemy.DrawEnemy();
        break;
        EndDrawing();
        EndMode2D();
    }

}

int GetCurrentMap() {
    return _currentScreen;
}

void Update() {
    player.PlayerController();
    player.Draw();

    if (player.IsPlayerJump() && !player.PlayerMaxJump() && !player.GetPlayerCanJump()) {
        player.MoveVertically();
    }
    else if (!PlayerOnGround(player, mainGroundFloor)) {
        player.MoveVerticallyDown();
        player.SetPlayerCanJump(false);
    }
}
