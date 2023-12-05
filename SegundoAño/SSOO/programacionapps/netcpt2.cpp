#include <iostream> //std::cout/std::cin
#include <vector> //std::Vector
#include <optional> //std::optional
#include <stdint.h> //uint8_t
#include <system_error> // std::error_code
#include <expected> //std::expected
#include <stdexcept>
#include <sys/types.h> //inclyde tipos para resolver problema direccion
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <filesystem>
#include <fcntl.h>
#include <string>
#include <cerrno>
#include <signal.h>

#include <sys/socket.h> //include socket
#include <arpa/inet.h> //include htonl
#include <experimental/scope>

using std::experimental::scope_exit;

void Usage() {
  std::cout << "el programa se ejecuta asi: \n";
}

struct program_options {
  bool show_help = false;
  std::string output_filename;
  bool listening = false;
  std::string listener_filename;
};

std::optional<program_options> parse_args(int argc, char** argv) {
  std::vector<std::string_view> args(argv + 1, argv + argc);
  program_options options;
  for(auto it = args.begin(), end = args.end(); it != end; it++) {
    if(*it == "-h" || *it == "--help") {
      options.show_help = true;
    }
    if(*it == "-l") {
      if(++it != end) {
        options.listening = true;
        options.listener_filename = *it;
      }
      else {
        std::cerr << "Error...\n";
        return std::nullopt;
      }
    }
  }
  return options;
}

void print_usage(void) {
  std::cout << "falta un archivo como argumento\n"
               "Modo de empleo: netcp [-h] ORIGEN\n";
}

[[nodiscard]]
std::error_code read_file(int fd, std::vector<uint8_t>& buffer) {
  ssize_t bytes_read = read(fd, buffer.data(), buffer.size()); //me falta la definicion de read buffer.data = inicio de la posicion
  if(bytes_read < 0) {
    return std::error_code(errno, std::system_category()); //debo consultar el valor de errno para saber el tipo de error
  }
  buffer.resize(bytes_read);
  return std::error_code(0, std::system_category());
} //devuelve 0 en caso de exito o un valor distinto (errno) en caso de error

 //falta open, este esta correcto, primera parte realizada.
[[nodiscard]]
std::expected<int, std::error_code> open_file(const std::string& path, int flags, mode_t mode) {
  int fd = open(path.c_str(), flags, mode);
  if(fd == -1) {
    std::error_code error(errno, std::system_category());
    return std::unexpected(error);
  }
  return fd;
}

std::optional<sockaddr_in> make_ip_address(
  const std::optional<std::string> ip_address, uint16_t port) {
  //in_addr_t ipAddress = inet_addr(ip_address.value().c_str());

  sockaddr_in remote_address {}; //en c++ es una inicializacion por valor, automaticamente crea un codigo para generarlo a 0, es decir asi me aseguro que esta a 0, ahora relleno los campos que necesito.
  remote_address.sin_family = AF_INET; //familia af_inet
  remote_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //los protocolos en internet trabaja en bigendian, pero la mayoria de nuestros ordenadores estan en little endian, htonl, hace la conversion a nuestro endian, ya sea little o big
  remote_address.sin_port = htons(port); //esta vez es htons(network short) pero sigue siendo por big y littl endian
  return remote_address;
}

std::expected<int, std::error_code> make_socket(
  std::optional<sockaddr_in> address = std::nullopt) {
    int fd_socket=socket(AF_INET,SOCK_DGRAM,0); //creamos un socket AF_INET:IPv4 Internet protocols SOCK_DGRAM: Supports datagrams (connectionless, unreliable messages ofa fixed maximum length).
    if(fd_socket<0) {
      std::error_code error (errno, std::system_category());
      return std::unexpected(error);
    }
    return fd_socket;
  }

std::error_code send_to(int fd_socket, const std::vector<uint8_t>& buffer, 
  const sockaddr_in& remote_address) {
  size_t bytes_sent = sendto(
                  fd_socket,
                  buffer.data(),
                  buffer.size(),
                  0,
                  reinterpret_cast<const sockaddr*>(&remote_address), //puntero sockaddr a la direccion de remote_addres
                  sizeof(remote_address));
    if(bytes_sent<0) {
      std::error_code error(errno, std::system_category());
      return error;
  }
return std::error_code (0, std::system_category());
}

