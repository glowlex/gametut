#version 330 compatibility

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
uniform mat4 matViewProjection;

out vec2 texCoordMask;
out vec2 texCoordLayers;
out vec2 texCoord3;

void main(void)
{	
	texCoordMask = gl_MultiTexCoord0.xy;
	texCoordLayers = gl_MultiTexCoord1.xy;
	texCoord3= gl_MultiTexCoord3.xy;
	gl_Position = matViewProjection*vec4(position, 1.0);
}
