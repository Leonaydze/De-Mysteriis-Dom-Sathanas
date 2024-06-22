#include "Player.h"

void Player::SetRandomDamage()
{
	_damage = 0;
	_damage = rand() % 30;
	std::cout << _damage << std::endl;
}

void Player::MissAttack(){
	if (_damage == 0) {
		DrawTextEx(_playerFont, "Miss", { _playerPosition.x + 100, _playerPosition.y - 100 }, 40, 3, WHITE);
	}
	if (_damage >= 25) {
		DrawTextEx(_playerFont, "CRITICAL DAMAGE", {_playerPosition.x + 80, _playerPosition.y - 80}, 40, 3, RED);
	}
}

void Player::DrawHUD() {
	DrawRectangle(_playerPosition.x - 900, _playerPosition.y - 650, 210, 30, DARKBROWN);
	DrawRectangle(_playerPosition.x - 895, _playerPosition.y - 645, GetPlayerHealth() * 2, 20, RED);
}

Player::Player() {
}

Player::Player(Vector2 playerPosition) {
	_playerPosition = playerPosition;
	_playerTexture = LoadTexture("Resources\\PlayerText.png");
	_playerFont = LoadFont("Resources\\KHTitle.otf");
	_playerDeath = LoadSound("Resources\\PlayerDeath.wav");
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
	DrawTextureRec(_playerTexture, _frameRectangle, _playerPosition, WHITE);
	MissAttack();
	DrawHUD();
}

void Player::PlayerController() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && _health > 0) {
		SetRandomDamage();
	}
	if (IsKeyDown(KEY_D) && _health > 0 && _playerPosition.x < GetMonitorWidth(GetCurrentMonitor()) + 1000 && !IsKeyDown(KEY_A) && _playerCanWalk) {
		_playerVelocity.x += _playerSpeed;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			_playerVelocity.x *= 1.5;
		}
		if (_frameRectangle.width < 0) {
			_frameRectangle.width = -_frameRectangle.width;
		}
		_playerPosition.x += _playerVelocity.x;
	}
	if (IsKeyDown(KEY_A) && _health > 0 && _playerPosition.x > 0 && !IsKeyDown(KEY_D) && _playerCanWalk) {
		_playerVelocity.x -= _playerSpeed;
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			_playerVelocity.x *= 1.5;
		}
		if (_frameRectangle.width > 0) {
			_frameRectangle.width = -_frameRectangle.width;
		}
		_playerPosition.x += _playerVelocity.x;
	}
	if (IsKeyPressed(KEY_SPACE) && _health > 0 && !IsKeyPressedRepeat(KEY_SPACE) && _playerCanJump) {
		_playerJump = true;
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
	if (_jumpHeight >= _jumpMaxHeight) {
		_playerJump = false;
		return true;
	}
	return false;
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
	_jumpHeight = 0;
	_playerPosition.y += _playerJumpSpeed;
	if (_playerJumpSpeed <= 6.5f)
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

int Player::GetPlayerDamage(){
	return _damage;
}

void Player::PlayerTakesDamageFromTheEnemy(int damage){
	_health -= damage;
}

void Player::PlayerDeath(){
	if (_health <= 0) {
		DrawTextEx(_playerFont, "YOU ARE DEAD", { _playerPosition.x - 200, _playerPosition.y - 500 }, 50, 4, WHITE);
		DrawTextEx(_playerFont,"PRESS ESC TO QUIT", { _playerPosition.x - 270, _playerPosition.y - 450}, 50, 4,  WHITE);
		PlaySound(_playerDeath);
	}
}
