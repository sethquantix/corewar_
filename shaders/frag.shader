#version 400

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;

flat in int index;

uniform sampler2D	textDiffuse;
uniform sampler2D	textLight;

layout(location = 0) out vec4 FragColor;

vec3 get_light_at(int x, int y)
{
	float a;
	float b;

	a = (1.0f / 256) * (x + index % 256);
	b = (1.0f / 256) * (y + index / 256);
	return (texture(textLight, vec2(a, b))).xyz;
}

void main(void)
{
	vec3 diffuse_color;
	diffuse_color = texture(textLight, uv).rgb;
//	diffuse_color = texture(textDiffuse, uv).rgb;

//	FragColor = vec4(diffuse_color.xyz, 1);
	float c = dot(normalize(-pos_color - vec3(0, 0, 0)), normal);
	if (c < 0)
		c = 0;

	//FragColor = vec4(texture(textDiffuse, uv).xyz * (c + 0.2), 1);
	FragColor = vec4(get_light_at(0, 0) * texture(textDiffuse, uv).xyz, 1);
}
