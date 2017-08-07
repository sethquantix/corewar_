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
in vec3				camDir;
in vec2 			uv;
in vec3 			normal;
in vec3				scale;
in vec3				box_pos;
in vec3				box_dir;

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

vec3 sunDir  = normalize( vec3(  0.35, 0.1,  0.3 ) );
const vec3 sunColour = vec3(1.0, .95, .8);


#define SCALE 2.8
#define MINRAD2 (sin(time / 4) + 1) / 2
// float minRad2 = clamp(MINRAD2, 1.0e-9, 1.0);
float minRad2 = 0.25;
vec4 scalevec = vec4(SCALE, SCALE, SCALE, abs(SCALE)) / minRad2;
float absScalem1 = abs(SCALE - 1.0);
float AbsScaleRaisedTo1mIters = pow(abs(SCALE), float(1-10));
float fixedRadius2 = 1;
vec3 fogCol = vec3(0.4, 0.4, 0.4);
float gTime;


//----------------------------------------------------------------------------------------
float Noise( in vec3 x )
{
    vec3 p = floor(x);
    vec3 f = fract(x);
	f = f*f*(3.0-2.0*f);
	
	vec2 uv = (p.xy+vec2(37.0,17.0)*p.z) + f.xy;
	vec2 rg = vec2(0);
	return mix( rg.x, rg.y, f.z );
}

//----------------------------------------------------------------------------------------
float Map(vec3 pos) 
{
//	float s = 4;
//	pos = (fract(pos / s) * 2 - 1) * s;

	vec4 p = vec4(pos,1);
	vec4 p0 = vec4(p.xyz, 1);  // p.w is the distance estimate

	float theta = time;
	float c = cos(theta);
	float s = sin(theta);
	mat3 rotx = mat3(
	        vec3(1, 0, 0),
	        vec3(0, c, -s),
	        vec3(0, s, c)
	        );

	for (int i = 0; i < 7; i++)
	{
		//box folding
		p.xyz = clamp(p.xyz, -1, 1) * 2.0 - p.xyz;

		float r2 = dot(p.xyz, p.xyz);
		// sphere folding:
		/*if (r2 < minRad2)
			p /= minRad2;
		else if (r2 < fixedRadius2)
			p /= r2;*/
		p *= clamp(max(minRad2 / r2, minRad2), 0.0, 1.0);

		// scalevec, translate
		float a = time;
		// p.xyz *= rotx;
		p = p * scalevec + p0;
	}
	return ((length(p.xyz) - absScalem1) / p.w - AbsScaleRaisedTo1mIters);
}

//----------------------------------------------------------------------------------------
float GetSky(vec3 pos)
{
    pos *= 2.3;
	float t = Noise(pos);
    t += Noise(pos * 2.1) * .5;
    t += Noise(pos * 4.3) * .25;
    t += Noise(pos * 7.9) * .15;
	return t;
}

//----------------------------------------------------------------------------------------
vec2 Scene(in vec3 rO, in vec3 rD)
{
	float t = 0;
	vec4 p = vec4(rO, 0);
	vec4 tD = vec4(rD, 1) * 0.8;
    bool hit = false;
    float glow = 0.0;
    vec2 dist;
	for( int j=0; j < 80; j++ )
	{
		if (p.w > 42) break ;
        
		float h = Map(p.xyz);
        
		if( h <0.002)
		{
            hit = true;
            break;
        }
        else
        {
        	glow += clamp(.05-h, 0.0, .4);
			p += h * tD;
        }
 	}
    if (!hit)
        p.w = 10000.0;
    return vec2(p.w, clamp(glow*.25, 0.0, 1.0));
}

//----------------------------------------------------------------------------------------
float Hash(vec2 p)
{
	return fract(sin(dot(p, vec2(12.9898, 78.233))) * 33758.5453)-.5;
} 

//----------------------------------------------------------------------------------------
vec3 PostEffects(vec3 rgb, vec2 xy)
{
	// Gamma first...
	rgb = pow(rgb, vec3(0.27));

	// Then...
	#define CONTRAST 1.4
	#define SATURATION 1.4
	#define BRIGHTNESS 1.2
	rgb = mix(vec3(.5), mix(vec3(dot(vec3(.2125, .7154, .0721), rgb*BRIGHTNESS)), rgb*BRIGHTNESS, SATURATION), CONTRAST);
	// Noise...
	//rgb = clamp(rgb+Hash(xy*time)*.1, 0.0, 1.0);
	// Vignette...
	rgb *= .5 + 0.5*pow(20.0*xy.x*xy.y*(1.0-xy.x)*(1.0-xy.y), 0.2);	

	return rgb;
}

//----------------------------------------------------------------------------------------
float Shadow( in vec3 ro, in vec3 rd)
{
	float res = 1.0;
    float t = 0.05;
	float h;
	
    for (int i = 0; i < 8; i++)
	{
		h = Map( ro + rd*t );
		res = min(6.0*h / t, res);
		t += h;
	}
    return max(res, 0.0);
}

//---------------------------------------------------------------------------------------

vec2 hash( vec2 x )  // replace this by something better
{
	const vec2 k = vec2( 0.3183099, 0.3678794 );
	x = x*k + k.yx;
	return -1.0 + 2.0*fract( 16.0 * k*fract( x.x*x.y*(x.x+x.y)) );
}

float noise( in vec2 x ){return texture(textNoise, x*.01).x;}
//----------------------------------------------------------------------------------------
vec4 mainImage( in vec2 uv, in vec2 alternateuv )
{
	float m = 0;
	gTime = (time+m)*.01 + 15.00;

	float	dist = 14;
	// vec3	ro = vec3(cos(time / 4) * dist, 0, sin(time / 4) * dist);
	vec3 ro = box_pos;
	ro.y -= scale.y / 2;
	ro *= 5;

	//perspective view
	vec3    dir = normalize(box_dir - camPos);

	vec3 col = vec3(0.0);
	vec2 ret = Scene(ro, dir);
	float a = 1;
    
    if (ret.x < 100.0)
    {
    	col = vec3(1, 1, 1);
		vec3 p = ro + ret.x*dir; 

       	vec2 t1 = vec2(time / 4, 0);
       	vec2 t2 = vec2(10, time / 8);
       	vec2 t3 = vec2(10, time / 16 + (index / 4096.0) * 10);
       	float n1 = noise(p.xy / 2 + t1) * 2;
       	float n2 = noise(p.yz / 4 + t2 + 10) * 2;
       	float n3 = noise(p.xz / 3 + t3 + 100) * 2;
       	vec3 addColor = normalize(vec3(n1 + n2, n2 + n3, n3 + n1)) / 2.8;
       	col = addColor;

    	col += vec3(pow(abs(ret.y), 2.)) * vec3(.1, .15, .25);
 	 
		col = PostEffects(col, alternateuv);
    }
    else
    	a = 0;
	
	return vec4(col, a);
}

void main(void)
{
	FragColor = mainImage((uv - 0.5) * 2, uv);
}
