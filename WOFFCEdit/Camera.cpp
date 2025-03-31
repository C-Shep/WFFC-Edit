#include "Camera.h"
#include <string>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
	//functional
	m_movespeed = 0.30;
	m_camRotRate = 3.0;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camUp.x = 0.0f;
	m_camUp.y = 0.0f;
	m_camUp.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;

	m_mouseSensitivity = 1.f;

}

Camera::~Camera()
{
}

void Camera::Update(InputCommands* input)
{
	//camera motion is on a plane, so kill the 7 component of the look direction
	Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	//Mouse Rotate
	if (input->mouseRBDown)
	{
		//lock mouse to screen
		//RECT rect;
		//GetWindowRect(cameraWindow, &rect);
		//SetCursorPos(rect.right / 2, rect.bottom / 2);


		if (input->mouseX > oldMouseX)
		{
			m_camOrientation.y += input->mouseX - oldMouseX;// m_camRotRate* m_mouseSensitivity;
		}

		if (input->mouseX < oldMouseX)
		{
			m_camOrientation.y += input->mouseX - oldMouseX;//(m_camRotRate) * m_mouseSensitivity;
		}

		if (input->mouseY < oldMouseY)
		{
			m_camOrientation.x -= input->mouseY - oldMouseY;// m_camRotRate* m_mouseSensitivity;
		}

		if (input->mouseY > oldMouseY)
		{
			m_camOrientation.x -= input->mouseY - oldMouseY;// m_camRotRate * m_mouseSensitivity;
		}
	}

	//Keyboard Move & Rotate
	if (input->rotRight)
	{
		m_camOrientation.y += m_camRotRate;
	}
	if (input->rotLeft)
	{
		m_camOrientation.y -= m_camRotRate;
	}
	if (input->rotUp)
	{
		m_camOrientation.x -= m_camRotRate;
	}
	if (input->rotDown)
	{
		m_camOrientation.x += m_camRotRate;
	}

	//camera clamping
	if (m_camOrientation.x >= 90)
	{
		m_camOrientation.x = 90;
	}
	if (m_camOrientation.x <= -90)
	{
		m_camOrientation.x = -90;
	}

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180)* cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);

	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);
	m_camRight.Normalize();

	//create up vector from look Direction
	m_camUp = Vector3(0.f, 1.f, 0.f);

	//process input and update stuff
	if (input->forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (input->back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (input->right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (input->left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}
	if (input->up)
	{
		m_camPosition += m_camUp * m_movespeed;
	}
	if (input->down)
	{
		m_camPosition -= m_camUp * m_movespeed;
	}

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	//for mouse delta
	oldMouseX = input->mouseX;
	oldMouseY = input->mouseY;
}

DirectX::SimpleMath::Vector3 Camera::GetPosition()
{
	return m_camPosition;
}

DirectX::SimpleMath::Vector3 Camera::GetLookAt()
{
	return m_camLookAt;
}

DirectX::SimpleMath::Vector3 Camera::GetUpVector()
{
	return m_camUp;
}
