#include "Ground.h"

Ground::Ground() {
	_groundPosition = { 0.0f, 0.0f };
	_groundWidth = 0;
	_groundHeight = 0;
	_groundColor = BLACK;
}

Ground::Ground(Vector2 groundPosition, int groundWidth, int groundHeight, Color groundColor) {
	_groundPosition = groundPosition;
	_groundWidth = groundWidth;
	_groundHeight = groundHeight;
	_groundColor = groundColor;
}


void Ground::SetGroundWidth(int groundWidth){
	_groundWidth = groundWidth;
}

int Ground::GetGroundWidth()
{
	return _groundWidth;
}

void Ground::SetGroundHeight(int groundHeight){
	_groundHeight = groundHeight;
}

int Ground::GetGroundHeight()
{
	return _groundHeight;
}

float Ground::GetGroundPositionX()
{
	return _groundPosition.x;
}

void Ground::SetGroundPositionX(float groundPositionX){
	_groundPosition.x = groundPositionX;
}

float Ground::GetGroundPositionY()
{
	return _groundPosition.y;
}

void Ground::SetGroundPositionY(float groundPositionY) {
	_groundPosition.y = groundPositionY;
}

Color Ground::GetGroundColor()
{
	return _groundColor;
}

void Ground::SetGroundColor(Color groundColor){
	_groundColor = groundColor;
}

void Ground::GroundDraw(){
	DrawRectangle(_groundPosition.x, _groundPosition.y, _groundPosition.x + _groundWidth, _groundPosition.y + _groundHeight, _groundColor);
}

