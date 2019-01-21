#include "Camera.h"

Camera::Camera(float sensitivity, glm::vec3 camDir, glm::vec3 camPosition, glm::vec3 camVertical, float xpos, float ypos)
	: sensitivity(sensitivity), camDir(camDir), camPosition(camPosition), camVertical(camVertical), pitch(0), yaw(-90.0f), lastXpos(xpos), lastYpos(ypos) {
}

void Camera::ProcessMouseInput(float xpos, float ypos) {
	float xoffset = xpos - lastXpos;
	float yoffset = lastYpos - ypos;
	lastXpos = xpos;
	lastYpos = ypos;

	yaw += xoffset * sensitivity;
	pitch += yoffset * sensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	camDir.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	camDir.y = sin(glm::radians(pitch));
	camDir.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}

void Camera::ProcessKeyboardInput(GLFWwindow* window, float speed) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camPosition += speed * camDir;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camPosition -= speed * camDir;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camPosition -= glm::normalize(glm::cross(camDir, camVertical)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camPosition += glm::normalize(glm::cross(camDir, camVertical)) * speed;
}
