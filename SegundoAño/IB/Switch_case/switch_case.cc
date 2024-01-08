#include <iostream>

void usage(int argc, char* argv[]) {
  if(argc != 2 ) {
    std::cerr << "Error en los parámetros\n";
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char* argv[]) {
  usage(argc, argv);
  std::string cadena{argv[1]};
  std::string resultado;
  for(int i = 0; i < cadena.length(); ++i) {
    cadena[i] == toupper(cadena[i]) ? resultado.push_back(tolower(cadena[i])) : resultado.push_back(toupper(cadena[i]));
  }
  std::cout << resultado << std::endl;
  return 0;
}