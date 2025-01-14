#include "AppClass.h"
void Application::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(35.0f, 0.0f, 35.0f), vector3(), AXIS_Y);//Set Camera position
	
	//Models to load
	uint uCount = 1000;
#ifndef DEBUG
	uCount = 2500;
#endif // DEBUG

	//Message for the App
	m_sToPrint = std::to_string(uCount) + " objects!";
	//Create the objects and position them inside of a random position in a sphere
	for (uint i = 0; i < uCount; i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube");//Add cube entities
		vector3 v3Position = vector3(glm::sphericalRand(14.0f));//make a position
		m_pEntityMngr->SetModelMatrix(glm::translate(v3Position), -1);//place the last one
	}
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube");//Add cube entities
	
	//Change the possition of the last cube
	m_v3Position = vector3(-50.0f, 50.0f, -50.0f);//make a position
	m_pEntityMngr->SetModelMatrix(glm::translate(m_v3Position), -1);//place the last one

	//Initialize how many divisions the grid will have (its even for simplified purposes)
	m_nLevels = 3;

	//Create the grid
	m_pRootSpace = new Space(m_nLevels);
}
void Application::RecalculateTree()
{
	//Know how many subdivisions the grid had last
	static uint uSubdivisions = m_nLevels;
	static vector3 v3Position = m_v3Position;

	//If there are any changes on the tree
	if (uSubdivisions != m_nLevels || v3Position != m_v3Position)
	{
		SafeDelete(m_pRootSpace);
		m_pRootSpace = new Space(m_nLevels);
		uSubdivisions = m_nLevels;
		v3Position = m_v3Position;
	}
}
void Application::Update(void)
{
	//Message to the user
	m_sToPrint = std::to_string(m_nLevels) + " levels and " 
		+ std::to_string(m_nSpace) + " space is render.";
	
	//Change the position of the last cube
	m_pEntityMngr->SetModelMatrix(glm::translate(m_v3Position), -1);

	//recalculat the tree if needed
	RecalculateTree();

	m_pSystem->Update();//Update the system
	ArcBall();//Is the arcball active?
	CameraRotation(); //Is the first person camera active?
	//This play the grid
	m_pRootSpace->Display(m_nSpace);
	m_pEntityMngr->Update(); //Update Entity Manager (the one in the system)
	uint uEntities = m_pEntityMngr->GetEntityCount();
	if (m_nSpace < m_pRootSpace->GetSpaceCount())
	{
		for (uint i = 0; i < uEntities; i++)
		{
			RTSG::Entity* pEntity = m_pEntityMngr->GetEntity(i);
			//Ask the entity if its in space
			if (pEntity->IsInSpace(m_nSpace))
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
	ShutdownGUI();//release GUI
}