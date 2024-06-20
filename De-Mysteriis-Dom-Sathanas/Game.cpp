#include "Game.h"
#include "Player.h"
#include "Pugalo.h"
#include "Ground.h"
#include "Door.h"
#include "Enemy.h"
#include "CustomColors.h"
#include <ctime>

Player player;
Camera2D _playerCamera;

Pugalo pugalo;

Ground mainGroundFloor;
Ground leftBorder;

Door door;

Enemy enemy;

double lastUpdateTime = 0;
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Init() {
    player = Player({ 50.0f , 950.0f });

    _playerCamera;

    pugalo = Pugalo({ 2500.0f, 930.0f});

    mainGroundFloor = { { 0, 1000 } , 2920, 150, darkGrey };
    leftBorder = { {-1000.0f, 0.0f}, 2000, 5000, DARKGRAY };

    door = Door({2700, 900});

    enemy = { { 1488.0f, 950.0f}, 100, 10 };
}

bool EnemyIsLookingForAPLayerLeft() {
    return (player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() - 250
        && player.GetPlayerPositionX() + 32 <= enemy.GetEnemyPositionX() + 32);
}

bool EnemyIsLookingForAPLayerRight() {
    return (player.GetPlayerPositionX() + 64 <= enemy.GetEnemyPositionX() + 250
        && player.GetPlayerPositionX() >= enemy.GetEnemyPositionX() + 32);
}

void EnemyGoesToThePlayer(Enemy &enemy) {
    if (EnemyIsLookingForAPLayerLeft() && enemy.GetEnemyHealth() > 0) {
        enemy.EnemyMoveX(-4.0f);
    }
    if (EnemyIsLookingForAPLayerRight() && enemy.GetEnemyHealth() > 0) {
        enemy.EnemyMoveX(4.0f);
    }
}

void EnemyAttacksThePlayer(Enemy &enemy) {
    if (enemy.GetEnemyHealth() > 0 && EnemyIsLookingForAPLayerLeft() &&
        player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() - 100
        && player.GetPlayerPositionX() + 32 <= enemy.GetEnemyPositionX() + 32) {
        if (EventTriggered(1)) {
            player.PlayerTakesDamageFromTheEnemy(enemy.GetEnemyDamage());
        }
    }
    if (enemy.GetEnemyHealth() > 0 && EnemyIsLookingForAPLayerRight() &&
        player.GetPlayerPositionX() + 64 <= enemy.GetEnemyPositionX() + 100
        && player.GetPlayerPositionX() >= enemy.GetEnemyPositionX() + 32) {
        if (EventTriggered(1)) {
            player.PlayerTakesDamageFromTheEnemy(enemy.GetEnemyDamage());
        }
    }
}

void PlayerAttacksEnemy(Enemy &enemy) {
    if (player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() + 32 - 70
        && player.GetPlayerPositionX() + 32 <= enemy.GetEnemyPositionX() + 32) {
        if (EventTriggered(0.5f)) {
            enemy.EnemyTakesDamageFromThePlayer(player.GetPlayerDamage());
        }
    }
    if (EnemyIsLookingForAPLayerRight() &&
        player.GetPlayerPositionX() + 64 <= enemy.GetEnemyPositionX() + 32 + 70
        && player.GetPlayerPositionX() >= enemy.GetEnemyPositionX() + 32) {
        if (EventTriggered(0.5f)) {
            enemy.EnemyTakesDamageFromThePlayer(player.GetPlayerDamage());
        }
    }
}

extern GameScreen _currentScreen = LEVEL_2;

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
    _playerCamera.target = {player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200};
    _playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
    _playerCamera.zoom = 1.0f;
    _playerCamera.rotation = 0.0f;

    switch (_currentScreen)
    {
    case MAIN_MENU:
        if ((GetMouseX() >= GetScreenWidth() / 2 - 50 && GetMouseX() <= GetScreenWidth() / 2 + 50)
            && (GetMouseY() >= GetScreenHeight() / 2 - 25 && GetMouseY() <= GetScreenHeight() / 2 + 25)
            && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
            _currentScreen = LEVEL_1;
        }
        break;
    case LEVEL_1:
        if (player.GetPlayerPositionX() + 64 >= door.DoorPositionX() && player.GetPlayerPositionX() - 64 <= door.DoorPositionX() + 128 &&
            player.GetPlayerPositionY() + 64 >= door.DoorPositionY() && player.GetPlayerPositionY() <= door.DoorPositionY() + 128){
            _currentScreen = LEVEL_2;
            player.SetPlayerPosition({ 50.0f , 950.0f });
        }
        break;
    case LEVEL_2:
        EnemyGoesToThePlayer(enemy);
        EnemyAttacksThePlayer(enemy);
        PlayerAttacksEnemy(enemy);
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
        leftBorder.GroundDraw();
        DrawText("LEVEL_1", player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700, 40, WHITE);
        pugalo.Draw();
        door.DrawDoor();
        break;
    case LEVEL_2:
        BeginMode2D(_playerCamera);
        mainGroundFloor.GroundDraw();
        DrawText("LEVEL_2", player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700, 40, WHITE);
        enemy.DrawEnemy();
        break;
        EndMode2D();
        EndDrawing();
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
