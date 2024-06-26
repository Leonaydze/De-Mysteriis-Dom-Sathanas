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

Texture2D background_1, background_2, background_3 ;

Sound EnemyDeath;
Sound PlayButton, PlayerTakesDamage, EnemyTakesDamage, EnemyTakesDamage_2, EnemyTakesDamage_3, PlayerJump;
Sound MainMenuTheme, Level_1Theme, Level_2Theme, Level_3Theme;

Player player;
Camera2D _playerCamera;

Pugalo pugalo;

Ground mainGroundFloor;
Ground leftBorder;

Ground platform, platform_2, platform_3, platform_4;

Ground mainBorder;

Door door;

Enemy enemy_lv2;
Enemy enemy_lv3, enemy_lv3_2, enemy_lv3_3, enemy_lv3_4;

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

	background_1 = LoadTexture("Resources\\background_1.png");
	background_1.width *= 2;
	background_2 = LoadTexture("Resources\\background_2.png");
	background_2.width *= 2;

	EnemyDeath = LoadSound("Resources\\EnemyDeath.wav");

	PlayButton = LoadSound("Resources\\PlayButtonSound.wav");
	PlayerTakesDamage = LoadSound("Resources\\PlayerTakesDamage.mp3");
	EnemyTakesDamage = LoadSound("Resources\\EnemyTakesDamage.wav");
	EnemyTakesDamage_2 = LoadSound("Resources\\EnemyTakesDamage_2.wav");
	EnemyTakesDamage_3 = LoadSound("Resources\\EnemyTakesDamage_3.wav");
	PlayerJump = LoadSound("Resources\\PlayerJump.mp3");

	MainMenuTheme = LoadSound("Resources\\MainMenuTheme.wav");
	Level_1Theme = LoadSound("Resources\\Level_1Theme.wav");
	Level_2Theme = LoadSound("Resources\\Level_2Theme.wav");
	Level_3Theme = LoadSound("Resources\\Level_3Theme.wav");

	player = Player({ 50.0f , 950.0f });
	_playerCamera;

	pugalo = Pugalo({ 2150.0f , 850.0f});

	mainGroundFloor = { { -1000 , 1000 } , 5400, 1500, darkGrey };
	leftBorder = { { -1000.0f , 0.0f }, 1000, 5000, DARKGRAY };

	door = Door( { 3000 , 900 } );

	enemy_lv2 = { { 1488.0f , 950.0f }, 100, 15 };

	platform = { { 1000 , 900 }, 256, 32, DARKGRAY };
	enemy_lv3 = { { 1020 , 820 }, 100, 15 };

	platform_2 = { { 1300 , 740 }, 256, 32, DARKGRAY };
	enemy_lv3_2 = { { 1320 , 680 }, 100, 15 };

	platform_3 = { { 2300 , 740 }, 256, 32, DARKGRAY };
	enemy_lv3_3 = { { 2400 , 680 }, 100, 15 };

	platform_4 = { { 2700 , 860 }, 256, 32, DARKGRAY };
	enemy_lv3_4 = { { 2800 , 800 }, 100, 15 };
}


void EnemyDead(Enemy &enemy) {
	if (enemy.GetEnemyHealth() <= 0 && !enemy.BoolCheckIsEnemyDeath()) {
		_playerKillsCount++;
		enemy.SetBoolCheckIsEnemyDeath(true);
		PlaySound(EnemyDeath);
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

void SoundEnemyTakesDamage() {
	int choice = rand() % 3;

	switch (choice){
		case 0:
			PlaySound(EnemyTakesDamage);
			break;
		case 1:
			PlaySound(EnemyTakesDamage_2);
			break;
		case 2:
			PlaySound(EnemyTakesDamage_3);
			break;
	}
}

void PlayerAttacksEnemy(Enemy &enemy) {
	if (player.GetPlayerPositionX() + 64 >= enemy.GetEnemyPositionX() - 70
		&& player.GetPlayerPositionX() <= enemy.GetEnemyPositionX() + 134
		&& player.GetPlayerPositionY() >= enemy.GetEnemyPositionY() - 40
		&& player.GetPlayerPositionY() + 64 <= enemy.GetEnemyPositionY() + 104) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && EventTriggered(0.5f)) {
			SoundEnemyTakesDamage();
			enemy.EnemyTakesDamageFromThePlayer(player.GetPlayerDamage());
		}
	}
}

