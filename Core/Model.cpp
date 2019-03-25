#include "Model.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "ResourceManager.h"


Model::Model(GLchar * filename)
{
	loadModel(filename);
}

void Model::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		///Check and bind diffuse map from material
		if (materials[i]->diffuseTexture != nullptr)
		{
			glActiveTexture(GL_TEXTURE1);
			materials[i]->diffuseTexture->BindTexture();
			shader->SetInteger("hasDiffuseMap", true);
			shader->SetInteger("diffuseTex", 1);
		}
		else
		{
			shader->SetInteger("hasDiffuseMap", false);
		}

		///Check and bind specular map from material
		if (materials[i]->specularTexture != nullptr)
		{
			glActiveTexture(GL_TEXTURE2);
			materials[i]->specularTexture->BindTexture();
			shader->SetInteger("hasSpecularMap", true);
			shader->SetInteger("specularTex", 2);
		}
		else
		{
			shader->SetInteger("hasSpecularMap", false);
		}

		///Check and bind specular map from material
		if (materials[i]->normalMap != nullptr)
		{
			glActiveTexture(GL_TEXTURE3);
			materials[i]->normalMap->BindTexture();
			shader->SetInteger("hasNormalMap", true);
			shader->SetInteger("normalMap", 3);
		}
		else
		{
			shader->SetInteger("hasNormalMap", false);
		}

		//Pass material to shader
		shader->SetVector3f("material.ambient", materials[i]->ambient);
		shader->SetVector3f("material.diffuse", materials[i]->diffuse);
		shader->SetVector3f("material.specular", materials[i]->specular);
		shader->SetFloat("material.shiness", materials[i]->shiness);

		meshes[i]->Draw();

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
}

void Model::DrawShadow()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw();
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	Mesh* model_mesh = new Mesh();
	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		model_mesh->vertices.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		model_mesh->normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		if(mesh->mTextureCoords[0])
		{
			model_mesh->uvs.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
		}
		else
		{
			model_mesh->uvs.push_back(glm::vec2(0.0f, 0.0f));
		}
		//model_mesh->tangents.push_back(glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z));
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			model_mesh->indices.push_back(face.mIndices[j]);
	}

	//Process materials from loaded model
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		Material* mat = new Material();
		mat->ambient = Material::white.ambient;
		mat->diffuse = Material::white.diffuse;
		mat->specular = Material::white.specular;
		mat->shiness = Material::white.shiness;
		aiColor3D difColor, ambColor, specColor;
		float shininess = 0.0f;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, difColor);
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambColor);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specColor);
		material->Get(AI_MATKEY_SHININESS, shininess);
		//mat->ambient = glm::vec3(ambColor.r, ambColor.g, ambColor.b);
		//mat->diffuse = glm::vec3(difColor.r, difColor.g, difColor.b);
		mat->diffuse = glm::vec3(1.0f,1.0f,1.0f);


		mat->specular = glm::vec3(specColor.r, specColor.g, specColor.b);
		mat->shiness = shininess;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString texString;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &texString);
			if (ResourceManager::GetTexture(texString.C_Str()) == nullptr)
			{
				std::string texture_path = this->directory + "/" + texString.C_Str();
				ResourceManager::LoadTexture(texture_path.c_str(), texString.C_Str());
			}
			mat->diffuseTexture = ResourceManager::GetTexture(texString.C_Str());
		}

		materials.push_back(mat);
	}

	model_mesh->RecalculateNormals();
	model_mesh->CreateMesh();
	return model_mesh;
}
