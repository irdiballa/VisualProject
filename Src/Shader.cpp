#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



Shader::Shader(const std::string& filename) :
	filePath(filename), rendererID(0)
{
    ShaderSource source = parseShader(filePath);
    rendererID = createShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader()
{
    glDeleteProgram(rendererID);
}

void Shader::bind() const
{
    GLCall(glUseProgram(rendererID));
}

void Shader::unbind()
{
    GLCall(glUseProgram(0));
}

void Shader::setUnifrom1i(const std::string& name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUnifrom1f(const std::string& name, float value)
{
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUnifromMat4f(const std::string& name, const glm::mat4 & matrix)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string& name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));
    if (location == -1)
        std::cout << "WARNING: uniform (" << name << ") doesnt exist" << std::endl;
    else
        uniformLocationCache[name] = location;

	return location;
}

ShaderSource Shader::parseShader(const std::string& path) {

    std::ifstream stream(path);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {

        if (line.find("#shader") != std::string::npos) {

            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }

    }

    return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "ERROR " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}




