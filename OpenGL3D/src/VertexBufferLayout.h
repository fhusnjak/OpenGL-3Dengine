#pragma once

#include <glew.h>
#include <vector>
#include <cassert>

struct BufferLayoutAttribs {
	int count;
	GLenum type;
	bool normalize;
	unsigned int getSize() const {
		switch (type) {
		case GL_FLOAT:
			return 4;
		case GL_INT:
			return 4;
		case GL_BYTE:
			return 1;
		default:
			return 0;
		}
	}
};

class VertexBufferLayout {
private:
	std::vector<BufferLayoutAttribs> layout;
	unsigned int stride;
public:
	VertexBufferLayout() 
		: stride(0) {
	}

	template<typename T>
	void Push(int count, bool normalize) {
		static_assert(false);
	}

	template<>
	void Push<float>(int count, bool normalize) {
		layout.push_back({count, GL_FLOAT, normalize});
		stride += count * sizeof(float);
	}

	template<>
	void Push<unsigned int>(int count, bool normalize) {
		layout.push_back({ count, GL_UNSIGNED_INT, normalize });
		stride += count * sizeof(unsigned int);
	}

	template<>
	void Push<unsigned char>(int count, bool normalize) {
		layout.push_back({ count, GL_UNSIGNED_BYTE, normalize });
		stride += count * sizeof(unsigned char);
	}

	const std::vector<BufferLayoutAttribs> GetLayout() const {
		return layout;
	}

	const unsigned int GetStride() const {
		return stride;
	}
};