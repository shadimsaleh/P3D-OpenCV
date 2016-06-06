#include "Camera.h"
#include <gl\glew.h>
#include <vector>
#include <Debug\Console.h>
#include <string>

Camera* Camera::active = nullptr;
bool Camera::callbacks = false;

Camera::Camera()
{
	if (!active)
		active = this;

	if (!callbacks)
		Console::Instance()->RegisterCommand("camera", CameraCommandCallback);

	callbacks = true;
}

Camera::~Camera()
{
}

void Camera::SetPerspective(float fov, float aspectRatio, float near, float far)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, aspectRatio, near, far);

	glMatrixMode(GL_MODELVIEW);
}

void Camera::LookAt(glm::vec3 up)
{
	gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z, up.x, up.y, up.z);
}

void Camera::CameraCommandCallback(Console * console, std::vector<std::string>& args)
{
	if (active == nullptr)
		return;

	float x, y, z;

	std::string command = args[0];

	if (command == "position" || command == "rotation" || command == "lookAt")
	{
		x = args.size() >= 2 ? atof(args[1].c_str()) : 0;
		y = args.size() >= 3 ? atof(args[2].c_str()) : 0;
		z = args.size() >= 4 ? atof(args[3].c_str()) : 0;

		if (command == "position")
		{
			active->position.x = x;
			active->position.y = y;
			active->position.z = z;
		}
		else if (command == "rotation")
		{
			active->rotation.x = x;
			active->rotation.y = y;
			active->rotation.z = z;
		}
		else if (command == "lookAt")
		{
			active->lookAt.x = x;
			active->lookAt.y = y;
			active->lookAt.z = z;
		}

		console->Print("Camera " + command + " set to " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
	}
}
