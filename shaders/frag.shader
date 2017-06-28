#version 400

#define M_PI        3.1415926535897932384626433832795
#define MAX_DIST    1000
#define FUDGE       0.8
#define EPS         0.01

# define OPT_VALUES		0x1
# define OPT_ROTATION	0x2
# define OPT_LOWRES		0x4

in vec3 			pos_color;
in vec3				camPos;
in vec2 			uv;
in vec3 			normal;
in vec3             scale;

flat in uint    data;
flat in uint    val;
flat in int     face;
flat in float   index;

uniform float           in_time;
uniform sampler2D	    textNoise;
uniform sampler2DArray  font;
uniform int             opts;

uniform vec3    L1;

const float	LC1 = 0.7;
const float COL = 60;
const float R1 = 0.001;

float   time = in_time;
float   dtime = index + 0.4 * in_time;
//float   time = index + in_time;

layout(location = 0) out vec4 FragColor;

const vec3  colors[] = vec3[](
    vec3(0.3, 0.3, 0.3),
    vec3(0.8, 0.28, 0.15),
    vec3(0.86, 0.13, 0.97),
    vec3(0.3, 0.25, 0.8),
    vec3(0.3, 0.9, 0.2)
);

#define tau 6.2831853

vec2 rotate(vec2 p, float a)
{
	return vec2(p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a));
}

// 1D random numbers
float rand(float n)
{
    return fract(sin(n) * 43758.5453123);
}

// 2D random numbers
vec2 rand2(in vec2 p)
{
	return fract(vec2(sin(p.x * 591.32 + p.y * 154.077), cos(p.x * 391.32 + p.y * 49.077)));
}

// 1D noise
float noise(float p)
{
	float fl = floor(p);
	float fc = fract(p);
	return mix(rand(fl), rand(fl + 1.0), fc);
}

mat2 makem2(in float theta){float c = cos(theta);float s = sin(theta);return mat2(c,-s,s,c);}
float noise( in vec2 x ){return texture(textNoise, x*.01).x;}
mat2 m2 = mat2( 0.80,  0.60, -0.60,  0.80 );

float grid(vec2 p)
{
	float s = sin(p.x)*cos(p.y);
	return s;
}

float flow(in vec2 p)
{
	float z=2.;
	float rz = 0.;
	vec2 bp = p;
	for (float i= 1.;i < 7.;i++ )
	{
		bp += time*1.5;
		vec2 gr = vec2(grid(p*3.-time*2.),grid(p*3.+4.-time*2.))*0.4;
		gr = normalize(gr)*0.4;
		gr *= makem2((p.x+p.y)*.3+time*10.);
		p += gr*0.5;

		rz+= (sin(noise(p)*8.)*0.5+0.5) /z;

		p = mix(bp,p,.5);
		z *= 1.7;
		p *= 2.5;
		p*=m2;
		bp *= 2.5;
		bp*=m2;
	}
	return rz;
}

// voronoi distance noise, based on iq's articles
float voronoi(in vec2 x)
{
	vec2 p = floor(x);
	vec2 f = fract(x);

	vec2 res = vec2(8.0);
	for(int j = -1; j <= 1; j ++)
	{
		for(int i = -1; i <= 1; i ++)
		{
			vec2 b = vec2(i, j);
			vec2 r = vec2(b) - f + rand2(p + b);

			// chebyshev distance, one of many ways to do this
			float d = max(abs(r.x), abs(r.y));

			if(d < res.x)
			{
				res.y = res.x;
				res.x = d;
			}
			else if(d < res.y)
			{
				res.y = d;
			}
		}
	}
	return res.y - res.x;
}

vec3   brain(vec2 uv, vec3 cexp)
{
	float v = 0.0;

    uv = (uv - 0.5) * 2;

//   	uv *= 0.6 + sin(time * 0.1) * 0.4;
//  	uv = rotate(uv, sin(time * 0.3) * 1.0);
//   	uv += time * 0.4;

	float a = 0.6, b = 1.6, f = 1.0;

	for(int i = 0; i < 2; i ++)
	{
		float v1 = voronoi(uv * f + 5.0);
		float v2 = 0.0;

		if(i > 0)
		{
			v2 = voronoi(uv * f * 0.5 + 50.0 + time);

			float va = 0.0, vb = 0.0;
			va = 1.0 - smoothstep(0.0, 0.1, v1);
			vb = 1.0 - smoothstep(0.0, 0.08, v2);
			v += b * pow(va * (0.5 + vb), 2.0);
		}

		v1 = 1.0 - smoothstep(0.0, 0.3, v1);

		v2 = a * (noise(v1 * 5.5 + 0.1));

		v += v2;
		f *= 3.0;
		a *= 0.7;
	}

   	vec3 col = v * cexp;

	return (col);
}

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

