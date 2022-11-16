#include <glew.h>
#include <freeglut.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <cmath>
#include <stdlib.h>
#include <time.h>

///#include<math.h>
#include <vector>
#include <list>
#include <string>
#include "stb_image.h"
#include "Vertices.h"
#include "Positions.h"
#include "Camera.h"
#include "shaderClass.h"
#include "Model.h"
#include "shader_stuff.h"
#include "text-ft.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"
using namespace std;
const int num_npc = 2;

glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
float gamma = 2.2f;
int grzyb_znaleziony = 0;
unsigned int samples = 8;
float r = 0; // controls rotation of object - dogs
unsigned int cubemapTexture;

int interaction=10;
int reaction = 10;
int npc_list[num_npc];
Npc npc0(1,1,1,1), npc1(1, 0, 0, 0), npc2(1, 0, 0, 0);
Model model1, light, grass, skybox1, model2, model3, model4,model5,model6, model7, model8,model9,model10,model11,model12, model4a, model4b;
Shader shaderProgram, lightShader, grassProgram, skyboxShader, asteroidShader, asteroidShader2;
Camera camera;
Shader framebufferProgram, shadowMapProgram;
CGround myGround;
CPlayer myPlayer;
unsigned int RBO;
unsigned int rectVAO, rectVBO;
unsigned int framebufferTexture;
unsigned int postProcessingFBO;
unsigned int postProcessingTexture;
unsigned int FBO;
unsigned int shadowMapWidth = 2024, shadowMapHeight = 2024;
unsigned int shadowMap;
unsigned int shadowMapFBO;
float angle = 0.0;
float delta_angle = 0.0;
// Camera 
glm::vec3 position1 = glm::vec3(-4.0f, 3.0f, 4.0f);
glm::vec3 orientation = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
float rotation = 0.0f;
float sensitivity = 4.0f;
float speed = 0.05f;
GLfloat _scene_rotate_x = 0.0f;
GLfloat _scene_rotate_y = 0.0f;
GLfloat _scene_translate_x = 0.0f;
GLfloat _scene_translate_y = 0.0f;
GLfloat _scene_translate_z = 0.0f;
int _mouse_buttonState = GLUT_UP;
int _mouse_buttonX, _mouse_buttonY;
//light controls - menu
int light_type = 1;
int light_col = 0;
int light_mode = 1;
float OffX; 
float OffZ;
double prevTime = clock();

clock_t last_T = 0;

const unsigned int width = 800;
const unsigned int height = 800;

glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Pos6 = glm::vec3(2.0f, 0.0f, 2.0f);

glm::vec3 Pos7 = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec3 Pos8 = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec3 Pos9 = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec3 Pos10 = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec3 Pos11 = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec3 Pos12 = glm::vec3(2.0f, 2.0f, 2.0f);

glm::vec3 scale11 = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 scale22 = glm::vec3(0.1f, 0.1f, 0.1f);
glm::vec3 scale33 = glm::vec3(20.0f, 20.0f, 20.0f);
glm::vec3 scale44 = glm::vec3(0.5f, 0.5f, 0.5f);

glm::mat4 Modell = glm::mat4(1.0f);
glm::mat4 Modell4 = glm::mat4(1.0f);
glm::mat4 Modell5 = glm::mat4(1.0f);

