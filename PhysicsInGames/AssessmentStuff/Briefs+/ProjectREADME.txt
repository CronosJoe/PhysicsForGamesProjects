Hello this is my physics for games assessment Read me! For this assessment I have provided 2 applications and the project files for Unity/Visual studio compilation.

In this folder I provide a builds folder which contains a build for each project.

To compile each of these projects for yourself follow the below directions;

Physics Handler: To compile the physics handler project, open up the project and navigate to the 'build' tab in the top left corner and select 'Build PhysicsHandler',
from here select which folder you'd like to build it to and press select! In that folder you should find your executable to run the program.

Controls for the physics handler-
1 - press the 1 key to select circle as your spawn type shape.
2- press the 2 key to select a non rotating square as your type shape (AABB)
left click - apply a force to all objects to pull them towards the current mouse position.
right click - spawn the currently selected object.

Ball Game: To compile this project open up the project in Unity 2020.1.10f1, navigate to 'File' and select 'Build Settings' from here select 'Build',
it should prompt you for a file directory to build the executable in. In that folder you should find your executable to run the program.

Controls for the Ball Game:
Left Click - select red or blue objects to interact with their obstacle, while an object is selected you can activate it using right click.
WASD - move an object with a blue interactable based on your input.

Project explanation for assessment requirements:
Physics Handler:
	The physics handler features collision and depenetration for any combination of the objects circle and square. Refer to the controls above to operate this program.
Ball Game:
	The ball game features an object that uses a joint to rotate a cube and try to knock the player off, a fan that uses a kinematic collision to throw the player in a given direction,
a spring that when pressed on drops down before slowly moving back to it's original position, and finally a ragdoll sitting in the middle of the level on a spring.

Github project - https://github.com/CronosJoe/PhysicsForGamesProjects

Assessment created and designed by Joseph Huskey.