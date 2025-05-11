#include "AppClass.h"
void Application::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(35.0f, 0.0f, 35.0f), vector3(), AXIS_Y);//Set Camera position
	
	//Models to load
	uint uCount = 1000; 
	//Message for the App
	m_sToPrint = std::to_string(uCount) + " objects!";
	//Create the objects and position them inside of a random position in a sphere
	for (uint i = 0; i < uCount; i++) 
	{
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube");//Add cube entities
		vector3 v3Position = vector3(glm::sphericalRand(14.0f));//make a position
		m_pEntityMngr->SetModelMatrix(glm::translate(v3Position), -1);//place the last one
	}
	//Initialize how many divisions the grid will have (its even for simplified purposes)
	m_nLevels = 2;
	//Create the grid
	m_pSpaceRoot = new Node(m_nLevels, m_nLevels, m_nLevels);
}
void Application::Update(void)
{
	//Message to the user
	m_sToPrint = std::to_string(m_nLevels) + " subdiv and "
		+ std::to_string(m_uSpace) + " space is render.";
	//Know how many subdivisions the grid had last
	static uint uSubdivisions = m_nLevels;
	//If this number change create a new grid (its expensive to create so saving resources)
	if (uSubdivisions != m_nLevels)
	{
		SafeDelete(m_pSpaceRoot); 
		m_pSpaceRoot = new Node(m_nLevels, m_nLevels, m_nLevels);
		uSubdivisions = m_nLevels;
	}
	m_pSystem->Update();//Update the system
	ArcBall();//Is the arcball active?
	CameraRotation(); //Is the first person camera active?
	//This play the grid
	m_pSpaceRoot->Display(m_uSpace);
	m_pEntityMngr->Update(); //Update Entity Manager (the one in the system)
	uint uEntities = m_pEntityMngr->GetEntityCount();
	if (m_uSpace < m_pSpaceRoot->GetNodeCount())
	{
		for (uint i = 0; i < uEntities; i++)
		{
			RTSG::Entity* pEntity = m_pEntityMngr->GetEntity(i);
			//Ask the entity if its in space
			if (pEntity->IsInSpace(m_uSpace))
			{
				m_pEntityMngr->AddEntityToRenderList(i); //Add objects to render list
			}
		}
	}
	else
	{
		m_pEntityMngr->AddEntityToRenderList(-1); //Add all objects to render list
	}
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
	SafeDelete(m_pSpaceRoot);
	ShutdownGUI();//release GUI
}