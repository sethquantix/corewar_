#version 400

layout(location = 0) in vec3    in_Position;
layout(location = 1) in vec3    in_Normal;
layout(location = 2) in vec2    in_uv;
layout(location = 3) in int     in_face;
layout(location = 4) in vec3    in_trans;
layout(location = 5) in vec3    in_rot;
layout(location = 6) in vec3    in_scale;
layout(location = 7) in uint    in_data;
layout(location = 8) in uint    in_val;

uniform mat4    P;
uniform mat4    V;
uniform float   time;

out vec3    pos_color;
out vec2    uv;
out vec3    normal;
out vec3    scale;
out vec3    camPos;


flat out uint   data;
flat out uint   val;
flat out int    face;
flat out float  index;

void main(void)
{
    bool    proc = (in_data & uint(0xF)) != 0;
    vec3 cam = vec3(V[0].w, V[1].w, V[2].w);
    mat4 rot = V;
	mat4    yrot;

	rot[0].w = 0;
    rot[1].w = 0;
    rot[2].w = 0;
	uv = in_uv;
	gl_Position = vec4(in_Position, 1.0);
	normal = (vec4(in_Normal.xyz, 0)).xyz;
	gl_Position.y *= in_scale.y;
	gl_Position.y += proc && in_face > 1 && gl_Position.y > 0.1 ? 10.0 : 0;
	uv.y *= proc && in_face != 1 ? 10.0 : 1.0;
	yrot[0] = vec4(0);
	yrot[1] = vec4(0);
	yrot[2] = vec4(0);
	yrot[3] = vec4(0);
	yrot[0].x = 1;
	yrot[1].y = 1;
	yrot[2].z = 1;
	yrot[3].w = 1;
	yrot[0].x = cos(0.5 * time);
	yrot[2].z = cos(0.5 * time);
	yrot[2].x = -sin(0.5 * time);
	yrot[0].z = sin(0.5 * time);
	gl_Position.xyz += in_trans;// * (1 + 0.5 * sin(time));
	gl_Position *= yrot;
	pos_color = gl_Position.xyz;
	gl_Position.xyz += cam;
	gl_Position *= inverse(rot);
	gl_Position *= P;
	index = gl_InstanceID;
	data = in_data;
	face = in_face;
	scale = in_scale;
	camPos = -cam;
	val = in_val;
}
