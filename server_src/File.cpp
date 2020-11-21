#include <iostream>
#include <sstream>

#include "File.h"

File::File(const char *filepath) : f(filepath) {
  if (!this->f) throw std::runtime_error("Unable to open file");
}

File::~File() {
  (this->f).close();
}

std::string File::read() {
  std::stringstream stream;
  stream << (this->f).rdbuf();
  return stream.str();
}
