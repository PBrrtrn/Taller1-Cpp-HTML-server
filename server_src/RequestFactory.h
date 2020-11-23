#ifndef __REQUEST_FACTORY_H__
#define __REQUEST_FACTORY_H__

#include <string>
#include <memory>

#include "HTTPRequest.h"

class RequestFactory {
	/* Clase RequestFactory; encapsula los criterios de creación de un petitorio
	HTTP.																																			*/
private:
  std::unique_ptr<HTTPRequest> build(const std::string& message,
                                     const std::string& method,
                                     const std::string& resource_name);
  /* Función auxiliar -- convierte el mensaje con sus componentes ya separadas
  en el request final.

  Parámetros:
  	- const std::string& message: Una referencia a un string que contiene el
  	mensaje original recibido.
  	- const std::string& method: Una referencia a un string que contiene el
  	método HTTP del pedido a realizar
  	crear.
  	- const std::string& resource_name: Una referencia a un string que contiene
  	el nombre del recurso involucrado en el pedido.													 */
public:
  RequestFactory();
  ~RequestFactory();
  std::unique_ptr<HTTPRequest> operator()(std::string& message);
  /* Ejecuta la construcción del pedido HTTP, parseando el mensaje y
  encapsulándolo en una instancia de una clase derivada de HTTPRequest.

  Parámetros:
  	- std::string& message: Una referencia al string que contiene la
  	especificación del pedido HTTP.

  Valor de retorno:
  	Se devuelve un std::unique_ptr que wrappea un puntero a una clase base
  HTTPRequest. Este puntero apunta a la dirección de memoria donde se almacena
  un objeto de una clase derivada de HTTPRequest correspondiente a la realizada
  por el mensaje original.																									 */
};

#endif
