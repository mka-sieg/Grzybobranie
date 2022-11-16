#pragma once
//fixed positions for some objects - not used temporary
#include <vector>
#include <glew.h>
#include <freeglut.h>

std::vector <glm::vec3> Pos2;
std::vector <glm::vec3> Pos3;

void Init_pos2(std::vector <glm::vec3> &Pos2) {
	Pos2.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	Pos2.push_back(glm::vec3(10.0f, 10.0f, 50.0f));
	Pos2.push_back(glm::vec3(-50.0f, 4.0f, -2.0f));
	Pos2.push_back(glm::vec3(20.0f, 1.0f, 15.0f));
	Pos2.push_back(glm::vec3(-25.0f, 1.0f, -15.0f));
	Pos2.push_back(glm::vec3(-50.0f, 1.0f, -35.0f));
	Pos2.push_back(glm::vec3(-100.0f, 1.0f, 20.0f));
	Pos2.push_back(glm::vec3(15.0f, 1.0f, -80.0f));
	Pos2.push_back(glm::vec3(-50.0f, 10.0f, -120.0f));
	Pos2.push_back(glm::vec3(200.0f, 1.0f, -200.0f));
}
void Init_pos3(std::vector <glm::vec3>& Pos3) {
	Pos3.push_back(glm::vec3(5.0f, 1.0f, 2.0f));
	Pos3.push_back(glm::vec3(15.0f, 1.0f, 75.0f));
	Pos3.push_back(glm::vec3(-30.0f, 1.0f, -15.0f));
	Pos3.push_back(glm::vec3(2.0f, 1.0f, 15.0f));
	Pos3.push_back(glm::vec3(-2.0f, 1.0f, -15.0f));
}


