#include"Model.h"
#include "obj_loader.h"
#include "Other.h"
Model::Model() {
	///
}
void Model::Model_start_skybox(float vertices[], unsigned int indices[], Shader& shader)
{

	shader.Activate();

	cube.Mesh_start_skybox(vertices,indices);

	printf("Skybox loaded \n");
	glUseProgram(0);
}
void Model::Model_start(const char* file, Shader& shader,Model& light,Texture& texture, unsigned int number,int nn, glm::vec3 tempScale)
{
	
	std::vector<glm::vec3> OBJ_vertices;
	std::vector<glm::vec2> OBJ_uvs;
	std::vector<glm::vec3> OBJ_normals;

	loadOBJ(file, OBJ_vertices, OBJ_uvs, OBJ_normals);

	Model::vertices = OBJ_vertices;
	Model::texture = texture;
	//calculations width, height, length of object
	glm::vec3 min = glm::vec3(10000.0, 10000.0, 10000.0);
	glm::vec3 max = glm::vec3(-10000.0, -10000.0, -10000.0);
	for (int i=0; i < OBJ_vertices.size(); i++) {
		if (OBJ_vertices[i].x < min.x) {
			min.x = float(OBJ_vertices[i].x);
		}if(OBJ_vertices[i].x > max.x) {
			max.x = float(OBJ_vertices[i].x);
		}if (OBJ_vertices[i].y < min.y) {
			min.y = OBJ_vertices[i].y;
		}if (OBJ_vertices[i].y > max.y) {
			max.y = OBJ_vertices[i].y;
		}if (OBJ_vertices[i].z < min.z) {
			min.z = OBJ_vertices[i].z;
		}if (OBJ_vertices[i].z > max.z) {
			max.z = OBJ_vertices[i].z;
		}
	}
	d_x = abs(max.x - min.x);
	d_y= abs(max.y - min.y);
	d_z= abs(max.z - min.z);

	shader.Activate();

	if (number == 1) {
		if(nn>1){
		//avoiding collisions of created objects
		for (int ii = 0; ii < nn; ii++) {
			int test = 0;
			int max = 80;
			int min = -80;
			int range = max - min + 1;
			glm::vec3 tempTranslation;
			do {
				tempTranslation = glm::vec3(rand() % range + min, 0.0f, rand() % range + min);
				for (int j = 0; j < num; j++) {
					// collision x-axis?
					bool collisionX = tempTranslation.x + d_x >= PosList[j].x &&
						PosList[j].x + d_x >= tempTranslation.x;
					// collision z-axis?
					bool collisionZ = tempTranslation.z + d_z >= PosList[j].z &&
						PosList[j].z + d_z >= tempTranslation.z;
					// collision only if on both axes
					if (collisionX && collisionZ) {
						test = 0;
						break;
					}
					else {
						test += 1;

					}
					//printf("%d %d \n", test, num);

				}
				

			} while (test != num);
			Model::num += 1;
			Model::PosList.push_back(glm::vec4(tempTranslation,0.0));
			
		}
		//for (int i = 0; i < num; i++) {
			//printf("%f %f %f \n", PosList[i].x, PosList[i].y, PosList[i].z);
		//}
		}
		cube.Mesh_start_obj(OBJ_vertices, OBJ_uvs, OBJ_normals, texture);
	}
	else {

		// Holds all transformations for the asteroids
		std::vector <glm::mat4> instanceMatrix;
		// Creates the cubemap texture object
		for (unsigned int i = 0; i < number; i++)
		{

			// Holds transformations before multiplying them
			glm::vec3 tempTranslation;
			glm::quat tempRotation;
			//glm::vec3 tempScale;
			//avoiding collisions of created objects - instancing
			int test = 0;
			int max = 80;
			int min = -80;
			int range = max - min + 1;
			do {
				tempTranslation = glm::vec3(rand() % range + min, 0.0f, rand() % range + min);
				for (int j = 0; j < num; j++) {
					// collision x-axis?
					bool collisionX = tempTranslation.x + d_x >= PosList[j].x &&
						PosList[j].x + d_x >= tempTranslation.x;
					// collision z-axis?
					bool collisionZ = tempTranslation.z + d_z >= PosList[j].z &&
						PosList[j].z + d_z >= tempTranslation.z;
					// collision only if on both axes
					if (collisionX && collisionZ) {
						test = 0;
						break;
					}
					else {
						test += 1;
						
					}
					//printf("%d %d \n", test, num);
				}
			} while (test != num);
			
			Model::PosList.push_back(glm::vec4(tempTranslation,0.0));
			Model::num += 1;

			// Initialize matrices
			glm::mat4 model = glm::mat4(1.0f);

			// Transform the matrices to their correct form
			model = glm::scale(model, tempScale);
			model = glm::translate(model, tempTranslation);
			

			// Push matrix transformation
			instanceMatrix.push_back(model);
		}
		Model::instancing = number;
		Model::instanceMatrix = instanceMatrix;

		cube.Mesh_start_instance(OBJ_vertices, OBJ_uvs, OBJ_normals, texture, number, instanceMatrix);
	}
	printf("Model loaded \n");
	glUseProgram(0);
}
void Model::Model_light(const char* file, Shader& shader)
{
	std::vector<glm::vec3> OBJ_vertices1;
	std::vector<glm::vec2> OBJ_uvs1;
	std::vector<glm::vec3> OBJ_normals1;
	
	loadOBJ(file, OBJ_vertices1, OBJ_uvs1, OBJ_normals1);

	
	shader.Activate();
	cube.Mesh_start_obj_light(OBJ_vertices1, OBJ_uvs1, OBJ_normals1);

	printf("Light loaded \n");
	glUseProgram(0);
	
}

void Model::Draw_light
(
	Shader& shader,
	Camera& camera,
	glm::vec4 Color,
	glm::mat4 Modell,
	glm::mat4 scale
)
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(scale));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), Color.x, Color.y, Color.z, Color.w);
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	Model::cube.Draw_light(shader, camera);
	glUseProgram(0);
}
void Model::Draw_skybox
(
	Shader& shader,
	Camera& camera,
	glm::mat4 view,
	glm::mat4 projection,
	unsigned int cubemapTexture
)
{
	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, "skybox"), 0);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	Model::cube.Draw_skybox(shader, camera,cubemapTexture);
	glUseProgram(0);
}
void Model::Draw
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

)
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), Color.x, Color.y, Color.z, Color.w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), Poslight0.x, Poslight0.y, Poslight0.z);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos1"), Poslight1.x, Poslight1.y, Poslight1.z);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos2"), Poslight2.x, Poslight2.y, Poslight2.z);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos3"), Poslight3.x, Poslight3.y, Poslight3.z);
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform1i(glGetUniformLocation(shader.ID, "light_type"), light_type);
	glUniform1i(glGetUniformLocation(shader.ID, "light_color"), light_color);
	Model::cube.Draw(shader, camera, name, nr,instancing, shadowMap);
	glUseProgram(0);
}
