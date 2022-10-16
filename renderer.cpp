#include <GL/glew.h>

#include "renderer.h"


void Renderer::draw(VertexBuffer &vertexBuffer, IndexBuffer &indexBuffer, Shader &shader){
		shader.bind();
		vertexBuffer.bind();
		indexBuffer.bind();
		
		glDrawElements(GL_TRIANGLES, indexBuffer.getNumIndices(), GL_UNSIGNED_INT,0);
}
