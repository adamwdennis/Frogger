#include "Camera.h"
#include "Coord3.h"

Camera* Camera::p_pInstance = 0;

Camera* Camera::GetInstance()
{
	if(p_pInstance == 0)
	{
		p_pInstance = new Camera();
	}
	return p_pInstance;
}

Camera::Camera()
{
	m_vPosition.SetX(-50.f);
	m_vPosition.SetY(125.f);
	m_vPosition.SetZ(0.f);

	m_vUp.SetY(1.f);
	m_vDirectional.SetZ(-1.f);
	m_fCurrentRotation = 0.f;
	SetType(E_CAMERA_BIRDS_EYE);
}

Camera::~Camera()
{

}

void Camera::SetType(E_Camera_Type p_eType)
{
	switch(p_eType)
	{
	case E_CAMERA_FREE_FLOAT:
		m_fTheta = 0.f;
		break;

	case E_CAMERA_BIRDS_EYE:
		m_vPosition.SetX(-50.f);
		m_vPosition.SetY(125.f);
		m_vPosition.SetZ(0.f);

		m_vDirectional.SetX(-0.2f);
		m_vDirectional.SetY(-0.9f);
		m_vDirectional.SetZ(0.0f);

		m_vDirectional.Normalize();
		m_fTheta = 0.f;
		break;
	}
}