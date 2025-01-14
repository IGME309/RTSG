#include "AppClass.h"
void Application::InitVariables(void)
{
	//Message for the App
	
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(35.0f, 0.0f, 35.0f), vector3(), AXIS_Y);//Set Camera position
	
	//Models to load
	m_pMyEntityMngr = EntityManager::GetInstance();

	uint uCount = 1000;

	m_sToPrint = std::to_string(uCount) + " objects!";
	for (uint i = 0; i < uCount; i++)
	{
		m_pMyEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube");
		vector3 v3Position = vector3(glm::sphericalRand(14.0f));

		m_pMyEntityMngr->AddDimension(-1, 0);

		m_pMyEntityMngr->SetModelMatrix(glm::translate(v3Position), -1);
	}
	std::vector<vector3> listOfPoints;
	for (uint i = 0; i < uCount; i++)
	{
		Entity* pEntity = m_pMyEntityMngr->GetEntity(i);
		RigidBody* pRB = pEntity->GetRigidBody();
		listOfPoints.push_back(pRB->GetMinGlobal());
		listOfPoints.push_back(pRB->GetMaxGlobal());
	}
	m_pRigidBody = new RigidBody(listOfPoints);
	m_v3Position = m_pRigidBody->GetCenterGlobal();
	m_v3Size = m_pRigidBody->GetHalfWidth() * 2.0f;
}
void Application::Update(void)
{
	m_pSystem->Update();//Update the system
	ArcBall();//Is the arcball active?
	CameraRotation(); //Is the first person camera active?

	//Add the space
	m_pRigidBody->AddToRenderList();
	//m_pModelMngr->AddWireCubeToRenderList(glm::translate(m_v3Position) *
	//	glm::scale(m_v3Size), C_RED);

	//Add the model matrix to the entities
	m_pMyEntityMngr->Update();
	
	//Render the entieies
	//-1 means all of the entities
	m_pMyEntityMngr->AddEntityToRenderList(-1, true);
	
	m_pEntityMngr->Update(); //Update Entity Manager (the one in the system)
	m_pEntityMngr->AddEntityToRenderList(-1); //Add objects to render list
}
void Application::Display(void)
{
	ClearScreen(); // Clear the screen
	m_pModelMngr->AddSkyboxToRenderList(); // draw a skybox
	m_uRenderCallCount = m_pModelMngr->Render(); //render list call
	m_pModelMngr->ClearRenderList(); //clear the render list
	DrawGUI(); //draw gui
	m_pWindow->display(); //end the frame (swap front and back buffers)
}
void Application::Release(void)
{
	//Release the memory of the Rigid Body
	m_pMyEntityMngr->ReleaseInstance();

	ShutdownGUI();//release GUI
}