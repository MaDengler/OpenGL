#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <cmath>

#include "libs/glm/glm.hpp"
#include "libs/glm/ext/matrix_transform.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"


#include "vertex_buffer.h"
#include "shader.h"
#include "index_buffer.h"
#include "renderer.h"
#include "texture.h"
#include "fps_camera.h"

struct Vertex{
	float x,y,z, u,v, r,g,b,a;
};

void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam){
	std::cout << "[OpnGL debug message] " << message << std::endl;
	std::cout << "severity = " << severity << std::endl;
}

int main(){

	SDL_Window* window;
	SDL_Init(SDL_INIT_EVERYTHING);
				
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	
	#ifdef _DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	std::cout << "Debug mode" << std::endl;
	#endif
		
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	
	GLenum err = glewInit();
	if(err != GLEW_OK){
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		return -1;
	}
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openGLDebugCallback,0);
	
	Vertex vertices[] = {
		Vertex{-0.5f,-0.5f,0.0f, 0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f},
		Vertex{-0.5f,0.5f,0.0f, 0.0f,1.0f, 0.0f,1.0f,0.0f, 1.0f},
		Vertex{0.5f,0.5f,0.0f, 1.0f,1.0f, 1.0f,0.0f,1.0f, 1.0f},
		Vertex{0.5f,-0.5f,0.0f, 1.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f},
	};
	uint numVertices = 4;

	uint indices[] = {
		0,1,2,0,2,3
	};
	uint numIndices=6;
			
		
	VertexBuffer vertexBuffer(vertices, numVertices, sizeof(Vertex));
	IndexBuffer indexBuffer(indices, numIndices, sizeof(indices[0]));
	Texture texture("graphics/logo.png");

	
	Shader shader("shaders/basic.vs","shaders/basic.fs");
	shader.bind();
	
	FPSCamera camera(90.0f, 800.0f, 600.0f);
	camera.translate(glm::vec3(0.0f, 0.0f, 5.0f));
	camera.update();
	

	int modelViewProjMatrixLocation = glGetUniformLocation(shader.getShaderId(), "u_modelViewProj");
	
	shader.setColorUniformLocation("u_color");
	shader.setTextureUniformLocation("u_texture");
	shader.setTextureSlot(0);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 modelViewProj = glm::mat4(1.0f);
	
	bool run = true;
	double time = 0;
	double FPS=60;
	Uint64 start=SDL_GetPerformanceCounter();
	Uint64 stop=0;
	
	float cameraSpeed=6.0f;
	
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	bool w_pressed=false, a_pressed=false, s_pressed=false, d_pressed=false;
	
	Renderer renderer;
	
	
	while(run){		
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				run=false;
			}

			switch(event.key.keysym.sym){
				case SDLK_w:
					if(event.type==SDL_KEYDOWN)
						w_pressed=true;
					else
						w_pressed=false;
				break;					
				case SDLK_a:
					if(event.type==SDL_KEYDOWN)
						a_pressed=true;
					else
						a_pressed=false;
				break;
				case SDLK_s:
					if(event.type==SDL_KEYDOWN)
						s_pressed=true;
					else
						s_pressed=false;
				break;
				case SDLK_d:
					if(event.type==SDL_KEYDOWN)
						d_pressed=true;
					else
						d_pressed=false;
				break;
			}
			
			if(event.type == SDL_MOUSEMOTION)
				camera.onMouseMove(event.motion.xrel, event.motion.yrel);
					
		}
		
		if(w_pressed)
			camera.moveFront(1/FPS * cameraSpeed);
		if(a_pressed)
			camera.moveSideways(1/FPS * cameraSpeed);			
		if(s_pressed)
			camera.moveFront(-1/FPS * cameraSpeed);		
		if(d_pressed)
			camera.moveSideways(-1/FPS * cameraSpeed);		
		camera.update();
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.setColorUniformValues(sinf(time)*sinf(time), sinf(time+0.3)*sinf(time+0.3), sinf(time+0.6)*sinf(time+0.6), 1.0f);
		
		renderer.draw(vertexBuffer, indexBuffer, shader);


		glActiveTexture(GL_TEXTURE0);
		texture.bind();
		
		modelViewProj = camera.getViewProj() * model;
				
		glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]);
		

		
		
		SDL_GL_SwapWindow(window);										//double Buffering	
		
		stop=SDL_GetPerformanceCounter();				
		FPS=(double)(SDL_GetPerformanceFrequency()/((double)(stop-start)));
		start=SDL_GetPerformanceCounter();
		
		time+=1/FPS;
		std::cout<<FPS<<" "<<time<<"\r";



	}
	 
	return 0;
}

