
#version 410

in vec4 color;
layout (location=0) out vect4 frag_color;

void main()
{
    frag_color = color;
}
