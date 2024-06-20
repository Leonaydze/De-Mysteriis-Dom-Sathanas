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
}

int Enemy::GetEnemyDamage() {
	return _damage;
}

void Enemy::DrawEnemy() {
	DrawRectangle(_enemyPosition.x, _enemyPosition.y, 64, 64, RED);
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

void Enemy::EnemyMoveX(float coef) {
	_enemyPosition.x += coef;
}

void Enemy::EnemyTakesDamageFromThePlayer(int damage){
	_health -= damage;
}
