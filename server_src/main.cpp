#include "ServerApplication.h"

int main(int argc, char *argv[]) {
	ServerApplication app(argv[1], argv[2]);
	app.rackup();

	return 0;
}
