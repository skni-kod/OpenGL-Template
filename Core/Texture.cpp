#include "Texture.h"
#include <iostream>

Texture::Texture() :
	width(0), height(0), internal_format(GL_RGBA), image_format(GL_RGBA), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), filter_min(GL_LINEAR_MIPMAP_LINEAR), filter_max(GL_LINEAR), type(TextureType::STANDARD)
{
	glGenTextures(1, &this->id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}

GLuint Texture::GetWidth()
{
	return this->width;
}

GLuint Texture::GetHeight()
{
	return this->height;
}

GLuint Texture::GetInternalFormat()
{
	return this->internal_format;
}

GLuint Texture::GetImageFormat()
{
	return this->image_format;
}


void Texture::LoadFromFile(GLchar* filename)
{
	ILuint imageName;
	ilGenImages(1, &imageName);
	ilBindImage(imageName);
	ilLoadImage(filename);
	if (ilGetError() == IL_COULD_NOT_OPEN_FILE)
	{
		std::cout << "ERROR::TEXTURE: Failed to read texture image file" << filename << std::endl;
	}

	this->width = ilGetInteger(IL_IMAGE_WIDTH);
	this->height = ilGetInteger(IL_IMAGE_HEIGHT);

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, this->id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);

	glBindTexture(GL_TEXTURE_2D, 0);
	ilDeleteImages(1, &imageName);
}

void Texture::LoadCubemapFromFile(std::vector<GLchar*> filenames)
{
	if (filenames.size() != 6) throw "Not enough files for cubemap creation";
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);

	for (int i = 0; i < 6; i++)
	{
		ILuint imageName;
		ilGenImages(1, &imageName);
		ilBindImage(imageName);
		ilLoadImage(filenames[i]);

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

		ilDeleteImages(1, &imageName);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	type = TextureType::CUBEMAP;
}