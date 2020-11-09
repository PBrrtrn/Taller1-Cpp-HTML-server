#include "ServerApplication.h"

int main(int argc, char *argv[]) {
	ServerApplication app(argv[1]);
	app.run();

	return 0;
}
