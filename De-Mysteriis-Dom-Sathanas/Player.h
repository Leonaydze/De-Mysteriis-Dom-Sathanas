#pragma once
#include <raylib.h>

class Player {
private:
	int _health;

	float _playerSpeed = 5;
	Vector2 _playerVelocity{ 0.0f, 0.0f };

	Vector2 _playerPosition{ 100.0f, 983.0f };

	float _jumpHeight = 0;
	float _jumpMaxHeight = 150;
	float _playerJumpSpeed = 5.5f;

	bool _playerCanJump = true;
	bool _playerJump = false;
	bool _playerCanWalk = true;

	Sound fallOnGround = LoadSound("Resources\\FallOnGround.mp3");
public:
	Player();

	float GetPlayerPositionX();
	float GetPlayerPositionY();

	bool PlayerOnGround();

	int GetPlayerHealth();

	void Draw();

	void PlayerController();

	bool IsPlayerJump();
	float GetJumpHeight();
	bool PlayerMaxJump();
	void SetPlayerJump(bool playerJump);
	void SetPlayerCanJump(bool playerCanJump);
	bool GetPlayerCanJump();

	void MoveVertically();
	void MoveVerticallyDown();

	bool GetBoolPlayerCanWalk();
	void SetBoolPlayerCanWalk(bool playerCanWalk);

	Vector2 GetPlayerPosition();
	~Player();
};