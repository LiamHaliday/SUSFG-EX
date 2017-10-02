#version 430 core 
in vec3 outColor; 
in vec2 TexCoord;


out vec4 color;

uniform sampler2D Texture;
uniform float currentTime;

void main(){

    color = texture(Texture, TexCoord) * vec4(outColor, 1.0f) * abs(1);

}