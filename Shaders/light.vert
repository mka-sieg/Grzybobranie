#version 330 core

layout( location = 0 ) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;


out vec3 crntPos;

uniform mat4 camMatrix;

uniform mat4 model;
uniform mat4 scale;

void main()
{
	crntPos = vec3(model  *scale* vec4(aPos, 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}