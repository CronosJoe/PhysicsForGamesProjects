#pragma once

#include "shape.h"

class physicsObject
{
public:
	glm::vec2 pos;
	glm::vec2 vel; //will be determined while running
	glm::vec2 totalForce; //will be determined while running
	float mass;
	Color playerColor;
	shape collisionShape;
	bool isStatic;
	//this will be the direction the object has to go to make it to the mouse
	glm::vec2 directionVector;
	//standard constructor
	physicsObject();
	//the cooler constructor
	physicsObject(glm::vec2 position, Color colorOfPlayer, float massOfPlayer, shape createdShape, bool IsStatic);
	void onTickPhys(float delta);

	void addForces(glm::vec2 force); //adding a force to total forces based on delta and mass

	void addAccel(glm::vec2 force); //adding a force to total forces based on delta

	void addVelocity(glm::vec2 force); //adding a force based on nothing but this force!

	void addImpulse(glm::vec2 force); //adding a force based on mass

	void drawObject() const;
	glm::vec2 findVectorToMouse();
};
	float resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 normal);

	void resolvePhysicsBodies(physicsObject& lhs, physicsObject& rhs, float elasticity, const glm::vec2 normal, float pen);