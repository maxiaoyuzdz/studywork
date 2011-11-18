#ifndef top_h
#define top_h

#include <iostream>
using namespace std;

//TODO: Add appropriate include statements


class Top {
public:
	// Constructor
	Top();

	// Selector
	int lookAt() const;

//TODO: Add write method prototype
	// Modifier
	void change(int value);

	

	void write(ostream &fout) const;

private:
	
	// Data member
	int _value;

	
};
#endif