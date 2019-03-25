#include "LightManager.h"

std::vector<DirectionalLight*> LightManager::dirLights = std::vector<DirectionalLight*>();

glm::mat4 LightManager::GetDirLightSpaceMatrix()
{
	glm::mat4 view = glm::lookAt(-(dirLights[0]->direction), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	GLfloat near_plane = 0.1f, far_plane = 50;
	glm::mat4 lightProjection = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, near_plane, far_plane);
	return lightProjection * view;
}

void LightManager::ApplyToShader(Shader* shader)
{
	for (auto &light : dirLights)
	{
		light->ApplyToShader(shader);
	}

	//for (auto &light : pointLights)
	//{

	//}
}
