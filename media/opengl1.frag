#version 420   

uniform sampler2D mask;
uniform sampler2D layer1;
uniform sampler2D layer2;
uniform sampler2D layer3;
uniform sampler2D grid;
in vec2 texCoordMask; 
in vec2 texCoordLayers; 
in vec2 texCoord3;
layout (location = 0) out vec4 fragColor;
in vec4 gl_FragCoord;
//layout(binding = 3, rgba8) writeonly uniform image2D layer3;
void main (void)
{
   vec4 a = texture2D(mask, texCoordMask); 
   vec4 i = texture2D(layer1, texCoordLayers);
   vec4 j = texture2D(layer2, texCoordLayers); 
   vec4 k = texture2D(layer3, texCoordLayers); 

	vec3 oneminus;
	oneminus.r = 1.0 - a.r; 
	oneminus.g = 1.0 - a.g; 
	oneminus.b = 1.0 - a.b; 

   vec4 l = a.r * i + oneminus.r * i; 
   vec4 m = a.g * j + oneminus.g * l; 
   vec4 n = a.b * k + oneminus.b * m; 
   //imageStore(layer3, ivec2(gl_FragCoord.xy), m);
   fragColor = mix(texture(mask, texCoordMask), texture(grid, texCoordLayers), 0.5);// vec4(1.0, 0.0, 0.0, 1.0);
}
