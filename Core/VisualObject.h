#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "Model.h"
#include "Material.h"
#include "LightManager.h"

class VisualObject : public GameObject
{
public:
	Shader* shader;
	Model model;
	
	virtual void Draw() override;
	virtual void DrawShadow() override;

	//! Constructor

	/*!
	\param model_file - path to model file.
	\param shaderType - select type of shader, by default it's set to standard shader.
	*/
	VisualObject(GLchar* model_file, ShaderType shaderType = STANDARD);

	//! Destructor
	~VisualObject();

	bool receiveShadows = false;
};