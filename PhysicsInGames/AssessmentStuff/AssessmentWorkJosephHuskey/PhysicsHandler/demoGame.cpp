#include "DemoGame.h"

demoGame::demoGame()
{
	testSphere = physicsObject();
}
void demoGame::onDraw() const
{
	ClearBackground(backgroundColor);

	DrawText("window made!", (GetScreenWidth() / 2) - 75, (GetScreenHeight() / 2), 30, RED);
	testSphere.drawObject();
}
void demoGame::onInit()
{
	gravity = glm::vec2(0, 9.1);
}
void demoGame::onFixedTimeStep()
{
	testSphere.addAccel(gravity);
	testSphere.onTickPhys(fixedTimestep);
}
