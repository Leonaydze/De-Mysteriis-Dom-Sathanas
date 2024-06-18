#include "Player.h"

void Player::SetRandomDamage()
{
	_damage = rand() % 30;
	std::cout << _damage << std::endl;
}

void Player::MissAttack(){
	if (_damage == 0) {
		DrawText("Miss", _playerPosition.x + 100, _playerPosition.y - 100, 40, WHITE);
	}
}

void Player::DrawHUD() {
	DrawRectangle(15, 60, 210, 30, DARKBROWN);
	DrawRectangle(20, 65, GetPlayerHealth() * 2, 20, RED);
}

Player::Player(Vector2 playerPosition) {
	_playerPosition = playerPosition;
}

void Player::SetPlayerPosition(Vector2 playerPosition){
	_playerPosition = playerPosition;
}

float Player::GetPlayerPositionX()
{
	return _playerPosition.x;
}

float Player::GetPlayerPositionY()
{
	return _playerPosition.y;
}

int Player::GetPlayerHealth() {
	return _health;
}

void Player::Draw() {
	DrawRectangle(_playerPosition.x, _playerPosition.y, 64, 64, WHITE);
	MissAttack();
	DrawHUD();
}

void Player::PlayerController() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		SetRandomDamage();
	}
	if (IsKeyDown(KEY_D) && _playerPosition.x < GetMonitorWidth(GetCurrentMonitor()) + 1000 && !IsKeyDown(KEY_A) && _playerCanWalk) {
		_playerVelocity.x += _playerSpeed;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			_playerVelocity.x *= 1.5;
		}
		_playerPosition.x += _playerVelocity.x;
	}
	if (IsKeyDown(KEY_A) && _playerPosition.x > 0 && !IsKeyDown(KEY_D) && _playerCanWalk) {
		_playerVelocity.x -= _playerSpeed;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			_playerVelocity.x *= 1.5;
		}
		_playerPosition.x += _playerVelocity.x;
	}
	if (IsKeyPressed(KEY_SPACE) && !IsKeyPressedRepeat(KEY_SPACE) && _playerCanJump) {
		_playerJump = true;
		_playerCanJump = false;
		PlaySound(fallOnGround);
	}

	_playerVelocity.y = 0;
	_playerVelocity.x = 0;
}

bool Player::IsPlayerJump() {
	return _playerJump;
}

float Player::GetJumpHeight() {
	return _jumpHeight;
}

bool Player::PlayerMaxJump() {
	return (_jumpHeight >= _jumpMaxHeight);
}

void Player::SetPlayerCanJump(bool playerCanJump) {
	_playerCanJump = playerCanJump;
}
bool Player::GetPlayerCanJump() {
	return _playerCanJump;
}

void Player::MoveVertically() {
	_jumpHeight += _playerJumpSpeed;
	_playerPosition.y -= _playerJumpSpeed;
	if(_playerJumpSpeed > 0.5f)
		_playerJumpSpeed -= 0.1f;
}
void Player::MoveVerticallyDown() {
	_jumpHeight -= _playerJumpSpeed;
	_playerPosition.y += _playerJumpSpeed;
	if (_playerJumpSpeed <= 5.5f)
		_playerJumpSpeed += 0.3f;
}

bool Player::GetBoolPlayerCanWalk() {
	return _playerCanWalk;
}

void Player::SetBoolPlayerCanWalk(bool playerCanWalk) {
	_playerCanWalk = playerCanWalk;
}

Vector2 Player::GetPlayerPosition() {
	return _playerPosition;
}

int Player::GetPlayerDamage()
{
	return _damage;
}

Player::~Player() {
	UnloadSound(fallOnGround);
}