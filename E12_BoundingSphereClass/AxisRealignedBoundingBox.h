#include "RE\ReEng.h"

class AxisRealignedBoundingBox
{
	float m_fRadius = 0.0f; //Radius of the Bounding Cube
	vector3 m_v3Size = vector3(0.0f);
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Cube Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Cube Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Cube Class

public:
	AxisRealignedBoundingBox(std::vector<vector3> a_lVectorList);
	AxisRealignedBoundingBox(AxisRealignedBoundingBox const& other);
	AxisRealignedBoundingBox& operator=(AxisRealignedBoundingBox const& other);
	~AxisRealignedBoundingBox(void);
	void Swap(AxisRealignedBoundingBox& other);
	void SetModelMatrix(matrix4 a_m4ToWorld);
	vector3 GetCenterG(void);
	float GetRadius(void);
	bool IsColliding(AxisRealignedBoundingBox* const a_pOther);

	vector3 GetSize(void);
	matrix4 GetModelMatrix(void);

private:
	void Release(void);
	void Init(void);
};

