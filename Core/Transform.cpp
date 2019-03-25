#include "Transform.h"

void Transform::UpdateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	front.y = sin(glm::radians(rotation.x));
	front.z = -(sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)));
	forward = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, forward));
}


glm::mat4 Transform::ApplyTransform()
{
	glm::mat4 transMat(1.0f);
	transMat = glm::translate(transMat, position);
	transMat = glm::rotate(transMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transMat = glm::rotate(transMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transMat = glm::rotate(transMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transMat = glm::scale(transMat, scale);

	if (parent != nullptr) {
		transMat = parent->ApplyTransform() * transMat;
	}

	return transMat;
}



glm::vec3 Transform::WorldPosition()
{
	return (glm::vec3) (ApplyTransform() * glm::vec4(0, 0, 0, 1));
}

Transform::Transform()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	UpdateVectors();
}

Transform::~Transform()
{
	this->parent = nullptr;
}
