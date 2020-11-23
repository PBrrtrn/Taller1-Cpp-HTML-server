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

