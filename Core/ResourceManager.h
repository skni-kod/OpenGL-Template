#pragma once

#include <map>
#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"

//! Resource manager singleton

/*!
Resource manager is a singleton used to load and manage all resources.
*/
class ResourceManager
{
public:
	//! std::map holding all shaders.
	static std::map<std::string, Shader> Shaders;
	//! std::map holding all textures.
	static std::map<std::string, Texture*> Textures;
	//! Loads shader from specified files.

	/*!
	This method loads shader from specified files and adds it to Shaders map with given name.
	\param vertexSource - path to a file with vertex shader code.
	\param fragmentSource - path to a file with fragment shader code.
	\param geometrySource - path to a file with geometry shader code.
	\param name - name used to identify this shader.
	*/
	static void LoadShader(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource, std::string name);

	//! Loads texture from specified file.

	/*!
	This method loads shader from specified files and adds it to Textures map with given name.
	\param texture - path to a texture image file.
	\param name - name used to identify this texture.
	\param type - specifies if this texture is normal texture or cubemap. By default it's set to STANDARD type.
	*/
	static void LoadTexture(const GLchar* texture, std::string name, TextureType type=TextureType::STANDARD);

	//! Loads cubemap texture.

	/*!
	This method loads cubemap texture with given filenames and adds it to Textures map with given name.
	\param filenames - vector array of 6 textures used to create cubemap.
	\param name - name used to identify this texture.
	*/
	static void LoadCubeMap(std::vector<GLchar*> filenames, std::string name);

	//! Get Shader with given name.

	/*!
	\param name - name of the shader that we want.
	\return Shader with given name.
	*/
	static Shader* GetShader(std::string name);

	//! Get Texture with given name.

	/*!
	\param name - name of the shader that we want.
	\return Shader with given name.
	*/
	static Texture* GetTexture(std::string name);
private:
	ResourceManager() {};
	static Shader LoadShaderFromFile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource);
	static Texture* LoadTextureFromFile(const GLchar* texture, TextureType type);
	static Texture* LoadCubeMapFromFile(std::vector<GLchar*> filenames);
};