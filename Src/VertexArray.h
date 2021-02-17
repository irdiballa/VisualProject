#pragma once
/*!
 * Class: VertexArray
 * Creates the Vertex array state for rendering
 *
 */
#include "VertexBuffer.h"


class VertexBufferLayout;

class VertexArray {

public:
	VertexArray();
	~VertexArray();

	//add vertex buffer and the corresponding layout
	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	//bind and unbind the vertex array
	void bind() const;
	void unbind() const;

private:
	unsigned int rendererID;

};
