#pragma once
#include <vector>
#include "SceneObject.h"
#include "DisplayObject.h"
#include "DisplayChunk.h"
#include "ChunkObject.h"
#include "InputCommands.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Update(InputCommands* input);

	DirectX::SimpleMath::Vector3 GetPosition();
	DirectX::SimpleMath::Vector3 GetLookAt();
	DirectX::SimpleMath::Vector3 GetUpVector();

protected:

	float oldMouseX;
	float oldMouseY;

	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;
	DirectX::SimpleMath::Vector3		m_camUp;
	DirectX::SimpleMath::Vector2		m_lastMousePos;
	float m_camRotRate;
	float m_movespeed;
	float m_mouseSensitivity;
};

