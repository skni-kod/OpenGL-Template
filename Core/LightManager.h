#pragma once

#include <vector>

#include "Shader.h"
#include "DirectionalLight.h"

//! Light manager class.

/*!
Light manager is a singleton that manages all lights and aplies them to appropiate shaders.
*/
class LightManager
{
public:
	//! Add directional light to list.
	static void AddDirectionalLight(DirectionalLight* light)
	{
		dirLights.push_back(light);
	}

	//static void AddPointLight(PointLight* light) {
	//	pointLights.push_back(light);
	//}

	//! Get calculated Directional Light space matrix.

	/*!
	\return glm::mat4 that holds position and all needed data to render objects with light.
	*/
	static glm::mat4 GetDirLightSpaceMatrix();

	//! Apply all lights to shader.
	static void ApplyToShader(Shader* shader);
private:
	static std::vector<DirectionalLight*> dirLights;
	//static std::vector<PointLight*> pointLights;

	//! Constructor.
	LightManager();
	//! Destructor.
	~LightManager();
};