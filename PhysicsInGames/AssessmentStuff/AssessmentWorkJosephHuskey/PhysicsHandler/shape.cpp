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
		circleData.radius = 30; //hardcoding cause we don't care, in the future make this prettier
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
bool aabbAABBCollision(glm::vec2 posA, AABB shapeA, glm::vec2 posB, AABB shapeB)
{
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
bool circleAABBCollision(const glm::vec2 posA, circle shapeA, glm::vec2 posB, AABB shapeB) 
{
	//grabbing half extents
	glm::vec2 halfExtents(shapeB.offset, shapeB.offset); //our offset is a half extent I'm doing it this way to try and get a vector set for X and Y

	//getting difference between both shapes centers
	glm::vec2 differenceVec = posA - posB;
	glm::vec2 clamped = glm::clamp(differenceVec, -halfExtents, halfExtents);

	//getting the closest point
	glm::vec2 closest = posB + clamped;

	//retrieving vector between center circle and closest point AABB and check if the length <= the radius
	differenceVec = closest - posA;
	return glm::length(differenceVec)<shapeA.radius;
}
bool circleAABBCollision(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB)
{
	return circleAABBCollision(posA,shapeA.circleData,posB,shapeB.dataOfAABB);
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
glm::vec2 depenetrateCircleCircle(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen)
{
	//write the collision depth
	glm::vec2 offset = posA - posB;
	float radiiSum = shapeA.circleData.radius + shapeB.circleData.radius;
	float distance = glm::length(offset);

	//write the penetration depth
	pen = radiiSum - distance;

	return glm::normalize(offset); //return the collision normal
}
glm::vec2 depenetrateAABBAABB(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen)
{
	//getting an offset vector
	glm::vec2 posOffset = posA - posB;
	//getting the closest points using world position
	glm::vec2 closestPointA = glm::clamp(posA, shapeB.dataOfAABB.GetMin(posB), shapeB.dataOfAABB.GetMax(posB));
	glm::vec2 closestPointB = glm::clamp(posB, shapeA.dataOfAABB.GetMin(posA), shapeB.dataOfAABB.GetMax(posA));
	//getting our difference vector
	glm::vec2 diffVec = closestPointA - closestPointB;
	//saving the penetration
	pen = glm::length(diffVec);
	//returning a normalized version of teh original position offset to counteract single axis penetration.
	return glm::normalize(posOffset);
}
glm::vec2 depenetrateCircleAABB(const glm::vec2 posA, const circle shapeA, const glm::vec2 posB, const AABB shapeB, float& pen) 
{
	//half extents
	glm::vec2 halfExtents(shapeB.offset, shapeB.offset);
	//getting an offset vector
	glm::vec2 posOffset = posA - posB;
	//creating a closest point vec
	glm::vec2 closestPt = posB + glm::clamp(posOffset, -halfExtents, halfExtents);

	glm::vec2 normalForce = posA - closestPt;

	//finding penetration 
	pen = shapeA.radius - glm::length(normalForce); 
	return glm::normalize(normalForce);
}
glm::vec2 depenetrateCircleAABB(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB, float& pen)
{
	
	return depenetrateCircleAABB(posA,shapeA.circleData,posB,shapeB.dataOfAABB,pen);
}
