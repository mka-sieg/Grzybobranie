#version 330

out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the fragment position of the light
in vec4 fragPosLight;




// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
//uniform sampler2D specular0;
uniform sampler2D shadowMap;
//uniform samplerCube shadowCubeMap;

// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 lightPos3;

// Gets the position of the camera from the main function
uniform vec3 camPos;
//uniform float farPlane;
uniform int light_type;
uniform int light_color;

float pointLight(vec3 l)
{
// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = l - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 5.0;
	float b = 0.9;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.2f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specular = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 halfwayVec = normalize(viewDirection + lightDirection);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

		return  (diffuse  * inten + ambient);
}
float direcLight(){
// ambient lighting
	float ambient = 0.10f;
// diffuse lighting
		vec3 normal = normalize(Normal);
		vec3 lightDirection = normalize(lightPos);
		float diffuse = max(dot(normal, lightDirection), 0.0f);

		// specular lighting
		float specular = 0.0f;
		if (diffuse != 0.0f)
		{
			float specularLight = 0.50f;
			vec3 viewDirection = normalize(camPos - crntPos);
			vec3 halfwayVec = normalize(viewDirection + lightDirection);
			float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
			specular = specAmount * specularLight;
		};
		// Shadow value
		//float shadow = 0.0f;
		// Sets lightCoords to cull space
		//vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
		//if(lightCoords.z <= 1.0f)
		//{
			// Get from [-1, 1] range to [0, 1] range just like the shadow map
			//lightCoords = (lightCoords + 1.0f) / 2.0f;
			//float currentDepth = lightCoords.z;
			// Prevents shadow acne
			//float bias = max(0.025f * (1.0f - dot(normal, lightDirection)), 0.0005f);

			// Smoothens out the shadows
			//int sampleRadius = 2;
			//vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);
			//for(int y = -sampleRadius; y <= sampleRadius; y++)
			//{
				//for(int x = -sampleRadius; x <= sampleRadius; x++)
				//{
					//float closestDepth = texture(shadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
					//if (currentDepth > closestDepth + bias)
						//shadow += 1.0f;     
				//}    
			//}
			// Get average shadow
			//shadow /= pow((sampleRadius * 2 + 1), 2);
		//}
		 return (diffuse  + ambient);//* (1.0f - shadow);
}
float spotLight()
{

// controls how big the area that is lit up is
		float outerCone = 0.90f;
		float innerCone = 0.95f;

		// ambient lighting
		float ambient = 0.20f;

		// diffuse lighting
		vec3 normal = normalize(Normal);
		vec3 lightDirection = normalize(lightPos - crntPos);
		float diffuse = max(dot(normal, lightDirection), 0.0f);

		// specular lighting
		float specular = 0.0f;
		if (diffuse != 0.0f)
		{
			float specularLight = 0.50f;
			vec3 viewDirection = normalize(camPos - crntPos);
			vec3 halfwayVec = normalize(viewDirection + lightDirection);
			float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
			specular = specAmount * specularLight;
		};

		// calculates the intensity of the crntPos based on its angle to the center of the light cone
		float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
		float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

		// Shadow value
		//float shadow = 0.0f;
		// Sets lightCoords to cull space
		//vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
		//if(lightCoords.z <= 1.0f)
		//{
			// Get from [-1, 1] range to [0, 1] range just like the shadow map
			//lightCoords = (lightCoords + 1.0f) / 2.0f;
			//float currentDepth = lightCoords.z;
			// Prevents shadow acne
			//float bias = max(0.00025f * (1.0f - dot(normal, lightDirection)), 0.000005f);

			// Smoothens out the shadows
			//int sampleRadius = 2;
			//vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);
			//for(int y = -sampleRadius; y <= sampleRadius; y++)
			//{
				//for(int x = -sampleRadius; x <= sampleRadius; x++)
				//{
					//float closestDepth = texture(shadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
					//if (currentDepth > closestDepth + bias)
						//shadow += 1.0f;     
				//}    
			//}
			// Get average shadow
			//shadow /= pow((sampleRadius * 2 + 1), 2);

		//}
		return (diffuse  * inten + ambient);//* (1.0f - shadow);
}
void main()
{
	vec4 TotalLight=vec4(0.0f,0.0f,0.0f,0.0f); 
	if (light_type==1){
		TotalLight=direcLight()*lightColor ;
	}if(light_type==2){
		TotalLight=pointLight(lightPos)* lightColor ;
	}if(light_type==3){
		TotalLight=spotLight()* lightColor ;
	}
	if (light_color==1){
		TotalLight+=pointLight(lightPos1)* vec4(1.0,0.0,0.0,0.0);
	}if(light_color==2){
		TotalLight+=pointLight(lightPos2)* vec4(0.0,1.0,1.0,0.0);
	}if(light_color==3){
		TotalLight+=pointLight(lightPos3)* vec4(1.0,1.0,0.0,0.0);
	}
    
	
    FragColor = texture(diffuse0, texCoord)*TotalLight;
}