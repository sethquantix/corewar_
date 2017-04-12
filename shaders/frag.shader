#version 400

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;

flat in int index;

uniform sampler2D	textDiffuse;
uniform sampler2D	textLight;

layout(location = 0) out vec4 FragColor;


vec4 get_light_at(int x, int y)
{
	float a;
	float b;

	a = (1.0f / 64.0f) * (x + index % 64);
	b = (1.0f / 64.0f) * (y + index / 64);
	return (texture(textLight, vec2(a, b))).xyzw;
}


vec3 deduce_light_pos(int i, int j)
{
	vec3 ret;

	ret.x = (1.0f / 64.0f) * ((i + index % 64) - 32) * 2.3;
	ret.y = (1.0f / 64.0f) * ((i + index % 64) - 32) * 2.3;
	ret.z = get_light_at(i, j).w;
	return (vec3(0, 0, 0));
}

vec3 compute_diffuse(vec3 pos, vec3 normal, vec3 lightpos, vec3 lightcol)
{
	vec3 ret;
	float c = dot(normalize(lightpos - pos), normal);

	if (c < 0)
		c = 0;
	ret = lightcol * c;
	ret /= distance(lightpos, pos) * distance(lightpos, pos);
	return (ret);
}

vec3 compute_light()
{
	vec3 ret = vec3(0, 0, 0);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (i != 0 && j != 0)
			{
				ret += compute_diffuse(pos_color, normal, deduce_light_pos(i - 2, j - 2), get_light_at(i - 2, j - 2).xyz);
			}
		}
	return (ret);
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
	//compute_light();
	FragColor = vec4((.15f + get_light_at(0, 0).xyz + compute_light()).xyz * texture(textDiffuse, uv).xyz, 1);
}