// --------------------------------------------------------------
//Rysowanie
// --------------------------------------------------------------
void DisplayScene()
{
	glm::mat4 scalelight = glm::mat4(1.0f);
	glm::vec4 Colorlight = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 Poslight = glm::vec3(1.0f, 2.0f, 1.0f);
	glm::vec3 Poslight0 = glm::vec3(1.0f, 2.0f, 1.0f);
	glm::vec3 Poslight1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Poslight2 = glm::vec3(5.0f, 2.0f, 1.0f);
	glm::vec3 Poslight3 = glm::vec3(1.0f, 2.0f, 5.0f);
	// Matrices needed for the light's perspective 
	glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
	glm::mat4 lightView = glm::lookAt(20.0f * Poslight0, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightProjection = orthgonalProjection * lightView;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 Modellight = glm::mat4(1.0f);
	Modellight = glm::translate(Modellight, Poslight0);

	//opcje po zmianie w menu dzien/noc
	if (light_mode == 1) {
		Colorlight = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		//Colorlight = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		
	}
	else {
		Colorlight = glm::vec4(0.25f, 0.25f, 0.25f, 0.25f);
		
	}
	
	glEnable(GL_DEPTH_TEST);

	//---------------------------------------------------------
	// Shadow Maps
	// -------------------------------------------------------
	// Preparations for the Shadow Map
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);


	//ground
	shadowMapProgram.Activate();
	model1.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model1.vertices.size());
	model1.VAO1.Unbind();
	

	model2.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model2.vertices.size());
	model2.VAO1.Unbind();

	grass.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, grass.vertices.size());
	grass.VAO1.Unbind();

	model4.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model4.vertices.size());
	model4.VAO1.Unbind();

	model5.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model5.vertices.size());
	model5.VAO1.Unbind();

	model6.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model6.vertices.size());
	model6.VAO1.Unbind();

	model7.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model7.vertices.size());
	model7.VAO1.Unbind();

	model8.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model8.vertices.size());
	model8.VAO1.Unbind();

	model9.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model9.vertices.size());
	model9.VAO1.Unbind();

	model10.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model10.vertices.size());
	model10.VAO1.Unbind();

	model11.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model11.vertices.size());
	model11.VAO1.Unbind();

	model12.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model12.vertices.size());
	model12.VAO1.Unbind();

	model4a.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model4a.vertices.size());
	model4a.VAO1.Unbind();

	model4b.VAO1.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
	glDrawArrays(GL_TRIANGLES, 0, model4b.vertices.size());
	model4b.VAO1.Unbind();

	glUseProgram(0);
	
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//---------------------------------------------------------
	// Camera
	// -------------------------------------------------------
	//camera.updateMatrix(45.0f, 0.1f, 100.0f);
	
	//camera.cameraMatrix= glm::mat4(1.0f);
	//orientation.x = cos(glm::radians(myPlayer.Direction.x)) * cos(glm::radians(camera.pitch));
	//orientation.y = sin(glm::radians(camera.pitch));
	//orientation.z = sin(glm::radians(myPlayer.Direction.z)) * cos(glm::radians(camera.pitch));
	camera.update(position1, orientation, up);
	// Makes camera look in the right direction from the right position
	view = glm::lookAt(camera.Position + glm::vec3(0.0f, 3.0f, 0.0f)+ orientation, myPlayer.Position + orientation + glm::vec3(0.0f, 1.0f, 0.0f), camera.Up);
	
	//view = glm::lookAt(Position, myPlayer.Position, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

	// Sets new camera matrix
	camera.cameraMatrix =  projection * view;
	//camera.cameraMatrix = glm::rotate(camera.cameraMatrix, orientation.x, glm::vec3(1.0, 0.0, 0.0));
	//camera.cameraMatrix = glm::rotate(camera.cameraMatrix, orientation.z, glm::vec3(0.0, 0.0, 1.0));
	//---------------------------------------------------------
	// Render Screen
	// -------------------------------------------------------
	glEnable(GL_DEPTH_TEST);
	shaderProgram.Activate();
	//ziemia
	Modell = glm::translate(Modell, Pos);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell));
	model1.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0",1, 1, lightProjection, shadowMap,light_type, light_col);
	//drzewa
	model2.Draw(asteroidShader, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 6, 25, lightProjection, shadowMap, light_type, light_col);

	
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	//kwiaty
	grass.Draw(asteroidShader2, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse1", 4, 25, lightProjection, shadowMap, light_type, light_col);
	
	//grzyby 1
	for (int i = 0; i < model4.num; i++) {
		shaderProgram.Activate();
		Modell4 = glm::mat4(1.0f);
		Modell4 = glm::translate(Modell4, glm::vec3(model4.PosList[i].x, model4.PosList[i].y, model4.PosList[i].z));
		Modell4 = glm::scale(Modell4, scale22);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell4));
		//for (int j = 0; j < model4.PosList.size(); j++) {
		// TODO: spr czy juz jest ten grzyb znaleziony jak to kolizje
		if(!(model4.PosList[i].w)){
				// collision x-axis?
			bool collisionX = myPlayer.Position.x + 1.0 >= model4.PosList[i].x &&
			model4.PosList[i].x + 1.0 >= myPlayer.Position.x;
				// collision z-axis?
			bool collisionZ = myPlayer.Position.z + 1.0 >= model4.PosList[i].z &&
			model4.PosList[i].z + 1.0 >= myPlayer.Position.z;
				// collision only if on both axes
			if (collisionX && collisionZ) {
				//test = 0;
				std::cout << "Kolizja" << std::endl;
				std::cout << myPlayer.Position.x << " "<< model4.PosList[i].x<<std::endl;
				std::cout << myPlayer.Position.z << " " << model4.PosList[i].z << std::endl;
					//break;
				grzyb_znaleziony += 1;
				model4.PosList[i].w = 1.0;
			}
			else {
				model4.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 5, 1, lightProjection, shadowMap, light_type, light_col);

			}

		}
	}
	
	//grzyby 2
	for (int i = 0; i < model4a.num; i++) {
		shaderProgram.Activate();
		glm::mat4 Modell4a = glm::mat4(1.0f);
		Modell4a = glm::translate(Modell4a, glm::vec3(model4a.PosList[i].x, model4a.PosList[i].y, model4a.PosList[i].z));
		Modell4a = glm::scale(Modell4a, scale22);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell4a));
		//for (int j = 0; j < model4.PosList.size(); j++) {
		// TODO: spr czy juz jest ten grzyb znaleziony jak to kolizje
		if (!(model4a.PosList[i].w)) {
			// collision x-axis?
			bool collisionX = myPlayer.Position.x + 1.0 >= model4a.PosList[i].x &&
				model4a.PosList[i].x + 1.0 >= myPlayer.Position.x;
			// collision z-axis?
			bool collisionZ = myPlayer.Position.z + 1.0 >= model4a.PosList[i].z &&
				model4a.PosList[i].z + 1.0 >= myPlayer.Position.z;
			// collision only if on both axes
			if (collisionX && collisionZ) {
				//test = 0;
				std::cout << "Kolizja" << std::endl;
				std::cout << myPlayer.Position.x << " " << model4a.PosList[i].x << std::endl;
				std::cout << myPlayer.Position.z << " " << model4a.PosList[i].z << std::endl;
				//break;
				grzyb_znaleziony += 1;
				model4a.PosList[i].w = 1.0;
			}
			else {
				model4a.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 5, 1, lightProjection, shadowMap, light_type, light_col);

			}

		}
	}

	//grzyby 3
	for (int i = 0; i < model4b.num; i++) {
		shaderProgram.Activate();
		glm::mat4 Modell4b = glm::mat4(1.0f);
		Modell4b = glm::translate(Modell4b, glm::vec3(model4b.PosList[i].x, model4b.PosList[i].y, model4b.PosList[i].z));
		Modell4b = glm::scale(Modell4b, scale22);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell4b));
		//for (int j = 0; j < model4.PosList.size(); j++) {
		// TODO: spr czy juz jest ten grzyb znaleziony jak to kolizje
		if (!(model4b.PosList[i].w)) {
			// collision x-axis?
			bool collisionX = myPlayer.Position.x + 1.0 >= model4b.PosList[i].x &&
				model4b.PosList[i].x + 1.0 >= myPlayer.Position.x;
			// collision z-axis?
			bool collisionZ = myPlayer.Position.z + 1.0 >= model4b.PosList[i].z &&
				model4b.PosList[i].z + 1.0 >= myPlayer.Position.z;
			// collision only if on both axes
			if (collisionX && collisionZ) {
				//test = 0;
				std::cout << "Kolizja" << std::endl;
				std::cout << myPlayer.Position.x << " " << model4b.PosList[i].x << std::endl;
				std::cout << myPlayer.Position.z << " " << model4b.PosList[i].z << std::endl;
				//break;
				grzyb_znaleziony -= 1;
				model4b.PosList[i].w = 1.0;
			}
			else {
				model4b.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 5, 1, lightProjection, shadowMap, light_type, light_col);

			}

		}
	}

	r += 10.0;
	//pieski
	for (int i = 0; i < model5.num; i++) {
		shaderProgram.Activate();
		Modell5 = glm::mat4(1.0f);
		Modell5 = glm::translate(Modell5, glm::vec3(model5.PosList[i].x, model5.PosList[i].y, model5.PosList[i].z));
		Modell5 = glm::rotate(Modell5, glm::radians(r), glm::vec3(0.0f, -1.0f, 0.0f));
		Modell5 = glm::scale(Modell5, scale33);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell5));
		model5.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 7, 1, lightProjection, shadowMap, light_type,light_col);
	}
	//npc 1
	shaderProgram.Activate();
	glm::mat4 Modell6 = glm::mat4(1.0f);
	Modell6 = glm::translate(Modell6, Pos6);
	Modell6 = glm::scale(Modell6, glm::vec3(0.03f, 0.03f, 0.03f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell6));
	//if (!(model6.PosList[0].w)) {
		// collision x-axis?
		bool collisionX = myPlayer.Position.x + 2.0 >= Pos6.x &&
			Pos6.x + 2.0 >= myPlayer.Position.x;
		// collision z-axis?
		bool collisionZ = myPlayer.Position.z + 2.0 >= Pos6.z &&
			Pos6.z + 2.0 >= myPlayer.Position.z;
		// collision only if on both axes
		if (collisionX && collisionZ) {
			//test = 0;
			std::cout << "Kolizja" << std::endl;
			//std::cout << myPlayer.Position.x << " " << model4.PosList[i].x << std::endl;
			//std::cout << myPlayer.Position.z << " " << model4.PosList[i].z << std::endl;
			//break;
			//grzyb_znaleziony += 1;
			npc_list[0] = 1;
		}
		else {
			npc_list[0] = 0;
			interaction = 10;
			reaction = 10;
			//model4.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 5, 1, lightProjection, shadowMap, light_type, light_col);

		}
	//}

	
	model6.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 1, 1, lightProjection, shadowMap, light_type, light_col);

	//npc 2
	shaderProgram.Activate();
	glm::mat4 Modell7 = glm::mat4(1.0f);
	Modell7 = glm::translate(Modell7, Pos7);
	Modell7 = glm::scale(Modell7, scale22);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(Modell7));
	//if (!(model6.PosList[0].w)) {
		// collision x-axis?
	collisionX = myPlayer.Position.x + 2.0 >= Pos7.x &&
		Pos7.x + 2.0 >= myPlayer.Position.x;
	// collision z-axis?
	collisionZ = myPlayer.Position.z + 2.0 >= Pos7.z &&
		Pos7.z + 2.0 >= myPlayer.Position.z;
	// collision only if on both axes
	if (collisionX && collisionZ) {
		//test = 0;
		std::cout << "Kolizja" << std::endl;
		//std::cout << myPlayer.Position.x << " " << model4.PosList[i].x << std::endl;
		//std::cout << myPlayer.Position.z << " " << model4.PosList[i].z << std::endl;
		//break;
		//grzyb_znaleziony += 1;
		npc_list[0] = 1;
	}
	else {
		npc_list[0] = 0;
		interaction = 10;
		reaction = 10;
		//model4.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 5, 1, lightProjection, shadowMap, light_type, light_col);

	}
	//}


	model7.Draw(shaderProgram, camera, Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, "diffuse0", 1, 1, lightProjection, shadowMap, light_type, light_col);

	//tekst
	std::string tekst = "Znalezione grzyby:  " + std::to_string(grzyb_znaleziony);
	RenderText("ESC - Exit", 0, 0, 0.5f, glm::vec3(1.0, 0.0f, 0.0f));
	RenderText(tekst, 0.0f, 300.0f, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));
	float p = 40.f;
	if (interaction == 0 && npc_list[0] == 1 && npc0.nr<1) {
		if (npc0.a[0]) {
			RenderText("0: - Hello", 75.0f, p, 0.3f, glm::vec3(0.75, 0.75f, 0.25f));
			p -= 10.0f;
		}
		if (npc0.a[1]) {
			RenderText("1: - How are you? I can't find any mushrooms.", 75.0f, p, 0.3f, glm::vec3(0.75, 0.75f, 0.25f));
			p -= 10.0f;
		}
		if (npc0.a[2]) {
			RenderText("2: - Any luck finding mushrooms?", 75.0f, p, 0.3f, glm::vec3(0.75, 0.75f, 0.25f));
			p -= 10.0f;
		}
		
	}

	if (reaction < 10 && npc_list[0] == 1) {
		if (reaction==0) {
			RenderText("- Hello. What a good day for a mushroom picking...", 75.0f, p, 0.3f, glm::vec3(0.0, 0.75f, 0.25f));
			//RenderText("2: Evil", 75.0f, p, 0.3f, glm::vec3(0.75, 0.75f, 0.25f));
			//p -= 10.0f;
			//Sleep(5000);
			interaction = 10;
		}
		else if (reaction == 1) {
			RenderText("- I found a lot of mushrooms. Maybe you want one?", 75.0f, p, 0.3f, glm::vec3(0.0, 0.75f, 0.25f));
			p -= 10.0f;
			RenderText("- Yeah! Thanks!", 75.0f, p, 0.3f, glm::vec3(0.75, 0.75f, 0.25f));	
			if (npc0.nr < 1) {
				grzyb_znaleziony += 1;
			}
			//Sleep(5000);
			interaction = 10;
			//p -= 10.0f;
		}
		else if (reaction == 2) {
			if (grzyb_znaleziony == 0) {
				RenderText("- Ty biedaku. Nie masz nawet jednego grzyba.", 75.0f, p, 0.3f, glm::vec3(0.75, 0.75f, 0.25f));
				interaction = 10;
			}
			else {
				RenderText("- Oh, wow can I see that mushroom ...now it's mine....byeee", 75.0f, p, 0.3f, glm::vec3(0.0, 0.75f, 0.25f));
				p -= 10.0f;
				RenderText("- Hey!! That is not yours!!!", 75.0f, p, 0.3f, glm::vec3(0.75, 0.75f, 0.25f));
				
				if (npc0.nr < 1) {
					grzyb_znaleziony -= 1;
					interaction = 10;
				}
			}
			//p -= 10.0f;
			//Sleep(5000);
			//reaction = 10;
		}
		npc0.nr += 1;
	}
	
	myPlayer.Draw(Colorlight, Poslight0, Poslight1, Poslight2, Poslight3, camera, glm::mat4(1.0), shaderProgram, light_type, light_col);

	//light.Draw_light(lightShader, camera, Colorlight, Modellight, scalelight);

	//---------------------------------------------------------
	// Skybox
	// -------------------------------------------------------
	glDepthMask(GL_FALSE);
	glEnable(GL_DEPTH_CLAMP);
	glDepthFunc(GL_LEQUAL);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.5f, 500.0f);
	view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
	skybox1.Draw_skybox(skyboxShader, camera, view, projection, cubemapTexture);
	
	glDepthMask(GL_TRUE);

	glDisable(GL_DEPTH_CLAMP);
	glEnable(GL_CULL_FACE);
	glutSwapBuffers();

}
void Animation() {
	
	clock_t now_T = clock();
	if (now_T - last_T > 100) {
		glutPostRedisplay();
		last_T = now_T;
	}
}


