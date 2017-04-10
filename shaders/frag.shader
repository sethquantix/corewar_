#version 400

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;

//uniform sampler2D	textDiffuse;

layout(location = 0) out vec4 FragColor;

void main(void)
{
//	vec3 diffuse_color;
//	diffuse_color = texture(textDiffuse, uv).rgb;

//	FragColor = vec4(diffuse_color.xyz, 1);
	FragColor = vec4(1, 1, 1, 1);
}
