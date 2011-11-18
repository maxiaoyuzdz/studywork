#ifndef top_h
#define top_h

#include <iostream>
using namespace std;

class Top {
public:
	// Constructor
	Top();

	// Selector
	int lookAt() const;

	// Modifier
	void change(int value);

	void write(ostream &out) const;

private:
	// Data member
	int _value;
};
#endif