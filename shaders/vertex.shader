#version 400

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in vec3 in_trans;
layout(location = 4) in vec3 in_rot;

uniform mat4 V;
uniform mat4 P;

out vec3 pos_color;
out vec2 uv;
out vec3 normal;
out vec3 camPos;

void main(void)
{
	vec4 tmpcamPos;

	tmpcamPos.x = -V[0][3];
	tmpcamPos.y = -V[1][3];
	tmpcamPos.z = -V[2][3];
	tmpcamPos.w = 0;
	tmpcamPos *= inverse(V);

	uv = in_uv;
	camPos = tmpcamPos.xyz;
	gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	normal = (vec4(in_Normal.xyz, 0)).xyz;
	pos_color = gl_Position.xyz;
	gl_Position.xyz += in_trans;
	gl_Position *= V;
	gl_Position *= P;
}
