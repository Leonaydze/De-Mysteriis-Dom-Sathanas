#include "Game.h"
#include "Player.h"
#include "Pugalo.h"
#include "Ground.h"
#include "Door.h"
#include "Enemy.h"
#include "CustomColors.h"
#include <ctime>

extern GameScreen _currentScreen = LEVEL_2;

Font font;

Player player;
Camera2D _playerCamera;

Pugalo pugalo;

Ground mainGroundFloor;
Ground leftBorder;

Ground platform, platform_2;

Door door;

Enemy enemy_lv2;
Enemy enemy_lv3, enemy_lv3_2, enemy_lv3_3;

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
    font = LoadFont("Resources\\KHTitle.otf");
    
    player = Player({ 50.0f , 950.0f });
    _playerCamera;

    pugalo = Pugalo({ 2500.0f , 930.0f});

    mainGroundFloor = { { 0 , 1000 } , 5000, 1500, darkGrey };
    leftBorder = { { -1000.0f , 0.0f }, 1000, 5000, DARKGRAY };

    door = Door( { 2700 , 900 } );

    enemy_lv2 = { { 1488.0f , 950.0f }, 100, 15 };

    platform = { { 400 , 900 }, 256, 32, DARKGRAY };
    enemy_lv3 = { { 420 , 820 }, 100, 10 };

    platform_2 = { { 700 , 800 }, 256, 32, DARKGRAY };
    enemy_lv3_2 = { { 700 , 740 }, 100, 10 };
}

void EnemyGoesToThePlayer(Enemy &enemy) {
    if (player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() - 250
        && player.GetPlayerPositionX() + 32 <= enemy.GetEnemyPositionX() + 32 && enemy.GetEnemyHealth() > 0) {
        enemy.EnemyMoveX(-5.5f);
    }
    if (player.GetPlayerPositionX() + 64 <= enemy.GetEnemyPositionX() + 250
        && player.GetPlayerPositionX() >= enemy.GetEnemyPositionX() + 32 && enemy.GetEnemyHealth() > 0) {
        enemy.EnemyMoveX(5.5f);
    }
}

void EnemyAttacksThePlayer(Enemy &enemy) {
    if (enemy.GetEnemyHealth() > 0
        && player.GetPlayerPositionX() + 64 >= enemy_lv2.GetEnemyPositionX() - 100
        && player.GetPlayerPositionX() <= enemy.GetEnemyPositionX() + 164
        && player.GetPlayerPositionY() >= enemy.GetEnemyPositionY() - 40
        && player. GetPlayerPositionY() + 64 <= enemy.GetEnemyPositionY() + 104){
        if (EventTriggered(1.0f)) {
            player.PlayerTakesDamageFromTheEnemy(enemy.GetEnemyDamage());
        }
    }
}

void PlayerAttacksEnemy(Enemy &enemy) {
    if (player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() - 70
        && player.GetPlayerPositionX() <= enemy.GetEnemyPositionX() + 134
        && player.GetPlayerPositionY() >= enemy.GetEnemyPositionY() - 40
        && player.GetPlayerPositionY() + 64 <= enemy.GetEnemyPositionY() + 104) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && EventTriggered(0.5f)) {
            enemy.EnemyTakesDamageFromThePlayer(player.GetPlayerDamage());
        }
    }
}

