#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
// for https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%204%20-%20Organizing/shaderClass.h
#include<string>
#include <glew.h>
#include <freeglut.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	Shader();
	// Constructor that build the Shader Program from 2 different shaders
	void shader_start(const char* vertexFile, const char* fragmentFile);
	void shader_start(const char* vertexFile, const char* fragmentFile, const char* geometryFile);
	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
};

#endif