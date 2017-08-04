#version 400

#define PLAYER  0
#define PROC    1
#define REG     2

in vec3     pos;
in vec2 	uv;

uniform sampler2D	    board;
uniform sampler2D	    texNoise;
uniform vec2            res;
uniform float           _time;
uniform int             cursor_pos;
uniform vec4            player_box_pos;
uniform vec4            proc_box_pos;
uniform vec4            proc_reg_pos;

float       time = _time * 0.1;
const vec3  center = vec3(0, 36, -128);

out vec4 FragColor;

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

mat2 makem2(in float theta){float c = cos(theta);float s = sin(theta);return mat2(c,-s,s,c);}
float noise( in vec2 x ){return texture(texNoise, x*.01).x;}

mat2 m2 = mat2( 0.80,  0.60, -0.60,  0.80 );
float fbm( in vec2 p )
{
	float z=2.;
	float rz = 0.;
	for (float i= 1.;i < 7.;i++ )
	{
		rz+= abs((noise(p)-0.5)*2.)/z;
		z = z*2.;
		p = p*2.;
		p*= m2;
	}
	return rz;
}

vec4 mainImage(vec3 col, in vec2 _uv, float t)
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

bool    inside(vec2 uv, vec4 box)
{
    return (uv.x >= box.x && uv.x <= box.x + box.z &&
        uv.y >= box.y && uv.y <= box.y + box.w);
}

void    main(void)
{
    vec2    p = abs(uv - 0.5);
    float   h = 0.49;
    vec4    ct;
    vec3    c = texture(board, uv).xyz;

    FragColor = vec4(c, clamp(10 * length(c), 0, 1));
    ct = mainImage(FragColor.xyz, uv, time);
    if (uv.y < 0.2 || (uv.x < 0.5 && uv.y < 0.55))
        FragColor *= ct;
    if ((cursor_pos == PLAYER && inside(uv, player_box_pos)) ||
        (cursor_pos == PROC && inside(uv, proc_box_pos)) ||
        (cursor_pos == REG && inside(uv, proc_reg_pos)))
        FragColor = 1 - FragColor;
//    if (uv.y > 0.55 && uv.y < 0.555)
//        FragColor = vec4(blackbody(length(pos - center) * 100), 1.0);
//    if (uv.x > 0.4985 && uv.x < 0.5015 && uv.y < 0.50 && uv.y > 0.24)
//        FragColor = vec4(blackbody(length(pos - center) * 100), 1.0);
}
