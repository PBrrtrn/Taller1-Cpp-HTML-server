#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>
#include <memory>

#include "ResourceRepository.h"
#include "HTTPResponse.h"

class HTTPRequest {
  /* Clase abstracta HTTPRequest. Permite tratar un petitorio de forma 
  polimórfica sin necesidad de conocer sus contenidos o su clase, garantizando
  que toda clase derivada de HTTPRequest compartirá su interface.            */
protected:
  std::string resource_name;
public:
  explicit HTTPRequest(const std::string& resource_name);
  /* Constructor genérico que inicializa los miembros compartidos por todas las
  clases derivadas de HTTPRequest.

  Parámetros:
    - std::string& resource_name: Una referencia a un string que contiene el
    nombre del recurso que el pedido pretende alcanzar. Los contenidos del
    string se copian al miembro resource_name de la instancia, asegurando así
    ownership del recurso.                                                   */
  virtual ~HTTPRequest();
  virtual std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) = 0;
  /* Toda clase derivada de HTTPRequest deberá implementar el método execute,
  que ejecuta el petitorio encapsulado por la misma usando los recursos
  almacenados en el ResourceRepository parado por referencia, y devuelve un
  std::unique_ptr que wrappea un puntero a una clase base HTTPResponse.

  Parámetros:
    -ResourceRepository& repo: Una referencia a un objeto que permite el acceso
    concurrente para operaciones de agregado y búsqueda en un sistema de
    directorios. El request se ejecutará sobre este objeto, modificandolo de
    ser necesario, o sólo obteniendo el recurso que este contiene y usándolo
    para construir un objeto de tipo HTTPResponse.

  Valor de retorno: Un puntero a la respuesta correspondiente, que es una clase
  derivada de HTTPResponse. Para garantizar seguridad en memoria, el puntero se
  wrappea con un std::unique_ptr antes de devolverlo.                        */
};

class GetRequest : public HTTPRequest {
public:
  explicit GetRequest(const std::string& resource_name);
  std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

class PostRequest : public HTTPRequest {
private:
  std::string resource_body;
public:
  PostRequest(const std::string& resource_name,
              const std::string& resource_body);
  std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

class BadRequest : public HTTPRequest {
private:
  std::string invalid_method;
public:
  BadRequest(const std::string& resource_name, 
             const std::string& invalid_method);
  std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

#endif
