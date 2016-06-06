#pragma once
#include <glm\vec3.hpp>
#include <Debug\Console.h>

class Camera
{
public:
	Camera();
	~Camera();

	static Camera* active;

	void SetPerspective(float fov, float aspectRatio, float near, float far);
	void LookAt(glm::vec3 up);

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 lookAt;

private:
	static void CameraCommandCallback(Console* console, std::vector<std::string>& args);
	static bool callbacks;
};