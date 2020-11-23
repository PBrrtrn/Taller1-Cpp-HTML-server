#ifndef __SERVER_APPLICATION_H__
#define __SERVER_APPLICATION_H__

#include "AcceptorSocket.h"
#include "ResourceRepository.h"
#include "Protocol.h"


class ServerApplication {
	/* Clase ServerApplication: Representa el servidor como un entero, uniendo
	la lógica de manejo de pedidos HTTP por parte de clientes con la lógica	de
	manejo de los sockets mismos y el almacenamiento.										 	  */
private:
  ResourceRepository resources;
  HTTPProtocol protocol;
  AcceptorSocket acceptor;
public:
  ServerApplication(const char *service, const char *root_contents);
  /* Constructor de ServerApplication; inicializa sus miembros 
  ResourceRespository, HTTPProtocol y AcceptorSocket.

  Parámetros:
  	- const char *service: Puerto en el cual se aceptarán conexiones.
  	- const char *root_contents: Contenidos del directorio "/" del repositorio
  	de recursos del servidor.																								*/
  ~ServerApplication();
  void rackup();
  /* Inicializa el loop principal del servidor, iniciando el AcceptorSocket,
  y ejecutando hasta recibir un caracter 'q' por parte del usuario, en cuyo
  caso se rompe el bucle de la ejecución y se liberan los recursos.			 */
};

#endif
