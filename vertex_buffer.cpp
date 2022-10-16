#include <iostream>
#include <GL/glew.h>

#include "vertex_buffer.h"


VertexBuffer::VertexBuffer(void *data, uint32_t numVertices, uint vSize){
		
		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);
		
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);		
		glBufferData(GL_ARRAY_BUFFER, numVertices * vSize, data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vSize, (void*) 0);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,vSize, (void*) 12);	
		
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vSize, (void*) 24);	
}	
	
VertexBuffer::~VertexBuffer(){
		glDeleteBuffers(1, &bufferId);		
}
	
void VertexBuffer::bind(){
		glBindVertexArray(vao);
}
	
void VertexBuffer::unbind(){
		glBindVertexArray(0);		
}

	
