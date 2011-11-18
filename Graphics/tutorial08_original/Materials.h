#pragma once

#include "GXBase.h"
#include "Color.h"

class Materials {
private:
	Color _ambient;
	Color _diffuse;
	Color _emission;

public:
	Materials();

	void create(const Color &ambient=Color::black(), const Color &diffuse=Color::white(), const Color &emission=Color::null());

	void setAmbient(const Color &ambient);

	void setDiffuse(const Color &diffuse);

	void setEmission(const Color &emission);

	void apply() const;
};