void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}
// --------------------------------------------------------------
//Inicjalizacja
// --------------------------------------------------------------
void Inicialize() {
	// --------------------------------------------------------------
	// Texture data
	// --------------------------------------------------------------
	Texture texture("Textures/222.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture texture2("Textures/flower32bit.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture texture3("Textures/Mushroom_1_BaseColor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture texture4("Textures/lego.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture texture5("Textures/UV_mushroom.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture texture6("Textures/Albedo_1.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture texture7("Textures/Shiba_DIF01.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture texture8("Textures/Finn.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture texture9("Textures/Default_baseColor.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE);
	
	InitText("arial.ttf", 36);
	srand(time(NULL));
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	camera.Camera_start(width, height, glm::vec3(0.0f, 0.0f, 0.0f));
	// --------------------------------------------------------------
	// Shaders
	// --------------------------------------------------------------
	

	shaderProgram.shader_start("Shaders/default.vert", "Shaders/lights.frag");
	asteroidShader.shader_start("Shaders/asteroid.vert", "Shaders/lights.frag");
	grassProgram.shader_start("Shaders/default.vert", "Shaders/grass.frag");
	asteroidShader2.shader_start("Shaders/asteroid.vert", "Shaders/grass.frag");
	framebufferProgram.shader_start("Shaders/framebuffer.vert", "Shaders/framebuffer.frag");
	shadowMapProgram.shader_start("Shaders/shadowMap.vert", "Shaders/shadowMap.frag");
	lightShader.shader_start("Shaders/light.vert", "Shaders/light.frag");
	skyboxShader.shader_start("Shaders/skybox.vert", "Shaders/skybox.frag");

	//pirate, untitled1,finn, mush_gols, mush1111,mush2, Argise_The_Green_Alien
	// --------------------------------------------------------------
	// Modele
	// --------------------------------------------------------------
	light.Model_light("OBJ/cube.obj", lightShader);
	grass.Model_start("OBJ/flower.obj", asteroidShader2, light, texture2, 25, 1, scale11);
	model1.Model_start("OBJ/ground-large.obj", shaderProgram,light,texture,1,1, scale11);
	model2.Model_start("OBJ/tree_12.obj", asteroidShader, light, texture6, 25,1, scale11);
	//model4.Model_start("OBJ/mush1.obj", asteroidShader, light, texture3, 10,1);
	model4.Model_start("OBJ/mush1.obj", shaderProgram, light, texture9, 1,25, scale22);
	model4a.Model_start("OBJ/mush.obj", shaderProgram, light, texture5, 1, 25, scale22);
	model4b.Model_start("OBJ/mush_gold.obj", shaderProgram, light, texture6, 1, 25, scale22);

	model7.Model_start("OBJ/shiba_dog.obj", shaderProgram, light, texture7, 1, 1,scale33);
	skybox1.Model_start_skybox(skyboxVertices, skyboxIndices, skyboxShader);
	// All the faces of the cubemap (make sure they are in this exact order)
	model3.Model_start("OBJ/lego.obj", shaderProgram, light, texture4, 1,1, scale11);

	//model6.Model_start("OBJ/pirate.obj", shaderProgram, light, texture3, 1, 1, scale11);
	model6.Model_start("OBJ/finn.obj", shaderProgram, light, texture8, 1, 1, glm::vec3(0.01f, 0.01f, 0.01f));
	//model8.Model_start("OBJ/untitled1.obj", shaderProgram, light, texture3, 1, 1, scale11);
	//model10.Model_start("OBJ/mush1111.obj", shaderProgram, light, texture3, 1, 1, scale11);
	//model11.Model_start("OBJ/mush2.obj", shaderProgram, light, texture3, 1, 1, scale11);
	//model8.Model_start("OBJ/Argise_The_Green_Alien.obj", shaderProgram, light, texture3, 1, 1, scale44);
	
	myGround.Init(model1.vertices); //inicjalizacja podłoża
	//inicjalizacja gracza
	myPlayer.Init(model3.texture.ID, model3.cube.VAO1.ID, model3.vertices.size(), &myGround, glm::vec3(0.0, 0.0, 0.0));

	//skybox inicjalizacja
	const char* facesCubemap[6] =
	{
		"skybox/px.png",
		"skybox/nx.png",
		"skybox/py.png",
		"skybox/ny.png",
		"skybox/pz.png",
		"skybox/nz.png"

	};
	
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width1, height1, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i], &width1, &height1, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA,
				width1,
				height1,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				data
			);
			printf("Loaded \n");
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}


	// 1. Stworzenie obiektu tekstury
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// 2. Stworzenie obiektu ramki bufora jedynie z buforem glebokosci
	// Skladowa koloru nie jest nam potrzebna
	glGenFramebuffers(1, &shadowMapFBO);

	// 3. Dolaczanie tekstury do ramki bufora
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	


	std::cout << "Done init" << std::endl;
}
void welcomeDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	RenderText("Grzybobranie", 140.0f, 400.f, 1.0f, glm::vec3(0.75, 0.75f, 0.25f));
	RenderText("W lesie znajdziesz wiele rodzajow grzybow.", 80.0f, 330.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	RenderText("Jednak nie wszystkie warto zbierac.", 80.0f, 310.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	RenderText("Powodzenia!", 80.0f, 290.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	//RenderText("⸙𓍊𓋼", 175.0f, 200.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	RenderText("Sterowanie: ", 50.0f, 250.f, 0.5f, glm::vec3(0.75, 0.5f, 0.5f));
	RenderText("Zebranie grzyba - przejdz przez grzyba", 80.0f, 230.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	RenderText("Rozmowa z postaciami - kliknij E", 80.0f, 210.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	RenderText("Wybranie opcji odpowiedzi - kliknij 0,1,2,3", 80.0f, 190.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	RenderText("Ruch ludzika -  WASD", 80.0f, 170.f, 0.5f, glm::vec3(0.75, 0.5f, 0.25f));
	RenderText("Press X to start the game", 175.0f,5.0f, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));
	glutSwapBuffers();
}

// --------------------------------------------------------------
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{

	case GLUT_KEY_LEFT:
		position1 += speed * -glm::normalize(glm::cross(orientation, up));
		angle += 0.1;
		delta_angle = -0.1;
		myPlayer.Rotate(0.1);
		break;

	case GLUT_KEY_RIGHT:
		position1 += speed * glm::normalize(glm::cross(orientation, up));
		angle += -0.1;
		delta_angle = 0.1;
		myPlayer.Rotate(-0.1);
		break;

	case GLUT_KEY_UP:
		position1 += speed * orientation;
		myPlayer.Move(0.1);
		
		break;

	case GLUT_KEY_DOWN:
		position1 += speed * -orientation;
		myPlayer.Move(-0.1);
		break;

	}

	glutPostRedisplay();
}


// --------------------------------------------------------------
void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{

		_mouse_buttonState = state;


		if (state == GLUT_DOWN)
		{
			_mouse_buttonX = x;
			_mouse_buttonY = y;
			
		}
		if (state == GLUT_UP) {
			_scene_rotate_x = 0.0;
			_scene_rotate_y = 0.0;
			glutPostRedisplay();
		}
	}
}

// --------------------------------------------------------------
void MouseMotion(int x, int y)
{
	if (_mouse_buttonState == GLUT_DOWN)
	{
		_scene_rotate_y += sensitivity * (float)(_mouse_buttonX-x) / height;
		_mouse_buttonX = x;
		_scene_rotate_x -= sensitivity * (float)(_mouse_buttonY-y ) / width;
		_mouse_buttonY = y;
		
		orientation = glm::rotate(orientation, glm::radians(-_scene_rotate_x), glm::normalize(glm::cross(orientation, up)));
		orientation = glm::rotate(orientation, glm::radians(-_scene_rotate_y), up);
		glutPostRedisplay();
	}
}

// --------------------------------------------------------------
void MouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		// Zoom in
		_scene_translate_z += 0.5f;
	}
	else
	{
		// Zoom out
		_scene_translate_z -= 0.5f;
	}

	glutPostRedisplay(); 
}

void Keyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case 27: //ESC
		exit(0);
		break;

	case 'w':
		
		position1 += myPlayer.Direction * 0.05f;
		myPlayer.Move(0.1);
		
		break;

	case 's':
		position1 += myPlayer.Direction * -0.05f;
		myPlayer.Move(-0.1);
		break;

	case 'd':
		angle += -0.1;
		delta_angle = 0.1;
		myPlayer.Rotate(-0.1);
		//OffX = (float)( sin(glm::radians(delta_angle)));
		//OffZ = (float)(cos(glm::radians(delta_angle)));
		//orientation.x = myPlayer.Direction.x * OffX;
		//orientation.z = myPlayer.Direction.z * OffZ;
		//glm::fquat rot = glm::normalize(glm::angleAxis(delta_angle, up));
		//orientation = orientation * rot;
		
		break;

	case 'a':
		angle += 0.1;
		delta_angle = -0.1;
		myPlayer.Rotate(0.1);
		//OffX = (float)(sin(glm::radians(delta_angle)));
		//OffZ = (float)(cos(glm::radians(delta_angle)));
		//orientation.x = myPlayer.Direction.x * OffX;
		//orientation.z = myPlayer.Direction.z * OffZ
		
		break;
	case 'i':
		position1 += speed * up;
		break;
	case 'o':
		position1 += speed * -up;
		break;
	case 'x':
		glutDisplayFunc(DisplayScene);
		break;
	case 'e':
		for (int i = 0; i < num_npc; i++) {
			if (npc_list[i]==1) {
				if (i == 0) {
					interaction =0;
				}if (i == 1) {
					interaction =1;
				}if (i == 2) {
					interaction = 2;
				}
			}
		}	
		break;
	case '0':
		reaction = 0;
		break;
	case '1':
		reaction = 1;
		break;
	case '2':
		reaction = 2;
		break;
	case '3':
		reaction = 3;
		break;
	}
	/*float horizontalPosition = camera.calculateHorizontalDistance();
	float verticalPosition = camera.calculateVerticalDistance();
	float theta = angle + camera.angle_around_player;
	float OffsetX = (float)(horizontalPosition * sin(glm::radians(theta)));
	float OffsetZ = (float)(horizontalPosition * cos(glm::radians(theta)));
	position1.x = myPlayer.Position.x - OffsetX;
	position1.z = myPlayer.Position.z - OffsetZ;
	position1.y = myPlayer.Position.y + verticalPosition;*/
	
	//orientation = glm::rotate(orientation, glm::radians(180 - myPlayer.Direction.x), glm::normalize(glm::cross(orientation, up)));
	//orientation = glm::rotate(orientation, glm::radians(180 - myPlayer.Direction.y), up);
	//orientation.x = myPlayer.Direction.x + camera.angle_around_player;
	//orientation.z = myPlayer.Direction.z + camera.angle_around_player;
	///up= 180 - myPlayer.Direction.y + camera.angle_around_player;
	glutPostRedisplay();
	
}

