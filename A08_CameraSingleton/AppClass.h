/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class CameraManager
{
private:
	//Private vectors
	vector3 position = vector3(0.0f, 0.0f, 15.0f); 
	vector3 target = vector3(0.0f, 0.0f, 0.0f);
	vector3 top = vector3(0.0f, 1.0f, 0.0f);
	vector3 forward = vector3(0.0f, 0.0f, -1.0f);
	vector3 upward = vector3(0.0f, 1.0f, 0.0f);
	vector3 rightward = vector3(1.0f, 0.0f, 0.0f);
	vector3 pitchYawRoll = vector3(0.0f);
	
	glm::quat qOrientation;

	matrix4 m4_camera = IDENTITY_M4;
	

	//Projection and view marticies
	matrix4 projection = matrix4(1.0f);
	matrix4 view = matrix4(1.0f);

public:
	//Instance is used for singleton
	static CameraManager* instance;
	//Orientation quaternion
	

	static CameraManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CameraManager();
		}
		return instance;
	};
	static void ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	//Return the view matrix
	matrix4 GetView(void)
	{
		view = glm::mat4_cast(qOrientation);
		view = glm::translate(view, -position);
		return view;
	}

	//If false return perspective, if true return orthographic
	matrix4 GetProjection(bool bOrthographic)
	{
		if (bOrthographic == false)
		{
			projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
			return projection;
		}
		else
		{
			projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 1000.0f);
			return projection;
		}
	}


	//Set the position
	void SetPosition(vector3 v3Position)
	{
		position = v3Position;
	}

	//Set the target
	void SetTarget(vector3 v3Target)
	{
		target = v3Target;
	}

	//Set the up
	void SetUp(vector3 v3Up)
	{
		upward = v3Up;
	}

	//Move foward
	void MoveForward(float fIncrement)
	{
		//Change position using conjugate (basically the negation per se) of quaternion  and the z axis
		position += (glm::conjugate(qOrientation) * REAXISZ) * fIncrement;
	}

	//Same with x
	void MoveSideways(float fIncrement)
	{
		position += (glm::conjugate(qOrientation) * REAXISX) * fIncrement;
	}

	//Same with y
	void MoveVertical(float fIncrement)
	{
		position += (glm::conjugate(qOrientation) * REAXISY) * fIncrement;
	}

	//Change the pitch
	void ChangePitch(float fIncrement)
	{
		rotateByAngle(fIncrement, REAXISX);
	}

	//Change Roll
	void ChangeRoll(float fIncrement)
	{
		rotateByAngle(fIncrement, REAXISZ);
	}

	//Change yaw
	void ChangeYaw(float fIncrement)
	{
		rotateByAngle(fIncrement, REAXISY);
	}

	//Rotate helper function
	void rotateByAngle(float angleR, const glm::vec3& axis) 
	{
		//Use glm angle axis
		glm::quat q = glm::angleAxis(angleR, axis);
		rotateQ(q);
	}

	//Another helper function for multiplication
	void rotateQ(const glm::quat& rotation)
	{
		qOrientation = rotation * qOrientation;
	}
};

class AppClass : public ReEngAppClass
{
	PrimitiveClass* m_pCone1 = nullptr;
	PrimitiveClass* m_pCone2 = nullptr;
	PrimitiveClass* m_pCube = nullptr;
	PrimitiveClass* m_pCylinder = nullptr;
	CameraManager* m_pCamera;

	matrix4 m_m4Projection;
	matrix4 m_m4View;

	matrix4 mModelToWorld;

	float m_fTemp = 0.0f;
	bool inOrthoView = false;
public:
	typedef ReEngAppClass super;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) : super(hInstance, lpCmdLine, nCmdShow) {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName);

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void);

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void);

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void);

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void);

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void);

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
};

#endif //__APPLICATION_H_
