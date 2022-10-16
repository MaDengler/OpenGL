#pragma once
#include <GL/glew.h>

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"




class Renderer{
public:
	void draw(VertexBuffer &vertexBuffer, IndexBuffer &indexBuffer, Shader &shader);
	
private:
};
