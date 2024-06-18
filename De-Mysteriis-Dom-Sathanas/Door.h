#pragma once
#include "raylib.h"

class Door{
private:
	Vector2 _doorPosition;
public:
	Door();

	Door(Vector2 doorPosition);

	void DrawDoor();

	float DoorPositionX();
	float DoorPositionY();
};

