#version 330
in vec3 vertexColor;
out vec4 fColor;

void main()
{
    fColor = vec4(vertexColor, 1.0f);
}
