#include"Camera.h"
#include<cmath>
//from https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%208%20-%20Camera/Camera.cpp
Camera::Camera() {
	///
}
void Camera::Camera_start(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	//view = glm::lookAt(Position, myPlayer.Position, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}
void Camera::update(glm::vec3 pos, glm::vec3 ori, glm::vec3 u) {
	Position = pos;
	Orientation = ori ;
	Up = u;
}
float Camera::calculateHorizontalDistance() {
	return (float)(distance_from_player * cos(glm::radians(pitch)));
}
float Camera::calculateVerticalDistance() {
	return (float)(distance_from_player * sin(glm::radians(pitch)));
}
/*void Camera::calculateCameraPosition(float horizontalPosition, float verticalPosition, CPlayer& player) {
	float theta = player.Direction.y + angle_around_player;
	float OffsetX = (float)(horizontalPosition * sin(glm::radians(theta)));
	float OffsetZ = (float)(horizontalPosition * cos(glm::radians(theta)));
	Position.x = player.Position.x - OffsetX;
	Position.z = player.Position.z - OffsetZ;
	Position.y = player.Position.y +verticalPosition;
}*/

