#version 330 compatibility

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
uniform mat4 matViewProjection;
uniform mat4 mInvWorld;
uniform mat4 mTransWorld;
uniform vec3 mLightPos;
uniform vec4 mLightColor;

out vec2 texCoordMask;
out vec2 texCoordLayers;
out vec3 color0;

void main(void)
{	
//TexCoord0 = vec2(TexCoord.x, 1.0f - TexCoord.y);.
//TexCoord0 = TexCoord; 
color0=color;
 texCoord0 = gl_MultiTexCoord0.xy;
  texCoord1 = gl_MultiTexCoord1.xy;
  //gl_TexCoord[1].xy = gl_MultiTexCoord1.xy;

	gl_Position = matViewProjection*vec4(position, 1.0);

	/*vec4 normal = vec4(gl_Normal, 0.0);
	normal = mInvWorld * normal;
	normal = normalize(normal);
	
	vec4 worldpos = gl_Vertex * mTransWorld;
	
	vec4 lightVector = worldpos - vec4(mLightPos,1.0);
	lightVector = normalize(lightVector);
	
	float tmp2 = dot(-lightVector, normal);
	
	vec4 tmp = mLightColor * tmp2;
	gl_FrontColor = gl_BackColor = vec4(tmp.x, tmp.y, tmp.z, 0.0);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;*/
}
