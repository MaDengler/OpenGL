#include <iostream>
#include <GL/glew.h>

#include "index_buffer.h"


IndexBuffer::IndexBuffer(void *data, uint32_t numIndices, uint8_t elementsize){
	mNumIndices = numIndices;
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);		
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementsize, data, GL_STATIC_DRAW);
	
}	
	
IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1, &bufferId);		
}
	
void IndexBuffer::bind(){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}
	
void IndexBuffer::unbind(){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		
}

uint32_t IndexBuffer::getNumIndices(){
	return mNumIndices;
}
