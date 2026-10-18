/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "ShaderProgram.h"
#include "Camera.h"

#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

GLuint ShaderProgram::createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
    std::ifstream file(shaderFile);
    if (!file.is_open())
    {
        std::cerr << "Unable to open shader: " << shaderFile << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const char* source = shaderCode.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << shaderFile << ": " << infoLog << std::endl;
        glDeleteShader(shader);
        std::exit(EXIT_FAILURE);
    }

    return shader;
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile, Camera* camera)
    : camera(camera)
{
    GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertexFile);
    GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragmentFile);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader link failed: " << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }

    camera->attach(this);
}

ShaderProgram::~ShaderProgram()
{
    camera->detach(this);
    glDeleteProgram(shaderProgram);
}

void ShaderProgram::updateCamera(const Camera& camera)
{
    setUniform("viewMatrix", camera.getViewMatrix());
    setUniform("projectionMatrix", camera.getProjectionMatrix());
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}

void ShaderProgram::setUniform(const char* name, float value)
{
    use();
    glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::setUniform(const char* name, int value)
{
    use();
    glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z)
{
    use();
    glUniform3f(glGetUniformLocation(shaderProgram, name), x, y, z);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix)
{
    use();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(matrix));
}