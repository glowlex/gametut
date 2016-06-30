float4x4 matViewProjection : ViewProjection; 

sampler AlphaMap = sampler_state 
{ 
   ADDRESSU = WRAP; 
   ADDRESSV = WRAP; 
   ADDRESSW = WRAP; 
}; 

sampler TextureOne = sampler_state 
{ 
   MipFilter = LINEAR; 
   MinFilter = LINEAR; 
   MagFilter = LINEAR; 
   ADDRESSU = WRAP; 
   ADDRESSV = WRAP; 
   ADDRESSW = WRAP; 
}; 

sampler TextureTwo = sampler_state 
{ 
   MipFilter = LINEAR; 
   MinFilter = LINEAR; 
   MagFilter = LINEAR; 
   ADDRESSU = WRAP; 
   ADDRESSV = WRAP; 
   ADDRESSW = WRAP; 
}; 

sampler TextureThree = sampler_state 
{ 
   MipFilter = LINEAR; 
   MinFilter = LINEAR; 
   MagFilter = LINEAR; 
   ADDRESSU = WRAP; 
   ADDRESSV = WRAP; 
   ADDRESSW = WRAP; 
}; 

struct VS_INPUT 
{ 
   float4 Position : POSITION0; 
   float2 alphamap : TEXCOORD0; 
   float2 tex : TEXCOORD1; 
}; 

struct VS_OUTPUT 
{ 
   float4 Position : POSITION0; 
   float2 alphamap : TEXCOORD0; 
   float2 tex : TEXCOORD1; 
}; 

struct PS_OUTPUT 
{ 
   float4 diffuse : COLOR0; 
}; 

VS_OUTPUT vs_main( VS_INPUT Input ) 
{ 
   VS_OUTPUT Output; 
   Output.Position = mul( Input.Position, matViewProjection ); 
   Output.alphamap = Input.alphamap; 
   Output.tex = Input.tex; 

   return( Output ); 
} 

PS_OUTPUT ps_main(in VS_OUTPUT input) 
{ 
   float texScale = 1.0; 	
   PS_OUTPUT output = (PS_OUTPUT)0; 

   vector a = tex2D(AlphaMap, input.alphamap); 
   vector i = tex2D(TextureOne, mul(input.tex, texScale));
   vector j = tex2D(TextureTwo, mul(input.tex, texScale)); 
   vector k = tex2D(TextureThree, mul(input.tex, texScale)); 

   float4 oneminusx = 1.0 - a.x; 
   float4 oneminusy = 1.0 - a.y; 
   float4 oneminusz = 1.0 - a.z; 

   vector l = a.x * i + oneminusx * i; 
   vector m = a.y * j + oneminusy * l; 
   vector n = a.z * k + oneminusz * m; 

   output.diffuse = n; 

   return output; 
} 

technique Default_DirectX_Effect 
{ 
   pass Pass_0 
   { 
      VertexShader = compile vs_2_0 vs_main(); 
      PixelShader = compile ps_2_0 ps_main(); 
   } 
}