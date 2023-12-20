#include "subprocess.hpp"
// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Sistemas operativos
// Curso: 2º
// Práctica 2: Programación de apps
// Autor: Adrián Manuel Acuña Perdomo
// Correo: alu0101592084@ull.edu.es
// Fecha: 18/12/2023
// Archivo subprocess.cpp: Inplementacion de la clase subprocess.hpp
// 13/12/2023 - Creación del código


#include <iostream>

subprocess::subprocess(const std::vector<std::string> &args, subprocess::stdio redirected_io) {
  std::cout << "constructor\n";
}

bool subprocess::is_alive() {
  return false;
}

std::error_code subprocess::exec() {
  return std::error_code(0, std::system_category());
}

std::error_code subprocess::wait() {
  return std::error_code(0, std::system_category());
}

std::error_code subprocess::kill() {
  return std::error_code(0, std::system_category());
}

pid_t subprocess::pid() {
  return pid_t();
}

int subprocess::stdin_fd() {
  return 0;
}

int subprocess::stdout_fd() {
  return 0;
}
