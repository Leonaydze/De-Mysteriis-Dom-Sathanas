#include <raylib.h>

class Pugalo
{
private:

	Vector2 _pugaloPosition{ 1488.0f, 964.0f };

	bool PugaloOnTheGround();
public:
	Pugalo();

	void Draw();

};