#pragma once

#include "GXBase.h"
#include "MyWindow.h"
using namespace gxbase;

#define FRONTVIEW 1
#define  SIDEVIEW 2
#define		PLANVIEW	3
#define		PERPECTIVEVIEW 4

// This example draws two windows, a perspective view and a plan view
// You can control the camera in both views

class MyApp :public App {

private:
	float _angle;
	const float _angleInc;

public:
	MyWindow top, front,side;
	MyApp();
	void OnIdle();
	float getangle() const;
};

