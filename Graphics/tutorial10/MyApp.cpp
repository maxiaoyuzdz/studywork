#include "MyApp.h"

MyApp::MyApp() : _angleInc(30), top(90,PERPECTIVEVIEW), front(30,FRONTVIEW),side(120,SIDEVIEW) {
	_angle = 0;
}

void MyApp::OnIdle() {
	float deltatime = (float)App::GetDeltaTime();
	_angle += _angleInc * deltatime;

	if(_angle > 360.0f) 
		_angle -=360.0f;

}

float MyApp::getangle() const {
	return _angle;
}

