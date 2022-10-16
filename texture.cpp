#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"
#include "texture.h"
	
Texture::Texture(const char* filename){
	glGenTextures(1, &textureId);
	bind();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	loadTexture(filename);
	
	unbind();
}
	
Texture::~Texture(){
	glDeleteTextures(1, &textureId);
}	

void Texture::loadTexture(const char* imagefile){
	bind();	
	stbi_set_flip_vertically_on_load(true);
	auto textureBuffer = stbi_load(imagefile, &textureWidth, &textureHeight, &bitsPerPixel, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
	if(textureBuffer){
		stbi_image_free(textureBuffer);	
	}
	unbind();
}	

void Texture::bind(){	
	glBindTexture(GL_TEXTURE_2D, textureId);
}
	
void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

	




