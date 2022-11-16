#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
//from https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%206%20-%20Textures/Texture.h
//#include<glad/glad.h>
#include"stb_image.h"
#include <glew.h>
#include <freeglut.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;
	Texture();
	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};
#endif