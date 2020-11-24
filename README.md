# Taller de Programación I (75.42) - Trabajo Práctico 3
# Taller Pages
# Pablo Berrotarán

### https://github.com/PBrrtrn/7542-2C2020-TP3

## Introducción

Se diseñó y desarrolló una aplicación cliente-servidor multihilo para manejar pedidos HTTP de varios clientes en simultaneo, manteniendo un repositorio de recursos que estos puedan acceder de forma concurrente para realizar operaciones de consulta y agregado de directorios. El resultado final de este proceso de diseño y desarrollo toma la forma de dos programas instanciables desde consola:

* Server: Recibe un puerto sobre el cual atender clientes, y un *path* a un archivo que servirá de recurso raíz
* Client: Recibe el nombre del *host* al cual conectarse, y el puerto sobre el cual el servidor se encuentra atendiendo.

Cuando un cliente se pretenda conectar al puerto en el cual el servidor se encuentra atendiendo pedidos, se pedirá al usuario que ingrese texto por entrada estándar. Este texto es enviado por socket y recibido por el servidor de manera no bloqueante. El petitorio HTTP será analizado y ejecutado por el servidor, modificando el repositorio de recursos de ser necesario. El servidor mostrará por salida estándar la información básica de la operación pedida por el cliente, mientras que el cliente recibirá del servidor, por socket, la respuesta al petitorio, que le informará si fué posible o no ejecutar su pedido.

### Requerimientos de la arquitectura del servidor

Se espera que el servidor sea capaz de atender varios clientes en forma simultanea, implementando hilos del sistema operativo para resolver la comunicación de cada uno sin afectar la capacidad de la aplicación de continuar atendiendo. Periodicamente, el servidor deberá realizar una tarea de *cleanup*, liberando los recursos ocupados por los clientes que hayan terminado, a modo de permitir una ejecución estable y continua en el tiempo.

El servidor deberá correr hasta que el usuario que lo inició ingrese un caracter 'q' por entrada estándar, en cuyo caso deben cerrarse todas las conexiones clientes (por más que aún estén activas) y salir de forma ordenada, garantizando no dejar sockets abiertos o hilos sin recuperar.

Además es condición para el desarrollo de la aplicación el correcto uso de polimorfismo para la resolución de las respuestas del servidor.

Todo el código que compone el sistema fué escrito en el lenguaje de programación C++, acorde a las especificaciones establecidas en el estándard ISO C++11, usando nada más que las bibliotecas estándar del lenguaje. Se priorizó en el diseño el uso de tipos de datos abstractos y de objetos, evitando así el uso de variables y funciones globales.

## Diseño del cliente

La aplicación cliente es relativamente sencilla; esta pide al usuario que ingrese un petitorio HTTP por entrada estándar, lo envía al servidor, y espera su respuesta para imprimirla en pantalla tal cual se recibió. Para dar al servidor la señal de que el cliente terminó de enviar su mensaje, se cierra el canal de escritura del socket, dejando sólo abierta la lectura para recibir la respuesta.

## Diseño del servidor

Para el diseño del servidor, se buscó desacoplar la lógica de manejo de los clientes de la lógica de resolución de los pedidos en sí, obteniendo así una arquitectura que podría ser fácilmente reutilizada con distintos protocolos de comunicación. Para lograr esto, se definió una clase abstracta Protocol, que es luego extendida por la implementación puntual del protocolo HTTP encapsulada en la clase HTTPProtocol. Así, HTTPProtocol es capaz de recibir un pedido, resolverlo y enviar la respuesta de vuelta sin necesidad de saber absolutamente nada sobre cómo está implementada la arquitectura de sockets aceptadores y sockets activos. A su vez, ninguna de las clases que conforman la arquitectura del servidor necesitan saber nada de HTTP, sólo que existe un protocolo que llevar a cabo, y la interfaz del objeto que representa dicho protocolo.

### Arquitectura del servidor

Para permitir la comunicación concurrente con varios clientes, se implementa en el servidor una arquitectura multihilo con un objeto vivo AcceptorSocket, que a su vez es capaz de crear otros objetos vivos ActiveSocket. Al comenzar la ejecución del programa servidor, se crea una clase **ServerApplication**, que inicializa el protocolo HTTP con una referencia a un recurso compartido **ResourceRepository**. Con el protocolo creado, este se pasa por referencia al socket aceptador sobre el cual el servidor aceptará clientes. Llamando a rackup() del servidor, este pone a ejecutar el AcceptorSocket, y se queda a la espera de que el usuario ingrese un caracter 'q', en cuyo caso cierra la ejecución.

La clase **AcceptorSocket** se crea haciendo *bind* y *listen* a un puerto del sistema operativo. Una vez puesto en marcha con el método *start*, el AcceptorSocket correrá sobre su propio hilo, en un loop donde para cada iteración se atenderá un cliente y se lo pondrá a comunicarse con el programa mediante un socket activo. Acto seguido, el cliente se guarda en una lista y se procede a iterar la lista de clientes para borrar aquellos que ya terminaron de comunicarse, a modo de liberar recursos y asegurar que el servidor pueda atender un gran número de clientes sin perder performance. La creación de un socket activo se hace moviendo el socket que fué aceptado, a una clase ActiveSocket. De esta manera, se garantiza que el ownership del socket peer no será compartido por el aceptador que lo aceptó, y el socket activo que deberá usarlo para comunicarse con el cliente. 

