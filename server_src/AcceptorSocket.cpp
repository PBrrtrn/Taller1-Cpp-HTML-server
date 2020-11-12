#include <iostream>
#include <atomic>
#include <unistd.h>

#include "AcceptorSocket.h"

AcceptorSocket::AcceptorSocket(const char *port,
															 std::atomic<bool>& running,
															 Protocol& protocol)
															 : running(running), protocol(protocol) {
	this->socket.bind(port);
	this->socket.listen(1);
	std::cout << "Created acceptor socket!" << std::endl;
}

AcceptorSocket::~AcceptorSocket() {
	for (ActiveSocket *active_socket : this->active_sockets) {
		delete active_socket;
	}
}

void AcceptorSocket::run() {
	while (this->running) {
		/* 
		Aceptar un cliente en un ActiveSocket con un thread aparte
		Recibir el mensaje del ActiveSocket
		Hacer algo con el mensaje 
			-> Posiblemente inyectarle al AcceptorSocket (por movimiento)
				 un objeto HTMLProtocol de tipo Protocol que establezca qué
				 hacer con el mensaje, a modo de desacoplar AcceptorSocket
				 de la implementación de HTML.
			-> Otra alternativa: Protocol puede recibir el ActiveSocket
			   (por referencia) y manejar la comunicación con el cliente
			   a partir de él
		*/
		try {
			Socket peer = this->socket.accept();
			ActiveSocket *active_socket = new ActiveSocket(std::move(peer), 
																										 this->protocol);
			this->active_sockets.push_back(active_socket);

			active_socket->start();

			// ### thread cleanup ###
		} catch (int error) {
			std::cout << "Program halt" << std::endl;
		}
	}
}

void AcceptorSocket::shutdown() {
	this->socket.shutdown();
	this->socket.close();
}
