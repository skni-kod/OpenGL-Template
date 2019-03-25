#include "Camera.h"


Camera::Camera(int mode)
{
	this->lastMousePos.x = Input::GetMousePos().x;
	this->lastMousePos.y = Input::GetMousePos().y;

	yaw = 0.0;
	pitch = 0.0;
}

Camera::Camera()
{

}

Camera::~Camera()
{
}

void Camera::Update(GLfloat dt)
{
	float speed = 5.0f * dt;
	if (Input::GetKey(Key::KEY_W))
	{
		this->transform.Position(this->transform.Position() + (this->transform.Forward() * speed));
	}
	if (Input::GetKey(Key::KEY_S))
	{
		this->transform.Position(this->transform.Position() - (this->transform.Forward() * speed));
	}
	if (Input::GetKey(Key::KEY_A))
	{
		this->transform.Position(this->transform.Position() - (glm::cross(this->transform.Forward(), this->transform.Up())*speed));
	}
	if (Input::GetKey(Key::KEY_D))
	{
		this->transform.Position(this->transform.Position() + (glm::cross(this->transform.Forward(), this->transform.Up())*speed));
	}

	MousePosition currentMousePos = Input::GetMousePos();

	double offsetX = lastMousePos.x - currentMousePos.x;
	double offsetY = lastMousePos.y - currentMousePos.y;
	lastMousePos = currentMousePos;

	double sensitivity = 0.05;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0)
		pitch = 89.0;
	if (pitch < -89.0)
		pitch = -89.0;

	this->transform.Rotation(glm::vec3(pitch, yaw, 0.0));
}

void Camera::LookAt(glm::vec3 target)
{
	view = glm::lookAt(transform.Position(), target, transform.Up());
}

void Camera::Perspective(GLfloat fov, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlane)
{
	this->projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	
}

void Camera::Orthographic(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat zNear, GLfloat zFar)
{
	this->projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

glm::mat4 Camera::GetViewMat()
{
	return glm::lookAt(transform.Position(), transform.Position() + transform.Forward(), transform.Up());
}
