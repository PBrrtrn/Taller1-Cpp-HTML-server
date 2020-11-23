#ifndef __ACCEPTOR_SOCKET_H__
#define __ACCEPTOR_SOCKET_H__

#include <list>

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include "Protocol.h"
#include "ActiveSocket.h"

class AcceptorSocket : public Thread {
	/* Clase AcceptorSocket que extiende de Thread para correr sobre su propio
	thread (objeto vivo). Un AcceptorSocket representa el socket pasivo del
	servidor, y es por ende el encargado de manejar los clientes, reservando
	y liberando los recursos necesarios para la ejecución de cada uno.
		Para inicializar un	AcceptorSocket, primero debe ser construido, y luego se
	debe llamar al método start() de la clase base Thread.										 */
private:
  Protocol& protocol;
  Socket socket;
  std::list<ActiveSocket*> clients;
  void cleanup();
  /* Método privado, itera sobre la lista de sockets activos, borrando aquellos
  que terminaron de hablar con el cliente, a modo de evitar perder recursos en
  hilos que no están haciendo nada.																					 */
public:
  AcceptorSocket(const char* port, Protocol& protocol);
  /* Constructor de AcceptorSocket. Abre el socket pasivo sobre el puerto
  pasado por parámetro, y settea una referencia al protocolo que se utilizará
  para manejar la comunicación con cada cliente.														 */
  ~AcceptorSocket() override;
  /* Destructor de AcceptorSocket. Llama al destructor de cada ActiveSocket,
  independientemente de si este ha terminado de hablar o no, por lo que la
  conexión se cortará para cada uno.																				 */
  void run() override;
  /* El método run es llamado por referencia por el método start() heredado de
  Thread, que pone el hilo a ejecutar. run() implementa un loop que corre
  durante todo el tiempo de vida del AcceptorSocket, aceptando en cada
  iteración un cliente, atendiendolo con un ActiveSocket, y luego destruyendo
  los sockets activos que hayan terminado ya de hablar. Cuando el socket pasivo
  es cerrado mientras intenta aceptar un cliente, se atrapa la excepción y se
  la toma como señal de terminar la ejecución del programa, rompiendo así el
  loop principal.																														 */
};

#endif
