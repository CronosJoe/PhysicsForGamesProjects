#include "DemoGame.h"

#include "Raylib/raylib.h"

void demoGame::onDraw() const
{
	ClearBackground(GREEN);

	DrawText("window made!", (GetScreenWidth() / 2) - 75, (GetScreenHeight() / 2), 30, RED);
}
