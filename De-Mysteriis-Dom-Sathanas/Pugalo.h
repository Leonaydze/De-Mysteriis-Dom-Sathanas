#include <raylib.h>

class Pugalo
{
private:

	Vector2 _pugaloPosition{ 0.0f, 0.0f };

	bool PugaloOnTheGround();
public:
	Pugalo();

	Pugalo(Vector2 pugaloPosition);

	float GetPugaloPositionX();
	float GetPugaloPositionY();

	void Draw();
};