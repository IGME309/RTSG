#version 330

uniform vec3 vWireframe;

out vec4 Fragment;

void main()
{
	Fragment = vec4(vWireframe, 1);
	return;
}