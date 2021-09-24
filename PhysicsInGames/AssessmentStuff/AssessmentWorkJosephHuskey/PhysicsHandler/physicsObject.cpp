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
float resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 normal)
{
	//calculate relative velocity
	glm::vec2 relVel = velA - velB;
	//calculate the magnitude of the impulse to apply
	float impulseMag = glm::dot(-(1.0f + elasticity) * relVel, normal) / glm::dot(normal, normal * (1 / massA + 1 / massB));
	//return the impulse
	return impulseMag;
}

void resolvePhysicsBodies(physicsObject& lhs, physicsObject& rhs, float elasticity, const glm::vec2 normal, float pen)
{
	//calculate resolution impulse
	float impulseMag = resolveCollision(lhs.pos, lhs.vel, lhs.mass, rhs.pos, rhs.vel, rhs.mass, elasticity, normal);
	glm::vec2 impulse = impulseMag * normal;
	//depenetrate the objects aka seperate them
	pen *= .51f;
	glm::vec2 correction = normal * pen;
	lhs.pos += correction;
	rhs.pos -= correction;
	//apply resolution impulses to both objects.
	lhs.addImpulse(impulse);
	rhs.addImpulse(-impulse);
}