void PlayerAttacksPugalo(Pugalo& pugalo) {
	if (player.GetPlayerPositionX() + 64 >= pugalo.GetPugaloPositionX() - 70
		&& player.GetPlayerPositionX() <= pugalo.GetPugaloPositionX() + 134
		&& player.GetPlayerPositionY() >= pugalo.GetPugaloPositionY() - 40) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && EventTriggered(0.5f)) {
			SoundEnemyTakesDamage();
			pugalo.SetFrameRecX(124);
		}
		if (EventTriggered(1.0f)) {
			pugalo.SetFrameRecX(0);
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

void AttackEnemyAndPlayer(Enemy &enemy) {
	EnemyAttacksThePlayer(enemy);
	PlayerAttacksEnemy(enemy);
	EnemyGoesToThePlayer(enemy);
	EnemyDead(enemy);
}

void MapLogic() {
	_playerCamera.target = {player.GetPlayerPositionX(), player.GetPlayerPositionY() - 200};
	_playerCamera.offset = { 1920.0f / 2.0f, 1080.0f / 2.0f };
	_playerCamera.zoom = 1.0f;
	_playerCamera.rotation = 0.0f;

	switch (_currentScreen)
	{
	case MAIN_MENU:
		if (!IsSoundPlaying(MainMenuTheme)) {
			PlaySound(MainMenuTheme);
		}
		if ((GetMouseX() >= GetScreenWidth() / 2 - 50 && GetMouseX() <= GetScreenWidth() / 2 + 65)
			&& (GetMouseY() >= GetScreenHeight() / 2 - 35 && GetMouseY() <= GetScreenHeight() / 2 + 25)
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
		if (IsSoundPlaying(MainMenuTheme)) {
			StopSound(MainMenuTheme);
		}
		if (!IsSoundPlaying(Level_1Theme)) {
			PlaySound(Level_1Theme);
		}
		PlayerAttacksPugalo(pugalo);
		if (player.GetPlayerPositionX() + 64 >= door.DoorPositionX() && player.GetPlayerPositionX() <= door.DoorPositionX() + 80 &&
			player.GetPlayerPositionY() >= door.DoorPositionY() && player.GetPlayerPositionY() + 64 <= door.DoorPositionY() + 128){
			_currentScreen = LEVEL_2;
			player.SetPlayerPosition({ 50.0f , 950.0f });
		}
		break;
	case LEVEL_2:
		if (IsSoundPlaying(Level_1Theme)) {
			StopSound(Level_1Theme);
		}
		if (!IsSoundPlaying(Level_2Theme)) {
			PlaySound(Level_2Theme);
		}
		AttackEnemyAndPlayer(enemy_lv2);
		if (_playerKillsCount == 1) {
			if (player.GetPlayerPositionX() + 64 >= door.DoorPositionX() && player.GetPlayerPositionX() <= door.DoorPositionX() + 80 &&
				player.GetPlayerPositionY() >= door.DoorPositionY() && player.GetPlayerPositionY() + 64 <= door.DoorPositionY() + 128) {
				player.PlayerTakesDamageFromTheEnemy(-(100 - player.GetPlayerHealth()));
				_currentScreen = LEVEL_3;
				player.SetPlayerPosition({ 50.0f , 950.0f });
			}
		}
		break;
	case LEVEL_3:
		if (IsSoundPlaying(Level_2Theme)) {
			StopSound(Level_2Theme);
		}
		if (!IsSoundPlaying(Level_3Theme)) {
			PlaySound(Level_3Theme);
		}
		AttackEnemyAndPlayer(enemy_lv3);
		AttackEnemyAndPlayer(enemy_lv3_2);
		AttackEnemyAndPlayer(enemy_lv3_3);
		AttackEnemyAndPlayer(enemy_lv3_4);
		break;
	}
}

void DrawMap() {
	BeginDrawing();
	ClearBackground(BLACK);

	switch (_currentScreen)
	{
	case MAIN_MENU:
		DrawTextEx(font, "MAIN MENU", { (float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() / 2 - 70 }, 40, 2, WHITE);
		DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 15, 115, 50, WHITE);
		DrawTextEx(font, "Play", {(float) GetScreenWidth() / 2 - 45, (float)GetScreenHeight() / 2 - 10 }, 42, 4, BLACK);
		DrawTextEx(font, "DE-MYSTERIIS-DOM-SATHANAS", { (float)GetScreenWidth() / 2 - 450, (float)GetScreenHeight() / 2 - 500 }, 64, 4, WHITE);
		DrawTextEx(font, "by FILOSOFEM STUDIO", { (float)GetScreenWidth() / 2 - 175, (float)GetScreenHeight() - 100 }, 32, 4, WHITE);
		DrawRectangle(GetScreenWidth() / 10 - 100, GetScreenHeight() - 100, 115, 50, WHITE);
		DrawTextEx(font, "QUIT", { (float)GetScreenWidth() / 10 - 95, (float)GetScreenHeight() - 95 }, 42, 4, BLACK);
		break;
	case LEVEL_1:
		BeginMode2D(_playerCamera);
		DrawTexture(background_1, -400, 0, WHITE);
		DrawTextEx(font, "TUTORIAL", { player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700 }, 42, 4, WHITE);
		pugalo.Draw();
		door.DrawDoor();
		DrawTextEx(font, "Press WASD to move", { 200, 600 }, 36, 4, WHITE);
		DrawTextEx(font, "HOLD SHIFT to move FASTER", { 800, 600 }, 36, 4, WHITE);
		DrawTextEx(font, "Press left-click to attack", { 1900, 600 }, 36, 4, WHITE);
		DrawTextEx(font, "Go through the door to start the game", { 2650, 600 }, 36, 4, WHITE);
		break;
	case LEVEL_2:
		BeginMode2D(_playerCamera);
		DrawTexture(background_2, 0, 400, WHITE);
		DrawTextEx(font, "LEVEL 1", { player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700 }, 42, 4, WHITE);
		enemy_lv2.DrawEnemy();
		DrawTextEx(font, "Kill him to pass on", { 800, 600 }, 36, 4, WHITE);
		if (_playerKillsCount == 1) {
			DrawTextEx(font, "->", { 3000 , 800 }, 48, 4, WHITE);
		}
		break;
	case LEVEL_3:
		BeginMode2D(_playerCamera);
		mainGroundFloor.GroundDraw();
		DrawTextEx(font, "LEVEL 2", { player.GetPlayerPositionX() - 900, player.GetPlayerPositionY() - 700 }, 42, 4, WHITE);
		platform.GroundDraw();
		platform_2.GroundDraw();
		platform_3.GroundDraw();
		platform_4.GroundDraw();
		enemy_lv3.DrawEnemy();
		enemy_lv3_2.DrawEnemy();
		enemy_lv3_3.DrawEnemy();
		enemy_lv3_4.DrawEnemy();
		DrawTextEx(font, "Go right", { 0, 600 }, 48, 4, WHITE);
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
	else if ( GetCurrentMap() == 4 && (PlayerOnGround(player, platform) || PlayerOnGround(player, platform_2) || PlayerOnGround(player, platform_3))) {
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
		if (!EnemyOnGround(enemy_lv3_2, platform)) {
			if (!EnemyOnGround(enemy_lv3_2, mainGroundFloor)) {
				enemy_lv3_2.EnemyMoveVerticallyDown();
			}
		}
	}
	if (!EnemyOnGround(enemy_lv3_3, platform_3)) {
		if (!EnemyOnGround(enemy_lv3_3, platform_4)) {
			if (!EnemyOnGround(enemy_lv3_3, mainGroundFloor)) {
				enemy_lv3_3.EnemyMoveVerticallyDown();
			}
		}
	}
	if (!EnemyOnGround(enemy_lv3_4, platform_4)) {
		if (!EnemyOnGround(enemy_lv3_4, mainGroundFloor)) {
			enemy_lv3_4.EnemyMoveVerticallyDown();
		}
	}

	if (_playerKillsCount == 5) {
		DrawTextEx(font, "YOU PASSED THE GAME! YOU'VE WON", { (float)player.GetPlayerPositionX() - 380, (float)player.GetPlayerPositionY() - 550 }, 48, 4, WHITE);
		DrawTextEx(font, "PRESS ESC TO QUIT", { player.GetPlayerPositionX() - 150, player.GetPlayerPositionY() - 450 }, 36, 4, WHITE);
	}

	player.PlayerDeath();
}

void Quit() {
	DrawRectangle(player.GetPlayerPositionX() - 400, player.GetPlayerPositionY() - 300, 880, 50, WHITE);
	DrawTextEx(font, "ARE YOU SURE YOU  WANT TO QUIT THE GAME? ( Y / N )", { (float)player.GetPlayerPositionX() - 390, (float)player.GetPlayerPositionY() - 290}, 30, 4, BLACK);
}