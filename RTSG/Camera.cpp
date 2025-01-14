#include "RTSG\Camera\Camera.h"
using namespace RTSG;
//  Camera
void Camera::MoveForward(float a_fDistance)
{
	//TODO:: replace the parent code with internal functionality 
	//Tip:: Moving will modify both positional and directional vectors
	super::MoveForward(a_fDistance);
}
void Camera::MoveVertical(float a_fDistance)
{
	//TODO:: replace the parent code with internal functionality 
	//Tip:: Moving will modify both positional and directional vectors
	super::MoveSideways(a_fDistance);
}
void Camera::MoveSideways(float a_fDistance)
{
	//TODO:: replace the parent code with internal functionality 
	//Tip:: Moving will modify both positional and directional vectors
	super::MoveSideways(a_fDistance);
}
void Camera::SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	//TODO:: replace the parent code with internal functionality 
	//Tip: Changing any positional vector forces you to calculate new directional ones
	super::SetPositionTargetAndUpward(a_v3Position, a_v3Target, a_v3Upward);

	//After Changing any vectors you need to recalculate the Camera View matrix
	CalculateProjection();
}
void Camera::CalculateView(void)
{
	//TODO:: replace the parent code with internal functionality
	//Tip:: Directional vectors will be affected by the orientation in the quaternion
	super::CalculateView();

	//After calculating any new vector one needs to update the View Matrix
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Upward);
}
void Camera::Init(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	m_bFPS = true;
	m_nMode = BTXs::eCAMERAMODE::CAM_PERSP;
	m_fFOV = 45.0f;
	m_v2NearFar = vector2(0.001f, 1000.0f);
	m_v3PitchYawRoll = vector3(0.0f);
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	vector2 v3WidthHeigh(	static_cast<float>(pSystem->GetWindowWidth()),
							static_cast<float>(pSystem->GetWindowHeight()));
	SetWidthAndHeightOfDisplay(v3WidthHeigh);

	return SetPositionTargetAndUpward(a_v3Position, a_v3Target, a_v3Upward);
}
void Camera::Swap(Camera& other)
{
	std::swap(m_bFPS, other.m_bFPS);

	std::swap(m_nMode, other.m_nMode);

	std::swap(m_fFOV, other.m_fFOV);

	std::swap(m_v2NearFar, other.m_v2NearFar);

	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_v3Target, other.m_v3Target);
	std::swap(m_v3Above, other.m_v3Above);

	std::swap(m_v3Forward, other.m_v3Forward);
	std::swap(m_v3Upward, other.m_v3Upward);
	std::swap(m_v3Rightward, other.m_v3Rightward);

	std::swap(m_v3PitchYawRoll, other.m_v3PitchYawRoll);

	std::swap(m_m4Projection, other.m_m4Projection);
	std::swap(m_m4View, other.m_m4View);
}
void Camera::Release(void){}
//The big 3
Camera::Camera()
{
	Init(vector3(0.0f, 0.0f, 5.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f));
}
Camera::Camera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	Init(a_v3Position, a_v3Target, a_v3Upward);
}
Camera::Camera(Camera const& other)
{
	m_bFPS = other.m_bFPS;

	m_nMode = other.m_nMode;

	m_fFOV = other.m_fFOV;

	m_v2NearFar = other.m_v2NearFar;

	m_v3Position = other.m_v3Position;
	m_v3Target = other.m_v3Target;
	m_v3Above = other.m_v3Above;

	m_v3Forward = other.m_v3Forward;
	m_v3Upward = other.m_v3Upward;
	m_v3Rightward = other.m_v3Rightward;

	m_v3PitchYawRoll = other.m_v3PitchYawRoll;

	m_m4Projection = other.m_m4Projection;
	m_m4View = other.m_m4View;
}
Camera& Camera::operator=(Camera const& other)
{
	if (this != &other)
	{
		Release();
		Init(other.m_v3Position, other.m_v3Target, other.m_v3Upward);
		Camera temp(other);
		Swap(temp);
	}
	return *this;
}
Camera::~Camera(){ Release(); };
//Accessors
vector3 Camera::GetPosition(void){ return m_v3Position; }
vector3 Camera::GetForward(void) { return m_v3Forward; }
vector3 Camera::GetUpward(void) { return m_v3Upward; }
vector3 Camera::GetRightward(void) { return m_v3Rightward; }
void Camera::SetForward(vector3 a_v3Input) { m_v3Forward = a_v3Input; }
void Camera::SetUpward(vector3 a_v3Input) { m_v3Upward = a_v3Input; }
void Camera::SetRightward(vector3 a_v3Input) { m_v3Rightward = a_v3Input; }
matrix4 Camera::GetViewMatrix(void){ CalculateView(); return m_m4View; }
matrix4 Camera::GetProjectionMatrix(void){ CalculateProjection(); return m_m4Projection; }
void Camera::SetNearFarPlanes(float a_fNear, float a_fFar){ m_v2NearFar = vector2(a_fNear, a_fFar); }
void Camera::SetFOV(float a_fFOV){ m_fFOV = a_fFOV; }
void Camera::SetFPS(bool a_bFPS){ m_bFPS = a_bFPS; }
void Camera::SetCameraMode(BTXs::eCAMERAMODE a_nMode){ m_nMode = a_nMode; ResetCamera(); }
BTXs::eCAMERAMODE Camera::GetCameraMode(void){ return m_nMode; }
void Camera::SetPosition(vector3 a_v3Position)
{
	return SetPositionTargetAndUpward(a_v3Position, m_v3Target, m_v3Upward);
}
void Camera::SetTarget(vector3 a_v3Target)
{
	return SetPositionTargetAndUpward(m_v3Position, a_v3Target, m_v3Upward);
}
void Camera::SetViewMatrix(matrix4 a_m4View)
{
	m_m4View = a_m4View;
}
void Camera::SetProjectionMatrix(matrix4 a_m4Projection)
{
	m_m4Projection = a_m4Projection;
}
matrix4 Camera::GetMVP(matrix4 a_m4ModelToWorld)
{
	CalculateProjection();
	CalculateView();
	return m_m4Projection * m_m4View * a_m4ModelToWorld;
}
matrix4 Camera::GetVP(void)
{
	CalculateProjection();
	CalculateView();
	return m_m4Projection * m_m4View;
}
//--- Non Standard Singleton Methods
void Camera::CalculateProjection(void)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	vector2 v3WidthHeigh(	static_cast<float>(pSystem->GetWindowWidth()),
							static_cast<float>(pSystem->GetWindowHeight()));
	SetWidthAndHeightOfDisplay(v3WidthHeigh);
	float fRatio = v3WidthHeigh.x / v3WidthHeigh.y;
	float fPos = 0;
	switch (m_nMode)
	{
	default:
		m_m4Projection = glm::perspective(m_fFOV, fRatio, m_v2NearFar.x, m_v2NearFar.y);
		break;

	case BTXs::eCAMERAMODE::CAM_ORTHO_X:
		fPos = m_v3Position.x;
		m_m4Projection = glm::ortho(-fPos * fRatio, fPos * fRatio, -fPos, fPos, m_v2NearFar.x, m_v2NearFar.y);
		break;

	case BTXs::eCAMERAMODE::CAM_ORTHO_Y:
		fPos = m_v3Position.y;
		m_m4Projection = glm::ortho(-fPos * fRatio, fPos * fRatio, -fPos, fPos, m_v2NearFar.x, m_v2NearFar.y);
		break;

	case BTXs::eCAMERAMODE::CAM_ORTHO_Z:
		fPos = m_v3Position.z;
		m_m4Projection = glm::ortho(-fPos * fRatio, fPos * fRatio, -fPos, fPos, m_v2NearFar.x, m_v2NearFar.y);
		break;
	}
}

