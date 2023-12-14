// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Sistemas operativos
// Curso: 2º
// Práctica 2: Programación de apps
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 18/12/2023
// Archivo subprocess.hpp: Archivo que contiene la clase de subprocess subprograma
// 13/12/2023 - Creación del código

#pragma once

#include <vector>
#include <string>
#include <system_error>

class subprocess {
  public: 
    enum class stdio {
      in,
      out,
      err,
      outerr
    };

    subprocess(
      const std::vector<std::string>& args,
      subprocess::stdio redirected_io
    );

    bool is_alive();

    std::error_code exec();
    std::error_code wait();
    std::error_code kill();

    pid_t pid();

    int stdin_fd();
    int stdout_fd();
};