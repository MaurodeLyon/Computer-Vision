#pragma once
class S_Vertex
{
public:
	float x;				// Kan ook een Vec3 zijn 	
	float y;
	float z;
	float normalx;			// Kan ook een Vec3 zijn
	float normaly;
	float normalz;
	float texcoordx;		// kan ook een Vec2 zijn
	float texcoordy;
	S_Vertex(float, float, float, float, float, float, float, float);
	~S_Vertex() {};
};

