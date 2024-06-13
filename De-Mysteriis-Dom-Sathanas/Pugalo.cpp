#include "Pugalo.h"

// private methods

bool Pugalo::PugaloOnTheGround()
{
	return (_pugaloPosition.y <= GetMonitorHeight(GetCurrentMonitor()) - 50);
}


// public methods

void Pugalo::Draw(){
	DrawRectangle(_pugaloPosition.x, _pugaloPosition.y, 64, 84, YELLOW);
}

Pugalo::Pugalo() {

}
