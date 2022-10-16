#pragma once

#include <iostream>
#include <GL/glew.h>

class VertexBuffer
{
public:
		VertexBuffer(void *data, uint32_t numVertices, uint vSize);
		virtual ~VertexBuffer();
		void bind();
		void unbind();
private:
		GLuint bufferId;
		GLuint vao;

		
};
