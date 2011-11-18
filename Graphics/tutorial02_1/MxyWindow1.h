#pragma once

#include "GXBase.h"
using namespace gxbase;

class MxyWindow1 :public GLWindow {
public:
	void OnDisplay();
	void OnIdle();

	MxyWindow1::MxyWindow1();
};