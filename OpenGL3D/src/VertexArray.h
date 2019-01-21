#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class VertexArray {
private:
	unsigned int ID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vlb) const;

};