#include "Enemy.h"

Enemy::Enemy(Vector2 enemyPosition, int health, int damage){
	_enemyPosition = enemyPosition;
	_health = health;
	_damage = damage;
}

int Enemy::GetEnemyDamage(){
	return _damage;
}

void Enemy::DrawEnemy(){
	DrawRectangle(_enemyPosition.x, _enemyPosition.y, 64, 64, RED);
}