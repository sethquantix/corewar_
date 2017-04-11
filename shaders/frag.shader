#version 400

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;

flat in int index;

uniform sampler2D	textDiffuse;

layout(location = 0) out vec4 FragColor;

void main(void)
{
//	vec3 diffuse_color;
//	diffuse_color = texture(textDiffuse, uv).rgb;

//	FragColor = vec4(diffuse_color.xyz, 1);
	float c = dot(normalize(-pos_color - vec3(0, 0, 0)), normal);
	if (c < 0)
		c = 0;

	FragColor = vec4(texture(textDiffuse, uv).xyz * (c + 0.2), 1);
}
