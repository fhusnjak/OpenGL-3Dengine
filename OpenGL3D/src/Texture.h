#pragma once
#include <iostream>
#include "stb_image/stb_image.h"
#include <glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Texture {
private:
	unsigned int ID;
	int width, height, bpp;
	std::string& filePath;
public:
	Texture(std::string& filePath);
	~Texture();
	void Bind() const;
	void Unbind() const;
};