std::error_code netcp_send_file(const std::string& filename) {
  
  std::cout << "Modo escritura...\n";
  //const char *archivo = filename;
  
//hacer el socket
//make address
const std::optional<std::string> ip_address("127.0.0.1");
uint16_t port(8080);

auto remote_address = make_ip_address(ip_address, port);
if(!remote_address) {
  std::cerr << "Error al crear la ip\n";
  std::error_code error(errno, std::system_category());
  return error;
}
//socket
int fd_socket;
auto result = make_socket(remote_address.value());
if(result) {
  fd_socket = result.value();
}
else {
  std::cerr << "error al crear el socket\n";
  std::error_code error (errno, std::system_category());
  return error;
}
  
  int flags = O_RDONLY;
  mode_t filemode = 0666;
  
  //abrir el archivo
  std::expected<int, std::error_code> fd = open_file(filename, flags, filemode);
  if(!fd.has_value()) {
    std::error_code error(errno, std::system_category());
    std::cerr << "Error al abrir el archivo\n";
    return error; // no se como otra forma para salir del programa asi qeu supongo que esto es lo que hare
  }

  //fd -> descriptor de archivo, resulta que la funcion open ya está creada
  std::vector<uint8_t> buffer(1024);
  while(buffer.size() > 0) {
  //si el tamaño del buffer es mayor a 0 eso significa que todavia hay bytes por leer. 
  std::error_code error_read = read_file(fd.value(), buffer);
 //el tamaño del buffer indica la cantidad de bytes leidos
  if (error_read) {
    close(fd.value());
    error_read.message();
    std::error_code error (errno, std::system_category());
    return error;
  }
  //uso la funcion sendto
  //tenemos que hacer una conversion porque sendto coge socketaddr y tenemos socketaddr_in
  std::error_code send_result = send_to(fd_socket, buffer, remote_address.value());
  
  if (send_result) {
    close(fd.value());
    send_result.message();
    return send_result;
  }
  usleep(1000);
}

//scope_exit para que siempre se cierre el socket
auto src_guard=scope_exit( //esto sale mal pero funciona con g++ -o netcp -std=c++2b netcpclase.cpp
            [fd_socket] { close(fd_socket); }
            ); //si fd socket sale del bloque donde se definio se llama a fd_socket close, por lo que no hay que poner close en cada detección de error.

auto src_guard2=scope_exit( //esto sale mal pero funciona con g++ -o netcp -std=c++2b netcpclase.cpp
            [fd] { close(fd.value()); }
            ); //si fd socket sale del bloque donde se definio se llama a fd_socket close, por lo que no hay que poner close en cada detección de error.


  close(fd_socket);
  close(fd.value());
  return std::error_code (0, std::system_category());
}
//receive_from
std::error_code recieve_from(int fd, std::vector<uint8_t>& buffer, sockaddr_in& address) {
  socklen_t src_len = sizeof(address);
  int bytes_recieved = recvfrom(
                                fd,
                                buffer.data(),
                                buffer.size(),
                                0,
                                reinterpret_cast<sockaddr*>(&address),
                                &src_len);
  
  if(bytes_recieved < 0) {
    return std::error_code(errno, std::system_category());
  }
  buffer.resize(bytes_recieved);
  return std::error_code(0, std::system_category());
}


//int open(const char *pathname, int flags, mode_t mode);
std::error_code write_file(int fd, const std::vector<uint8_t>& buffer) {
  size_t bytes_written = write(
                  fd,
                  buffer.data(),
                  buffer.size());
    if(bytes_written<0) {
      return std::error_code(errno, std::system_category());
  }
return std::error_code (0, std::system_category());
}

//recieve from

