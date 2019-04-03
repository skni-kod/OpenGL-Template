#include "Game.h"
#include "ResourceManager.h"
#include "LightManager.h"
#include "Input.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

Game* Game::instance = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(GLuint screen_width, GLuint screen_height)
{
	if (instance != nullptr)
	{
		throw "Multiple instances of game";
	}
	instance = this;

	this->screen_width = screen_width;
	this->screen_height = screen_height;

	srand((unsigned int)time(NULL));
	
	if ((ilGetInteger(IL_VERSION_NUM) < IL_VERSION) ||
		(ilGetInteger(ILU_VERSION_NUM) < ILU_VERSION) ||
		(ilGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION))
	{
		printf("DevIL version is different...exiting!\n");
	}

	ilInit();
	iluInit();
	ilutInit();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(screen_width, screen_height, "OGL Sample Engine", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	ilutRenderer(ILUT_OPENGL);
	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, screen_width, screen_height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float screenVertices[24] = {
		-1.0f,	1.0f,	0.0f,	1.0f,
		-1.0f,	-1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,	1.0f,	0.0f,

		-1.0f,	1.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	1.0f,	1.0f
	};

	glGenVertexArrays(1, &this->screenVAO);
	glGenBuffers(1, &this->screenVBO);
	glBindVertexArray(this->screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &this->fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

	// create a color attachment texture
	glGenTextures(1, &this->tbo);
	glBindTexture(GL_TEXTURE_2D, this->tbo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->tbo, 0);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &this->rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screen_width, screen_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenFramebuffers(1, &this->depthMapFBO);

	//Create shadowmap texture and bind it to depthMap FBO
	glGenTextures(1, &this->depthMap);
	glBindTexture(GL_TEXTURE_2D, this->depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->SHADOW_WIDTH, this->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Create HDR FBO
	glGenFramebuffers(1, &this->hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
	glGenTextures(2, this->colorBuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGB16F, this->screen_width, this->screen_height, 0, GL_RGB, GL_FLOAT, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->screen_width, this->screen_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ping-pong-framebuffer for blurring
	glGenFramebuffers(2, this->pingpongFBO);
	glGenTextures(2, this->pingpongColorbuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, this->pingpongColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->screen_width, this->screen_height, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->pingpongColorbuffers[i], 0);
		// also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}



	Input::GetInstance();
	glfwGetCursorPos(window, &Input::mousePos.x, &Input::mousePos.y);
	ResourceManager::LoadShader("shaders/standard.vs", "shaders/standard.fs", nullptr, "standard");
	ResourceManager::LoadShader("shaders/standard.vs", "shaders/standard_alpha.fs", nullptr, "standard_alpha");
	ResourceManager::LoadShader("shaders/skybox.vs", "shaders/skybox.fs", nullptr, "skybox");

	ResourceManager::LoadShader("shaders/shadows.vs", "shaders/shadows.fs", nullptr, "shadow");

	ResourceManager::LoadShader("shaders/blur.vs", "shaders/blur.fs", nullptr, "blur");
	ResourceManager::LoadShader("shaders/bloom.vs", "shaders/bloom.fs", nullptr, "bloom");
	ResourceManager::GetShader("blur")->Use();
	ResourceManager::GetShader("blur")->SetInteger("image", 0);

	ResourceManager::GetShader("bloom")->Use();
	ResourceManager::GetShader("bloom")->SetInteger("scene", 0);
	ResourceManager::GetShader("bloom")->SetInteger("bloomBlur", 1);


	ResourceManager::LoadShader("shaders/post_process.vs", "shaders/post_process.fs", nullptr, "post_process");
	ResourceManager::GetShader("post_process")->Use();
	ResourceManager::GetShader("post_process")->SetInteger("screenTexture", 0);

	
}

void Game::ProcessInput(GLfloat dt)
{
	Input::previousState = Input::keyState;
	for (auto &key : Input::keyState)
	{
		key.second = glfwGetKey(this->window, (int)key.first) == GLFW_PRESS ? true : false;
	}
	glfwGetCursorPos(window, &Input::mousePos.x, &Input::mousePos.y);
}

void Game::Render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	ResourceManager::GetShader("shadow")->Use();
	ResourceManager::GetShader("shadow")->SetMatrix4("lightSpaceMatrix", LightManager::GetDirLightSpaceMatrix());
	glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto &object : objects)
	{
		object->DrawShadow();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, this->hdrFBO);
	glViewport(0, 0, this->screen_width, this->screen_height);
	
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	sky->Draw();

	for (auto &object : opaque_objs)
	{
		object->Draw();
	}

	glDisable(GL_CULL_FACE);

	std::map<float, GameObject*> sorted;
	for (auto &object : transparent_objs)
	{
		float distance = glm::length(this->camera["main"]->transform.Position() - object->transform.Position());
		sorted[distance] = object;
	}

	for (std::map<float, GameObject*>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		it->second->Draw();
	}

	glEnable(GL_CULL_FACE);

	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);

	//BLUR
	bool horizontal = true, first_iteration = true;
	unsigned int amount = 5;
	ResourceManager::GetShader("blur")->Use();
	for (unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->pingpongFBO[horizontal]);
		ResourceManager::GetShader("blur")->SetInteger("horizontal", horizontal);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, first_iteration ? this->colorBuffers[1] : this->pingpongColorbuffers[!horizontal]);
		glBindVertexArray(this->screenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}
	//END_BLUR

	//Finalize bloom
	ResourceManager::GetShader("bloom")->Use();
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->colorBuffers[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->pingpongColorbuffers[!horizontal]);
	ResourceManager::GetShader("bloom")->SetInteger("bloom", true);
	ResourceManager::GetShader("bloom")->SetFloat("exposure", 1.0f);
	glBindVertexArray(this->screenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	ResourceManager::GetShader("post_process")->Use();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->screenVAO);
	glBindTexture(GL_TEXTURE_2D, this->tbo);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(this->window);
}

void Game::Exit()
{
	glfwTerminate();
}