#include "DirectionalLight.h"

void DirectionalLight::ApplyToShader(Shader * shader)
{
	shader->SetVector3f("dirLight.direction", this->direction);
	shader->SetVector3f("dirLight.ambient", this->ambient);
	shader->SetVector3f("dirLight.diffuse", this->diffuse);
	shader->SetVector3f("dirLight.specular", this->specular);
}
