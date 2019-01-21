#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "Texture.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Camera.h"

static float deltaTime = 0.0f;
static float sensitivity = 0.05f;
static float yaw = -90.0f, pitch = 0.0f;

static int initialScreensizeW = 3840, initialScreensizeH = 2160;

static bool firstMouse = true;

static glm::vec3 camDir(0, 0, -1), camPosition(0, 0, 3), camVertical(0, 1, 0);

Camera mainCamera(0.05f, camDir, camPosition, camVertical, 0.0f, 0.0f);

static glm::mat4 model(1);
static glm::mat4 view(1);
static glm::mat4 projection(1);

static float lastX = 400, lastY = 300;

void FrameResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	projection = glm::perspective(glm::radians(45.0f), width * 1.0f / height, 0.1f, 100.0f);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	mainCamera.ProcessMouseInput(xpos, ypos);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, true);
	} 
}

void ProcessInput(GLFWwindow *window) {
	float camSpeed = 2.0f * deltaTime;
	mainCamera.ProcessKeyboardInput(window, camSpeed);
}

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

int main() {
	if (!glfwInit()) {
		std::cout << "Error initializing glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(initialScreensizeW, initialScreensizeH, "3DGraphics", NULL, NULL);

	if (!window) {
		std::cout << "Window creation failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetFramebufferSizeCallback(window, FrameResizeCallback);

	glfwSetKeyCallback(window, KeyCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseCallback);

	glfwMakeContextCurrent(window);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	mainCamera = Camera(0.05f, camDir, camPosition, camVertical, (float)xpos, (float)ypos);

	if (glewInit() != GLEW_OK) {
		std::cout << "Glew initialization failed!" << std::endl;
		return -1;
	}

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));

	{
		VertexBuffer vb(vertices, 180 * sizeof(float));
		VertexBufferLayout vbl = VertexBufferLayout();
		vbl.Push<float>(3, false);
		vbl.Push<float>(2, false);

		VertexArray vao = VertexArray();
		vao.addBuffer(vb, vbl);
		vao.Bind();

		unsigned int ib;
		GLCall(glGenBuffers(1, &ib));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

		Shader shader("");
		std::string filePath = "res/container.jpg";
		Texture bg(filePath);

		filePath = "res/awesomeface.png";
		Texture fg(filePath);

		GLCall(glActiveTexture(GL_TEXTURE0));
		bg.Bind();

		GLCall(glActiveTexture(GL_TEXTURE1));
		fg.Bind();

		shader.SetUniform1i("myTexture1", 0);
		shader.SetUniform1i("myTexture2", 1);

		projection = glm::perspective(glm::radians(45.0f), initialScreensizeW * 1.0f / initialScreensizeH, 0.1f, 100.0f);
		
		float lastTime = 0.0f;

		while (!glfwWindowShouldClose(window)) {
			float currTime = glfwGetTime();
			deltaTime = currTime - lastTime;
			lastTime = currTime;
			ProcessInput(window);
			view = glm::lookAt(mainCamera.getCamPosition(), mainCamera.getCamPosition() + mainCamera.getCamDir(), mainCamera.getCamDirVertical());
			shader.SetUniformMat4f("view", view);
			shader.SetUniformMat4f("projection", projection);
			GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
			vao.Bind();
			shader.Bind();
			for (int i = 0; i < 10; ++i) {
				glm::mat4 model(1);
				model = glm::translate(model, cubePositions[i]);
				if (i > 0) model = glm::rotate(model, glm::radians(i * 10.0f), cubePositions[i]);
				shader.SetUniformMat4f("model", model);
				GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL));
			}
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}













