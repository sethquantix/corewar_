#version 400

layout(location = 0) in vec3    in_Position;
layout(location = 1) in vec3    in_Normal;
layout(location = 2) in vec2    in_uv;
layout(location = 3) in int     in_face;
layout(location = 4) in vec3    in_trans;
layout(location = 5) in vec3    in_rot;
layout(location = 6) in vec3    in_scale;
layout(location = 7) in uint    in_data;


uniform mat4    P;
uniform mat4    V;

out vec3    pos_color;
out vec2    uv;
out vec3    normal;
out vec3    scale;
out vec3    camPos;

flat out uint data;
flat out int index;
flat out int face;

void main(void)
{
    vec3 cam = vec3(V[0].w, V[1].w, V[2].w);
    mat4 rot = V;
    rot[0].w = 0;
    rot[1].w = 0;
    rot[2].w = 0;
	uv = in_uv;
	gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	normal = (vec4(in_Normal.xyz, 0)).xyz;
	gl_Position.xyz *= in_scale;
	gl_Position.xyz += in_trans;
	gl_Position.xyz += cam;
	gl_Position *= inverse(rot);
	pos_color = gl_Position.xyz;
	gl_Position *= P;
	index = gl_InstanceID;
	data = in_data;
	face = in_face;
	scale = in_scale;
	camPos = cam;
}
