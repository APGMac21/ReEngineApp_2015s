#pragma once

#include "RE\ReEng.h"

//System Class
class MyBoundingObject
{
	float m_fRadius = 0.0f;
	matrix4 m_m4ToWorld = IDENTITY_M4;
	vector3 m_v3Center = vector3(0.0f);
	vector3 m_v3Min = vector3(0.0f);
	vector3 m_v3Max = vector3(0.0f);
	vector3 m_v3Size = vector3(0.0f);
	vector3 m_v3ColorSphere = REGREEN;
	vector3 m_v3ColorCube = REBLUE;


public:
	MyBoundingObject(std::vector<vector3> a_lVectorList);
	MyBoundingObject(MyBoundingObject const& other);
	MyBoundingObject& operator=(MyBoundingObject const& other);
	~MyBoundingObject(void);
	void Swap(MyBoundingObject& other);
	void SetModelMatrix(matrix4 a_m4ToWorld);
	vector3 GetCenterG(void);
	vector3 GetSize(void);
	float GetRadius(void);
	bool IsCollidingSphere(MyBoundingObject* const a_pOther);
	bool IsCollidingCube(MyBoundingObject* const a_pOther);
	matrix4 GetModelMatrix(void);
	void DrawBO(MeshManagerSingleton* m_pMeshMngr);
	vector3 GetMax(void);
	vector3 GetMin(void);
	void SetColorSphere(vector3 color);
	void SetColorCube(vector3 color);

private:
	void Release(void);
	void Init(void);
};