bool EnemyOnGround(Enemy &enemy, Ground& ground) {
    return (enemy.GetEnemyPositionX() + 64 >= ground.GetGroundPositionX() && enemy.GetEnemyPositionX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
        && enemy.GetEnemyPositionY() + 64 >= ground.GetGroundPositionY() + 15 && enemy.GetEnemyPositionY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
}

bool PlayerOnGround(Player player, Ground& ground) {
    player.SetPlayerCanJump(true);
    return (player.GetPlayerPositionX() + 64 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
        && player.GetPlayerPositionY() + 64 >= ground.GetGroundPositionY() + 15 && player.GetPlayerPositionY() <= ground.GetGroundPositionY() + ground.GetGroundHeight());
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
        if (player.GetPlayerPositionX() + 64 >= door.DoorPositionX() && player.GetPlayerPositionX() <= door.DoorPositionX() + 80 &&
            player.GetPlayerPositionY() >= door.DoorPositionY() && player.GetPlayerPositionY() + 64 <= door.DoorPositionY() + 128){
            _currentScreen = LEVEL_2;
            player.SetPlayerPosition({ 50.0f , 950.0f });
        }
        break;
    case LEVEL_2:
        EnemyGoesToThePlayer(enemy_lv2);
        EnemyAttacksThePlayer(enemy_lv2);
        PlayerAttacksEnemy(enemy_lv2);
        if (player.GetPlayerPositionX() + 64 >= door.DoorPositionX() && player.GetPlayerPositionX() <= door.DoorPositionX() + 80 &&
            player.GetPlayerPositionY() >= door.DoorPositionY() && player.GetPlayerPositionY() + 64 <= door.DoorPositionY() + 128) {
            player.PlayerTakesDamageFromTheEnemy(-(100 - player.GetPlayerHealth()));
            _currentScreen = LEVEL_3;
            player.SetPlayerPosition({ 50.0f , 950.0f });
        }
        break;
    case LEVEL_3:
        EnemyGoesToThePlayer(enemy_lv3);
        EnemyAttacksThePlayer(enemy_lv3);
        PlayerAttacksEnemy(enemy_lv3);
        EnemyGoesToThePlayer(enemy_lv3_2);
        EnemyAttacksThePlayer(enemy_lv3_2);
        PlayerAttacksEnemy(enemy_lv3_2);
        break;
    }
}


void DrawMap() {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (_currentScreen)
    {
    case MAIN_MENU:
        DrawTextEx(font, "MAIN_MENU", { 20, 20 }, 40, 2, WHITE);
        DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 25, 100, 50, WHITE);
        DrawTextEx(font, "Play", {(float) GetScreenWidth() / 2 - 45, (float)GetScreenHeight() / 2 - 20 }, 42, 4, BLACK);
        break;
    case LEVEL_1:
        BeginMode2D(_playerCamera);
        mainGroundFloor.GroundDraw();
        leftBorder.GroundDraw();
        DrawTextEx(font, "LEVEL_1", { player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700 }, 42, 4, WHITE);
        pugalo.Draw();
        door.DrawDoor();
        break;
    case LEVEL_2:
        BeginMode2D(_playerCamera);
        DrawTextEx(font, "LEVEL_2", { player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700 }, 42, 4, WHITE);
        mainGroundFloor.GroundDraw();
        enemy_lv2.DrawEnemy();
        door.DrawDoor();
        break;
    case LEVEL_3:
        BeginMode2D(_playerCamera);
        mainGroundFloor.GroundDraw();
        leftBorder.GroundDraw();
        DrawTextEx(font, "LEVEL_3", { player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700 }, 42, 4, WHITE);
        platform.GroundDraw();
        platform_2.GroundDraw();
        enemy_lv3.DrawEnemy();
        enemy_lv3_2.DrawEnemy();
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


    if (player.IsPlayerJump() && !player.PlayerMaxJump() && player.GetPlayerCanJump()) {
        player.MoveVertically();
    }
    else if (PlayerOnGround(player, mainGroundFloor)) {
        player.SetPlayerCanJump(true);
    }
    else if (PlayerOnGround(player, platform)) {
        player.SetPlayerCanJump(true);
    }
    else if (player.PlayerMaxJump() || !player.IsPlayerJump()) {
        player.MoveVerticallyDown();
    } 

    if (!EnemyOnGround(enemy_lv3, platform)) {
        if (!EnemyOnGround(enemy_lv3, mainGroundFloor)) {
            enemy_lv3.EnemyMoveVerticallyDown();
        }
    }
    if (!EnemyOnGround(enemy_lv3_2, platform_2)) {
        if (!EnemyOnGround(enemy_lv3_2, mainGroundFloor)) {
            enemy_lv3_2.EnemyMoveVerticallyDown();
        }
    }

    player.PlayerDeath();
}