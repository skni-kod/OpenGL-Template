#pragma once



#include "Transform.h"
#include <gl/glew.h>

enum ShaderType {STANDARD, STANDARD_ALPHA, STANDARD_SHADELESS};

//! GameObject class
class GameObject
{
public:
	//! Tranform of the object in world space.

	/*!
	This field is used to move object around world and rotate or scale it.
	It can be attached to another Transform from other object to move group of objects together.
	*/
	Transform transform;

	//! Constructor
	GameObject();
	//! Destructor
	~GameObject();

	//! Updates logic of the object.

	/*!
	This method is not implmented in GameObject. All derrived classes must implement it.
	\param dt delta time between frames of game. Allows to have frame independent movement.
	*/
	virtual void Update(GLfloat dt) = 0;
	
	//! Draw object normally

	/*!
	Draws object normally using standard shaders.
	*/
	virtual void Draw() = 0;
	//! Draw object to shadowmap

	/*!
	Draws object to shadowmap using simplified shadow shader.
	*/
	virtual void DrawShadow() = 0;
};