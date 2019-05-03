#include "Camera.h"
#include "glm.hpp"
#include <iostream>
#include <freeglut.h>

void Camera::initializeCamera()
{
	camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::calculate()
{
	newPos = glm::vec4(0, 0, 3, 1);
	camPos = glm::vec3(newPos);
	camTar = glm::vec3(0.0f, 0.0f, 0.0f);
	view = glm::lookAt(camPos, camTar, camUpDir);

}



