#pragma once

#include <string>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
//! Model class

/*!
Model has multiple materials and meshes used to create one whole object.
*/
class Model
{
public:
	//! Constructor for models.

	/*!
	Load model with assimp library.
	Load textures for materials.
	Load materials.
	\param filename - path to the model file (eg. fbx file).
	*/
	Model(GLchar* filename);

	//! Draw model normally

	/*!
	Draws object normally using specified shader.
	\param shader - pointer to the shader used to render model.
	*/
	void Draw(Shader* shader);

	//! Draw model to shadowmap

	/*!
	Draws model to shadowmap using simplified shadow shader.
	*/
	void DrawShadow();
private:
	std::vector<Mesh*> meshes;
	std::vector<Material*> materials;
	std::string directory;
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
};