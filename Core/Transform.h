#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
	//! Vector that is facing to forward of the object.
	glm::vec3 forward;

	//! Vector that is facing to right of the object.
	glm::vec3 right;

	//! Vector that is facing to up of the object.
	glm::vec3 up;
	

	//! This variable holds current position of object.
	glm::vec3 position;
	//! This variable holds current rotation of object.
	glm::vec3 rotation;
	//! This variable holds current scale of object.
	glm::vec3 scale;

	//! Recalculates forward, right and up vectors.

	/*!
	This method is called each time transform is modified.
	All operations like changing position, rotation or scalling are calling this method to update vectors.
	*/
	void UpdateVectors();

public:

	//! Transform's parent object used to calculate transform from parent's values
	Transform* parent = nullptr;

	//void LookAt(glm::vec3 target);

	//! Returns object forward vector considering it's rotation.

	/*!
	Mostly used to transform object position forward with considering it's rotation.
	*/
	glm::vec3 Forward() { return forward; }

	//! Returns object right vector considering it's rotation.

	/*!
	Mostly used to transform object position right with considering it's rotation.
	*/
	glm::vec3 Right() { return right; }

	//! Returns object up vector considering it's rotation.

	/*!
	Mostly used to transform object position up with considering it's rotation.
	*/
	glm::vec3 Up() { return up; }

	//! Returns current position of object.

	/*!
	This method returns current position of object using glm::vec3 type. Each axis is represented by corresponding value in glm::vec3 type.
	*/
	glm::vec3 Position() { return position; }

	//! Change position of object to given glm::vec3 value.

	/*!
	Sets object's position to the new position given in newPos parameter. Each value in glm::vec3 is corresponding to one of the X,Y,Z axes.
	*/
	void Position(glm::vec3 newPos) {
		position = newPos;
		UpdateVectors();
	}

	//! Change position of object to given float values

	/*!
	Sets object's position to the new position given in x,y and z parameters. Each value is corresponding to one of the X,Y,Z axes.
	*/
	void Position(float x, float y, float z) {
		position = glm::vec3(x, y, z);
		UpdateVectors();
	}

	//! Returns current rotation of object.

	/*!
	This method return rotation of object packed in glm::vec3 type. Each field of glm::vec3 is representing rotation in degrees for corresponding axis.
	*/
	glm::vec3 Rotation() { return rotation; }

	//! Rotates object with rotation given in X,Y,Z axes inside glm::vec3.

	/*!
	Sets rotation of object with given glm::vec3 value. Each field from glm::vec3 represents each axis of rotation.
	This method of rotation will cause Gimbal Lock
	*/
	void Rotation(glm::vec3 newRot) {
		rotation = newRot;
		UpdateVectors();
	}

	//! Rotates object with rotation given in X,Y,Z float values.

	/*!
	Sets rotation of object with given float values. Each field from glm::vec3 represents each axis of rotation.
	This method of rotation will cause Gimbal Lock
	*/
	void Rotation(float x, float y, float z) {
		rotation = glm::vec3(x, y, z);
		UpdateVectors();
	}

	//! Returns current scale of object.

	/*!
	This method returns scale of object packed in glm::vec3 type which is created by joining 3 float values for X, Y and Z axes.
	*/
	glm::vec3 Scale() { return scale; }

	//! Scales object with scale given in X,Y,Z axes.

	/*!
	Sets scale of transformed object to the given glm::vec3 with set x,y,z  axes.
	*/
	void Scale(glm::vec3 newScale) { scale = newScale; }

	//! Scales object with given scale in X,Y,Z axes.

	/*!
	Sets scale of transformed object to the given float values with axes x,y,z.
	*/
	void Scale(float x, float y, float z) {
		scale = glm::vec3(x, y, z);
	}

	//! Returns transformation matrix for object.

	/*!
	This method returns transformation matrix for object after applying position, scale and rotation to the identity matrix.
	If transform has parrent it is then multiplied by parrent's transformation matrix.
	*/
	glm::mat4 ApplyTransform();
	
	//! Returns position in world space.

	/*!
	This method uses ApplyTransform() and multiplies it by world central position to get position in world space.
	Transform matrix is then converted to glm::vec3.
	*/
	glm::vec3 WorldPosition();

	//! Constructor for Transform class

	/*!
	Sets position and rotation to 0.
	Sets scale to 1.
	*/
	Transform();

	//! Destructor for Transform class
	~Transform();
};