/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MyOctant_H_
#define __MyOctant_H_

#include "RE/ReEng.h"
#include "MyBOManager.h"


//System Class
class MyOctant
{
	vector3 m_v3Center; //center of the octant
	float m_fSize = 0.0f; //how large the cube is
	MeshManagerSingleton* m_pMeshMngr = nullptr;
	MyOctant* m_pParent = nullptr;
	uint m_uChildren = 0;
	bool m_bHead = true;
	MyBOManager* m_pBOMngr = nullptr;
	std::vector<MyBOClass*> inOctantBOVector;
	bool displaySphere = true;
	
public:

	MyOctant* m_pChildren = nullptr;

	MyOctant(float a_fSize);
	/*
	Method: MyOctant
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MyOctant(void);
	/*
	Method: MyOctant
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyOctant(MyOctant const& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyOctant& operator=(MyOctant const& other);
	/*
	Method: ~MyOctant
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyOctant(void);

	/*
	Method: Swap
	Usage: Changes object contents for other object's
	Arguments:
	other -> object to swap content from
	Output: ---
	*/
	void Swap(MyOctant& other);

	void Draw(void);
	void Subdivide(std::vector<MyBOClass*> bOVector);
	void DestroyOctant(void);
	bool inOctant(MyBOClass* boClass);
	void CheckCollisions();
	bool GetDisplaySphere();
	void ToggleDisplaySphere();
private:
	/*
	Method: Release
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};


#endif //__MyOctant_H__