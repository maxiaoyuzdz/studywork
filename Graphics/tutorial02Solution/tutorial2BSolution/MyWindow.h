#pragma once

#include "GXBase.h"
using namespace gxbase;

class MyWindow :public GLWindow {
public:
	void OnDisplay();
	void OnIdle();
};

