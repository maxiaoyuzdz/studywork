#pragma once

#include "GXBase.h"
using namespace gxbase;

class terrain {
private:
	Image _heightfield;
	float (*_vertexarray)[3];
	float (*_normalarray)[3];
	GLuint *_indexarray;
	float (*_texarray)[2];
	int _width, _height;

public:
	terrain();

	~terrain();

	void OnCreate();

	void draw(bool texon) const;

	void normal(bool normon) const;

private:
	void _gen_normals();

	void _normalize();

};
