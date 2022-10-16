#pragma once
#include "libs/glm/glm.hpp"

class Camera {
public:
	Camera(float fov, float width, float height);
	glm::mat4 getViewProj();
	void update();
	void translate(glm::vec3 v);
	
protected:
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 viewProj; 
};
