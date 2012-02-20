//file: vec3.cpp

#include <cmath>
#include <iostream>
#include "Coord3.h"
using namespace std;

//These functions assume that all vectors are 3D.

//Copies a vector.
void Coord3_copy(Coord3 src, Coord3* dst)
{
	dst->SetX(src.GetX());
	dst->SetY(src.GetY());
	dst->SetZ(src.GetZ());
}

//Normalizes a vector.
void Coord3::Normalize()
{
    float length = GetLength();

	SetX(GetX()/length);
	SetY(GetY()/length);
	SetZ(GetZ()/length);
}

//Returns the dot product of two vectors.
float Coord3_dotproduct(Coord3 v1, Coord3 v2)
{
	return ((v1.GetX() * v2.GetX()) + (v1.GetY() * v2.GetY()) + (v1.GetZ() * v2.GetZ()));
}

//Calculates the cross product of two vectors.
Coord3 Coord3::CrossProduct(Coord3 val)
{
	return Coord3( 
		(GetY() * val.GetZ() - GetZ() * val.GetY()),
		(GetZ() * val.GetX() - GetX() * val.GetZ()),
		(GetX() * val.GetY() - GetY() * val.GetX())
		);
}

//Adds two vectors.
void Coord3_add(Coord3 v1, Coord3 v2)
{
	v1.SetX(v1.GetX() + v2.GetX());
	v1.SetY(v1.GetY() + v2.GetY());
	v1.SetZ(v1.GetZ() + v2.GetZ());
}

//Subtracts two vectors.
void Coord3_subtract(Coord3* v1, Coord3 v2)
{
	v1->SetX(v1->GetX() - v2.GetX());
	v1->SetY(v1->GetY() - v2.GetY());
	v1->SetZ(v1->GetZ() - v2.GetZ());
}

//Rotates vector about x-axis.
void Coord3_rotateX(Coord3* v, float theta)
{
    Coord3 temp;
    float cTheta = cos(theta);
    float sTheta = sin(theta);

	Coord3_copy(*v,&temp);

	v->SetY(temp.GetY() * cTheta - temp.GetZ() * sTheta);
	v->SetZ(temp.GetY() * sTheta + temp.GetZ() * cTheta);
}

//Rotates vector about y-axis.
void Coord3_rotateY(Coord3* v, float theta)
{
	Coord3 temp;
	float cTheta = cos(theta);
	float sTheta = sin(theta);

	Coord3_copy(*v,&temp);

	v->SetX(temp.GetX() * cTheta - temp.GetZ() * sTheta);
	v->SetZ(temp.GetX() * sTheta + temp.GetZ() * cTheta);
}

//Rotates vector about z-axis.
void Coord3_rotateZ(Coord3* v, float theta)
{
	Coord3 temp;
	float cTheta = cos(theta);
	float sTheta = sin(theta);

	Coord3_copy(*v,&temp);

	v->SetX(temp.GetX() * cTheta + temp.GetY() * sTheta);
	v->SetY(temp.GetY() * cTheta - temp.GetX() * sTheta);
}

//Rotates vector about an arbitrary axis.
void Coord3_rotate(Coord3* v, float x, float y, float z, float theta)
{
    //Matrix used is found is found at:
    //http://www.gamedev.net/reference/articles/article1199.asp

    float s = sin(theta);
    float c = cos(theta);
    float t = 1 - c;

    Coord3 temp;
    
    Coord3_copy(*v,&temp);

    v->SetX(temp.GetX()*(t*x*x+c)+temp.GetY()*(t*x*y+s*z)+temp.GetZ()*(t*x*z-s*y));
    v->SetY(temp.GetX()*(t*x*y-s*z)+temp.GetY()*(t*y*y+c)+temp.GetZ()*(t*y*z+s*x));
    v->SetZ(temp.GetX()*(t*x*z+s*y)+temp.GetY()*(t*y*z-s*x)+temp.GetZ()*(t*z*z+c));
}

void Coord3::Scale(float scaler)
{
	SetX(GetX() * scaler);
	SetY(GetY() * scaler);
	SetZ(GetZ() * scaler);
}

//Returns the length of a vector.
float Coord3::GetLength()
{
	return sqrt(GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ());
}
