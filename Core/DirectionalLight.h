#pragma once
#include "Light.h"
#include "Shader.h"

//! Directional Light class
class DirectionalLight : public Light
{
public:
	//! Direction to which DirectionalLight will point

	/*!
	Due to how directional light is modelled in all games this light cannot have position.
	All light rays are parallel, so no position is needed.
	*/
	glm::vec3 direction;

	//! Aply light to shader.

	/*!
	Apply light values (colors and direction) to shader.
	\param shader - pointer to shader that will have aplied ligths.
	*/
	void ApplyToShader(Shader* shader);
};