#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &rendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bindBuffer();

	const auto& elements = layout.getElements();
	unsigned int offset = 0;

	for ( unsigned int i = 0; i < elements.size(); i++) {

		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(),(const void*)offset));
		
		offset += element.count * VertexBufferStructure::getTypeSize(element.type);
	}
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(rendererID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
