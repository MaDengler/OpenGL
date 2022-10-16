#pragma once

#include <iostream>
#include <GL/glew.h>
#include <stdint.h>

class IndexBuffer
{
public:
	IndexBuffer(void *data, uint32_t numVertices, uint8_t elementsize);
	virtual ~IndexBuffer();
	void bind();
	void unbind();
	uint32_t getNumIndices();
private:
	GLuint bufferId;
	uint32_t mNumIndices;		
};
