#version 400

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;

flat in int index;

uniform sampler2D	textDiffuse;
uniform sampler2D	textLight;

layout(location = 0) out vec4 FragColor;


vec3 deduce_light_pos(int i, int j)
{
	return (vec3(0, 0, 0));
}

vec3 get_light_at(int x, int y)
{
	float a;
	float b;

	a = (1.0f / 64.0f) * (x + index % 64);
	b = (1.0f / 64.0f) * (y + index / 64);
	return (texture(textLight, vec2(a, b))).xyz;
}


vec3 compute_light()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			get_light_at(i - 2, j - 2);
		}
	return (vec3(0, 0, 0));
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
	compute_light();
	FragColor = vec4((.15f + get_light_at(0, 0)) * texture(textDiffuse, uv).xyz, 1);
}
