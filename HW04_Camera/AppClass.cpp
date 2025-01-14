#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 15.0f, 25.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCamera = new Camera();
	m_pCamera->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	/// <summary>
	/// The following code will run only once because its static, but it will
	/// initialize the variable pModel as a pointer to this model in the
	/// model manager, this is faster than AddConeToRenderList in the nested
	/// for loop, as looking for the cone in the list is slower than passing
	/// the pointer to the model, as this is done quite often indexing will
	/// slow down your program, not really for the amount of objects to render
	/// but the amount of search by strings
	/// </summary>
	static String sPlane = m_pModelMngr->LoadModel("UV.obj");
	static RTSG::Model* pPlane = m_pModelMngr->GetModel(sPlane);
	static String sModel = m_pModelMngr->LoadModel("Minecraft\\Creeper.obj");
	static RTSG::Model* pModel = m_pModelMngr->GetModel(sModel);

	//Total size of the Scene
	float fSize = 100.0f;

	//Add the floor
	m_pModelMngr->AddModelToRenderList(pPlane, glm::scale(vector3(fSize)));

	//Add the Creepers
	//How many Creepers per row
	uint uCount = 10;
	//Create an array of cones to populate the scene
	vector3 v3StartPosition(-fSize / 2.0f, 1.0f, -fSize / 2.0f);
	vector3 v3Delta(fSize / static_cast<float>(uCount - 1));
	vector3 v3CurrentPosition = v3StartPosition;
	for (uint i = 0; i < uCount; ++i)
	{
		for (uint j = 0; j < uCount; ++j)
		{
			m_pModelMngr->AddModelToRenderList(pModel,
				glm::translate(v3CurrentPosition) * glm::scale(vector3(3.0f)),
				RTSG::eBTX_RENDER::RENDER_SOLID | RTSG::eBTX_RENDER::RENDER_WIRE);
			v3CurrentPosition.x += v3Delta.x;
		}
		v3CurrentPosition.x = -fSize / 2.0f;
		v3CurrentPosition.z += v3Delta.z;
	}
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	matrix4 m4Model = RTSG::ToMatrix4(m_qArcBall);//model matrix

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	matrix4 m4Projection = m_pCamera->GetProjectionMatrix();
	matrix4 m4View = m_pCamera->GetViewMatrix();
	vector3 v3CameraPosition = m_pCamera->GetPosition();
	m_uRenderCallCount = m_pModelMngr->Render(m4Projection, m4View, v3CameraPosition);

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pCamera);
	//release GUI
	ShutdownGUI();
}