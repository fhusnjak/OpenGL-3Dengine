#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw3.h>

class Camera {
private:
	float sensitivity;
	glm::vec3 camDir, camPosition, camVertical;
	float pitch, yaw;
	float lastXpos, lastYpos;
public:
	Camera(float sensitivity, glm::vec3 camDir, glm::vec3 camPosition, glm::vec3 camVertical, float xpos, float ypos);
	void ProcessMouseInput(float xpos, float ypos);
	void ProcessKeyboardInput(GLFWwindow* window, float speed);
	glm::vec3 getCamDir() const { return camDir; };
	glm::vec3 getCamPosition() const { return camPosition; };
	glm::vec3 getCamDirVertical() const { return camVertical; };

};
