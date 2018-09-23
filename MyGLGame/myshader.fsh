
#version 410

in vec4 color;
in vec2 uv;
uniform sampler2D tex;
layout (location=0) out vec4 frag_color;

void main()
{
    frag_color = texture(tex,uv) * color;
}
