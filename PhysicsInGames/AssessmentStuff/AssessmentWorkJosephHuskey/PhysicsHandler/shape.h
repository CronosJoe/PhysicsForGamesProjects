#pragma once
#include "baseGame.h"

struct circle
{
	float radius;
};
struct AABB
{
	glm::vec2 min;
	glm::vec2 max;

	operator Rectangle() const;
};
enum class shapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};
struct shape
{
	//enum identification type
	shapeType type;

	//add new types of shapes this this anonymous union
	union
	{
		circle circleData;
		AABB dataOfAABB;
	};
	
};
bool circleCircleCollision();


