#pragma once

#include <Game.h>
#include <gl/glew.h>
#include <Skybox.h>

//! Test implementation of engine.

/*!
This class inherits from Game class from UmiEngine.
It is proper game implementation used to represent how to use engine.
*/
class TestGame : public Game
{
public:
	//! Constructor
	TestGame();

	//! Destructor
	~TestGame();

	//! Initialization method.

	/*!
	Setup game engine and load all assets.
	Also create basic scene.
	\param screen_width - width of the screen.
	\param screen_height - height of the screen.
	*/
	void Init(GLuint screen_width, GLuint screen_height);
	//! Inherited from UmiEngine project. For more information go to UmiEngine documentation.
	/*!
	\param dt - delta time calculated between two frames.*/
	virtual void Update(GLfloat dt) override;
	virtual void MainLoop() override;
	//! Inherited from UmiEngine project. For more information go to UmiEngine documentation.
private:
	GLfloat color;
};