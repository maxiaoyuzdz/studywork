#pragma once

#include "GXBase.h"
#include "Vector4f.h"
#include "Color.h"
#include "Materials.h"
#include "Lights.h"
#include "Sphere.h"

using namespace gxbase;

// this is a simple example: it creates one window,
// and draws a rotating sphere with hidden surface removal

class MyWindow :public GLWindow {
private:
	// OpenGL objects
	Lights _light1, _light2, _light3;
	Materials _material1, _material2, _material3;
	Sphere _sphere1, _sphere2;

	// Simulation data
	const float _angleInc;
	float _angle;
	float _cameraAngle, _cameraPosition, _cameraRotation;
	bool _leftDown, _rightDown;

public:
	MyWindow();
	void OnCreate();
	void floor() const;
	void OnDisplay();
	void OnIdle();
	void OnResize(int w, int h);
	void OnKeyboard(int key, bool down);
	void OnMouseButton(MouseButton button, bool down);
	void OnMouseMove(int x, int y);
};

