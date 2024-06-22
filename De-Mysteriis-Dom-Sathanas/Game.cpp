#include "Game.h"
#include "Player.h"
#include "Pugalo.h"
#include "Ground.h"
#include "Door.h"
#include "Enemy.h"
#include "CustomColors.h"
#include <ctime>

extern GameScreen _currentScreen = MAIN_MENU;

Font font;

Sound PlayButton, PlayerTakesDamage, EnemyTakesDamage, PlayerJump;

Player player;
Camera2D _playerCamera;

Pugalo pugalo;

Ground mainGroundFloor;
Ground leftBorder;

Ground platform, platform_2;

Ground mainBorder;

Door door;

Enemy enemy_lv2;
Enemy enemy_lv3, enemy_lv3_2, enemy_lv3_3;

bool _exitWindowRequested = false;
bool _exitWindow = false;

int _playerKillsCount = 0;

bool GetExitWindow() {
	return _exitWindow;
}
void SetExitWindow(bool exitWindow) {
	_exitWindow = exitWindow;
}

bool GetExitWindowRequest() {
	return _exitWindowRequested;
}
void SetExitWindowRequest(bool exitWindowRequest) {
	_exitWindowRequested = exitWindowRequest;
}


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

	PlayButton = LoadSound("Resources\\PlayButtonSound.wav");
	PlayerTakesDamage = LoadSound("Resources\\PlayerTakesDamage.mp3");
	EnemyTakesDamage = LoadSound("Resources\\EnemyTakesDamage.wav");
	PlayerJump = LoadSound("Resources\\PlayerJump.mp3");

	player = Player({ 50.0f , 950.0f });
	_playerCamera;

	pugalo = Pugalo({ 2500.0f , 930.0f});

	mainGroundFloor = { { 0 , 1000 } , 5000, 1500, darkGrey };
	leftBorder = { { -1000.0f , 0.0f }, 1000, 5000, DARKGRAY };

	door = Door( { 2700 , 900 } );

	enemy_lv2 = { { 1488.0f , 950.0f }, 100, 15 };

	platform = { { 1000 , 900 }, 256, 32, DARKGRAY };
	enemy_lv3 = { { 1020 , 820 }, 100, 15 };

	platform_2 = { { 1300 , 740 }, 256, 32, DARKGRAY };
	enemy_lv3_2 = { { 1320 , 680 }, 100, 15 };
}


void EnemyDead(Enemy &enemy) {
	if (enemy.GetEnemyHealth() <= 0 && !enemy.BoolCheckIsEnemyDeath()) {
		_playerKillsCount++;
		enemy.SetBoolCheckIsEnemyDeath(true);
	}
}

void EnemyAttacksThePlayer(Enemy &enemy) {
	if (player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() - 100
		&& player.GetPlayerPositionX() <= enemy.GetEnemyPositionX() + 164
		&& player.GetPlayerPositionY() >= enemy.GetEnemyPositionY() - 40
		&& player. GetPlayerPositionY() + 64 <= enemy.GetEnemyPositionY() + 104 && enemy.GetEnemyHealth() > 0){
		if (EventTriggered(1.0f)) {
			PlaySound(PlayerTakesDamage);
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
			PlaySound(EnemyTakesDamage);
			enemy.EnemyTakesDamageFromThePlayer(player.GetPlayerDamage());
		}
	}
}

