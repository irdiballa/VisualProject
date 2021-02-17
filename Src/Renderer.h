#pragma once
/*!
 * Class: Cube
 * Draws the objects
 *
 */

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <GL/glew.h>

//Macro to check for opengl error during debug
#define ASSERT(x) if (!(x))  __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	Renderer();
	~Renderer();

	//draw : draw object specified by the va ib and shader
	void draw(const VertexArray& va,const IndexBuffer& ib, const Shader& shader) const;

	//clear framebuffer
	void clear() const;
private:

};



