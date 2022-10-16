#SOURCES = main.cpp vertex_buffer.cpp shader.cpp index_buffer.cpp texture.cpp camera.cpp fps_camera.cpp renderer.cpp
SOURCES = *.cpp
OBJECTS = $(SOURCES:.cpp=.o)


Test: $(OBJECTS)
	g++ -o Test $(OBJECTS) -l SDL2 -l GL -l GLEW

	
$(OBJECTS): $(SOURCES)
	g++ -c $(SOURCES) -D _DEBUG
				



clean:
	rm *.o Test
