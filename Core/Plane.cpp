#include "Plane.h"

Plane::Plane() : PrimitiveVisual(STANDARD)
{
	Mesh* tMesh = new Mesh();

	//front
	tMesh->vertices.push_back(glm::vec3(0.5, 0.0, -0.5));
	tMesh->vertices.push_back(glm::vec3(0.5, 0.0, 0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.0, 0.5));
	tMesh->vertices.push_back(glm::vec3(-0.5, 0.0, -0.5));

	tMesh->uvs.push_back(glm::vec2(1, 1));
	tMesh->uvs.push_back(glm::vec2(0, 1));
	tMesh->uvs.push_back(glm::vec2(0, 0));
	tMesh->uvs.push_back(glm::vec2(1, 0));

	tMesh->indices.push_back(0);
	tMesh->indices.push_back(2);
	tMesh->indices.push_back(1);
	tMesh->indices.push_back(0);
	tMesh->indices.push_back(3);
	tMesh->indices.push_back(2);

	tMesh->RecalculateNormals();
	tMesh->CreateMesh();

	this->meshes.push_back(tMesh);
}

Plane::~Plane()
{
}

void Plane::Update(GLfloat dt)
{
	//this->transform.Rotation(this->transform.Rotation() + glm::vec3(1.0f, 0.0f, 0.0f));
}
