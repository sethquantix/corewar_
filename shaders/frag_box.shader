#version 400

#define MAX_DIST    1000
#define FUDGE       0.8
#define EPS         0.01

in vec3     pos;
in vec3     norm;
in vec3     camPos;

uniform vec3    L1;

const float	LC1 = 0.7;
const float R1 = 0.001;
const float COL = 60;

out vec4 FragColor;

float   de(vec3 p)
{
//    float d1 = abs(dot((pos - p), norm));
    float d2 = sqrt(dot(L1 - p, L1 - p)) - R1;
    return (d2);
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
    return LC1 / sqrt(dot(t, t));
}

vec3    color()
{
    vec4    p = vec4(camPos, 0);
    vec3    d = normalize(pos - p.xyz);
    int     i = 0;
    bool    hit = false;
    float   cl = 0;

    while (i < 100 && p.w < MAX_DIST)
    {
        float l = de(p.xyz) * FUDGE;
        p += vec4(d, 1) * l;
        cl += evaluateLight(p.xyz) * 0.12;
        if (l < EPS)
        {
            hit = true;
            break ;
        }
        i++;
    }
    return blackbody(cl * COL);
}

void    main(void)
{
    FragColor = vec4(color(), 1.0);
}
