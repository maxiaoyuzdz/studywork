


float4x4 matWorldViewProj	: WORLDVIEWPROJ;	//our world view projection matrix
float4x4 matWorldI			: WORLDVIEWIT;		//our inverse transpose matrix
float4x4 matWorld			: WORLD;			//our world matrix
float4 lightDir				= float4(0,0,1,0);	//our light position



/******************************************************************************/
/*                                                                            */
/*  *********  *******  ****  ****  *********  ****  ****  *******   *******  */
/*  *********  ***       ***  ***   *********  ****  ****  ***  ***  ***      */
/*     ***     *******    **  **       ***     ****  ****  ***  ***  *******  */
/*     ***     *******     ****        ***     ****  ****  *** ***   *******  */
/*     ***     ***        ******       ***      ***  ***   *******   ***      */
/*     ***     *******  ****  ****     ***       ******    ***  ***  *******  */
/*                                                                            */
/******************************************************************************/
texture texture0;

 
sampler2D texSampler0 : TEXUNIT0 = sampler_state
{
	Texture	  = (texture0);
    MIPFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
};

 
 
 
//application to vertex structure
struct vin
{ 
    float4 position   : POSITION0;
    float3 normal	  : NORMAL;
    float2 tex0       : TEXCOORD0;
};
 
//vertex to pixel shader structure
struct vout
{
    float4 position	   : POSITION0;
    float2 tex0        : TEXCOORD0;
};
 
 

/******************************************************************************/
/*                                                                            */
/*   ***       ***  ********  ********   *********  ********  ***     ***     */
/*    ***     ***   ***       ***   ***  *********  ***        ***   ***      */
/*     ***   ***    ***       ***   ***     ***     ***         *******       */
/*      *** ***     ********  ***   ***     ***     ********     *****        */
/*       *****      ***       ********      ***     ***         *******       */
/*        ***       ***       ***  **       ***     ***        ***   ***      */
/*         *        ********  ***   ***     ***     ********  ***     ***     */
/*                                                                            */
/******************************************************************************/


//VERTEX SHADER
void vs( in vin IN, out vout OUT ) 
{
    //getting to position to object space
    OUT.position    = mul(IN.position, matWorldViewProj);
 
    //getting the position of the vertex in the world
    float4 posWorld = mul(IN.position, matWorld);
 
	//transform our normal vector so its facing the right way!
	float3 normal   = mul( matWorldI, IN.normal );
	
	//use the light direction & normal to determine the intensity
	float diffuse = max(0,dot(-lightDir,normal));
	
	//use diffuse colour as an offset into our x texture colour
	OUT.tex0.x = diffuse;
	OUT.tex0.y = 0.0f;
}

 
/******************************************************************************/
/*                                                                            */
/*            ********  ***   ****     ****    ******    ***                  */
/*            **    **  ***    ****   ****     ******    ***                  */
/*            **    **  ***      *** ***       ***       ***                  */
/*            ******    ***       *****        ******    ***                  */
/*            **        ***      *** ***       ***       ***                  */
/*            **        ***     ****  ****     ******    *********            */
/*            **        ***    ****    ****    ******    *********            */
/*                                                                            */
/******************************************************************************/

//PIXEL SHADER
float4 ps( in vout IN ) : COLOR
{
    //get our colour
    float4 finalcolor = tex2D(texSampler0, IN.tex0);

    //return final pixel colour
	return finalcolor;
}


 
technique ToonEffect
{
    pass p0
    {
        vertexshader = compile vs_1_1 vs();
        pixelshader  = compile ps_1_4 ps();
    }
}