std::error_code netcp_receive_file(const std::string& filename) { //al hacer el socket hay que usar bind para darle un puerto e ip
  std::cout << "Modo escucha...\n";

//hacer el socket
//make address
std::optional<std::string> ip_address;
char* ip_char = std::getenv("NETCP_IP"); //necesito las variables de entonro para el puerto y para la ip
if(!ip_char) {
  ip_address = "127.0.0.1";
}
else {
  ip_address = ip_char;
}
char* puerto_char = std::getenv("NETCP_PORT");
uint16_t port;
if(puerto_char) {
  port = static_cast<uint16_t>(std::strtoul(puerto_char, nullptr, 10)); // no funciona
}
else {
  port = 8080;
}

  auto remote_address = make_ip_address(ip_address, port);
  if(!remote_address) {
    std::cerr << "Error al crear la ip\n";
    std::error_code error(errno, std::system_category());
    return error;
  }
  //socket
  int fd_socket;
  auto result = make_socket(remote_address.value());
  if(result) {
    fd_socket = result.value();
  }
  else {
    std::cerr << "error al crear el socket\n";
    std::error_code error (errno, std::system_category());
    return error;
  }

  //asignar la dirección al socket
  if (bind(fd_socket, reinterpret_cast<sockaddr*>(&remote_address), sizeof(remote_address)) == -1) {
    std::cerr << "Error al enlazar el socket a la dirección." << std::endl;
    close(fd_socket);
    std::error_code error (errno, std::system_category());
    return error;
  }

  int flags = O_RDONLY | O_CREAT; // si no existe tengo que crearlo
  mode_t filemode = 0666;
  
  //abrir el archivo
  std::expected<int, std::error_code> fd = open_file(filename, flags, filemode);
  if(!fd.has_value()) {
    std::error_code error(errno, std::system_category());
    std::cerr << "Error al abrir el archivo\n";
    return error; // no se como otra forma para salir del programa asi qeu supongo que esto es lo que hare
  }

  std::vector<uint8_t> buffer(1024);
  
  while(true) {
    std::error_code recieve_result = recieve_from(fd.value(), buffer, remote_address.value());
    if(recieve_result) {
      std::cerr << "Error al recibir el archivo\n";
      return std::error_code(errno, std::system_category());
    }
    if(!buffer.empty()) {
      std::error_code write_result = write_file(fd.value(), buffer);
      if(write_result) {
        std::cerr << "Error al escribir el archivo\n";
        return std::error_code(errno, std::system_category());
      }
    } else {
      break;
    }
  }

  //devolver recursos
  close(fd_socket);
  close(fd.value());
  return std::error_code (0, std::system_category());
}

int main(int argc, char** argv) {
  
  auto options = parse_args(argc, argv);
  if(!options) return EXIT_FAILURE;
  if(options.value().show_help) {
    print_usage();
    return EXIT_SUCCESS;
  }
  if(options.value().listening) {
    std::error_code fallo_listening = netcp_receive_file(options.value().listener_filename);
    if(fallo_listening) {
      fallo_listening.message();
      return fallo_listening.value();
    }
  }
  else {
    std::error_code fallo_sending = netcp_send_file(argv[1]);
    if(fallo_sending) {
      fallo_sending.message();
      return fallo_sending.value();
    }
}

std::cout << "fin ok\n";

return EXIT_SUCCESS;

}
/*Comprobacion:
dd if=/dev/urandom of=testfile bs=1K count=1 iflag=fullblock //creo un testfile con datos aleatorios menor de 1K
netcat -lu 8080 > testfile2 hago un testfile 2 volcando la info
cmp testfile testfile2 para comprobar si son iguales

  //aqui va el socket y toda la parte del netcpclase.cpp
    //make socket


//la libreria de linux esta escrita en C

// Adress to send to

//asignar la direccion al socket
/*
if (bind(fd_socket, reinterpret_cast<sockaddr*>(&remote_address), sizeof(remote_address)) == -1) {
    std::cerr << "Error al enlazar el socket a la dirección." << std::endl;
    close(fd_socket);
    std::error_code error (errno, std::system_category());
    return error;
  }
*/ //esto es solo para el recieve?
