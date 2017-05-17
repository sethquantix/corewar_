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
	vec4 ret;
	a = (1.0f / 64.0f) * (x + index % 64);
	b = (1.0f / 64.0f) * (y + index / 64);
	ret =(texture(textLight, vec2(a, b))).xyzw;
	return (ret);
}

vec3 deduce_light_pos(int i, int j)
{
	vec3 ret;

	ret.x = ((i + index % 64 - 32)) * 2.3;
	ret.z = ((j + index / 64 - 32)) * 2.3;
	ret.y = get_light_at(i, j).w;
	return (ret);
}

vec3 compute_diffuse(vec3 pos, vec3 normal, vec3 lightpos, vec3 lightcol)
{
	vec3 ret;
	//c = ;
	float c = dot(normalize(lightpos - pos), normal);
	if (c < 0.4)
		c = 0.4;
	ret = lightcol * c;
	ret /= distance(lightpos, pos) * distance(lightpos, pos)* distance(lightpos, pos)* distance(lightpos, pos) / 100;
	return (ret);
}

#define LOW 0.6

vec3 compute_light()
{
	float a; float b;
	vec3 ret = vec3(0, 0, 0);
	vec3 c = texture(textDiffuse, uv).xyz;
	vec3 d = clamp(c + (1 - LOW), 0, 1);
	d = vec3(pow(d.x, 100.0), pow(d.y, 100.0), pow(d.z, 100.0));
	float m = max(max(c.x, c.y), c.z);
	ret = vec3(m, m, m);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			a = 1;
			b = 1;
			if (i == 2 && j == 2)
			{
				a = -1;
				b = 0.01;
			}
			ret += compute_diffuse(pos_color, normal * a, deduce_light_pos(i - 2, j - 2), get_light_at(i - 2, j - 2).xyz) * c * b;
		}
	return (ret);
}

void main(void)
{
	vec3 diffuse_color;

//	diffuse_color = texture(textLight, uv).rgb;
//	FragColor = texture(textDiffuse, uv).rgba;
	//FragColor = vec4((get_light_at(0, 0).xyz) * texture(textDiffuse, uv).xyz + compute_light().xyz, 1);
	FragColor = vec4(compute_light().xyz, 1);
}
