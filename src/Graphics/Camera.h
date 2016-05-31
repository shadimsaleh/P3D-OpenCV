#pragma once
#include <GL\glew.h>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Initialize();
	void Update();
	void SetPosition(const glm::vec3& position);
	void SetPerspective(float fov, int width, int height, float near = 0.1f, float far = 1000.0f);

	static Camera* GetActive();

private:
	static GLuint ubo;
	static bool initialized;
	static Camera* activeCamera;

	glm::vec3 position;
	glm::mat4 transform;
	glm::mat4 projection;
	bool needsUpdate;
};