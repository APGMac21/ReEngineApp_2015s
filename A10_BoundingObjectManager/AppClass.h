/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObject.h"
#include <vector>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll


class BoundingObjectManager
{
	std::vector<MyBoundingObject*> objectVector;

public:
	//Instance is used for singleton
	static BoundingObjectManager* instance;
	//Orientation quaternion

	static BoundingObjectManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new BoundingObjectManager();
		}
		return instance;
	};
	static void ReleaseInstance()
	{
		if (instance != nullptr)
		{
			for (int i = 0; i < instance->objectVector.size(); i++) {
				delete instance->objectVector[i];
			}
			delete instance;
			instance = nullptr;
		}
	}

	void AddBO(std::vector<vector3> a_lVectorList)
	{
		MyBoundingObject* bo = new MyBoundingObject(a_lVectorList);
		objectVector.push_back(bo);
	}

	int GetBONum() { return objectVector.size(); }

	void RenderBO(int index, MeshManagerSingleton* m_pMeshManager) {
		objectVector[index]->DrawBO(m_pMeshManager);
	}

	void RenderAllBO(MeshManagerSingleton* m_pMeshManager) {
		for (int i = 0; i < objectVector.size(); i++) {
			RenderBO(i, m_pMeshManager);
		}
	}

	void CheckCollisions() {
		for (int i = 0; i < objectVector.size(); i++) {
			for (int j = 0; j < objectVector.size(); j++) {
				if (i != j) {
					if (objectVector[i]->IsCollidingSphere(objectVector[j])) {
						objectVector[i]->SetColorSphere(RERED);
						objectVector[j]->SetColorSphere(RERED);
						if (objectVector[i]->IsCollidingCube(objectVector[j])) {
							objectVector[i]->SetColorCube(RERED);
							objectVector[j]->SetColorCube(RERED);
						}
						else
						{
							objectVector[i]->SetColorCube(REBLUE);
							objectVector[j]->SetColorCube(REBLUE);
						}
					}
					else
					{
						objectVector[i]->SetColorSphere(REGREEN);
						objectVector[j]->SetColorSphere(REGREEN);
					}
				}
			}
		}
	}

	void SetModelMatrix(matrix4 modelMatrix, int index) {
		objectVector[index]->SetModelMatrix(modelMatrix);
	}

};

class AppClass : public ReEngAppClass
{
	BoundingObjectManager* boundingObject;

	vector3 m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	vector3 m_v3O2 = vector3( 2.5f, 0.0f, 0.0f);

public:
	typedef ReEngAppClass super;
	/*
	USAGE: Constructor
	ARGUMENTS:
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: ---
	*/
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void) { Release(); }
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS: String a_sWindowName -> Name of the window
	OUTPUT: ---
	*/
	virtual void InitWindow(String a_sWindowName) final;
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void) final;
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void) final;
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Display(void) final;
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void) final;
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void) final;
	/*
	USAGE: Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Release(void) final;
};

#endif //__APPLICATION_H_
