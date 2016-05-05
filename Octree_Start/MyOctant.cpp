#include "MyOctant.h"
using namespace ReEng;
//  MyOctant
void MyOctant::Init(void)
{
	m_v3Center = vector3(0.0f);
	m_fSize = 0.0f;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pBOMngr = MyBOManager::GetInstance();

	//Code for checking the size of the octree
	int nObjectCount = m_pBOMngr->GetObjectCount();

	MyBOClass* pBO = m_pBOMngr->GetBoundingObject(0);
	vector3 vMaxG = pBO->GetMaxG();
	vector3 vMinG = pBO->GetMinG();

	for (int i = 1; i < nObjectCount; i++)
	{
		MyBOClass* pBO = m_pBOMngr->GetBoundingObject(i);
		vector3 vMax = pBO->GetMaxG();
		vector3 vMin = pBO->GetMinG();
		//checking the X
		if (vMax.x > vMaxG.x) vMaxG.x = vMax.x;
		else if (vMin.x < vMinG.x) vMinG.x = vMin.x;
		//checking the y
		if (vMax.y > vMaxG.y) vMaxG.y = vMax.y;
		else if (vMin.y < vMinG.y) vMinG.y = vMin.y;
		//checking the z
		if (vMax.z > vMaxG.z) vMaxG.z = vMax.z;
		else if (vMin.z < vMinG.z) vMinG.z = vMin.z;
	}
	m_v3Center = (vMinG + vMaxG) / 2.0f;
	float sizeX = glm::distance(vector3(vMinG.x, 0, 0), vector3(vMaxG.x, 0, 0));
	float sizeY = glm::distance(vector3(0, vMinG.y, 0), vector3(0, vMaxG.y, 0));
	float sizeZ = glm::distance(vector3(0, 0, vMinG.z), vector3(0, 0, vMaxG.x));
	m_fSize = sizeX;
	if (m_fSize < sizeY) m_fSize = sizeY;
	if (m_fSize < sizeZ) m_fSize = sizeZ;
}
void MyOctant::Swap(MyOctant& other)
{

}
void MyOctant::Release(void)
{

}
//The big 3
MyOctant::MyOctant(float a_fSize)
{
	Init();
	m_fSize = a_fSize;
}
MyOctant::MyOctant(){Init();}
MyOctant::MyOctant(MyOctant const& other)
{

}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant(){Release();};
//Accessors

//--- Non Standard Singleton Methods

void MyOctant::Draw(void)
{
	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChildren[i].Draw();
	}
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_v3Center) * glm::scale(vector3(m_fSize)), REWHITE, WIRE);
}

void MyOctant::Subdivide(void)
{
	m_uChildren = 8;
	m_pChildren = new MyOctant[m_uChildren];
	float newSize = this->m_fSize / 2.0f;
	for (uint index = 0; index < m_uChildren; index++)
	{
		m_pChildren[index].m_fSize = newSize;
		m_pChildren[index].m_v3Center = m_v3Center;
		m_pChildren[index].m_bHead = false;
	}

	newSize /= 2.0f;

	//For index 0 octant
	m_pChildren[0].m_v3Center.x += newSize;
	m_pChildren[0].m_v3Center.y += newSize;
	m_pChildren[0].m_v3Center.z += newSize;

	//For index 1 octant
	m_pChildren[1].m_v3Center.x -= newSize;
	m_pChildren[1].m_v3Center.y += newSize;
	m_pChildren[1].m_v3Center.z += newSize;

	//For index 2 octant
	m_pChildren[2].m_v3Center.x -= newSize;
	m_pChildren[2].m_v3Center.y -= newSize;
	m_pChildren[2].m_v3Center.z += newSize;

	//For index 3 octant
	m_pChildren[3].m_v3Center.x += newSize;
	m_pChildren[3].m_v3Center.y -= newSize;
	m_pChildren[3].m_v3Center.z += newSize;

	//For index 4 octant
	m_pChildren[4].m_v3Center.x += newSize;
	m_pChildren[4].m_v3Center.y += newSize;
	m_pChildren[4].m_v3Center.z -= newSize;

	//For index 5 octant
	m_pChildren[5].m_v3Center.x -= newSize;
	m_pChildren[5].m_v3Center.y += newSize;
	m_pChildren[5].m_v3Center.z -= newSize;

	//For index 6 octant
	m_pChildren[6].m_v3Center.x -= newSize;
	m_pChildren[6].m_v3Center.y -= newSize;
	m_pChildren[6].m_v3Center.z -= newSize;

	//For index 7 octant
	m_pChildren[7].m_v3Center.x += newSize;
	m_pChildren[7].m_v3Center.y -= newSize;
	m_pChildren[7].m_v3Center.z -= newSize;
}
void MyOctant::DestroyOctant(void)
{
	if (m_pChildren != nullptr)
	{
		delete[] m_pChildren;
		m_pChildren = nullptr;
	}
}