void EnemyGoesToThePlayer(Enemy &enemy) {
	if (player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() - 250
		&& player.GetPlayerPositionX() + 64 <= enemy.GetEnemyPositionX() + 64 && enemy.GetEnemyHealth() > 0) {
		enemy.EnemyMoveX(-5.5f);
	}
	if (player.GetPlayerPositionX() + 64 <= enemy.GetEnemyPositionX() + 250
		&& player.GetPlayerPositionX() >= enemy.GetEnemyPositionX() && enemy.GetEnemyHealth() > 0) {
		enemy.EnemyMoveX(5.5f);
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

void PlayerCanWalk(Player player, Ground &ground) {
	if (player.GetPlayerPositionX() + 64 >= ground.GetGroundPositionX() && player.GetPlayerPositionX() <= ground.GetGroundPositionX() + ground.GetGroundWidth()
		 && player.GetPlayerPositionY() + 64 >= ground.GetGroundPositionY()) {
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
		if ((GetMouseX() >= GetScreenWidth() / 2 - 50 && GetMouseX() <= GetScreenWidth() / 2 + 65)
			&& (GetMouseY() >= GetScreenHeight() / 2 - 25 && GetMouseY() <= GetScreenHeight() / 2 + 25)
			&& (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
			PlaySound(PlayButton);
			_currentScreen = LEVEL_1;
		}
		if ((GetMouseX() >= GetScreenWidth() / 10 - 100 && GetMouseX() <= GetScreenWidth() / 10 + 115)
			&& (GetMouseY() >= GetScreenHeight() - 100 && GetMouseY() <= GetScreenHeight() - 50)
			&& (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
			SetExitWindow(true);
			EndDrawing();
			EndMode2D();
			CloseAudioDevice();
			CloseWindow();
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
		EnemyAttacksThePlayer(enemy_lv3);
		EnemyAttacksThePlayer(enemy_lv3_2);
		PlayerAttacksEnemy(enemy_lv3);
		PlayerAttacksEnemy(enemy_lv3_2);
		EnemyGoesToThePlayer(enemy_lv3);
		EnemyGoesToThePlayer(enemy_lv3_2);
		EnemyDead(enemy_lv3);
		EnemyDead(enemy_lv3_2);
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
		DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 25, 115, 50, WHITE);
		DrawTextEx(font, "Play", {(float) GetScreenWidth() / 2 - 45, (float)GetScreenHeight() / 2 - 20 }, 42, 4, BLACK);
		DrawTextEx(font, "DE-MYSTERIIS-DOM-SATHANAS", { (float)GetScreenWidth() / 2 - 450, (float)GetScreenHeight() / 2 - 500 }, 64, 4, WHITE);
		DrawTextEx(font, "by FILOSOFEM STUDIO", { (float)GetScreenWidth() / 2 - 280, (float)GetScreenHeight() / 2 - 400 }, 58, 4, WHITE);
		DrawRectangle(GetScreenWidth() / 10 - 100, GetScreenHeight() - 100, 115, 50, WHITE);
		DrawTextEx(font, "QUIT", { (float)GetScreenWidth() / 10 - 95, (float)GetScreenHeight() - 95 }, 42, 4, BLACK);
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
		PlaySound(PlayerJump);
	}
	else if ( GetCurrentMap() == 4 && (PlayerOnGround(player, platform) || PlayerOnGround(player, platform_2))) {
		player.SetPlayerCanJump(true);
		PlaySound(PlayerJump);
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
		if (!EnemyOnGround(enemy_lv3, platform)) {
			if (!EnemyOnGround(enemy_lv3_2, mainGroundFloor)) {
				enemy_lv3_2.EnemyMoveVerticallyDown();
			}
		}
	}

	if (_playerKillsCount == 2) {
		DrawTextEx(font, "YOU PASSED THE GAME! YOU'VE WON", { (float)player.GetPlayerPositionX() - 380, (float)player.GetPlayerPositionY() - 550 }, 48, 4, WHITE);
		DrawTextEx(font, "PRESS ESC TO QUIT", { player.GetPlayerPositionX() - 150, player.GetPlayerPositionY() - 450 }, 36, 4, WHITE);
	}

	player.PlayerDeath();
}

void Quit() {
	DrawRectangle(player.GetPlayerPositionX() - 400, player.GetPlayerPositionY() - 300, 880, 50, WHITE);
	DrawTextEx(font, "ARE YOU SURE YOU  WANT TO QUIT THE GAME? ( Y / N )", { (float)player.GetPlayerPositionX() - 390, (float)player.GetPlayerPositionY() - 290}, 30, 4, BLACK);
}