/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "ShaderProgram.h"

#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <string>
#include <iterator>
#include <iostream>

GLuint ShaderProgram::createShaderFromFile(
	GLenum shaderType,
	const char* shaderFile
) {
	// Creates an empty shader
	GLuint shaderID = glCreateShader(shaderType);

	if (shaderID == 0)
	{
		std::cout << "Unable to create shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	//Loading the contents of a file into a variable
	std::ifstream file(shaderFile);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << shaderFile << std::endl;
		glDeleteShader(shaderID);
		exit(-1);
	}
	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Set the shader source code
	const char* source = shaderCode.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);

	// Compile the shader source code
	glCompileShader(shaderID);

	// Check specialization/compilation status
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
		std::cout
			<< "Shader failed:\n"
			<< infoLog << std::endl;
		glDeleteShader(shaderID);
		exit(1);
	}
	return shaderID;
}

ShaderProgram::ShaderProgram(
	const char* vertexFile,
	const char* fragmentFile
) {
	// Create and compile the vertex and fragment shaders
	GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertexFile);
	GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragmentFile);

	//Create and link the shader program 
	this->shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
}

void ShaderProgram::use() {
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::setUniform(const char* name, float value)
{
	glUseProgram(shaderProgram);

	GLint location = glGetUniformLocation(shaderProgram, name);

	if (location == -1)
	{
		std::cout << "Uniform variable not found: " << name << std::endl;
		glUseProgram(0);
		return;
	}

	glUniform1f(location, value);

	glUseProgram(0);
}

void ShaderProgram::setUniform(const char* name, float x, float y, float z)
{
	glUseProgram(shaderProgram);

	GLint location = glGetUniformLocation(shaderProgram, name);

	if (location == -1)
	{
		std::cout << "Uniform variable not found: " << name << std::endl;
		glUseProgram(0);
		return;
	}

	glUniform3f(location, x, y, z);

	glUseProgram(0);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	glUseProgram(shaderProgram);

	GLint location = glGetUniformLocation(shaderProgram, name);

	if (location == -1)
	{
		std::cout << "Uniform variable not found: " << name << std::endl;
		glUseProgram(0);
		return;
	}

	glUniform1i(location, value);

	glUseProgram(0);
}

void ShaderProgram::setUniform(
	const char* name,
	const glm::mat4& matrix
)
{
	glUseProgram(shaderProgram);

	GLint location = glGetUniformLocation(
		shaderProgram,
		name
	);

	if (location == -1)
	{
		std::cout
			<< "Uniform variable not found: "
			<< name
			<< std::endl;

		glUseProgram(0);
		return;
	}

	glUniformMatrix4fv(
		location,
		1,
		GL_FALSE,
		glm::value_ptr(matrix)
	);

	glUseProgram(0);
}