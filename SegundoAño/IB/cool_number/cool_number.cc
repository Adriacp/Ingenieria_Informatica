/*
Un número natural se dice que es guay si la suma de los dígitos que están en posiciones
impares (empezando a contar por la derecha) es un número par. Por ejemplo, 2 y 679031 son números
guay, pero 357199 y 607 no lo son.
Escriba un programa que imprima si un número dado es guay o no. La salida del programa debiera ser “N
es GUAY” o bien “N no es GUAY”.
*/

#include <iostream>

void Usage(int argc, char* argv[]) {
  std::string help{"--help"};
  if (argc != 2) {
    std::cerr << "Error en el número de parámetros, pruebe --help\n";
    exit(EXIT_FAILURE);
  } else if (argv[1] == help) {
    std::cout << "El programa comprueba si un numero natural es guay, ejecute de la forma:\n ./cool_number \"numero\" \n";
    exit(EXIT_SUCCESS);
  } else {
    std::string cadena = argv[1];
    bool digito = true;
    for (int i = 0; i < cadena.length(); i++) {
      if(!isdigit(cadena[i])) digito = false;
    }
    if(!digito) {
      std::cerr << "Error, el parametro enviado no es un numero correcto, pruebe --help para mas informacion.\n";
      exit(EXIT_FAILURE);
    }
  }
}

bool IsCoolNumber(int n) {
    int sumaDigitosImpares = 0;
    bool posicionImpar = true;

    // Recorremos los dígitos del número
    while (n > 0) {
        int digito = n % 10;

        // Sumamos solo los dígitos en posiciones impares
        if (posicionImpar) {
            sumaDigitosImpares += digito;
        }

        // Cambiamos la posición para el próximo dígito
        posicionImpar = !posicionImpar;

        // Eliminamos el último dígito
        n /= 10;
    }

    // Verificamos si la suma de los dígitos en posiciones impares es par
    return sumaDigitosImpares % 2 == 0;
}

int main(int argc, char* argv[]) {
  Usage(argc, argv);

  std::string n = argv[1];
  int num = std::stoi(n);

  if(IsCoolNumber(num)) {
    std::cout << num << " es GUAY\n";
    exit(EXIT_SUCCESS);
  } else {
    std::cout << num << " no es GUAY\n";
    exit(EXIT_SUCCESS);
  }

  return 0;
}