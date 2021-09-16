#pragma once
class baseGame
{
protected:
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
    const float fixedTimestep = 0.02f;
    const float maxTimeStep = 0.3f;
    float accumulatedTime = 0.0f;
};
