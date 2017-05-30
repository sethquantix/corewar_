#version 400

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;
in vec3             scale;

flat in uint data;
flat in int index;
flat in int face;

uniform sampler2D	textNoise;
uniform float       in_time;

float   time = index + in_time;

layout(location = 0) out vec4 FragColor;

const vec3  colors[] = vec3[](
    vec3(0.3, 0.3, 0.3),
    vec3(0.8, 0.28, 0.15),
    vec3(0.86, 0.13, 0.97),
    vec3(0.2, 0.15, 0.8),
    vec3(0.3, 0.9, 0.2)
);

#define tau 6.2831853

mat2 makem2(in float theta){float c = cos(theta);float s = sin(theta);return mat2(c,-s,s,c);}
float noise( in vec2 x ){return texture(textNoise, x*.01).x;}

float fbm(in vec2 p)
{
	float z=2.;
	float rz = 0.;
	vec2 bp = p;
	for (float i= 1.;i < 6.;i++)
	{
		rz+= abs((noise(p)-0.5)*2.)/z;
		z = z*2.;
		p = p*2.;
	}
	return rz;
}

float dualfbm(in vec2 p)
{
    //get two rotated fbm calls and displace the domain
	vec2 p2 = p*.7;
	vec2 basis = vec2(fbm(p2-time*1.6),fbm(p2+time*1.7));
	basis = (basis-.5)*.2;
	p += basis;

	//coloring
	return fbm(p*makem2(time*0.2));
}

float circ(vec2 p)
{
	float r = length(p);
	r = log(sqrt(r));
	return abs(mod(r*4.,tau)-3.14)*3.+.2;

}

void mainImage(vec3 col, out vec4 fragColor, in vec2 uv )
{
	//setup system
	vec2 p = uv - 0.5;

	p *= 4.;
    float rz = dualfbm(p);

	//rings
	p /= exp(mod(time,3.14159));
	rz *= pow(abs((0.1-circ(p))),.9);

	//final color
	col /= rz;
	col = pow(abs(col),vec3(.99));
	fragColor = vec4(col,1.);
}

void main(void)
{
    bool    proc = (data & uint(0xF)) != 0;
    int     p = int(data & uint(0xF0)) >> 4;
    float   s = face == 1 ? 1 : scale.y;
    float   k = 0.35 + 0.65 * float(data >> 16) / 600.0;
    int     o = 0;
    for (int i = 0; i < 4; i++)
        if ((p & (1 << i)) != 0)
            o = i + 1;
    vec3    c = proc && face == 1 ? vec3(0.9) : colors[o];

    if (face != 0)
        c *= k;
    else
        c = vec3(0);
    mainImage(c, FragColor, uv * (face == 1 ? vec2(1) : scale.xy));
}
