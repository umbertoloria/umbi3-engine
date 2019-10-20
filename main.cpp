#include "engine/App.h"
#include "MyLayer.h"

/*
#include <iostream>
class X {

private:

	int a, b;

public:

	X (int a, int b) : a(a), b(b) {
		std::cout << "creato X (" << this << ") con " << a << ", " << b << "\n";
	}

	virtual ~X () {
		std::cout << "cancellato X (" << this << ") con " << a << ", " << b << "\n";
	}

};


class Box {

private:

	X x, y, z;

public:

	Box (const X& a1, const X& a2, const X& a3) : x(a1), y(a2), z(a3) {
		std::cout << "creo box a gli passo " << &a1 << ", " << &a2 << ", " << &a3 << "\n";
		std::cout << "il nuovo stato e'    " << &x << ", " << &y << ", " << &z << "\n";
	}

	virtual ~Box () {
		std::cout << "sto per cancellare box\n";
	}

};

void func () {
	X a(1, 2);
	X b(3, 4);
	X c(5, 6);
	std::cout << "prima della creazione di box\n";
	Box x(a, b, c);
	std::cout << "dopo la creazione di box\n";
}
*/

int main (int argc, char* argv[]) {

//	std::cout << "prima func\n";
//	func();
//	std::cout << "dopo func\n";

	App app{"OTEngine", 2200, 16 / 9.0f};

	MyLayer myLayer;
	app.add(&myLayer);

	app.run();
}