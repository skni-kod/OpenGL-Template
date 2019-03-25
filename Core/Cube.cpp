#include "Cube.h"

Cube::Cube() : PrimitiveVisual(STANDARD)
{
	Mesh* tMesh = new Mesh();

	//front
	tMesh->vertices.push_back(glm::vec3(0.5, 0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, -0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, -0.5, 0.5));

	tMesh->uvs.push_back(glm::vec2(1, 1));
	tMesh->uvs.push_back(glm::vec2(0, 1));
	tMesh->uvs.push_back(glm::vec2(0, 0));
	tMesh->uvs.push_back(glm::vec2(1, 0));

	//back
	tMesh->vertices.push_back(glm::vec3(0.5, 0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, -0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.5, -0.5));

	tMesh->uvs.push_back(glm::vec2(1, 1));
	tMesh->uvs.push_back(glm::vec2(1, 0));
	tMesh->uvs.push_back(glm::vec2(0, 0));
	tMesh->uvs.push_back(glm::vec2(0, 1));
	//right
	tMesh->vertices.push_back(glm::vec3(0.5, 0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, 0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, -0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, -0.5, -0.5));

	tMesh->uvs.push_back(glm::vec2(1, 0));
	tMesh->uvs.push_back(glm::vec2(1, 1));
	tMesh->uvs.push_back(glm::vec2(0, 1));
	tMesh->uvs.push_back(glm::vec2(0, 0));
	//left
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, -0.5, 0.5));

	tMesh->uvs.push_back(glm::vec2(1, 1));
	tMesh->uvs.push_back(glm::vec2(1, 0));
	tMesh->uvs.push_back(glm::vec2(0, 0));
	tMesh->uvs.push_back(glm::vec2(0, 1));
	//up
	tMesh->vertices.push_back(glm::vec3(0.5, 0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, 0.5, 0.5));

	tMesh->uvs.push_back(glm::vec2(1, 0));
	tMesh->uvs.push_back(glm::vec2(0, 0));
	tMesh->uvs.push_back(glm::vec2(0, 1));
	tMesh->uvs.push_back(glm::vec2(1, 1));
	//bottom
	tMesh->vertices.push_back(glm::vec3(0.5, -0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, -0.5, 0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, -0.5, -0.5));

	tMesh->uvs.push_back(glm::vec2(1, 1));
	tMesh->uvs.push_back(glm::vec2(1, 0));
	tMesh->uvs.push_back(glm::vec2(0, 0));
	tMesh->uvs.push_back(glm::vec2(0, 1));
	
	for (size_t i = 0; i < 6; i++)
	{
		tMesh->indices.push_back(i * 4);
		tMesh->indices.push_back(i * 4 + 1);
		tMesh->indices.push_back(i * 4 + 2);

		tMesh->indices.push_back(i * 4);
		tMesh->indices.push_back(i * 4 + 2);
		tMesh->indices.push_back(i * 4 + 3);
	}

	tMesh->RecalculateNormals();
	tMesh->CreateMesh();

	this->meshes.push_back(tMesh);
}


Cube::~Cube()
{

}

void Cube::Update(GLfloat dt)
{

}
