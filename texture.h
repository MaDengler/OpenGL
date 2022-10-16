#pragma once

#include <GL/glew.h>


class Texture{
	public:
		Texture(const char* filename);
		~Texture();
		void loadTexture(const char* filename);
		void bind();
		void unbind();
	
	private:
		int32_t textureWidth = 0;
		int32_t textureHeight = 0;
		int32_t bitsPerPixel = 0;
		GLuint textureId;	
};
