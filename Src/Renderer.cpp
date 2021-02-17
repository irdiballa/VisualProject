#include "Renderer.h"
#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "ERROR: (" << error << "):\n\tFILE: " << function << " : " << line << std::endl;
		return false;
	}
	return true;
}


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.bind();

	va.bind();
	ib.bindBuffer();

	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));
}
