#include "TestGame.h"

#include <VisualObject.h>

#include <iostream>

#include <Plane.h>
#include <Cube.h>
#include <ResourceManager.h>
#include <DirectionalLight.h>
#include <LightManager.h>

#include <vector>
#include <algorithm>


TestGame::TestGame() : Game()
{
	camera["main"] = new Camera();
	color = 0.0f;
}

TestGame::~TestGame()
{
}

void TestGame::Init(GLuint screen_width, GLuint screen_height)
{
	Game::Init(screen_width, screen_height);

	std::vector<GLchar*> filenames;

	filenames.push_back((GLchar*)"assets/textures/skybox/clouds/right.png");
	filenames.push_back((GLchar*)"assets/textures/skybox/clouds/left.png");
	filenames.push_back((GLchar*)"assets/textures/skybox/clouds/top.png");
	filenames.push_back((GLchar*)"assets/textures/skybox/clouds/bottom.png");
	filenames.push_back((GLchar*)"assets/textures/skybox/clouds/front.png");
	filenames.push_back((GLchar*)"assets/textures/skybox/clouds/back.png");

	ResourceManager::LoadCubeMap(filenames, "skybox_clouds");

	camera["main"]->Perspective(45.f, 16.f / 9.f, .01f, 1000.f);
	camera["main"]->transform.Position(glm::vec3(0.0f, 1.0f, 0.0f));
	camera["main"]->transform.Rotation(0, 0, 0);
	
	sky = new Skybox();
	sky->texture = ResourceManager::GetTexture("skybox_clouds");

	DirectionalLight* tLight = new DirectionalLight();
	tLight->direction = glm::vec3(-0.5f, -1.0f, 1.5f);
	tLight->diffuse = glm::vec3(0.85f, 0.85f, 0.8f);
	tLight->ambient = glm::vec3(0.7f,0.7f,0.7f);
	tLight->specular = glm::vec3(1.0f, 1.0f, 1.0f);

	LightManager::AddDirectionalLight(tLight);

	Cube* tCube = new Cube();
	tCube->material = Material::chrome;

	tCube->transform.Rotation(glm::vec3(80.0f,0.0f,0.0f));
	tCube->transform.Position(glm::vec3(10.0f, 3.0f, 10.0f));
	
	objects.push_back(tCube);
	opaque_objs.push_back(tCube);

	Plane* ground = new Plane();
	ground->material = Material::emerald;
	ground->transform.Scale(100.0f, 1.0f, 100.0f);
	ground->receiveShadows = true;
	objects.push_back(ground);
	opaque_objs.push_back(ground);

}

void TestGame::Update(GLfloat dt)
{
	camera["main"]->Update(dt);
	for (auto &object : objects)
	{
		object->Update(dt);
	}

	objects[0]->transform.Rotation(objects[0]->transform.Rotation() + glm::vec3(90.0f * dt, 0.0f, 30.0f * dt));
}

void TestGame::MainLoop()
{	
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	while (!glfwWindowShouldClose(this->window))
	{
		// Calculate delta time
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		std::cout << "FPS: " << 1.0f / deltaTime << std::endl;


		this->ProcessInput(deltaTime);
		this->Update(deltaTime);
		this->Render();

		glfwPollEvents();
	}
}
