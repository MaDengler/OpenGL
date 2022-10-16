#pragma once
#include "camera.h"

class FPSCamera : public Camera{
public:
	FPSCamera(float fov, float width, float height);
	void onMouseMove(float xRel, float yRel);
	void moveSideways(float amount);
	void moveFront(float amount);
	void update();

protected:
	float yaw;
	float pitch;
	glm::vec3 lookAt;
	const float mouseSensitivity = 0.3f;
	glm::vec3 up;
	
};
