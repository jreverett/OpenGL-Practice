#ifndef HELLOSHADERS_H
#define HELLOSHADERS_H

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int helloShaders();

class Shader
{
public:
	// program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		////////////////////////////////////////////////////////////
		// 1. Retrieve the vertex/fragment source code from filepath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close streams
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::LOAD::FILE_COULD_NOT_BE_READ" << std::endl;
		}		

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		////////////////////////////////////////////////////////////
		// 2. Compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILE::VERTEX_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILE::FRAGMENT_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		// shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::LINK::SHADER_PROGRAM_LINK_FAILED\n" << infoLog << std::endl;
		};

		// delete shaders (as they are already linked)
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	};

	////////////////////////////////////////////////////////////
	// 3. Use/activate the shader
	void use() {
		glUseProgram(ID);
	};

	////////////////////////////////////////////////////////////
	// Uniform utility functions
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	};
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	};
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), (float)value);
	};
};

#endif