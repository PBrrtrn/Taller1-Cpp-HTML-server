#ifndef __RESOURCE_REPOSITORY_H__
#define __RESOURCE_REPOSITORY_H__

#include <string>
#include <mutex>
#include <unordered_map>

class ResourceRepository {
  /* Clase ResourceRepository: Ofrece una interfaz thread-safe para acceder y
  modificar un mapa <string, string> de forma concurrente.                 */
private:
  const bool hasResource(const std::string& resource_name);
  /* Verifica que un recurso exista en el mapa de recursos.

  Parámetros:
    - const std::string& resource_name: Clave bajo la cual buscar el recurso.

  Valor de retorno:
    Un bool que indica si existe la clave resource_name en el mapa         */
  std::mutex mutex;
  std::unordered_map<std::string, std::string> resources;
public:
  explicit ResourceRepository(const char *root_contents_path);
  /* Constructor de ResourceRespository; instancia el objeto con un directorio
  root ("/")

  Parámetros:
    - const char *root_contents_path: Contenidos del directorio root. Se
    convierten a string antes de almacenar.                                  */
  ~ResourceRepository();
  ResourceRepository(const ResourceRepository&) = delete;
  ResourceRepository& operator=(const ResourceRepository&) = delete;
  void addResource(const std::string& resource_name,
                   const std::string& resource);
  /* Agrega un recurso al mapa, con clave resource_name y valor resource. Si
  bien los parámetros son recibidos por referencia para mejorar la eficiencia
  de la operación, los nombres y recursos guardados se almacenan copiandolos
  al map para atar el lifetime de los recursos al repositorio propiamente dicho
  y no al objeto que lo esté modificando.

  Parámetros:
    - const std::string& resource_name: Clave bajo la cual almacenar un recurso
    - const std::string& resource: Recurso a almacenar.                      */

  std::string getResource(const std::string& resource_name);
  /* Trae el valor del mapa bajo la clave que coincide con resource_name. Si el
  recurso no existe, levanta una excepción.

  Parámetros:
    - const std::string& resource_name: Clave del recurso a traer.

  Valor de retorno:
    Un string con una copia del recurso almacenado.                          */
};

#define BUF_LEN 256

class ResourceNotFoundError : public std::exception {
private:
  char error_msg[BUF_LEN];
public:
  explicit ResourceNotFoundError(const char* resource_name) noexcept;
  virtual const char* what() const noexcept;
  virtual ~ResourceNotFoundError() noexcept;
};

#endif
