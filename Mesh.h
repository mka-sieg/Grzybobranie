#ifndef MESH_CLASS_H
#define MESH_CLASS_H
//based on https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%2012%20-%20Mesh%20Class/Mesh.h
#include<string>
#include "VBO.h"
#include"VAO.h"
#include"Camera.h"
#include"Texture.h"
// Structure to standardize the vertices used in the meshes

class Mesh
{
public:
	std::vector<glm::vec3> vertices;
	std::vector <GLuint> indices;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	unsigned int instancing;
	Texture textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO1;
	Mesh();
	// Initializes the mesh
	void Mesh_start_skybox(float vertices[], unsigned int indices[]);
	void Mesh_start_obj(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& normals, Texture& textures);
	void Mesh_start_obj_light(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& normals);
	void Mesh_start_instance(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& normals, Texture& textures,
		unsigned int instancing,
		std::vector <glm::mat4> instanceMatrix
	);
	// Draws the mesh
	void Draw
	(
		Shader& shader,
		Camera& camera,
		const char* name,
		int nr,
		unsigned int instancing,
		unsigned int shadowMap
	);
	void Draw_light
	(
		Shader& shader,
		Camera& camera
	);
	void Draw_skybox
	(
		Shader& shader,
		Camera& camera,
		unsigned int cubemapTexture
	);
};
#endif
