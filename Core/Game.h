#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <IL/ilut.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <vector>

//#include <PxPhysicsAPI.h>

#include "Camera.h"
#include "GameObject.h"
#include "Skybox.h"


//! Main Game class

/*!
Main game class that is extended in an implementation.
It has all base methods and fields required to work.
It also has all vectors that hold all game objects.
*/
class Game
{
public:
	//! Instance of game.

	/*!
	This is game instance. It is used to prevent creating second isntance of engine in one process.
	It is created when initializing game.
	*/
	static Game* instance;

	//! Constructor for main game class
	Game();
	//! Destructor for main game class
	~Game();

	//! Initialize game engine.

	/*!
	This method setups all libraries and variables.
	Initializes OpenGL version 3.3 and creates all required texure objects and buffers.
	Initializes DevIL and loads standard shaders.
	*/
	void Init(GLuint screen_width, GLuint screen_height);

	//! Main logic update function

	/*!
	By default it is not implemented in engine.
	It is required to implement in game using this engine.
	Example of usage in UmiTest project.
	\param dt delta time calculated in MainLoop()
	*/
	virtual void Update(GLfloat dt) = 0;

	//! Handle input and pass it to Input class.

	/*!
	This method sets previousState field of Input class to the current state of keys in keyState.
	Then in foreach loop state of each key is read and set to corresponding value in keyState field.
	Reads and updates in Input class current mouse position.
	\param dt delta time calculated in MainLoop()
	*/
	void ProcessInput(GLfloat dt);

	//! Main render function

	/*!
	Draws objects shadows to shadowmap.
	Draws objects to framebuffer using HDR.
	Calculates bloom and selected post process effect and aplies them to the framebuffer.
	*/
	void Render();

	//! Main loop of the engine

	/*!
	Not implemented in engine library.
	Must be implemented in project. (Might change)
	Calculates delta time from previous frame and calls ProcessInput(GLfloat dt), Update(GLfloat dt) and Render() methods. 
	*/
	virtual void MainLoop() = 0;

	//! Do cleanup and properly close game.

	/*!
	Terminates glfw and destroys currently used windows.
	*/
	void Exit();

	//! Holds all cameras and allows to call them by their names.
	std::map<std::string, Camera*> camera;
	//! Vector to hold all game objects. Used in logic update.
	std::vector<GameObject*> objects;
	//! Vector to hold all transparent objects. Used to render them after all opaque objects.

	/*!
	This one is beeing sorted in reverse order by the distance from object to currently used camera.
	*/
	std::vector<GameObject*> transparent_objs;
	//! Vector to hold all opaque objects that are rendered firstly.
	std::vector<GameObject*> opaque_objs;
protected:
	//! Main game window
	GLFWwindow* window;
	//! Skybox used ingame.
	Skybox* sky;
	//! Vertex Array Object adress used to hold created screen geometry.
	unsigned int screenVAO;
	//! Vertex Buffer Object adress. It is used to hold our geometry in high-speed GPU memory.
	unsigned int screenVBO;
	//! Framebuffer Object.
	unsigned int fbo;
	//! Texture Bufffer Object - holds texture of rendered frame.
	unsigned int tbo;
	//! Render Buffer Object.
	unsigned int rbo;
	//! Framebuffer Object used to hold shadowmap frame.
	unsigned int depthMapFBO;
	//! OpenGL Texture for shadowmap.
	unsigned int depthMap;
	//! Framebuffer object used to hold frame rendered in high dynamic range.
	unsigned int hdrFBO;
	//! Two OpenGL textures used to hold separated HDR image - one with normal image, and secound with only bright parts.
	unsigned int colorBuffers[2];
	//! Framebuffer objects used to create bloom effect.
	unsigned int pingpongFBO[2];
	//! OpenGL Textures used to create bloom effect.
	unsigned int pingpongColorbuffers[2];
	//! Width of used shadowmap - will be changeable in future.
	const int SHADOW_WIDTH = 4096;
	//! Height of used shadowmap - will be changeable in future.
	const int SHADOW_HEIGHT = 4096;
	//! Currently set width of window and viewport.
	int screen_width = 1280;
	//! Currently set height of window and viewport.
	int screen_height = 720;

	//! TO-DO: Create separate class for scene loading with possibility to save placed objects to some kind of "binary" file
	/*!
	PhysX Scene to calculate physics.
	*/

};