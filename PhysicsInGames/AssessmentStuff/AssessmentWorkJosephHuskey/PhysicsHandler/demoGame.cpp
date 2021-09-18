#include "DemoGame.h"
#include "iostream"

demoGame::demoGame()
{
}
void demoGame::onDraw() const
{
	ClearBackground(backgroundColor);

	DrawText("window made!", (GetScreenWidth() / 2) - 75, (GetScreenHeight() / 2), 30, RED);
	for (size_t i = 0; i < physObjects.size(); i++)
	{
		physObjects[i].drawObject(); //drawing every object in the vector
	}
}
void demoGame::onInit()
{
	gravity = glm::vec2(0, 50);
	currentShape = 0; //just defaulting it here it will usually be changed later
}
void demoGame::onFixedTimeStep()
{
	//setting the object shape
	if (IsKeyPressed(KEY_ONE))
	{
		currentShape = 1;//circle
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		currentShape = 2;//aabb
	}
	else if(IsKeyPressed(KEY_THREE))
	{
		currentShape = 3;//none
	}
	for (size_t i = 0; i < physObjects.size(); i++)
	{
		physObjects[i].addAccel(gravity);
	}
	//creating the object
	if(IsMouseButtonPressed(1))
	{
		Vector2 tmpVec = GetMousePosition(); //mouse position
		glm::vec2 tmpPos = glm::vec2(tmpVec.x, tmpVec.y);
		shape tmpShape = shape(currentShape); //creating the shape
		physicsObject nextObject = physicsObject(tmpPos,BLUE,10,tmpShape); //creating the object, (position, color, weight, shape)
		physObjects.push_back(nextObject); //adding to the vector
	}
	if (IsMouseButtonDown(0)) {
		for (size_t i = 0; i < physObjects.size(); i++)
		{
			physObjects[i].addForces(physObjects[i].findVectorToMouse() * 100.0f); //adding forces to every object in the vector
		}
	}
}
