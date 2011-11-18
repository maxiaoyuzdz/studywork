#pragma once

#include "GXBase.h"
using namespace gxbase;

class MyWindow :public GLWindow {
private:
	float angle_inc;
	float angle;
	float current_time;

public:
	MyWindow();
	void OnCreate();
	void Face() const;
	void MyCube() const;
	void Cube() const;
	void MyCylinder() const;
	void OnDisplay();
	void OnIdle();
};

