#pragma once

#include "Raylib/raylib.h"
#include "GLM/glm.hpp"
#include "physicsObject.h"
#include "shape.h"
#include <vector>
#include <unordered_map>
//these are type alias' they don't actually create objects they simply create a new name for said objects
//a type alias to make things readable
using collisionPair = uint8_t;
//the function signature for our collision detection ie the variables for the funtion to use
using collisionFunc = bool(*)(const glm::vec2&, const shape&, const glm::vec2&, const shape&);
//a map that takes a collision pair and returns the correct function to call
using collisionMap = std::unordered_map<collisionPair, collisionFunc>;
class baseGame
{
    collisionMap map;

protected:

    std::vector<physicsObject> physObjects = std::vector<physicsObject>();
    // Called internally when game-specifc initialization occurs
    void virtual onInit() { }

    // Called internally when game-specifc tick occurs
    void virtual onTick() { }

    // Called internally when game-specifc drawing occurs
    void virtual onDraw() const { }

    // Called internally when game-specifc clean-up occurs
    void virtual onExit() { }

    //Fixed update, usually slower than real update
    void virtual onFixedTimeStep() { }
public:
    // Trivial constructor
    baseGame();

    // Initializes the game window
    void init();

    // Poll for input, update timers, etc.
    void tick();

    // Draw the current world state
    void draw() const;

    // Close the game and shutdown
    void exit();

    // Returns true if the game is trying to shut down
    bool shouldClose() const;

    //frame trackers
    float fixedTimestep;
    float accumulatedTime;
    Color backgroundColor;

    glm::vec2 gravity;

};
