#pragma once
#include "raylib.h"
#include <iostream>

class Enemy {
private:
	int _health;

	Vector2 _enemyPosition;

	int _damage;

	void DrawEnemyHUD();
public:
	Enemy();

	Enemy(Vector2 enemyPosition, int health, int damage);

	int GetEnemyDamage();

	void DrawEnemy();

	int GetEnemyHealth();

	float GetEnemyPositionX();

	void EnemyMoveX(float coef);
};

