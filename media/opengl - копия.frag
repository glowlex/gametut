#version 330   

uniform sampler2D mask;
uniform sampler2D layer1;
uniform sampler2D layer2;
uniform sampler2D layer3;
in vec2 texCoordMask; 
in vec2 texCoordLayers; 
in vec3 color; 
layout (location = 0) out vec4 fragColor;
void main (void)
{
   // vec4 col = texture2D(myTexture, vec2(gl_TexCoord[0]));
    //col *= gl_Color;
   vec4 a = texture2D(mask, texCoord0); 
   vec4 i = texture2D(layer1, texCoord1);
   vec4 j = texture2D(layer2, texCoord1); 
   vec4 k = texture2D(layer3, texCoord1); 
   vec3 oneminus;
  oneminus.r = 1.0 - a.r; 
    oneminus.g = 1.0 - a.g; 
    oneminus.b = 1.0 - a.b; 

   vec4 l = a.r * i + oneminus.r * i; 
   vec4 m = a.g * j + oneminus.g * l; 
   vec4 n = a.b * k + oneminus.b * m; 

   fragColor = n;//mix(texture(layer0,  TexCoord0.xy), texture(layer1, TexCoord0.xy),0.4);// vec4(1.0, 0.0, 0.0, 1.0);
}
