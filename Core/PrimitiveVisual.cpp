#include "PrimitiveVisual.h"
#include "Game.h"
#include "ResourceManager.h"

void PrimitiveVisual::Draw()
{
	this->shader->Use();

	glm::mat4 model = transform.ApplyTransform();
	glm::mat4 MVP = Game::instance->camera["main"]->GetProjectionMatrix() * Game::instance->camera["main"]->GetViewMat() * model;
	glm::mat3 normalModel = (glm::mat3) glm::transpose(glm::inverse(model));

	///Check and bind diffuse map from material
	if (this->material.diffuseTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		this->material.diffuseTexture->BindTexture();
		this->shader->SetInteger("hasDiffuseMap", true);
		this->shader->SetInteger("diffuseTex", 1);
	}
	else
	{
		this->shader->SetInteger("hasDiffuseMap", false);
	}

	///Check and bind specular map from material
	if (this->material.specularTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		this->material.specularTexture->BindTexture();
		this->shader->SetInteger("hasSpecularMap", true);
		this->shader->SetInteger("specularTex", 2);
	}
	else
	{
		this->shader->SetInteger("hasSpecularMap", false);
	}

	///Check and bind specular map from material
	if (this->material.normalMap != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		this->material.normalMap->BindTexture();
		this->shader->SetInteger("hasNormalMap", true);
		this->shader->SetInteger("normalMap", 3);
	}
	else
	{
		this->shader->SetInteger("hasNormalMap", false);
	}

	this->shader->SetMatrix4("MVP", MVP);
	this->shader->SetMatrix4("model", model);
	this->shader->SetVector3f("viewPos", Game::instance->camera["main"]->transform.Position());

	//Pass material to shader
	this->shader->SetVector3f("material.ambient", this->material.ambient);
	this->shader->SetVector3f("material.diffuse", this->material.diffuse);
	this->shader->SetVector3f("material.specular", this->material.specular);
	this->shader->SetFloat("material.shiness", this->material.shiness);

	this->shader->SetMatrix3("normalModel", normalModel);
	LightManager::ApplyToShader(this->shader);
	this->shader->SetMatrix4("lightSpaceMatrix", LightManager::GetDirLightSpaceMatrix());
	this->shader->SetInteger("receiveShadows", receiveShadows);
	this->shader->SetInteger("shadowMap", 0);

	this->shader->SetMatrix3("normalModel", normalModel);

	for (auto &mesh : this->meshes)
	{
		mesh->Draw();
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void PrimitiveVisual::DrawShadow()
{
	glm::mat4 model = transform.ApplyTransform();
	ResourceManager::GetShader("shadow")->SetMatrix4("model", model);
	for (auto &mesh : this->meshes)
	{
		mesh->Draw();
	}
}

PrimitiveVisual::PrimitiveVisual(ShaderType shaderType)
{
	switch (shaderType)
	{
		case STANDARD:
		{
			this->shader = ResourceManager::GetShader("standard");
			break;
		}
	}
}

PrimitiveVisual::~PrimitiveVisual()
{
}


