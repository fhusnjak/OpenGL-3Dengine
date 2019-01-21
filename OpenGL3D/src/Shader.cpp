#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

Shader::Shader(const std::string& filePath) 
	: ID(0), filePath(filePath) {
	ID = CreateShader();
}

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::Bind() const {
	glUseProgram(ID);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

unsigned int Shader::CreateShader() {
	ParseShader();

	unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
	const char* v = vertSource.c_str();
	GLCall(glShaderSource(vert, 1, &v, nullptr));

	unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
	const char* f = (fragSource.c_str());
	GLCall(glShaderSource(frag, 1, &f, nullptr));

	int success;
	GLCall(glCompileShader(vert));
	GLCall(glGetShaderiv(vert, GL_COMPILE_STATUS, &success));
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vert, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader " << infoLog << std::endl;
	}

	GLCall(glCompileShader(frag));
	GLCall(glGetShaderiv(frag, GL_COMPILE_STATUS, &success));
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(frag, 512, NULL, infoLog);
		std::cout << "Error compiling fragment shader: " << infoLog << std::endl;
	}

	unsigned int program = glCreateProgram();

	GLCall(glAttachShader(program, vert));
	GLCall(glAttachShader(program, frag));

	GLCall(glLinkProgram(program));

	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "PROGRAMLINK\n" << infoLog << std::endl;
	}

	GLCall(glUseProgram(program));

	return program;
}

void Shader::ParseShader() {
	vertSource = "#version 330 core\n"
		"\n"
		"layout(location=0) in vec3 position;\n"
		"layout(location=1) in vec2 tcords;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec2 myTcords;\n"
		"\n"
		"void main() {\n"
		"	gl_Position = projection * view * model * vec4(position, 1.0f);\n"
		"	myTcords = tcords;\n"
		"};\n;";

	fragSource = "#version 330 core\n"
		"out vec4 color;\n"
		"in vec2 myTcords;\n"
		"uniform sampler2D myTexture1;\n"
		"uniform sampler2D myTexture2;\n"
		"\n"
		"void main() {\n"
		"	color = mix(texture(myTexture1, myTcords), texture(myTexture2, myTcords), 0.0f);\n"
		"};\n";
}

void Shader::SetUniform1i(const char* name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4f(const char* name, glm::mat4 mat) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

int Shader::GetUniformLocation(const char* name) {
	GLCall(int location = glGetUniformLocation(ID, name));
	return location;
}
