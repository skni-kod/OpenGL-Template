#pragma once

#include <glm/glm.hpp>
#include "Texture.h"

//! Material structure holding all characteristics of each material.
struct Material
{
	//! Diffuse Texture of material. Can be changed after setting material to object.
	Texture* diffuseTexture = nullptr;
	//! Specular Texutre of material. Can be changed after setting material to object.
	Texture* specularTexture = nullptr;
	//! Normal Map Texture of material. Can be changed after setting material to object.
	Texture* normalMap = nullptr;

	//! glm::vec3 value that represents ambient color of material.
	glm::vec3 ambient;
	//! glm::vec3 value that represents diffuse color of material.
	glm::vec3 diffuse;
	//! glm::vec3 value that represents specular color of material.
	glm::vec3 specular;

	//! Represents how translucent material is going to be.
	float alfa = 1.0f;

	//! Represents how shiny material would appear in game.
	float shiness = 32;

#pragma region static materials
	static Material emerald;
	static Material jade;
	static Material obsidian;
	static Material pearl;
	static Material ruby;
	static Material turquoise;
	static Material brass;
	static Material bronze;
	static Material chrome;
	static Material copper;
	static Material gold;
	static Material silver;
	static Material blackPlastic;
	static Material cyanPlastic;
	static Material greenPlastic;
	static Material redPlastic;
	static Material whitePlastic;
	static Material yellowPlastic;
	static Material blackRubber;
	static Material cyanRubber;
	static Material greenRubber;
	static Material redRubber;
	static Material whiteRubber;
	static Material yellowRubber;
	static Material white;
#pragma endregion

	//! Creates material with given values.

	/*!
	\param ambient glm::vec3 representing color of material's ambient.
	\param diffuse glm::vec3 representing color of material's diffuse.
	\param specular glm::vec3 representing color of material's specular.
	\param shiness float value representing shiny object will look in game.
	\return new Material*/
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shiness) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shiness = shiness;
	}

	Material() {};
};
