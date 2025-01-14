#include "Camera.h"

//Accessors
void Camera::SetPosition(vector3 a_v3Position) { m_v3Position = a_v3Position; }
vector3 Camera::GetPosition(void) { return m_v3Position; }

void Camera::SetTarget(vector3 a_v3Target) { m_v3Target = a_v3Target; }
vector3 Camera::GetTarget(void) { return m_v3Target; }

void Camera::SetUp(vector3 a_v3Up) { m_v3Up = a_v3Up; }
vector3 Camera::GetUp(void) { return m_v3Up; }

matrix4 Camera::GetProjectionMatrix(void) { return m_m4Projection; }
matrix4 Camera::GetViewMatrix(void) { CalculateViewMatrix(); return m_m4View; }

Camera::Camera()
{
	Init(); //Init the object with default values
}

Camera::Camera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	Init(); //Initialize the object
	SetPositionTargetAndUpward(a_v3Position, a_v3Target, a_v3Upward); //set the position, target and up
}

Camera::Camera(Camera const& other)
{
	m_v3Position = other.m_v3Position;
	m_v3Target = other.m_v3Target;
	m_v3Up = other.m_v3Up;

	m_v3Forward = other.m_v3Forward;
	m_v3Upward = other.m_v3Upward;
	m_v3Rightward = other.m_v3Rightward;

	m_m4View = other.m_m4View;
	m_m4Projection = other.m_m4Projection;
}

Camera& Camera::operator=(Camera const& other)
{
	if (this != &other)
	{
		Release();
		SetPositionTargetAndUpward(other.m_v3Position, other.m_v3Target, other.m_v3Upward);
		Camera temp(other);
		Swap(temp);
	}
	return *this;
}

void Camera::Init(void)
{
	ResetCamera();
	CalculateProjectionMatrix();
	CalculateViewMatrix();
	//No pointers to initialize here
}

void Camera::Release(void)
{
	//No pointers to deallocate yet
}

void Camera::Swap(Camera & other)
{
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_v3Target, other.m_v3Target);
	std::swap(m_v3Up, other.m_v3Up);

	std::swap(m_v3Forward, other.m_v3Forward);
	std::swap(m_v3Upward, other.m_v3Upward);
	std::swap(m_v3Rightward, other.m_v3Rightward);

	std::swap(m_m4View, other.m_m4View);
	std::swap(m_m4Projection, other.m_m4Projection);
}

Camera::~Camera(void)
{
	Release();
}

void Camera::ResetCamera(void)
{
	m_v3Position = vector3(0.0f, 0.0f, 10.0f); //Where my camera is located
	m_v3Target = vector3(0.0f, 0.0f, 0.0f); //What I'm looking at
	m_v3Up = vector3(0.0f, 1.0f, 0.0f); //What is up

	m_v3Forward = vector3(0.0f, 0.0f, -1.0f); //View vector
	m_v3Upward = vector3(0.0f, 1.0f, 0.0f); //where my head is pointing up
	m_v3Rightward = vector3(0.0f, 1.0f, 0.0f); //What is to my right
}

void Camera::SetPositionTargetAndUpward(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward)
{
	m_v3Position = a_v3Position;
	m_v3Target = a_v3Target;
	m_v3Up = a_v3Upward;
}

void Camera::CalculateViewMatrix(void)
{
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Up);
}

void Camera::CalculateProjectionMatrix(void)
{
	//perspective
	float fRatio = 1280.0f / 720.0f;
	m_m4Projection = glm::perspective(45.0f, fRatio, 0.001f, 1000.0f);
	//m_m4Projection = glm::ortho(-5.0f * fRatio, 5.0f * fRatio, -5.0f, 5.0f, 0.001f, 1000.0f);
}
