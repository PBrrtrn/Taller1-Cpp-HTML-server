#include <iostream>
#include <atomic>
#include <unistd.h>

#include "AcceptorSocket.h"
#include "../common_src/Socket.h"

AcceptorSocket::AcceptorSocket(const char *port, std::atomic<bool>& running)
															 : socket(), running(running) {
	this->socket.bind(port);
	this->socket.listen(1);
	std::cout << "Created acceptor socket!" << std::endl;
}

AcceptorSocket::~AcceptorSocket() {
	std::cout << "Freed acceptor socket!" << std::endl;
}

void AcceptorSocket::run() {
	// std::vector<ActiveSocket&> active_sockets;

	while (this->running) {
		std::cout << "running..." << std::endl;
		sleep(1);
		/* 
		Aceptar un cliente en un ActiveSocket con un thread aparte
		Recibir el mensaje del ActiveSocket
		Hacer algo con el mensaje 
			-> Posiblemente inyectarle al AcceptorSocket (por movimiento)
				 un objeto HTMLProtocol de tipo Protocol que establezca qué
				 hacer con el mensaje, a modo de desacoplar AcceptorSocket
				 de la implementación de HTML.
			-> Protocol puede recibir el ActiveSocket (por referencia)
			   y manejar la comunicación con el cliente a partir de él


		Socket peer = this->socket.accept();
		ActiveSocket active_socket(peer);
		active_sockets.push_back(active_socket);

		active_socket.start();
		*/
	}

	std::cout << "Running reaper" << std::endl;
}
