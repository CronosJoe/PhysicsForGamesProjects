#pragma once

#include "baseGame.h"

#include "physicsObject.h"


class demoGame : public baseGame
{
	physicsObject testSphere;

	void onDraw() const override;
	void onInit() override;
	void onFixedTimeStep() override;
public:
	demoGame();
};
