#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"
#include "Texture.h"

//! Skybox object

/*!
Works almost like PrimitiveVisual class, but uses simple openGL values instead of built-in Mesh class.
It uses cubemap Texture to represent each side of the box.
*/
class Skybox
{
public:
	//! Cubemap texture of sky.
	Texture* texture;

	//! Constructor.

	/*!
	Setup vertices to create skybox cube.
	Generates VBOs.
	Sets skybox shader.
	*/
	Skybox();

	//! Destructor.
	~Skybox();

	//! Draws skybox using skybox shader.
	void Draw();
private:
	Shader* shader;
	std::vector<glm::vec3> vertices;
	unsigned int sVAO, sVBO;
};