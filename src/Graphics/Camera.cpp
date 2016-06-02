#include "Camera.h"
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

GLuint Camera::ubo = 0;
bool Camera::initialized = false;
Camera* Camera::activeCamera = nullptr;

Camera::Camera() : needsUpdate(true), position(glm::vec3(0.0f))
{
	if (!GetActive()) 
	{
		SetActive(this);
	}
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	if (!initialized) 
	{
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));
		initialized = true;
	}
}

void Camera::Update()
{
	if (needsUpdate) 
	{
		glm::mat4 transform;
		transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
		transform = glm::translate(transform, position);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(transform));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		needsUpdate = false;
	}
}

void Camera::SetPosition(const glm::vec3 & position)
{
	needsUpdate = true;
	this->position = position;
}

void Camera::SetRotation(const glm::vec3 & rotation)
{
	needsUpdate = true;
	this->rotation = rotation;
}

void Camera::SetPerspective(float fov, int width, int height, float near, float far)
{
	glm::mat4 projection;
	projection = glm::perspective(fov, (float)width / (float)height, near, far);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Camera::SetActive(Camera * camera)
{
	activeCamera = camera;
}

Camera * Camera::GetActive()
{
	return activeCamera;
}
