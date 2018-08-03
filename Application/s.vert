#version 330
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

uniform mat4 projection;

out vec3 vertexColor;
 
void main()
{
    gl_Position = projection * vec4(position, 0.0f, 1.0f);
    vertexColor = color;
}
