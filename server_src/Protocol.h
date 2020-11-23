#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "../common_src/Socket.h"
#include "ResourceRepository.h"
#include "RequestFactory.h"

class Protocol {
	/* Clase abstracta protocol; permite desacoplar la arquitectura mediante la
	cual se manejan los clientes de una aplicación cliente-servidor, de la lógica
	del manejo de cada cliente individual.																		 */
public:
  Protocol();
  virtual ~Protocol();
  virtual void handleSocket(const Socket& socket) = 0;
  /* Toda clase derivada de Protocol deberá implementar el método handleSocket,
  que recibe una referencia a un socket cliente listo para comunicarse. En este
  método se especificará la lógica de cada protocolo de comunicación, manejando
  el intercambio de información, transformaciones y cualquier potencial cambio
  del estado que debiera darse como resultado de una comunicación con un
  cliente.
  	Una restricción a toda extensión de Protocol es que el manejo del socket
  recibido debe respetar la inmutabilidad del mismo, a modo de garantizar que
  se respetará el ownership del mismo. Un protocol es capaz de utilizar el
  socket para realizar su trabajo, pero no por eso es dueño del socket. Para
  esto, el protocolo sólo puede utilizar los métodos de la interfaz de Socket
  que estén marcados como const.

  Parámetros:
  	- Socket& socket: Una referencia a un socket activo.										 */
};

class HTTPProtocol : public Protocol {
private:
  ResourceRepository& resources;
  RequestFactory request_factory;
public:
  explicit HTTPProtocol(ResourceRepository& resources);
  /* Implementación del protocolo de comunicación HTTP. Contiene como miembro
  una referencia a un ResourceRepository donde se buscarán y guardarán los
  pedidos que se vayan recibiendo durante la ejecución del servidor HTTP     */
  void handleSocket(const Socket& socket) override;
  /* Maneja un socket acorde a la especificación del protocolo HTTP, recibiendo
  un pedido por dicho socket, ejecutandolo y respondiendo al cliente con la
  respuesta adecuada para el petitorio realizado.														 */
};

#endif
