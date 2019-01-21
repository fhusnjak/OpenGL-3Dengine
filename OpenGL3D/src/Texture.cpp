#include "Texture.h"

Texture::Texture(std::string & filePath)
	: ID(0), width(0), height(0), bpp(0), filePath(filePath) {
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);
	if (data) {
		GLCall(glGenTextures(1, &ID));
		GLCall(glBindTexture(GL_TEXTURE_2D, ID));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		//GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {
		std::cout << stbi_failure_reason() << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &ID));
}

void Texture::Bind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));
}

void Texture::Unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
