#pragma once
#include <vector>

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool up;
	bool down;
	bool rotRight;
	bool rotLeft;
	DirectX::SimpleMath::Vector2 mouseMove;
	float mouseX;
	float mouseY;
};
