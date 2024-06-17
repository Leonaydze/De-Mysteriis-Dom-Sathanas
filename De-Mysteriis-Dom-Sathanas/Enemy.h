#pragma once
#include "raylib.h"

class Enemy{
private:
	int _health;

	Vector2 _enemyPosition;

	int _damage;
public:
	Enemy(Vector2 enemyPosition, int health, int damage);

	int GetEnemyDamage();

	void DrawEnemy();
};

