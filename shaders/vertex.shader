#version 400

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in vec3 in_trans;
layout(location = 4) in vec3 in_rot;
layout(location = 5) in vec3 in_scale;

uniform vec4    CamPos;
uniform mat4    P;
uniform mat4    V;

out vec3 pos_color;
out vec2 uv;
out vec3 normal;

flat out int index;

void main(void)
{
	uv = in_uv;
	gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	normal = (vec4(in_Normal.xyz, 0)).xyz;
	gl_Position.xyz *= in_scale;
	gl_Position.xyz += in_trans;
	gl_Position.xyz -= CamPos.xyz;
	gl_Position *= P;
	pos_color = gl_Position.xyz;
	index = gl_InstanceID;
	pos_color = CamPos.xyz;
}
