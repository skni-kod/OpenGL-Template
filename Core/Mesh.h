#pragma once
#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

//! Mesh class

/*!
This is mesh class. It is used to hold geometry data of any object.
Models are created by joining multiple meshes together.
*/
class Mesh
{
public:
	//! Flag that tells OpenGL to render geometry using triangles rather than squares.
	GLenum vertexFlag = GL_TRIANGLES;

	//! std::vector that holds all vertex positions.
	std::vector<glm::vec3> vertices;
	//! std::vector that holds colors for vertices.
	std::vector<glm::vec3> colors;
	//! std::vector that holds all indices used to render faces.
	std::vector<GLuint> indices;
	//! std::vector that holds normals.
	std::vector<glm::vec3> normals;
	//! std::vectro that holds texture coordinates (UV) for each vertex.
	std::vector<glm::vec2> uvs;
	//! std::vector that holds tangents.
	std::vector<glm::vec3> tangents;

	//! Get Vertex Array Object

	/*!
	\return GLuint - vertex array object adress.
	*/
	GLuint GetVAO() {
		return VAO;
	}

	//! NOT IMPLEMENTED
	void CreateInstanceAttribPointer();

	//! Draw mesh using created VAO.
	void Draw();

	//! Create mesh based on vertices, colors, indices, uvs and tangents.
	void CreateMesh();

	//! Recalculate normals after modyfing mesh.
	void RecalculateNormals();

	//! Destructor.
	~Mesh();

private:
	GLuint VBO, EBO, VAO;
	GLuint VBOClr, VBONorm;
	GLuint VBOTangent;
	GLuint VBOuv;

	glm::vec3 NormalFromIndices(GLuint a, GLuint b, GLuint c);
	glm::vec3 TangentFromIndices(GLuint a, GLuint b, GLuint c);
};