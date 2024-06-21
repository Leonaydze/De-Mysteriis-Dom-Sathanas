#pragma once
#include <raylib.h>
#include "random"
#include <iostream>

class Player {
private:
	int _health = 100;

	float _playerSpeed = 5;
	Vector2 _playerVelocity { 0.0f, 0.0f };

	Vector2 _playerPosition { 0.0f, 0.0f };

	float _jumpHeight = 0;
	float _jumpMaxHeight = 200;
	float _playerJumpSpeed = 6.5f;

	bool _playerCanJump = true;
	bool _playerJump = false;
	bool _playerCanWalk = true;

	int _damage = 1;

	void SetRandomDamage();

	void MissAttack();
	void DrawHUD();

	Texture2D _playerTexture;
	Font _playerFont;
	Rectangle _frameRectangle{ 0.0f, 0.0f, 64.0f, 64.0f };
public:
	Player();

	Player(Vector2 playerPosition);

	void SetPlayerPosition(Vector2 playerPosition);
	float GetPlayerPositionX();
	float GetPlayerPositionY();

	int GetPlayerHealth();

	void Draw();

	void PlayerController();

	bool IsPlayerJump();
	float GetJumpHeight();
	bool PlayerMaxJump();
	void SetPlayerCanJump(bool playerCanJump);
	bool GetPlayerCanJump();

	void MoveVertically();
	void MoveVerticallyDown();

	bool GetBoolPlayerCanWalk();
	void SetBoolPlayerCanWalk(bool playerCanWalk);

	Vector2 GetPlayerPosition();

	int GetPlayerDamage();
	void PlayerTakesDamageFromTheEnemy(int damage);

	void PlayerDeath();
};