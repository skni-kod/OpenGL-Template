#pragma once

#include "PrimitiveVisual.h"

class Cube : public PrimitiveVisual
{
public:
	//! Constructor

	/*!
	Setups cube mesh and recreates normals.
	*/
	Cube();
	//! Destructor
	~Cube();

	virtual void Update(GLfloat dt) override;
};