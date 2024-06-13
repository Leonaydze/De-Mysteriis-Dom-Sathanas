#pragma once
#include <raylib.h>

class Ground{
private:
	int _groundWidth = 0;
	int _groundHeight = 0;
	Vector2 _groundPosition = { 0, 0 };
	Color _groundColor;
public:
	Ground();

	Ground(Vector2 groundPosition, int groundWidth, int groundHeight, Color groundColor);

	void SetGroundWidth(int groundWidth);
	int GetGroundWidth();

	void SetGroundHeight(int groundHeight);
	int GetGroundHeight();

	float GetGroundPositionX();
	void SetGroundPositionX(float groundPositionX);

	float GetGroundPositionY();
	void SetGroundPositionY(float groundPositionY);

	Color GetGroundColor();
	void SetGroundColor(Color groundColor);

	void GroundDraw();
}; 