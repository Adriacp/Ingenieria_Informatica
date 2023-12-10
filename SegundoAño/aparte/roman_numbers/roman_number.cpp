#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

/// @brief Esta función devuelve el numero romano en numero decimal 
/// @param s numero romano en forma de string
/// @return numero romano en decimal
int romanToInt(std::string s) {
  std::unordered_map<char, int> number;
    number['I'] = 1;
    number['V'] = 5;
    number['X'] = 10;
    number['L'] = 50;
    number['C'] = 100;
    number['D'] = 500;
    number['M'] = 1000;
    int resultado = 0;
    for(int i = 0; i < s.length(); i++) {
      if(number[s[i]] < number[s[i+1]]) {
          resultado -= number[s[i]];
      } else {
          resultado += number[s[i]];
        }
      }
  return resultado;
}

/// @brief funcion usage para comprobar el correcto paso de parámetros
/// @param argc numero de parámetros
/// @param argv array con los parámetros
void Usage(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "Error en los parámetros, pruebe ./roman_numbers --help para ayuda\n";
    exit(EXIT_FAILURE);
  }
  std::string key_word{argv[1]};
  if (key_word == "--help") {
    std::cout << "Este programa se ejecuta de la siguiente forma:\n"
                 "./roman_numbers 'roman_number' \n";
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::string roman_number = argv[1];
  std::cout << romanToInt(roman_number) << std::endl;
  return EXIT_SUCCESS;
}