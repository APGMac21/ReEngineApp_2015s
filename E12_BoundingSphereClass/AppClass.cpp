#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A10 Bounding Object Manager"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");
<<<<<<< HEAD
	
	m_pBox1 = new MyBoundingCubeClass(m_pMeshMngr->GetVertexList("Steve"));
	m_pBox2 = new MyBoundingCubeClass(m_pMeshMngr->GetVertexList("Creeper"));

	m_pRealignedBox1 = new AxisRealignedBoundingBox(m_pMeshMngr->GetVertexList("Steve"));
	m_pRealignedBox2 = new AxisRealignedBoundingBox(m_pMeshMngr->GetVertexList("Creeper"));
=======
>>>>>>> lab/master
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

<<<<<<< HEAD
	m_pBox1->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"));
	m_pRealignedBox1->SetModelMatrix(m_pBox1->GetModelMatrix());
	m_pRealignedBox2->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"));

	bool isColliding = m_pRealignedBox1->IsColliding(m_pRealignedBox2);

	if (isColliding)
	{
		m_pMeshMngr->AddCubeToQueue(
			glm::translate(vector3(m_pBox1->GetCenterG())) *
			ToMatrix4(m_qArcBall) *
			glm::scale(vector3(m_pBox1->GetSize())), RERED, SOLID);
		m_pMeshMngr->AddCubeToQueue(glm::translate(vector3(m_pRealignedBox2->GetCenterG()))  *
			glm::scale(vector3(m_pRealignedBox2->GetSize())), RERED, WIRE);
		m_pMeshMngr->AddCubeToQueue(glm::translate(vector3(m_pRealignedBox1->GetCenterG()))  *
			glm::scale(vector3(m_pRealignedBox1->GetSize())), RERED, WIRE);
	}
	else
	{
		m_pMeshMngr->AddCubeToQueue(
			glm::translate(vector3(m_pBox1->GetCenterG())) *
			ToMatrix4(m_qArcBall) *
			glm::scale(vector3(m_pBox1->GetSize())), REGREEN, WIRE);
		m_pMeshMngr->AddCubeToQueue(glm::translate(vector3(m_pRealignedBox2->GetCenterG()))  *
			glm::scale(vector3(m_pRealignedBox2->GetSize())), REGREEN, WIRE);
		m_pMeshMngr->AddCubeToQueue(glm::translate(vector3(m_pRealignedBox1->GetCenterG()))  *
			glm::scale(vector3(m_pRealignedBox1->GetSize())), REGREEN, WIRE);
	}
	
=======
>>>>>>> lab/master
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
<<<<<<< HEAD

=======
>>>>>>> lab/master
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
<<<<<<< HEAD
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

=======
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
>>>>>>> lab/master
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
<<<<<<< HEAD
	if (m_pBox1 != nullptr)
	{
		delete m_pBox1;
		m_pBox1 = nullptr;
	}
	if (m_pBox2 != nullptr)
	{
		delete m_pBox2;
		m_pBox2 = nullptr;
	}
=======
>>>>>>> lab/master
	super::Release(); //release the memory of the inherited fields
}