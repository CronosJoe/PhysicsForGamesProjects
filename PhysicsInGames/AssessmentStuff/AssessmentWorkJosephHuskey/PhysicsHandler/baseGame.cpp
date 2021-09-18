#include "baseGame.h"

#include "enumUtils.h"

baseGame::baseGame()
{
	fixedTimestep = 0.02f;
	accumulatedTime = 0.0f;
	backgroundColor = RAYWHITE;
	gravity = glm::vec2(0,0); //defaulting before this is set in init


	//register what happens when a circle-cirlce pairing happens
	map[static_cast<collisionPair>(shapeType::CIRCLE | shapeType::CIRCLE)] = circleCircleCollision;
	map[static_cast<collisionPair>(shapeType::AABB | shapeType::AABB)] = aabbAABBCollision;
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

	accumulatedTime += GetFrameTime();

	while (accumulatedTime >= fixedTimestep) 
	{
		accumulatedTime -= fixedTimestep;

		onFixedTimeStep();

		for (size_t i = 0; i < physObjects.size(); i++)
		{
			physObjects[i].onTickPhys(fixedTimestep);
		}

		for (size_t i = 0; i < physObjects.size(); i++)
		{
			for (size_t j = 0; j < physObjects.size(); j++)
			{
				if (i == j) { continue; }

				if (physObjects[i].collisionShape.type == shapeType::NONE || physObjects[j].collisionShape.type == shapeType::NONE) { continue; }

				int lhs = i;
				int rhs = j;
				//don't need the uint16_t casts but it's to make it obvious
				if ((uint16_t)physObjects[i].collisionShape.type > (uint16_t)physObjects[j].collisionShape.type)
				{
					lhs = j;
					rhs = i;
				}

				collisionPair pairing = (collisionPair)(physObjects[lhs].collisionShape.type | physObjects[rhs].collisionShape.type);
				bool collision = map[pairing](physObjects[lhs].pos, physObjects[lhs].collisionShape, physObjects[rhs].pos, physObjects[rhs].collisionShape);
				if (collision)
				{
					//do the thing on collision
				}
			}
		}
	}
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