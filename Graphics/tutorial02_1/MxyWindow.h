#pragma once

#include "GXBase.h"
using namespace gxbase;

class MxyWindow :public GLWindow {
public:
	void OnDisplay();
	void OnIdle();

	MxyWindow::MxyWindow();
};