void Camera::ChangePitch(float a_fDegree)
{
	if (m_nMode == BTXs::eCAMERAMODE::CAM_PERSP)
		m_v3PitchYawRoll.x += a_fDegree;
}
void Camera::ChangeYaw(float a_fDegree)
{
	if (m_nMode == BTXs::eCAMERAMODE::CAM_PERSP)
		m_v3PitchYawRoll.y += a_fDegree;
}
void Camera::ChangeRoll(float a_fDegree)
{
	if (m_nMode == BTXs::eCAMERAMODE::CAM_PERSP)
		m_v3PitchYawRoll.z += a_fDegree;
}

void Camera::ResetCamera(void)
{
	m_v3PitchYawRoll = vector3(0.0f);

	switch (m_nMode)
	{
	default:
		m_v3Position = vector3(0.0f, 0.0f, 10.0f);
		m_v3Target = vector3(0.0f, 0.0f, 9.0f);
		m_v3Above = vector3(0.0f, 1.0f, 10.0f);

		m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
		break;
	case BTXs::eCAMERAMODE::CAM_ORTHO_X:
		m_v3PitchYawRoll = vector3(0.0f);
		m_v3Position = vector3(10.0f, 0.0f, 0.0f);
		m_v3Target = vector3(9.0f, 0.0f, 0.0f);
		m_v3Above = vector3(10.0f, 1.0f, 0.0f);

		m_v3Forward = vector3(-1.0f, 0.0f, 0.0f);
		m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		m_v3Rightward = vector3(0.0f, 0.0f, -1.0f);
		break;
	case BTXs::eCAMERAMODE::CAM_ORTHO_Y:
		m_v3PitchYawRoll = vector3(0.0f);
		m_v3Position = vector3(0.0f, 10.0f, 0.0f);
		m_v3Target = vector3(0.0f, 9.0f, 0.0f);
		m_v3Above = vector3(0.0f, 10.0f, -1.0f);

		m_v3Forward = vector3(0.0f, -1.0f, 0.0f);
		m_v3Upward = vector3(0.0f, 0.0f, -1.0f);
		m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
		break;
	case BTXs::eCAMERAMODE::CAM_ORTHO_Z:
		m_v3PitchYawRoll = vector3(0.0f);
		m_v3Position = vector3(0.0f, 0.0f, 10.0f);
		m_v3Target = vector3(0.0f, 0.0f, 9.0f);
		m_v3Above = vector3(0.0f, 1.0f, 10.0f);

		m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
		break;
	}
}
void Camera::SetWidthAndHeightOfDisplay(vector2 a_v2WidthHeight)
{
	m_fWidth = a_v2WidthHeight.x;
	m_fHeight = a_v2WidthHeight.y;
}