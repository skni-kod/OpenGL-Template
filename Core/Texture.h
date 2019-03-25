#pragma once

#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <string>
#include <vector>

//! Specifies type of texture that is going to be created.

/*!
Specifies type of texture that is going to be created.
Depending on value passed texture will be used as cubemap texture or normal texture.
*/
enum class TextureType
{
	STANDARD,
	CUBEMAP
};

//! Texture class

/*!
Texture class used internally within game engine.
It has all required methods to load texture from file and get it's properties.
*/
class Texture
{
public:
	//! Constructor for Texture class without parameters

	/*!
	Generates texture for use with methods void LoadFromFile(GLchar* filename) or void LoadCubemapFromFile(std::vector<GLchar*> filenames)
	As of current version of engine it is not possible to generate empty texture for eg. rendering to it.
	*/
	Texture();

	//! Destructor for Texture class

	/*!
	Deletes generated texture and frees it's memory.
	*/
	~Texture();

	//! BindTexture method

	/*!
	This method allows to bind created texture for use with OpenGL renderer.
	*/
	void BindTexture();

	//! Get width of the texture

	/*!
	Returns actual width of the texture.
	*/
	GLuint GetWidth();


	//! Get height of the texture

	/*!
	Returns actual height of the texture.
	*/
	GLuint GetHeight();


	//! GLuint GetInternalFormat()

	/*!
	Returns current format of the texture used internally within game engine.
	Default format is GL_RGBA
	*/
	GLuint GetInternalFormat();
	
	//void SetInternalFormat(GLuint format)


	//! GLuint GetImageFormat()

	/*!
	Returns current format of the image used to create texture
	*/
	GLuint GetImageFormat();
	
	//void SetImageFormat(GLuint format);

	//! void LoadFromFile(GLchar* filename)

	/*!
	Loads texture from file.
	Opens file from path specified by filename and converts it to proper internal format.
	After loading image it creates OpenGL texture and binds it with this object.
	*/
	void LoadFromFile(GLchar* filename);

	//! void LoadCubemapFromFile(std::vector<GLchar*> filenames)

	/*!
	Loads cubemap from files specified in std::vector.
	Opens all files from paths specified by filenames and converts them to proper internal format.
	After loading image it creates OpenGL texture and binds it with this object.
	Returned texture is built from 6 different textures to create cubemap.
	*/
	void LoadCubemapFromFile(std::vector<GLchar*> filenames);

private:
	//! unique ID of texture generated by OpenGL
	GLuint id;

	//! Width of texture
	GLuint width;
	//! Height of texture
	GLuint height;

	//! Specifies how texture will be repeated in S (equivalent of X - width) axis.
	GLuint wrap_s;
	//! Specifies how texture will be repeated in T (equivalent of Y - height) axis.
	GLuint wrap_t;

	//! Specifies how texture will be interpolated when scalling down.
	GLuint filter_min;

	//! Specifies how texture will be interpolated when scalling up.
	GLuint filter_max;

	//! Internal format used by texture.
	GLuint internal_format;

	//! Format of the image used to create texture.
	GLuint image_format;

	//! Specifies type of the texture.
	TextureType type;
};