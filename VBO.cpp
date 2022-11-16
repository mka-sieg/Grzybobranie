#include"VBO.h"
// Constructor that generates a Vertex Buffer Object and links it to vertices
//from https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%204%20-%20Organizing/VBO.cpp
VBO::VBO(std::vector<glm::vec3>& v)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, v.size()  * sizeof(glm::vec3), &v[0], GL_STATIC_DRAW);
}
VBO::VBO(std::vector<glm::vec2>& v2)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, v2.size() * sizeof(glm::vec2), &v2[0], GL_STATIC_DRAW);
}
VBO::VBO(float vertices[])
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}
VBO::VBO(std::vector<glm::mat4>& mat4s)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, mat4s.size()  * sizeof(glm::mat4), &mat4s[0], GL_STATIC_DRAW);
}
// Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}