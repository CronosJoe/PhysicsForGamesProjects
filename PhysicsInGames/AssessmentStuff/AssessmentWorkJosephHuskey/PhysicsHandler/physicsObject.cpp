#include "physicsObject.h"

physicsObject::physicsObject()
{
	pos = vel = glm::vec2( 0, 0 );
	mass = 0;
	totalForce = glm::vec2( 0, 0 );
	playerColor = RED;
	usesGravity = false;
	collisionShape = shape();
}
physicsObject::physicsObject(glm::vec2 position, Color colorOfPlayer, float massOfPlayer, bool canGravity, shape createdShape)
{
	pos = position;
	mass = massOfPlayer;
	totalForce = glm::vec2(0, 0);
	playerColor = colorOfPlayer;
	usesGravity = canGravity;
	vel = glm::vec2(0, 0);
	collisionShape = createdShape;
}

void physicsObject :: onTickPhys(float delta) //need the fixed tick for delta, probably accumulated time
{
	vel += totalForce * delta;
	totalForce = glm::vec2(0, 0);
	pos += vel * delta;
}
void physicsObject::addForces(glm::vec2 force)//force should be determined by input for player something else for ai
{
	totalForce += (force / mass);
}
void physicsObject::addAccel(glm::vec2 force)
{
	totalForce += force;
}
void physicsObject::addVelocity(glm::vec2 force)
{
	vel += force;
}
void physicsObject::addImpulse(glm::vec2 force)
{
	vel += (force / mass);
}
void physicsObject::drawObject() const
{
	switch (collisionShape.type)
	{
	case shapeType::NONE:
		DrawPixel(pos.x, pos.y, playerColor);
		break;
	case shapeType::CIRCLE:
		DrawCircle(pos.x, pos.y, collisionShape.circleData.radius, playerColor);
		break;
	case shapeType::AABB:
		Rectangle rec = collisionShape.dataOfAABB;
		rec.x = pos.x - rec.x;
		rec.y = pos.y - rec.y;
		DrawRectangleRec(rec, playerColor);
		break;
	default:
		break;
	}
}
