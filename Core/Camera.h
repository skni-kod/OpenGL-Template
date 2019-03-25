#pragma once

#include "Transform.h"
#include "Input.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//! Camera class
class Camera
{
public:
	//! Constructor with specified mode.

	/*!
	\param mode - set if camera will work in perpective or orthographic projection.
	*/
	Camera(int mode);

	//! Constructor for Camera
	Camera();

	//! Destructor
	~Camera();


	//! Update camera logic.

	/*!
	\param dt - delta time
	*/
	void Update(GLfloat dt);

	//! Set camera to look at position.

	/*!
	\param target - position at which camera will look.
	*/
	void LookAt(glm::vec3 target);

	//! Set camera to work with perspective projection.

	/*!
	\param fov - specifies how much space camera will see.
	\param aspectRatio - specifies current aspect ratio of camera.
	\param nearPlane - speciies how close objects will start to be discarded.
	\param farPlane - specfies how far objects will start to be discarded.
	*/
	void Perspective(GLfloat fov, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlane);

	//! Set camera to work with perspective projection.

	/*!
	\param left - specifies how much to the left of the screen camera will see.
	\param right - specifies how much to the right of the screen camera will see.
	\param top - specifies how much to the top of the screen camera will see.
	\param bottom - specifies how much to the bottom of the screen camera will see.
	\param near_plane - speciies how close objects will start to be discarded.
	\param far_plane - specfies how far objects will start to be discarded.
	*/
	void Orthographic(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near_plane, GLfloat far_plane);


	//! Transform of the camera.
	Transform transform;

	//! Get projection matrix form the camera.

	/*!
	\return glm::mat4 holding all required information about currently used projection.
	*/
	glm::mat4 GetProjectionMatrix() { return projection; }

	//! Get current camera view matrix.
	glm::mat4 GetViewMat();

protected:
	glm::mat4 projection;
	glm::mat4 view;
	MousePosition lastMousePos;
	double yaw;
	double pitch;
	friend class Game;
};