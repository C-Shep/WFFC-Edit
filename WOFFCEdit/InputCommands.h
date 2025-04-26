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
	bool rotUp;
	bool rotDown;
	DirectX::SimpleMath::Vector2 mouseMove;
	float mouseX;
	float mouseY;
	float oldMouseX;
	float oldMouseY;
	bool mouseLBDown;
	bool mouseRBDown;
	bool copyPressed;
	bool pastePressed;
	bool delPressed;
	bool undoPressed;
	bool redoPressed;
	bool leftArrowPressed;
	bool upArrowPressed;
	bool rightArrowPressed;
	bool downArrowPressed;
};
