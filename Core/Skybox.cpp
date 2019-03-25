#include "Skybox.h"
#include "Game.h"
#include "ResourceManager.h"

Skybox::Skybox()
{
	
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));

	this->vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));

	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));

	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	this->vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	this->vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));

	glGenVertexArrays(1, &sVAO);
	glGenBuffers(1, &sVBO);
	glBindVertexArray(sVAO);
	glBindBuffer(GL_ARRAY_BUFFER, sVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &(vertices[0]), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	this->shader = ResourceManager::GetShader("skybox");
}

Skybox::~Skybox()
{
}

void Skybox::Draw()
{
	this->shader->Use();
	glDepthMask(GL_FALSE);
	glm::mat4 view = glm::mat4(glm::mat3(Game::instance->camera["main"]->GetViewMat()));
	glBindVertexArray(sVAO);

	this->shader->SetMatrix4("view", view);
	this->shader->SetMatrix4("projection", Game::instance->camera["main"]->GetProjectionMatrix());

	this->texture->BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}