void mainImage(vec3 col, out vec4 fragColor, in vec2 uv_, bool m)
{
    vec3    c = col;

	//setup system
	vec2 p = uv_ - 0.5;
	vec2 cp = 2 * (uv_ - (face == 1 ? vec2(0.5) : scale.xy / 2));
	vec2 op = 2 * p;
	p *= 2.;
    float rz = 0;
    rz = (opts & OPT_LOWRES) != 0 ? dualfbm(p) : mix(dualfbm(p), flow(p + 1), 0.9);

	p /= m ? exp(mod(dtime,3.14159)) : 80;
	cp /= m ? exp(mod(dtime,3.14159)) : 80;
    rz *= pow(abs((0.1-circ(cp))),.9);
	col /= clamp(rz, 0.3, 1000);
	col = pow(abs(col),vec3(.99));
    if ((opts & OPT_LOWRES) == 0)
    {
        vec3 c1 = brain(op * 0.5, c);
	    float f = 0.4f * exp(-0.05 * length(camPos - pos_color));
	    fragColor = vec4(mix(col, c1, f), 1.0);
    }
    else
        fragColor = vec4(col, 1.0);
}

vec2   de(vec3 p)
{
    float d1 = abs(dot((pos_color - p), normal));
    float d2 = sqrt(dot(L1 - p, L1 - p)) - R1;

    return vec2(min(d1, d2), d1 > d2 ? 1 : 0);
}

vec3 blackbody(float Temp)
{
	vec3 col = vec3(255.);
    col.x = 56100000. * pow(Temp,(-3. / 2.)) + 148.;
   	col.y = 100.04 * log(Temp) - 623.6;
   	if (Temp > 6500.) col.y = 35200000. * pow(Temp,(-3. / 2.)) + 184.;
   	col.z = 194.18 * log(Temp) - 1448.6;
   	col = clamp(col, 0., 255.)/255.;
    if (Temp < 1000.) col *= Temp/1000.;
   	return col;
}

float evaluateLight(vec3 pos)
{
    vec3    t = L1 - pos;
    return LC1 / (1 * sqrt(dot(t, t)));
}

vec3    march(vec3 ro, vec3 rd)
{
    vec4    p = vec4(ro, 0);
    int     i = 0;
    bool    hit = false;
    float   cl = 0;

    while (i < 100 && p.w < MAX_DIST)
    {
        vec2 l = de(p.xyz);

        l.x *= FUDGE;
        p += vec4(rd, 1) * l.x;
        cl += evaluateLight(p.xyz) * 0.12;
        if (l.x < EPS)
        {
            hit = true;
            break ;
        }
        i++;
    }
    return hit ? blackbody(cl * COL) : vec3(0);
}

vec4 glyphColor(vec3 col, in vec2 _uv, float t)
{
	vec2 p = _uv * 2. - 1.;
//	p.x *= res.x/res.y;
	vec2 bp = p;
	p += 5.;
	p *= 0.6;
	float rb = fbm(p*.5+t*.17)*.1;
	rb = sqrt(rb);
	p *= makem2(rb*.2+atan(p.y,p.x)*1.);

	//coloring
	float rz = fbm(p*.9-t*.7);
	rz *= dot(bp*5.,bp)+.5;
	rz *= sin(p.x*.5+t*4.)*1.5;
	col /= (.1-rz);
	return vec4(sqrt(abs(col)),1.0);
}

void main(void)
{
    bool    proc = (data & uint(0xF)) != 0;
    int     p = int(data & uint(0xF0)) >> 4;
    float   s = face == 1 ? 1 : scale.y;
    float   k = 0.45 + 0.55 * float(data >> 16) / 600.0;
    int     o = 0;
    vec2    uv_ = uv;

    for (int i = 0; i < 4; i++)
        if ((p & (1 << i)) != 0)
            o = i + 1;
    vec3    c = proc && face == 1 ? vec3(0.9) : colors[o];

    if (face != 0) {
        c *= proc ? 1.0 : k;
//        c *= proc ? 2.0 : 0.4 * k;
        uv_.y -= proc && face != 1 ? 9 : 0;
        uv_.y *= s;
        if (!proc || face == 1 || uv.y >= 100 / (scale.y + 10))
            mainImage(c, FragColor, uv_, o != 0);
        else
        {
            vec3    c1 = vec3(1);
            float   k = 1 - uv.y / 10;
//            float   f = exp(-2 * (0.5 - abs(uv.x - 0.5)));
//            float   k = exp(-(9 - uv.y) * 10) * f;
            FragColor = vec4(c1, mix(0.6, 0.0, k));
        }
        if (face == 1 && (opts & OPT_VALUES) != 0 && (val != 0 || o != 0))
        {
            vec4 glyph = vec4(texture(font, vec3(uv, val)).xyzw);
            if (length(glyph.xyz) > 0.05)
                glyph.xyz = glyphColor(colors[o], uv, 0.1 * time).xyz;
            FragColor = vec4(mix(glyph.xyz, vec3(0), 1 - glyph.w), 1.0);
        }
        if ((opts & OPT_VALUES) == 0)
        {
            vec3 ro = camPos;
            vec3 rd = normalize(pos_color - camPos);
            FragColor.xyz += march(ro, rd);
        }
    }
    else
    {
        FragColor = vec4(vec3(0.0), 1);
    }
}
