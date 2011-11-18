#include "top.h"

Top::Top() {
	change(0);
}

void Top::change(int value) {
	_value = value;
}

int Top::lookAt() const {
	return _value;
}

void Top::write(ostream &out) const
{
	out << _value;
}
