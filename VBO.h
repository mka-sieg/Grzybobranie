#ifndef VBO_CLASS_H
#define VBO_CLASS_H
//from https ://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%204%20-%20Organizing/VBO.h
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include<vector>


class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<glm::vec3>& vertices);
	VBO(std::vector<glm::vec2>& vertices);
	VBO(std::vector<glm::mat4>& mat4s);
	VBO(float vertices[]);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif