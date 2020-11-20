#include <fstream>
#include <string>

#ifndef __FILE_H__
#define __FILE_H__

class File {
	/* 
	Clase que encapsula las operaciones necesarias para trabajar con un archivo
	garantizando seguir RAII, abriendo el archivo en el constructor y cerrandolo
	en el destructor de la clase.																							*/
private:
	std::ifstream f;
	File(const File &other) = delete;
	File& operator=(const File &other) = delete;
public:
	explicit File(const char *filepath);
	~File();
	std::string read();
};

#endif
