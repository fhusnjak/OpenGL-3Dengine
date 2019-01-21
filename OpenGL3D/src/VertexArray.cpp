#include "VertexArray.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &ID));
	GLCall(glBindVertexArray(ID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &ID));
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(ID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vlb) const {
	vb.Bind();
	Bind();
	unsigned int offset = 0;
	auto& layout = vlb.GetLayout();
	for (unsigned int i = 0; i < layout.size(); ++i) {
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalize, vlb.GetStride(), (const void*)offset));
		offset += layout[i].count * layout[i].getSize();
	}
}
