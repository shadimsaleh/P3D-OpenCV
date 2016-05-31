#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GLuint Camera::ubo = 0;
bool Camera::initialized = false;
Camera* Camera::activeCamera = nullptr;

Camera::Camera() : needsUpdate(true)
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	if (!initialized) {
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW); // allocate 150 bytes of memory
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));
		initialized = true;
	}
}

void Camera::Update()
{
	if (needsUpdate) 
	{
		transform = glm::mat4();
		transform = glm::translate(transform, position);

		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferSubData(ubo, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(transform));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		needsUpdate = false;
	}
}

void Camera::SetPosition(const glm::vec3 & position)
{
	needsUpdate = true;
	this->position = position;
}

void Camera::SetPerspective(float fov, int width, int height, float near, float far)
{
	projection = glm::mat4();
	projection = glm::perspective<float>(fov, (float)width / height, near, far);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(ubo, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Camera * Camera::GetActive()
{
	return activeCamera;
}
