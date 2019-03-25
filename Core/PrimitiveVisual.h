#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

#include "LightManager.h"

#include <vector>

//! Primitive visual object.

/*!
This is visual object that uses simple shapes that are not loaded as models.
*/
class PrimitiveVisual : public GameObject
{
public:
	//! Pointer to the used shader for this object.
	Shader* shader;
	//! List of meshes used to create this primitive. Look in Mesh for more info.
	std::vector<Mesh*> meshes;
	//! Material of this primitive. Look in Material for more info.
	Material material;

	//! Constructor for Primitive Visual.

	/*!
	\param shaderType Type of used shader, right now it is limited to built-in shaders.
	*/
	PrimitiveVisual(ShaderType shaderType = STANDARD);
	//! Destructor.
	~PrimitiveVisual();

	//! Determines if object will be rendered with shadows over it.
	bool receiveShadows = false;

	//Inherited from GameObject
	virtual void Draw() override;
	virtual void DrawShadow() override;
};