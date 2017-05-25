#version 400

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;
in vec3             scale;

flat in uint data;
flat in int index;
flat in int face;

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

vec3 compute_light(int o)
{
    float a; float b;

	vec3 c = texture(textDiffuse, uv).xyz;
	vec3 ret = c;

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

const float     int_h[] = float[](
    0.5,
    0.7,
    0.0,
    0.8,
    0.3
);

const float     int_v[] = float[](
    0.4,
    0.6,
    0.3,
    0.2
);

const vec3  colors[] = vec3[](
    vec3(0.3, 0.3, 0.3),
    vec3(0.2, 0.15, 0.8),
    vec3(0.7, 0.3, 0.1),
    vec3(0.3, 0.9, 0.2),
    vec3(0.8, 0.2, 0.1)
);

void main(void)
{
    bool    proc = (data & uint(0xF)) != 0;
    int     o = 0;
    int     p = int(data & uint(0xF0)) >> 4;
    float   s = face == 1 ? 1 : scale.y;
    float   k = 0.35 + 0.65 * float(data >> 16) / 600.0;

    for (int i = 0; i < 4; i++)
        if ((p & (1 << i)) != 0)
            o = i + 1;
    vec3    c = proc && face == 1 ? vec3(0.9) : colors[o];

    if (face == 1 && !proc)
        c = vec3(0.3, 0.3, 0.3);
    if (face == 0)
        FragColor = vec4(0, 0, 0, 1);
    else
    {
        float   lc = 0;
        float   v = 0.1;
        for (int i = 0; i < 1; i++) {
            float   dv = v + 0.15 * i;
            float   ku = pow(1 + (.01 / s) - abs(uv.y - (1 - dv / s)), 50 * s);
            float   kd = pow(1 + (.01 / s) - abs(uv.y - (dv / s)), 50 * s);
            float   kr = pow(1.01 - abs(uv.x - (1 - dv)), 50);
            float   kl = pow(1.01 - abs(uv.x - dv), 50);
            float   lv = max(ku, kd);
            float   lh = max(kr, kl);
            float   r = kr * (uv.y > 1 - ((dv + 0.08) / s) || uv.y < (dv + 0.08) / s ? 0 : 1);
            float   l = kl * (uv.y > 1 - ((dv + 0.08) / s) || uv.y < (dv + 0.08) / s ? 0 : 1);
            float   u = ku * (uv.x > (1 - dv + 0.02) || uv.x < (dv - 0.02) ? 0 : 1);
            float   d = kd * (uv.x > (1 - dv + 0.02) || uv.x < (dv - 0.02) ? 0 : 1);
            lc = max(max(max(r, l), max(u, d)), lc);
        }
        FragColor = vec4(lc * c * (face == 1 ? 1 : k), 1);
    }
}
