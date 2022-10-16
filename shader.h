#pragma once
#include <GL/glew.h>
#include <string>

struct Shader{
	Shader(const char *vertexShaderFilename, const char *fragmentShaderFilename);
	virtual ~Shader();
	
	void bind();
	void unbind();
	
	void setColorUniformLocation(const char* name_color_uniform_variable);	
	void setColorUniformValues(float r , float g, float b, float a);
	
	void setTextureUniformLocation(const char* name_texture_uniform_variable);
	void setTextureSlot(int slot);
	
	GLuint getShaderId();
	
private:
	GLuint compile(std::string shaderSource, GLenum type);
	std::string parse(const char *filename);
	GLuint createShader(const char *vertexShaderFilename, const char *fragmentShaderFilename);
	GLuint shaderId;
	int colorUniformLocation;
	int textureUniformLocation;
};
	
