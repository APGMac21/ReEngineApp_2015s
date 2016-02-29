#include "MyPrimitive.h"
#include <math.h>
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float iterate = 360 / a_nSubdivisions; //what to iterate angle by
	iterate *= (PI / 180); //convert to radians
	float angle = 0 * (PI / 180); //start angle in radians
	float angle2 = angle; //end angle
	vector3 point0(0, a_fHeight/2, 0); //tip of cone
	vector3 point1(0, -a_fHeight / 2, 0); //centerpoint of base
	vector3 point2; //base point 1
	vector3 point3; //base point 2
	for (int i = 0; i < a_nSubdivisions; i++) {

		//Find value of opposite and adjacent sides with angle 1
		float opposite = sin(angle) * a_fRadius;
		float adjacent = cos(angle) * a_fRadius;

		//Make angle 2 bigger and find o and a of angle 2
		angle2 += iterate;
		float opposite2 = sin(angle2) * a_fRadius;
		float adjacent2 = cos(angle2) * a_fRadius;
		
		//Point 2 is with angle one and point 3 is with angle two
		point2 = vector3(opposite, -a_fHeight / 2, adjacent);
		point3 = vector3(opposite2, -a_fHeight / 2, adjacent2);

		//Create triangle from tip to base points
		AddVertexPosition(point0);
		AddVertexPosition(point2);
		AddVertexPosition(point3);

		//Create triangle from centerpoint to base points
		AddVertexPosition(point2);
		AddVertexPosition(point1);
		AddVertexPosition(point3);

		//Iterate angle 1
		angle += iterate;
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float iterate = 360 / a_nSubdivisions; //what to iterate angle by
	iterate *= (PI / 180); //convert to radians
	float angle = 0 * (PI / 180); //start angle in radians
	float angle2 = angle; //end angle
	vector3 point0(0, a_fHeight / 2, 0); //centerpoint of top
	vector3 point1(0, -a_fHeight / 2, 0); //centerpoint of bottom
	vector3 point2; //bottom base point 1
	vector3 point3; //bottom base point 2
	vector3 point4; //top base point 1
	vector3 point5; //top base point 2
	for (int i = 0; i < a_nSubdivisions; i++) {

		//Find value of opposite and adjacent sides with angle 1
		float opposite = sin(angle) * a_fRadius;
		float adjacent = cos(angle) * a_fRadius;

		//Make angle 2 bigger and find o and a of angle 2
		angle2 += iterate;
		float opposite2 = sin(angle2) * a_fRadius;
		float adjacent2 = cos(angle2) * a_fRadius;

		//Point 2 is with angle one and point 3 is with angle two
		point2 = vector3(opposite, -a_fHeight / 2, adjacent);
		point3 = vector3(opposite2, -a_fHeight / 2, adjacent2);

		//Point 4 is with angle one and point 5 is with angle two
		point4 = vector3(opposite, a_fHeight / 2, adjacent);
		point5 = vector3(opposite2, a_fHeight / 2, adjacent2);

		//Create triangle from tip to base points
		AddVertexPosition(point0);
		AddVertexPosition(point4);
		AddVertexPosition(point5);

		//Create triangle from centerpoint to base points
		AddVertexPosition(point2);
		AddVertexPosition(point1);
		AddVertexPosition(point3);

		//Create Side
		AddQuad(point2, point3, point4, point5);

		//Iterate angle 1
		angle += iterate;
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float iterate = 360 / a_nSubdivisions; //what to iterate angle by
	iterate *= (PI / 180); //convert to radians
	float angle = 0 * (PI / 180); //start angle in radians
	float angle2 = angle; //end angle
	vector3 point0(0, a_fHeight / 2, 0); //centerpoint of top
	vector3 point1(0, -a_fHeight / 2, 0); //centerpoint of bottom
	vector3 point2; //bottom base point 1
	vector3 point3; //bottom base point 2
	vector3 point4; //top base point 1
	vector3 point5; //top base point 2
	vector3 point6; //bottom base inner point 1
	vector3 point7; //bottom base inner point 2
	vector3 point8; //top base inner point 1
	vector3 point9; //top base inner point 2
	for (int i = 0; i < a_nSubdivisions; i++) {

		//Find value of opposite and adjacent sides with angle 1 for outside circle
		float opposite = sin(angle) * a_fOuterRadius;
		float adjacent = cos(angle) * a_fOuterRadius;

		//Find value of opposite and adjacent sides with angle 1 for inside circle
		float opposite3 = sin(angle) * a_fInnerRadius;
		float adjacent3 = cos(angle) * a_fInnerRadius;

		//Make angle 2 bigger and find o and a of angle 2 for outside and inside circle
		angle2 += iterate;
		float opposite2 = sin(angle2) * a_fOuterRadius;
		float adjacent2 = cos(angle2) * a_fOuterRadius;
		float opposite4 = sin(angle2) * a_fInnerRadius;
		float adjacent4 = cos(angle2) * a_fInnerRadius;

		//Point 2 is with angle one and point 3 is with angle two
		point2 = vector3(opposite, -a_fHeight / 2, adjacent);
		point3 = vector3(opposite2, -a_fHeight / 2, adjacent2);

		//Point 4 is with angle one and point 5 is with angle two
		point4 = vector3(opposite, a_fHeight / 2, adjacent);
		point5 = vector3(opposite2, a_fHeight / 2, adjacent2);

		//Point 6 is with angle one and point 7 is with angle two
		point6 = vector3(opposite3, -a_fHeight / 2, adjacent3);
		point7 = vector3(opposite4, -a_fHeight / 2, adjacent4);

		//Point 8 is with angle one and point 9 is with angle two
		point8 = vector3(opposite3, a_fHeight / 2, adjacent3);
		point9 = vector3(opposite4, a_fHeight / 2, adjacent4);

		//Create Outside
		AddQuad(point2, point3, point4, point5);

		//Create Inside
		AddQuad(point7, point6, point9, point8);

		//Create Top
		AddQuad(point4, point5, point8, point9);

		//Create Bottom
		AddQuad(point6, point7, point2, point3);

		//Iterate angle 1
		angle += iterate;
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	vector3 point0(0, a_fRadius, 0); //Center top
	vector3 point1(0, -a_fRadius, 0); //Center bottom


	//Your code ends here
	CompileObject(a_v3Color);
}