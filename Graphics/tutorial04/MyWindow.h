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
	void Cube() const;
	void OnDisplay();
	void OnIdle();

	//my methods
	void drawCubebyVertexArr() const;

	
};

