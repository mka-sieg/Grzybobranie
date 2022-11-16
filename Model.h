#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H


#include"Mesh.h"
#include<math.h>

class Model
{
public:
	std::vector<glm::vec3> vertices;
	Texture texture;
	Mesh cube;
	VAO VAO1;
	float d_x;
	float d_y;
	float d_z;
	//glm::vec3 Pos;
	int num;
	std::vector<glm::vec4> PosList;
	unsigned int instancing;// = instancing;
	std::vector<glm::mat4> instanceMatrix;// = instanceMatrix;
	Model();
	void Model_start(const char* file, Shader& shader, Model& light,Texture& texture, unsigned int number,int nn, glm::vec3 tempScale);
	void Model_light(const char* file, Shader& shader);
	void Model_start_skybox(float vertices[], unsigned int indices[], Shader& shader);

	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::vec4 Color,
		glm::vec3 Poslight0,
		glm::vec3 Poslight1,
		glm::vec3 Poslight2,
		glm::vec3 Poslight3,
		const char* name,
		int nr,
		unsigned int instancing,
		glm::mat4 lightProjection,
		unsigned int shadowMap,
		int light_type,
		int light_color
	);
	void Draw_light
	(
		Shader& shader,
		Camera& camera,
		glm::vec4 Color,
		glm::mat4 Modell,
		glm::mat4 scale
	);
	void Draw_skybox
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 view,
		glm::mat4 projection,
		unsigned int cubemapTexture
	);
};
#endif
