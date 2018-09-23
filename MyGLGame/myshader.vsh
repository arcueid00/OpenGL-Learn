
#version 410

layout (location=0) in vec3 vertex_pos;
layout (location=1) in vec4 vertex_color;
layout (location=2) in vec2 vertex_uv;
out vec4 color;
out vec2 uv;

void main()
{
    gl_Position = vec4( vertex_pos, 1.0);
    color = vertex_color;
    uv = vertex_uv;
}
