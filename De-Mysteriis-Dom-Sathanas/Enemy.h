#pragma once
#include "raylib.h"
#include <iostream>

class Enemy {
private:
	int _health;

	Vector2 _enemyPosition;

	int _damage;

	void DrawEnemyHUD();

	bool _checkIsEnemyDeath = false;
public:
	Enemy();

	Enemy(Vector2 enemyPosition, int health, int damage);

	int GetEnemyDamage();

	void DrawEnemy();

	int GetEnemyHealth();

	float GetEnemyPositionX();
	float GetEnemyPositionY();

	void EnemyMoveX(float coef);
	void EnemyTakesDamageFromThePlayer(int damage);

	void EnemyMoveVerticallyDown();

	bool BoolCheckIsEnemyDeath();
	void SetBoolCheckIsEnemyDeath(bool checkIsEnemyDeath);
};

