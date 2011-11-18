#pragma once
#include <GXBase.h>

using namespace gxbase;

class PaletteWindow :public GLWindow {
private:
	Image m_image;
	float _rgb[3];

public:
	PaletteWindow();
	void OnCreate();
	void OnDisplay();
	void OnMouseButton(MouseButton button, bool down);
	void OnMouseMove(int x, int y);
	void OnKeyboard(int key, bool down);

	void DrawPixel();
	const float* ChoosedColor() const;

};