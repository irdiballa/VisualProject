#pragma once

/*!
 * Class: VertexBufferLayout
 * Creates the vertex buffer layout
 *
 */
#include <vector>
#include "Renderer.h"

//struct for the vertex buffer structure
struct VertexBufferStructure {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getTypeSize(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:			return 4;// sizeof(GLfloat);
		case GL_UNSIGNED_INT:	return 4;// sizeof(GLuint);
		case GL_BYTE:			return 1;// sizeof(GLbyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout() : stride(0) {

	}

	//return stride and a list of VertexBufferStructure
	inline const unsigned int getStride() const{ return stride; };
	inline const std::vector< VertexBufferStructure >& getElements() const{ return Elements; };


	//add new VertexBufferStructure depending on type and calculate stride
	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		stride += count * VertexBufferStructure::getTypeSize(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count) {
		Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		stride += count * VertexBufferStructure::getTypeSize(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count) {
		Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		stride += count * VertexBufferStructure::getTypeSize(GL_UNSIGNED_BYTE);
	}

private:
	std::vector< VertexBufferStructure > Elements;
	unsigned int stride;
};


