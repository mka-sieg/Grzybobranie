#version 330 core
//https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%2021%20-%20Instancing/asteroid.vert
// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
//layout (location = 2) in vec3 aColor;

// Instancing Transformations
layout (location = 3) in mat4 instanceMatrix;


// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
//out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
out vec4 fragPosLight;


// Imports the camera matrix
uniform mat4 camMatrix;
uniform mat4 lightProjection;

void main()
{
	// calculates current position
	crntPos = vec3(instanceMatrix * vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = aNormal;
	// Assigns the colors from the Vertex Data to "color"
	//color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;//mat3(0.0, -1.0, 1.0, 0.0) * 
	
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	fragPosLight = lightProjection * vec4(crntPos, 1.0f);
}