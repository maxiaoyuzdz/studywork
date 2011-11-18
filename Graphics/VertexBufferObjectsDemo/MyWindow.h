#pragma once

#include "GXBase.h"
#include "Cube.h"
using namespace gxbase;


enum drawMode {IMMEDIATE, DRAW_ARRAY_INTERLEAVED_VERTEX_ARRAY, DRAW_ARRAY_SEPARATE_VERTEX_ARRAY, VBOS, DISPLAY_LIST, RANGE_ELEMENTS, DRAW_ELEMENTS_INTERLEAVED_VERTEX_ARRAY};

class MyWindow :public GLWindowEx {
private:
	float _angle_inc;
	float _angle;
	float _current_time;

	float _startTime;
	int _frames;
	float _fps;

	Cube* _cube;

	drawMode _drawMode;
	int _numberOfCubes;

	bool _quads;
	
	

public:
	MyWindow();
	void OnCreate();
	void OnDisplay();
	void OnIdle();
	void initialiseLights();

	void OnKeyboard(int key, bool down);
};

