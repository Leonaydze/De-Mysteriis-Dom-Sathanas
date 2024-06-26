#include "Enemy.h"

Enemy::Enemy() {

}

void Enemy::DrawEnemyHUD() {
	DrawRectangle(_enemyPosition.x - 15, _enemyPosition.y - 50, GetEnemyHealth(), 30, DARKBROWN);
	DrawRectangle(_enemyPosition.x - 10, _enemyPosition.y - 45, GetEnemyHealth() - 10, 20, RED);
}

Enemy::Enemy(Vector2 enemyPosition, int health, int damage) {
	_enemyPosition = enemyPosition;
	_health = health;
	_damage = damage;
	_enemyTexture = LoadTexture("Resources\\Enemy_atlas.png");
}

int Enemy::GetEnemyDamage() {
	return _damage;
}

void Enemy::DrawEnemy() {
	DrawTextureRec(_enemyTexture, _frameRec, _enemyPosition, WHITE);
	//DrawRectangle(_enemyPosition.x, _enemyPosition.y, 64, 64, RED);
	DrawEnemyHUD();
}

int Enemy::GetEnemyHealth()
{
	return _health;
}

float Enemy::GetEnemyPositionX()
{
	return _enemyPosition.x;
}

float Enemy::GetEnemyPositionY()
{
	return _enemyPosition.y;
}

void Enemy::EnemyMoveX(float coef) {
	_enemyPosition.x += coef;
}

void Enemy::EnemyTakesDamageFromThePlayer(int damage){
	_health -= damage;
}

void Enemy::EnemyMoveVerticallyDown() {
	_enemyPosition.y += 6.0f;
}

bool Enemy::BoolCheckIsEnemyDeath()
{
	return _checkIsEnemyDeath;
}

void Enemy::SetBoolCheckIsEnemyDeath(bool checkIsEnemyDeath){
	_checkIsEnemyDeath = checkIsEnemyDeath;
}

void Enemy::SetFrameRecX(float x){
	_frameRec.x = x;
}

void Enemy::SetFrameRecWidth(float width){
	_frameRec.width = width;
}

