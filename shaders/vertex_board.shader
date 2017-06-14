#version 400

layout(location = 0) in vec3    in_Position;
layout(location = 1) in vec2    in_uv;

uniform mat4    P;
uniform mat4    V;

out vec3    pos;
out vec2    uv;

void    main(void)
{
    vec3 cam = vec3(V[0].w, V[1].w, V[2].w);
    mat4 rot = V;

	rot[0].w = 0;
    rot[1].w = 0;
    rot[2].w = 0;
    gl_Position = vec4(in_Position, 1.0);
  	pos = gl_Position.xyz;
  	gl_Position.xyz += cam;
   	gl_Position *= inverse(rot);
   	gl_Position *= P;
   	uv = in_uv;
}
