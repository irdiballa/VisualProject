#pragma once
/*!
 * Class: Shader
 * Creates and handles the Shader Program obejct
 *
 */
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

//struct for shader source
struct  ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:

	//create the shader object, both vertex and fragment buffer should be in the same file
	//add #vertex before vertex shader starts and #fragment before fragment section
	Shader(const std::string& filename);
	~Shader();

	//use and unbind the shader program
	void bind() const;
	void unbind();

	//set uniforms
	void setUnifrom1i(const std::string& name, int value);
	void setUnifrom1f(const std::string& name, float value);
	void setUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUnifromMat4f(const std::string& name, const glm::mat4 &matrix);

private:
	unsigned int rendererID;
	std::string filePath;
	std::unordered_map<std::string, int> uniformLocationCache;

	//retrieve uniform location from name. name must match uniform name in shader
	int getUniformLocation(const std::string& name);
	
	//functions to read the file, compile and create the shader, called in constructor
	ShaderSource parseShader(const std::string& path);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);


};

