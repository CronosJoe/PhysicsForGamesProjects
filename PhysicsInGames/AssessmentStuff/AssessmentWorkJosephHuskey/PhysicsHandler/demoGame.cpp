#include "DemoGame.h"
#include "iostream"

demoGame::demoGame()
{
}
void demoGame::onDraw() const
{
	ClearBackground(backgroundColor);

	DrawText("Press 1 to spawn circles and 2 to spawn squares!", (GetScreenWidth() / 2) - 100, (GetScreenHeight() / 2), 15, RED);
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
		currentShape = 3;//Static aabb
	}
	else if(IsKeyPressed(KEY_FOUR))
	{
		currentShape = 4;//none
	}
	for (size_t i = 0; i < physObjects.size(); i++)
	{
		if(!physObjects[i].isStatic) //this will make only non static objects be affected by gravity, at the moment I only have a cube for that
		physObjects[i].addAccel(gravity);
	}
	//creating the object
	if(IsMouseButtonPressed(1))
	{
		Vector2 tmpVec = GetMousePosition(); //mouse position
		glm::vec2 tmpPos = glm::vec2(tmpVec.x, tmpVec.y);
		shape tmpShape = shape(currentShape); //creating the shape
		bool isStatic = false;
		if(currentShape == 3)
		{
			isStatic = true;
		}
		physicsObject nextObject = physicsObject(tmpPos,BLUE,10,tmpShape, isStatic); //creating the object, (position, color, weight, shape)
		physObjects.push_back(nextObject); //adding to the vector
	}
	if (IsMouseButtonDown(0)) {
		for (size_t i = 0; i < physObjects.size(); i++)
		{
			if (!physObjects[i].isStatic)
			physObjects[i].addForces(physObjects[i].findVectorToMouse() * 100.0f); //adding forces to every object in the vector
		}
	}
}
