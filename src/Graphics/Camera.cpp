#include "Camera.h"
#include <gl\glew.h>

Camera* Camera::active = nullptr;

Camera::Camera()
{
	if (!active)
		active = this;
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
