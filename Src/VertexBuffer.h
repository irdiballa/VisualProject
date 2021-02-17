#pragma once

class VertexBuffer {

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bindBuffer() const;
	void unbindBuffer() const;

private:
	unsigned int rendererID;

};
