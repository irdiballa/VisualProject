#pragma once
/*!
 * Class: Texture
 * Reads , creates and manages the texture
 *
 */
#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	//bind texture to slot or unbind
	void bind(unsigned int slot = 0) const;
	void unbind() const;

	//returns texture sizes
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }


private:
	unsigned int rendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, BPP; 


};