En su destructor, la clase AcceptorSocket borra todos los sockets activos, y acto seguido cierra su propio socket, lo que genera una excepción en el hilo aceptador, que está constantemente esperando una cliente mediante la función accept() de la interfaz de socket. La excepción es entonces atrapada y tomada como señal de que es necesario frenar la ejecución del bucle en el hilo.

El objeto vivo **ActiveSocket** recibe por movimiento un socket, tomando el control de este en su estado, y una referencia al protocolo que instanció el servidor (en este caso, un HTTPProtocol). En su ejecución, ActiveSocket lanza un hilo nuevo y delega al protocolo el manejo del socket. Es sumamente importante notar que el atributo socket en el método handleSocket de Protocol es declarado constante; de esta forma se garantiza que al delegar el manejo del socket al protocolo, este no será modificado, y que sólo se realizarán las operaciones que no modifican su estado. Así se evita que el protocolo realice operaciones inválidas como querer cerrar el socket, que podrían ocasional problemas como *double-free*. Además, se propone atrapar los errores que pudieran surgir durante la ejecución de handleSocket (puntualmente, errores levantados en los métodos de *send* y *receive*) al momento de delegar desde ActiveSocket. De esta manera, se evita que los errores puedan propagarse hasta cerrar el servidor por algo que sólo debería frenar la ejecución de un socket en particular.

![Diagrama de hilos](https://github.com/PBrrtrn/7542-2C2020-TP3/blob/master/img/diagrama_de_threads.png)

### Implementación del protocolo HTTP

Para llevar a cabo las tareas requeridas del servidor, se hizo una implementación del protocolo HTTP capaz de manejar pedidos y respuestas de forma polimórfica. Al tomar temporalmente el control de un socket, el protocolo HTTP debe usar el socket para recibir un pedido HTTP del cliente en forma de texto plano, ejecutarlo y enviar la respuesta en texto plano al cliente. La recepción del mensaje se realiza byte a byte, escribiendo sobre un caracter buffer y de ahí a un *stringstream*. El envío de la respuesta se lleva a cabo con el mensaje completo. Es una decisión de diseño consciente que **HTTPProtocol** reciba una referencia a run ResultRepository en lugar de crearlo por su cuenta, ya que esto permite al servidor ser el único dueño de sus recursos, y poder acceder a ellos sin necesitar que el protocolo se lo habilite, ya que esta función iría más allá de las responsabilidades de la clase.

![Diagrama de clases](https://github.com/PBrrtrn/7542-2C2020-TP3/blob/master/img/diagrama_de_clase_1.png)

Una vez recibido el petitorio del cliente, este se usa para construir un *string* que se pasa a un objeto **RequestFactory** que reside en el estado del protocolo. Request factory sobrecarga el operador *()*, permitiendo a la clase ser tratada como una función de creación de pedidos HTTP. Al llamarse a esta "función", se parsea el *string* y se devuelve un puntero a una clase derivada de **HTTPRequest** wrappeado en un *unique_ptr* para asegurar la seguridad en memoria.

**HTTPRequest** es una clase abstracta de la cual heredan los petitorios realizables por el usuario (GET y POST), y una clase derivada más *BadRequest* para representar pedidos inválidos que el usuario podría realizar (como PUT o DELETE). Cada clase derivada de HTTPRequest sabe ejecutarse a sí misma, ya que la clase base declara un método virtual puro *execute* que debe ser implementado. El método *execute* recibe siempre una referencia al repositorio de recursos con la que el protocolo fué construido, ya que este será consultado o modificado para la ejecución de un petitorio, y devuelve un puntero a una clase derivada de **HTTPResponse** con el resultado del petitorio. El tipo de la clase devuelta depende del resultado de la ejecución, por lo que esta resolución se realiza de forma también polimórfica. Al igual que con el puntero a HTTPRequest, el puntero a la clase respuesta se wrappea en un *unique_ptr*.

Una clase derivada de **HTTPResponse** recibe por parámetro referencias a los strings necesarios para su construcción; sin embargo, no guarda estas referencias, si no que copia sus contenidos a una variable interna. Cada clase derivada debe entonces implementar un método *getResponse* que devuelve un string con la respuesta al pedido del cliente en texto plano. 

Así, a partir del string con el pedido del cliente, HTTPProtocol crea un HTTPRequest y lo ejecuta, obteniendo un HTTPResponse. Luego se llama a *getResponse* para obtener un string con la respuesta, el cual es casteado a una cadena de caracteres y enviado de vuelta al cliente.

![Diagrama de clases](https://github.com/PBrrtrn/7542-2C2020-TP3/blob/master/img/diagrama_de_clase_2.png)