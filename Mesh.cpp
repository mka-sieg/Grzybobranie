#include "Mesh.h"
//based on https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%2012%20-%20Mesh%20Class/Mesh.cpp
Mesh::Mesh() {
	///
}
void Mesh::Mesh_start_skybox(float vertices[], unsigned int indices[])
{
	VAO1.VAO_start();
	VAO1.Bind();
	VBO VBO1(vertices);
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0,NULL);
	VAO1.Unbind();
	VBO1.Unbind();
	printf("Mesh loaded \n");
}
void Mesh::Mesh_start_instance(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& normals, Texture& textures,
	unsigned int instancing,
	std::vector <glm::mat4> instanceMatrix
)
{
	Mesh::vertices = vertices;
	Mesh::uv = uv;
	Mesh::normals = normals;
	Mesh::textures = textures;
	Mesh::instancing = instancing;

	Mesh::VAO1.VAO_start();
	Mesh::VAO1.Bind();
	VBO instanceVBO(instanceMatrix);
	VBO VBO1(vertices);
	Mesh::VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0, NULL);
	VBO VBO3(normals);
	Mesh::VAO1.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 0, NULL);
	VBO VBO2(uv);
	Mesh::VAO1.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 0, NULL);
	if (instancing != 1)
	{
		instanceVBO.Bind();
		// Can't link to a mat4 so you need to link four vec4s
		VAO1.LinkAttrib(instanceVBO, 3, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
		VAO1.LinkAttrib(instanceVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
		VAO1.LinkAttrib(instanceVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		VAO1.LinkAttrib(instanceVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		// Makes it so the transform is only switched when drawing the next instance
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
	}
	// Unbind all to prevent accidentally modifying them
	Mesh::VAO1.Unbind();
	VBO1.Unbind();
	VBO3.Unbind();
	VBO2.Unbind();
	instanceVBO.Unbind();
	printf("Instance loaded \n");
}
void Mesh::Mesh_start_obj(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& normals, Texture& textures)
{
	Mesh::vertices = vertices;
	Mesh::uv = uv;
	Mesh::normals = normals;
	Mesh::textures = textures;
	Mesh::VAO1.VAO_start();
	Mesh::VAO1.Bind();
	
	
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices);
	
	
	// Links VBO attributes such as coordinates and colors to VAO
	Mesh::VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0, NULL);
	VBO VBO3(normals);
	Mesh::VAO1.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 0, NULL);
	VBO VBO2(uv);
	Mesh::VAO1.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 0, NULL);
	Mesh::VAO1.Unbind();
	VBO1.Unbind();
	VBO3.Unbind();
	VBO2.Unbind();

	printf("Mesh loaded \n");
}
void Mesh::Mesh_start_obj_light(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& normals)
{
	Mesh::vertices = vertices;
	Mesh::uv = uv;
	Mesh::normals = normals;
	//Mesh::textures = textures;
	Mesh::VAO1.VAO_start();
	Mesh::VAO1.Bind();


	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices);
	
	
	// Links VBO attributes such as coordinates and colors to VAO
	Mesh::VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0, NULL);
	VBO VBO3(normals);
	Mesh::VAO1.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 0, NULL);
	VBO VBO2(uv);
	Mesh::VAO1.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 0, NULL);
	Mesh::VAO1.Unbind();
	VBO1.Unbind();
	VBO3.Unbind();
	VBO2.Unbind();

	printf("Mesh loaded \n");
}

void Mesh::Draw_light
(
	Shader& shader,
	Camera& camera
)
{

	Mesh::VAO1.Bind();
	camera.Matrix(shader, "camMatrix");
	// Draw the actual mesh
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	Mesh::VAO1.Unbind();
}
void Mesh::Draw_skybox
(
	Shader& shader,
	Camera& camera,
	unsigned int cubemapTexture
)
{
	Mesh::VAO1.Bind();
	camera.Matrix(shader, "camMatrix");
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Mesh::VAO1.Unbind();
}
void Mesh::Draw
(
	Shader& shader,
	Camera& camera,
	const char* name,
	int nr,
	unsigned int instancing,
	unsigned int shadowMap
)
{
	Mesh::VAO1.Bind();
	
	//if (nr == 0)glActiveTexture(GL_TEXTURE0);
	if (nr == 1)glActiveTexture(GL_TEXTURE1);
	if (nr == 3)glActiveTexture(GL_TEXTURE3);
	if (nr == 4)glActiveTexture(GL_TEXTURE4);
	if (nr == 5)glActiveTexture(GL_TEXTURE5);
	if (nr == 6)glActiveTexture(GL_TEXTURE6);
	if (nr == 7)glActiveTexture(GL_TEXTURE7);
	if (nr == 8)glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, textures.ID);
	textures.texUnit(shader, name, nr);
	// Bind the Shadow Map
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glUniform1i(glGetUniformLocation(shader.ID, "shadowMap"), 9);
	camera.Matrix(shader, "camMatrix");
	if (instancing == 1) {
		
		// Draw the actual mesh
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		
	}
	else {
		
		// Draw the actual mesh
		glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), instancing);
	}
	Mesh::VAO1.Unbind();
}