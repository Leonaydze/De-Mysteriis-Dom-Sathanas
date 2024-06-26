#include "Pugalo.h"

// private methods

bool Pugalo::PugaloOnTheGround()
{
	return (_pugaloPosition.y <= GetMonitorHeight(GetCurrentMonitor()) - 50);
}


// public methods

void Pugalo::Draw(){
	DrawTextureRec(_pugaloTexture, _frameRec, _pugaloPosition, WHITE);
	//DrawRectangle(_pugaloPosition.x, _pugaloPosition.y, 64, 84, YELLOW);
}

Pugalo::Pugalo() {

}

Pugalo::Pugalo(Vector2 pugaloPosition){
	_pugaloPosition = pugaloPosition;
	_pugaloTexture = LoadTexture("Resources\\Pugalo_atlas.png");
	_pugaloTexture.width *= 2;
	_pugaloTexture.height *= 2;
}

float Pugalo::GetPugaloPositionX()
{
	return _pugaloPosition.x;
}

float Pugalo::GetPugaloPositionY()
{
	return _pugaloPosition.y;
}

void Pugalo::SetFrameRecX(float x)	{
	_frameRec.x = x;
}