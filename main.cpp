#include "engine/App.h"
#include "MyLayer.h"

int main (int argc, char* argv[]) {

	App app{"OTEngine", 2200, 16 / 9.0f};

	MyLayer myLayer;
	app.add(&myLayer);

	app.run();

}