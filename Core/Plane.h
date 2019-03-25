#pragma once

#include "PrimitiveVisual.h"

class Plane : public PrimitiveVisual
{
public:
	//! Constructor

	/*!
	Setups cube mesh and recreates normals.
	*/
	Plane();

	//! Destructor
	~Plane();
	// Inherited via PrimitiveVisual
	virtual void Update(GLfloat dt) override;
};