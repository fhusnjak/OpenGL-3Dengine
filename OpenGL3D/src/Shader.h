#pragma once
#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Shader {
private:
	unsigned int ID;
	std::string filePath;
	std::string vertSource, fragSource;
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	unsigned int CreateShader();
	void ParseShader();
	void SetUniform1i(const char* name, int value);
	void SetUniformMat4f(const char* name, glm::mat4 mat);
	int GetUniformLocation(const char* name);
};