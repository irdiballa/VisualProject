#pragma once
/*!
 * Class: IndexBuffer
 * Creates and handles the Index Buffer object
 *
 */

class IndexBuffer {

public:
	//IndexBuffer : constructor : generate buffer and attach the data
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	// bindBuffer, unbindBuffer : bin and unbind the buffer
	void bindBuffer() const;
	void unbindBuffer() const;

	//getCount : return the number of indices
	inline unsigned int getCount() const{ return indicesCount; };

private:
	unsigned int rendererID;
	unsigned int indicesCount;

};
