#include "AppClass.h"

CameraManager* CameraManager::instance = nullptr;

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A08_CameraSingleton"); // Window Name
}
void AppClass::InitVariables(void)
{
	m_pCamera = CameraManager::GetInstance();
	//Generate the Cone
	m_pCone1 = new PrimitiveClass();
	m_pCone1->GenerateCone(1.0f, 3.0f, 10, RERED);

	m_pCone2 = new PrimitiveClass();
	m_pCone2->GenerateCone(1.0f, 3.0f, 20, REBLUE);

	m_pCube = new PrimitiveClass();
	m_pCube->GenerateCube(1.0f, REGREEN);

	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(1.0f, 2.0f, 10, REYELLOW);

	// if false, no ortho view
	inOrthoView = false;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	// neccessary matrix
	mModelToWorld = IDENTITY_M4;

	// toggle button for ortho view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		if (inOrthoView == true) { inOrthoView = false; }
		else if (inOrthoView == false) { inOrthoView = true; }
	}
}

void AppClass::Display(void)
{
	//Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render the grid
	//m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY);

	//Render the cone
	//m_pCone->Render(m_m4Projection, m_m4View, IDENTITY_M4);

	//Render our shapes
	m_pCone1->Render(m_pCamera->GetProjection(inOrthoView), m_pCamera->GetView(), mModelToWorld * glm::translate(glm::vec3(0.0f, 0.0f, 5.0f)));
	m_pCone2->Render(m_pCamera->GetProjection(inOrthoView), m_pCamera->GetView(), mModelToWorld * glm::translate(glm::vec3(0.0f, 0.0f, -5.0f)));
	m_pCube->Render(m_pCamera->GetProjection(inOrthoView), m_pCamera->GetView(), mModelToWorld * glm::translate(glm::vec3(5.0f, 0.0f, 0.0f)));
	m_pCylinder->Render(m_pCamera->GetProjection(inOrthoView), m_pCamera->GetView(), mModelToWorld * glm::translate(glm::vec3(-5.0f, 0.0f, 0.0f)));

	//Render the rest of the meshes
	m_pMeshMngr->Render();

	//Swaps the OpenGL buffers
	m_pGLSystem->GLSwapBuffers();
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCone1);
	SafeDelete(m_pCone2);
	SafeDelete(m_pCube);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	m_pCamera->ReleaseInstance();
	super::Release(); 
}