#include "ClientApplication.h"

int main(int argc, const char* argv[]) {
	ClientApplication app(argv[1], argv[2]);
	app.run();
	return 0;
}
