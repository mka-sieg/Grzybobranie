#version 330 core
//https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%2025%20-%20Shadow%20Maps%20(Directional%20Lights)/framebuffer.frag
out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;
uniform float gamma;

void main()
{
    vec4 fragment = texture(screenTexture, texCoords);
    FragColor.rgb = pow(fragment.rgb, vec3(1.0f / gamma));
}