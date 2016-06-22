#include "stdafx.h"
#include "S_Vertex.h"



S_Vertex::S_Vertex(float xC, float yC,float zC, float normalxC, float normalyC, float normalzC, float texcoordxC,float texcoordyC)
{
	x = xC;						// Kan ook een Vec3 zijn 	
	y = yC;
	z = zC;
	normalx=normalxC;			// Kan ook een Vec3 zijn
	normaly=normalyC;
	normalz=normalzC;
	texcoordx= texcoordxC;		// kan ook een Vec2 zijn
	texcoordy= texcoordyC;

}