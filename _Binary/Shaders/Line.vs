#version 330
layout (location = 0) in vec3 Position_b;
layout (location = 1) in vec3 Color_b;
layout (location = 6) in mat4 Matrix_b;

uniform mat4 VP;

out vec3 Color;

void main()
{
	gl_Position = (VP * Matrix_b) * vec4(Position_b, 1);
	
	Color = Color_b;
}