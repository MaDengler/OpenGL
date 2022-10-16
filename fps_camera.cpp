#include "libs/glm/glm.hpp"
#include "libs/glm/ext/matrix_transform.hpp"

#include "libs/glm/gtc/matrix_transform.hpp"


#include "fps_camera.h"

FPSCamera::FPSCamera(float fov, float width, float height) : Camera(fov, width, height){
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	onMouseMove(0.0f, 0.0f);
	update();
}

void FPSCamera::onMouseMove(float xRel, float yRel){
	yaw+=-xRel*mouseSensitivity;
	pitch+=yRel*mouseSensitivity;
	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
	
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	lookAt = glm::normalize(front);
	update();	
}

void FPSCamera::moveFront(float amount){
	translate(glm::normalize(glm::vec3(1.0f,0.0f,1.0f)*lookAt) * amount);     
	update();
}

void FPSCamera::moveSideways(float amount){
	translate(glm::normalize(glm::cross(lookAt,up))*amount);
	update();
}

void FPSCamera::update(){
	view = glm::lookAt(position, position+lookAt, up);
	viewProj = projection * view; 
}
