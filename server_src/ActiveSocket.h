#ifndef __ACTIVE_SOCKET_H__
#define __ACTIVE_SOCKET_H__

#include "../common_src/Thread.h"
#include "../common_src/Socket.h"
#include "Protocol.h"

class ActiveSocket : public Thread {
	/* Clase ActiveSocket que extiende de Thread para correr sobre su propio
	thread (objeto vivo). Representa un cliente aceptado por el socket 
	pasivo/aceptador que debe ser manejado según un protocolo de comunicación.
	Cada ActiveSocket es instanciado por el AcceptorSocket que aceptó el cliente,
	y debe ser destruído por el mismo una vez que concluyó la comunicación. 
		Para inicializar un	ActiveSocket, primero debe ser construido, y luego se
	debe llamar al método start() de la clase base Thread.										 */
private:
  Protocol& protocol;
  bool finished_talking = false;
  Socket socket;

public:
  ActiveSocket(Socket socket, Protocol& protocol);
  /* Constructor de la clase. Establece al momento de construir el socket, el
  protocolo con el cualse ejecutará, y toma ownership del socket.

  Atributos:
  	- Socket socket: Un socket peer para llevar a cabo la comunicación con un
  	cliente. Importante notar que esta construcción se realiza por movimiento,
  	de este modo garantizando que ActiveSocket es el único con control del
  	socket.
  	- Protocol& protocol: Una referencia a una clase derivada de Protocol que
  	será la encargada de manejar el socket peer de forma inmutable.				 */
  ~ActiveSocket();
  void run() override;
  /* El método run es llamado por referencia por el método start() heredado de
  Thread, que pone el hilo a ejecutar. run() llama al método handleSocket de
  Protocol, delegando a este el manejo de la comunicación. Al terminar la
  ejecución del protocolo, se cierran las comunicaciones del socket y se marca
  la instancia de ActiveSocket como terminada, habilitando por ende que esta
  sea destruida.																														 */
  bool finishedTalking() const;
  /* Getter del miembo finishedTalking que permite saber si el ActiveSocket
	puede ser destruido si afectar la comunicación con el cliente.

	Valor de retorno: La variable finished_taking (por copia)									 */
};

#endif
