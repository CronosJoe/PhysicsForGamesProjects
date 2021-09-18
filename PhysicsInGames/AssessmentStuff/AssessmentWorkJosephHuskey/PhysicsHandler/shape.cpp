#include "shape.h"


shape::shape()
{

}
shape::shape(int shapeType)
{
	switch(shapeType)
	{
	case 1:
		type = shapeType::CIRCLE;
		circleData.radius = 10; //hardcoding cause we don't care, in the future make this prettier
		break;
	case 2:
		type = shapeType::AABB;
		dataOfAABB.offset = 30;
		break;
	default:
		type = shapeType::NONE;
		break;
	}
}
bool circleCircleCollision(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB)
{
	glm::vec2 offset = posA - posB; //this gets our difference between the positions
	float distance = glm::length(offset);
	float radiiSum = circleA.radius + circleB.radius;
	return distance<radiiSum;
}
bool circleCircleCollision(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB)
{
	return circleCircleCollision(posA, shapeA.circleData, posB, shapeB.circleData);
}

#include <iostream>

bool aabbAABBCollision(glm::vec2 posA, AABB shapeA, glm::vec2 posB, AABB shapeB)
{
	std::cout << "dasdasd" << std::endl;

	//setting the position of min max in world space of shapeA
	glm::vec2 WorldAMin = shapeA.GetMin(posA);
	glm::vec2 WorldAMax = shapeA.GetMax(posA);
	
	//setting the position of min max in world space of shapeB
	glm::vec2 WorldBMin = shapeB.GetMin(posB);
	glm::vec2 WorldBMax = shapeB.GetMax(posB);
	//returning the collision true false
	return (WorldAMax.x > WorldBMin.x
		 && WorldAMax.y > WorldBMin.y
		 && WorldBMax.x > WorldAMin.x
		 && WorldBMax.y > WorldAMin.y);
}
bool aabbAABBCollision(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB)
{
	return aabbAABBCollision(posA, shapeA.dataOfAABB, posB, shapeB.dataOfAABB);
}
AABB :: operator Rectangle() const
{
	// expect calling code to set the x/y
	return Rectangle{0.0f, 0.0f, (float)offset, (float)offset};
}

Rectangle AABB::GetWorldRectangle(glm::vec2 pos) const
{
	return Rectangle{ pos.x - offset, pos.y - offset, (float)offset * 2, (float)offset *2 };
}

glm::vec2 AABB::GetMin(glm::vec2 pos) const
{
	return glm::vec2(pos.x - offset, pos.y - offset);
}

glm::vec2 AABB::GetMax(glm::vec2 pos) const
{
	return glm::vec2(pos.x + offset, pos.y + offset);
}