void Menu(int value)
{
	switch (value)
	{
	case 1:
		printf("Dzien\n");
		light_mode = 1;
		break;
	case 2:
		printf("Noc\n");
		light_mode = 0;
		break;
	case 3:
		printf("Direct light\n");
		light_type = 1;
		break;
	case 4:
		printf("Point light\n");
		light_type = 2;
		break;
	case 5:
		printf("Spotlight\n");
		light_type = 3;
		break;
	case 6:
		printf("Czerwone\n");
		light_col = 1;
		break;
	case 7:
		printf("Niebieskie\n");
		light_col = 2;
		break;
	case 8:
		printf("Zielone\n");
		light_col = 3;
		break;
	default:
		printf("Wybrano %d \n", value);
	}
}
int main(int argc, char* argv[])
{
	// GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Grzybobranie");


	glutDisplayFunc(welcomeDisplay);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutMouseWheelFunc(MouseWheel);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);

	// GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("GLEW Error\n");
		exit(1);
	}

	// OpenGL
	if (!GLEW_VERSION_3_2)
	{
		printf("Brak OpenGL 3.2!\n");
		exit(1);
	}
	// Utworzenie podmenu
	int podmenuA = glutCreateMenu(Menu);
	glutAddMenuEntry("Dzien", 1);
	glutAddMenuEntry("Noc", 2);

	// Utworzenie podmenu
	int podmenuB = glutCreateMenu(Menu);
	glutAddMenuEntry("Direct", 3);
	glutAddMenuEntry("Point", 4);
	glutAddMenuEntry("Spotlight", 5);

	// Utworzenie podmenu
	int podmenuC = glutCreateMenu(Menu);
	glutAddMenuEntry("Czerwone", 6);
	glutAddMenuEntry("Niebieskie", 7);
	glutAddMenuEntry("Zielone", 8);
	// Utworzenie glownego menu kontekstowego
	glutCreateMenu(Menu);

	//glutAddMenuEntry("Pozycja 5", 5);
	glutAddSubMenu("Pora dnia", podmenuA);
	glutAddSubMenu("Typ swiatla", podmenuB);
	glutAddSubMenu("Kolorowe swiatla", podmenuC);
	// Przypisanie klawisza myszy uruchamiajacego menu
	// GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, and GLUT_RIGHT_BUTTON.
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	Inicialize();
	glutIdleFunc(Animation);
	glutMainLoop();
	shaderProgram.Delete();
	//glDeleteFramebuffers(1, &FBO);
	//glDeleteFramebuffers(1, &postProcessingFBO);
	lightShader.Delete();
	skyboxShader.Delete();

	return 0;
}