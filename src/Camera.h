#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "common.h"
#include "Coord3.h"

enum E_Camera_Type
{
	E_CAMERA_FREE_FLOAT = 0,
	E_CAMERA_BIRDS_EYE
};


const float turboSpeed = 3.0;

class Camera // Singleton
{
public:
	static Camera* GetInstance();
	~Camera();

	void SetType(E_Camera_Type p_eType);
	E_Camera_Type GetType() { return m_eType; }

	Coord3 GetPosition() const { return m_vPosition; }
	void SetPosition(Coord3 val) { m_vPosition = val; }

	Coord3 GetDirVec() const { return m_vDirectional; }
	void SetDirVec(Coord3 val) { m_vDirectional = val; }

	Coord3 GetView() const { return m_vView; }
	void SetView(Coord3 val) { m_vView = val; }

	Coord3 GetUp() const { return m_vUp; }
	void SetUp(Coord3 val) { m_vUp = val; }

	float GetCurrentRotation() const { return m_fCurrentRotation; }
	void SetCurrentRotation(float val) { m_fCurrentRotation = val; }

protected:
	Camera();

private:
	static Camera* p_pInstance;

	Coord3 m_vPosition;
	Coord3 m_vDirectional;
	Coord3 m_vView;
	Coord3 m_vUp;

	float m_fCurrentRotation;
	float m_fTheta;

	E_Camera_Type m_eType;
};

#endif