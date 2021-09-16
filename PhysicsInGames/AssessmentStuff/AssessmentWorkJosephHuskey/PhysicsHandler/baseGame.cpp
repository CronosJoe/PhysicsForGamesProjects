#include "baseGame.h"

#include "Raylib/raylib.h"

baseGame::baseGame()
{

}
void baseGame::init()
{
	//setup window
	int screenWidth = 800;
	int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "WE did it!");

	SetTargetFPS(60);

	onInit();
}
void baseGame::tick()
{
	onTick();
	while(accumulatedTime>=fixedTimestep)
	{
		onFixedTimeStep();
		if(accumulatedTime > maxTimeStep)
		{
			accumulatedTime = maxTimeStep;
		}
		accumulatedTime -= fixedTimestep;
	}
	accumulatedTime += GetFrameTime();
}
void baseGame::draw() const
{
	BeginDrawing();

	onDraw();
	

	EndDrawing();

}
void baseGame::exit()
{
	onExit();

	CloseWindow();// Close window and OpenGL context
}
bool baseGame::shouldClose() const
{
	return WindowShouldClose();
}