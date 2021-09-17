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
	bool usesGravity;
	shape collisionShape;
	//standard constructor
	physicsObject();
	//the cooler constructor
	physicsObject(glm::vec2 position, Color colorOfPlayer, float massOfPlayer, bool canGravity, shape createdShape);
	void onTickPhys(float delta);

	void addForces(glm::vec2 force); //adding a force to total forces based on delta and mass

	void addAccel(glm::vec2 force); //adding a force to total forces based on delta

	void addVelocity(glm::vec2 force); //adding a force based on nothing but this force!

	void addImpulse(glm::vec2 force); //adding a force based on mass

	void drawObject() const;
};