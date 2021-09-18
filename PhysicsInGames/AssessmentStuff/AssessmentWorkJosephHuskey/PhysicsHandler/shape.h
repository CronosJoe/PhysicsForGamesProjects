#pragma once

#include "GLM/glm.hpp"
#include "Raylib/raylib.h"

struct circle
{
	float radius;
};
struct AABB
{
	//glm::vec2 min;
	//glm::vec2 max;
	int offset;
	operator Rectangle() const;

	Rectangle GetWorldRectangle(glm::vec2 pos) const;
	glm::vec2 GetMin(glm::vec2 pos) const;
	glm::vec2 GetMax(glm::vec2 pos) const;
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

	shape();

	shape(int shapeTyping);

	//add new types of shapes this this anonymous union, because it's anonymous we just have to reference the shape not the name of the union
	union
	{
		circle circleData;
		AABB dataOfAABB;
	};
	
};
bool circleCircleCollision(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);

bool circleCircleCollision(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB);

bool aabbAABBCollision(glm::vec2 posA, AABB AABBA, glm::vec2 posB, AABB AABBB);

bool aabbAABBCollision(const glm::vec2& posA, const shape& shapeA, const glm::vec2& posB, const shape& shapeB);


