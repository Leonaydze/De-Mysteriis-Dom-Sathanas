#include "Door.h"

Door::Door(Vector2 doorPosition){
	_doorPosition = doorPosition;
}

void Door::DrawDoor() {
	Rectangle rec = { _doorPosition.x, _doorPosition.y, 80, 128 };
	DrawRectangle(_doorPosition.x, _doorPosition.y, 80, 128, BROWN);
	DrawRectangleLinesEx(rec, 5, DARKBROWN);
}

float Door::DoorPositionX()
{
	return _doorPosition.x;
}

float Door::DoorPositionY()
{
	return _doorPosition.y;
}
