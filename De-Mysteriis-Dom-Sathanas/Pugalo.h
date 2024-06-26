#include <raylib.h>

class Pugalo
{
private:

	Vector2 _pugaloPosition{ 0.0f, 0.0f };

	Texture2D _pugaloTexture;
	Rectangle _frameRec = { 0, 0, 124, 164 };

	bool PugaloOnTheGround();
public:
	Pugalo();

	Pugalo(Vector2 pugaloPosition);

	float GetPugaloPositionX();
	float GetPugaloPositionY();

	void Draw();

	void SetFrameRecX(float x);
};