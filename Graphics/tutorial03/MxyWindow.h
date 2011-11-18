#pragma once

#include "GXBase.h"
using namespace gxbase;

class MxyWindow :public GLWindow {
private:
	float angle_inc;
	float angle;
	float current_time;

	float angle1;

public:
	MxyWindow();
	void OnCreate();
	void OnDisplay();
	void OnIdle();
};