#include "AppClass.h"
using namespace BTXs;

//Keyboard continuous update
void Application::ProcessKeyboard(void)
{
	if (!m_bFocused)
		return;
	/*
	This is used for things that are continuously happening,
	for discreet on/off use ProcessKeyboardPressed/Released
	*/
#pragma region Character Orientation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		//create a new quaternion based on this change and append it to the existing one
		quaternion q1 = glm::angleAxis(glm::radians(1.0f), vector3(1.0f, 0.0f, 0.0f));
		m_qOrientation = m_qOrientation * q1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		//create a new quaternion based on this change and append it to the existing one
		quaternion q1 = glm::angleAxis(glm::radians(1.0f), vector3(0.0f, 1.0f, 0.0f));
		m_qOrientation = m_qOrientation * q1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		//create a new quaternion based on this change and append it to the existing one
		quaternion q1 = glm::angleAxis(glm::radians(1.0f), vector3(0.0f, 0.0f, 1.0f));
		m_qOrientation = m_qOrientation * q1;
	}
#pragma endregion
#pragma region Camera Position
	float fSpeed = 1.0f;
	float fMultiplier = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

	if (fMultiplier)
		fSpeed *= 5.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);
#pragma endregion

}

//Keyboard
void Application::ProcessKeyPressed(sf::Event a_event)
{
	if (!m_bFocused)
		return;

	switch (a_event.key.code)
	{
	default: break;
	case sf::Keyboard::Space:
		break;
	case sf::Keyboard::LShift:
	case sf::Keyboard::RShift:
		m_bModifier = true;
		break;
	}
	//gui
	gui.io.KeysDown[a_event.key.code] = true;
	gui.io.KeyCtrl = a_event.key.control;
	gui.io.KeyShift = a_event.key.shift;
}
void Application::ProcessKeyReleased(sf::Event a_event)
{
	if (!m_bFocused)
		return;
	static bool bFPSControl = false;

	switch (a_event.key.code)
	{
	default: break;
	case sf::Keyboard::Escape:
		m_bRunning = false;
		break;
	case sf::Keyboard::F1:
		m_pCameraMngr->SetCameraMode(eCAMERAMODE::CAM_PERSP);
		break;
	case sf::Keyboard::F2:
		m_pCameraMngr->SetCameraMode(eCAMERAMODE::CAM_ORTHO_Z);
		break;
	case sf::Keyboard::F3:
		m_pCameraMngr->SetCameraMode(eCAMERAMODE::CAM_ORTHO_Y);
		break;
	case sf::Keyboard::F4:
		m_pCameraMngr->SetCameraMode(eCAMERAMODE::CAM_ORTHO_X);
		break;
	case sf::Keyboard::F:
		bFPSControl = !bFPSControl;
		m_pCameraMngr->SetFPS(bFPSControl);
		break;
	case sf::Keyboard::P:
		RTSG::TextureManager::SaveScreenshot(m_pSystem->GetAppName());
		break;
	case sf::Keyboard::Add:
		break;
	case sf::Keyboard::Subtract:
		m_pEntityMngr->RemoveEntity(-1);
		break;
	case sf::Keyboard::Space:
		m_pEntityMngr->ApplyForce(vector3(0.0f, 1.0f, 0.0f), "Steve");
		break;
	case sf::Keyboard::LShift:
	case sf::Keyboard::RShift:
		m_bModifier = false;
		break;
	case sf::Keyboard::R:
		m_v3Orientation = vector3(0.0f); //reset the orientation vector
		m_qOrientation = quaternion(); //reset the orientation quaternion
		break;
	}

	//gui
	gui.io.KeysDown[a_event.key.code] = false;
	gui.io.KeyCtrl = a_event.key.control;
	gui.io.KeyShift = a_event.key.shift;
}
//Mouse
void Application::ProcessMousePressed(sf::Event a_event)
{
	if (!m_bFocused)
		return;
	switch (a_event.mouseButton.button)
	{
	default: break;
	case sf::Mouse::Button::Left:
		gui.m_bMousePressed[0] = true;
		m_bArcBall = true;
		break;
	case sf::Mouse::Button::Middle:
		gui.m_bMousePressed[1] = true;
		m_bArcBall = true;
		break;
	case sf::Mouse::Button::Right:
		gui.m_bMousePressed[2] = true;
		m_bFPC = true;
		break;
	}

	for (int i = 0; i < 3; i++)
		gui.io.MouseDown[i] = gui.m_bMousePressed[i];
}
void Application::ProcessMouseReleased(sf::Event a_event)
{
	if (!m_bFocused)
		return;
	switch (a_event.mouseButton.button)
	{
	default: break;
	case sf::Mouse::Button::Left:
		gui.m_bMousePressed[0] = false;
		m_bArcBall = false;
		break;
	case sf::Mouse::Button::Middle:
		gui.m_bMousePressed[1] = false;
		m_bArcBall = false;
		break;
	case sf::Mouse::Button::Right:
		gui.m_bMousePressed[2] = false;
		m_bFPC = false;
		break;
	}

	for (int i = 0; i < 3; i++)
		gui.io.MouseDown[i] = gui.m_bMousePressed[i];
}
void Application::ProcessMouseScroll(sf::Event a_event)
{
	if (!m_bFocused)
		return;
	gui.io.MouseWheel = a_event.mouseWheelScroll.delta;
	float fSpeed = a_event.mouseWheelScroll.delta;
	float fMultiplier = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

	if (fMultiplier)
		fSpeed *= 2.0f;
	m_pCameraMngr->MoveForward(-fSpeed);
}
void Application::ProcessMouseMovement(sf::Event a_event)
{
	if (!m_bFocused)
		return;
	//get global mouse position
	sf::Vector2i mouse = sf::Mouse::getPosition();
	sf::Vector2i window = m_pWindow->getPosition();
	m_v3Mouse.x = static_cast<float>(mouse.x - window.x);
	m_v3Mouse.y = static_cast<float>(mouse.y - window.y);
	if (!m_pSystem->IsWindowFullscreen() && !m_pSystem->IsWindowBorderless())
		m_v3Mouse += vector3(-8.0f, -32.0f, 0.0f);
	gui.io.MousePos = ImVec2(m_v3Mouse.x, m_v3Mouse.y);
}
//Mouse continuous update
void Application::ArcBall(float a_fSensitivity)
{
	if (!m_bFocused)
		return;
	//If the arcball is not enabled return
	if (!m_bArcBall)
		return;

	//static quaternion qArcBall;
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	//Initialize the position of the pointer to the middle of the screen
	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	//Calculate the difference in position and update the quaternion orientation based on it
	float DeltaMouse;
	if (MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		m_qArcBall = quaternion(vector3(0.0f, glm::radians(a_fSensitivity * DeltaMouse), 0.0f)) * m_qArcBall;
	}
	else if (MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		m_qArcBall = quaternion(vector3(0.0f, glm::radians(-a_fSensitivity * DeltaMouse), 0.0f)) * m_qArcBall;
	}

	if (MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		m_qArcBall = quaternion(vector3(glm::radians(-a_fSensitivity * DeltaMouse), 0.0f, 0.0f)) * m_qArcBall;
	}
	else if (MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		m_qArcBall = quaternion(vector3(glm::radians(a_fSensitivity * DeltaMouse), 0.0f, 0.0f)) * m_qArcBall;
	}

	SetCursorPos(CenterX, CenterY);//Position the mouse in the center
}
void Application::CameraRotation(float a_fSpeed)
{
	if (!m_bFocused)
		return;
	if (m_bFPC == false)
		return;

	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

								//Initialize the position of the pointer to the middle of the screen
	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	//Calculate the difference in view with the angle
	float fAngleX = 0.0f;
	float fAngleY = 0.0f;
	float fDeltaMouse = 0.0f;
	if (MouseX < CenterX)
	{
		fDeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += fDeltaMouse * a_fSpeed;
	}
	else if (MouseX > CenterX)
	{
		fDeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= fDeltaMouse * a_fSpeed;
	}

	if (MouseY < CenterY)
	{
		fDeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= fDeltaMouse * a_fSpeed;
	}
	else if (MouseY > CenterY)
	{
		fDeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += fDeltaMouse * a_fSpeed;
	}
	//Change the Yaw and the Pitch of the camera
	m_pCameraMngr->ChangeYaw(fAngleY * 0.25f);
	m_pCameraMngr->ChangePitch(-fAngleX * 0.25f);
	SetCursorPos(CenterX, CenterY);//Position the mouse in the center
}
