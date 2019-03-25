#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

//! Base Light class
class Light
{
public:
	//! Diffuse color of light.
	glm::vec3 diffuse;
	//! Ambient color of light.
	glm::vec3 ambient;
	//! Specular color of light.
	glm::vec3 specular;
};