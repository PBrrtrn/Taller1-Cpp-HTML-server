#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

class Socket {
  /* Clase socket; encapsula el comportamiento de un socket en el sistema
  operativo, ofreciendo una interfaz de operaciones autocontenidas para
  realizar comunicaciones a través de este.                            */
private:
  int fd;
  struct addrinfo* initializeAddrinfo(const char *host,
                                      const char* service,
                                      int flags);
  /* Función auxiliar initializeAddrinfo.

  Parámetros:
    - const char *host: Nombre del host del cual se quiere obtener direcciones.
    Puede ser NULL en el caso de estar inicializando direcciones para un
    servidor.
    - const char *service: Número del puerto
    - int flags: Flags del sistema                                           */

public:
  Socket();
  ~Socket();
  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;
  Socket(Socket&& other);
  Socket& operator=(Socket&& other);
  int bind(const char *service);
  int connect(const char *host, const char *service);
  int listen(int queue_size) const;
  Socket accept() const;
  int send(const char *data, size_t data_size) const;
  int receive(char *buffer, size_t n_bytes) const;
  void shutdown();
  void shutdown_write();
  void close();
};

#define BUF_LEN 256

class SocketError : public std::exception {
private:
  char error_msg[BUF_LEN];
public:
  explicit SocketError(int fd, const char* origin) noexcept;
  virtual const char* what() const noexcept;
  virtual ~SocketError() noexcept;
};

#endif
