#include "physicsObject.h"

physicsObject::physicsObject()
{
	pos = vel = glm::vec2( 0, 0 );
	mass = 0;
	totalForce = glm::vec2( 0, 0 );
	playerColor = RED;
	collisionShape = shape();
}
physicsObject::physicsObject(glm::vec2 position, Color colorOfPlayer, float massOfPlayer, shape createdShape)
{
	pos = position;
	mass = massOfPlayer;
	totalForce = glm::vec2(0, 0);
	playerColor = colorOfPlayer;
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
		//setting the position of min max in world space of shapeA
		/*collisionShape.dataOfAABB.min = glm::vec2(pos.x - collisionShape.dataOfAABB.offset, pos.y - collisionShape.dataOfAABB.offset);
		collisionShape.dataOfAABB.max = glm::vec2(pos.x + collisionShape.dataOfAABB.offset, pos.y + collisionShape.dataOfAABB.offset);*/
		DrawRectangleRec(collisionShape.dataOfAABB.GetWorldRectangle(pos), playerColor);
		break;
	default:
		break;
	}
}
glm::vec2 physicsObject::findVectorToMouse()
{
	Vector2 tmpMousePos = GetMousePosition();
	return glm::vec2(tmpMousePos.x-pos.x, tmpMousePos.y-pos.y);
}
