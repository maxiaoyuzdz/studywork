#pragma once

#include "GXBase.h"
using namespace gxbase;

class MxyWindow2 :public GLWindow {
public:
	void OnDisplay();
	void OnIdle();

	MxyWindow2::MxyWindow2();
};