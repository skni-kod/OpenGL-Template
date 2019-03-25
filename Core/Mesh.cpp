#include "Mesh.h"

glm::vec3 Mesh::NormalFromIndices(GLuint a, GLuint b, GLuint c)
{
	glm::vec3 vertA = vertices[a];
	glm::vec3 vertB = vertices[b];
	glm::vec3 vertC = vertices[c];

	return glm::cross(vertB - vertA, vertC - vertA);
}

glm::vec3 Mesh::TangentFromIndices(GLuint a, GLuint b, GLuint c)
{
	glm::vec3 vertA = vertices[a];
	glm::vec3 vertB = vertices[b];
	glm::vec3 vertC = vertices[c];

	glm::vec2 uv1 = uvs[a];
	glm::vec2 uv2 = uvs[b];
	glm::vec2 uv3 = uvs[c];

	glm::vec3 edge1 = vertB - vertA;
	glm::vec3 edge2 = vertC - vertA;

	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	glm::vec3 tangent;
	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent = glm::normalize(tangent);

	return tangent;
}

void Mesh::CreateInstanceAttribPointer()
{
	//glBindVertexArray(VAO);

	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
	//glEnableVertexAttribArray(5);
	//glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
	//glEnableVertexAttribArray(6);
	//glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

	//glVertexAttribDivisor(3, 1);
	//glVertexAttribDivisor(4, 1);
	//glVertexAttribDivisor(5, 1);
	//glVertexAttribDivisor(6, 1);

	//glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(vertexFlag, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::CreateMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBOClr);
	glDeleteBuffers(1, &VBONorm);
	glDeleteBuffers(1, &VBOuv);
	glDeleteBuffers(1, &VBOTangent);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBOClr);
	glGenBuffers(1, &VBONorm);
	glGenBuffers(1, &VBOuv);
	glGenBuffers(1, &VBOTangent);

	glBindVertexArray(VAO);

	if (vertices.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &(vertices[0]), GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	}

	if (colors.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBOClr);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &(colors[0]), GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	}

	if (normals.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBONorm);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &(normals[0]), GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	}

	if (uvs.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBOuv);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid*)0);
	}

	if (tangents.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBOTangent);
		glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(glm::vec3), &tangents[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	}

	if (indices.size() != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices[0]), GL_DYNAMIC_DRAW);
	}
	glBindVertexArray(0);
}

void Mesh::RecalculateNormals()
{
	if (vertexFlag != GL_TRIANGLES) {
		throw "Cannot calculate normals with given flag!";
	}

	normals.resize(vertices.size());

	for (size_t i = 0; i < indices.size() / 3; i++)
	{
		GLuint triangleIndex = i * 3;
		GLuint pointA = indices[triangleIndex];
		GLuint pointB = indices[triangleIndex + 1];
		GLuint pointC = indices[triangleIndex + 2];

		glm::vec3 normal = NormalFromIndices(pointA, pointB, pointC);

		normals[pointA] += normal;
		normals[pointB] += normal;
		normals[pointC] += normal;

		//std::cout << pointA << "  " << pointB << "  " << pointC << std::endl;
		//std::cout << triangleIndex << "  " << triangleIndex + 1 << "  " << triangleIndex + 2 << std::endl;
		//std::cout << i << "   " << normals[pointA].x << "  " << normals[pointA].y << "  " << normals[pointA].z << "  " << std::endl;
		//std::cout << i << "   " << normals[pointB].x << "  " << normals[pointB].y << "  " << normals[pointB].z << "  " << std::endl;
		//std::cout << i << "   " << normals[pointC].x << "  " << normals[pointC].y << "  " << normals[pointC].z << "  " << std::endl;

	}

	for (size_t i = 0; i < normals.size(); i++)
	{
		//std::cout << i << "   " << normals[i].x << "  " << normals[i].y << "  " << normals[i].z << "  " << std::endl;

		normals[i] = glm::normalize(normals[i]);
	}

	if (uvs.size() > 0) {
		tangents.resize(vertices.size());
		for (size_t i = 0; i < indices.size() / 3; i++)
		{
			GLuint triangleIndex = i * 3;
			GLuint pointA = indices[triangleIndex];
			GLuint pointB = indices[triangleIndex + 1];
			GLuint pointC = indices[triangleIndex + 2];

			glm::vec3 tangent = TangentFromIndices(pointA, pointB, pointC);

			tangents[pointA] = tangent;
			tangents[pointB] = tangent;
			tangents[pointC] = tangent;

		}
	}
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBOClr);
	glDeleteBuffers(1, &VBONorm);
	glDeleteBuffers(1, &VBOuv);
	glDeleteBuffers(1, &VBOTangent);

}
