#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <string>

struct HTTPResponse {
  /* Clase abstracta HTTPResponse. Encapsula la respuesta a un petitorio HTTP,
  así como la lógica necesaria para representarla en texto.                  */
public:
  HTTPResponse();
  virtual ~HTTPResponse();
  virtual std::string getResponse() = 0;
  /* Toda clase derivada de HTTPResponse implementa el método getResponse, que
  devuelve la representación en string de la instancia particular de esa
  respuesta.                                                                 */
};

struct OKResponse : public HTTPResponse {
private:
  std::string body;
public:
  explicit OKResponse(const std::string& body);
  std::string getResponse() override;
};

struct ForbiddenResponse : public HTTPResponse {
  std::string getResponse() override;
};

struct NotFoundResponse : public HTTPResponse {
  std::string getResponse() override;
};

struct NotAllowedResponse : public HTTPResponse {
private:
  std::string method_called;
public:
  explicit NotAllowedResponse(const std::string& method_called);
  std::string getResponse() override;
};

#endif
