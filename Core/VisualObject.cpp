#include "VisualObject.h"
#include "ResourceManager.h"
#include "Game.h"

#include <glm\gtc\type_ptr.hpp>

void VisualObject::Draw()
{
	this->shader->Use();

	glm::mat4 model = transform.ApplyTransform();
	glm::mat4 MVP = Game::instance->camera["main"]->GetProjectionMatrix() * Game::instance->camera["main"]->GetViewMat() * model;
	glm::mat3 normalModel = (glm::mat3) glm::transpose(glm::inverse(model));

	this->shader->SetMatrix4("MVP", MVP);
	this->shader->SetMatrix4("model", model);
	this->shader->SetVector3f("viewPos", Game::instance->camera["main"]->transform.Position());
	this->shader->SetMatrix3("normalModel", normalModel);
	LightManager::ApplyToShader(this->shader);
	this->shader->SetMatrix3("lightSpaceMatrix", LightManager::GetDirLightSpaceMatrix());
	this->shader->SetInteger("receiveShadows", receiveShadows);


	this->model.Draw(this->shader);
}

void VisualObject::DrawShadow()
{
	glm::mat4 model = transform.ApplyTransform();
	ResourceManager::GetShader("shadow")->SetMatrix4("model", model);
	this->model.DrawShadow();
}

VisualObject::VisualObject(GLchar* model_file, ShaderType shaderType) : GameObject(), model(model_file)
{
	switch (shaderType)
	{
		case STANDARD:
		{
			this->shader = ResourceManager::GetShader("standard");
			break;
		}
		case STANDARD_ALPHA:
		{
			this->shader = ResourceManager::GetShader("standard_alpha");
			break;
		}
		case STANDARD_SHADELESS:
		{
			this->shader = ResourceManager::GetShader("standard_shadeless");
			break;
		}
	}
}

VisualObject::~VisualObject()
{

}