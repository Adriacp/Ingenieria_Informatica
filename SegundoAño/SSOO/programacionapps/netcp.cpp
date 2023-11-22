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
};

std::optional<program_options> parse_args(int argc, char** argv) {
  std::vector<std::string_view> args(argv + 1, argv + argc);
  program_options options;
  for(auto it = args.begin(), end = args.end(); it != end; it++) {
    if(*it == "-h" || *it == "--help") {
      options.show_help = true;
    }
    if(*it == "-o" || *it == "--output") {
      if(++it != end) {
        std::cout << *it;
        options.output_filename = *it;
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


//int open(const char *pathname, int flags, mode_t mode);
std::error_code write_file(int fd, const std::vector<uint8_t>& buffer);

int main(int argc, char** argv) {
  
  
  auto options = parse_args(argc, argv);
  if(!options) return EXIT_FAILURE;
  if(options.value().show_help) print_usage();


  const char *filename = argv[1];
  int flags = O_RDONLY | O_CREAT;
  mode_t filemode = 0666;
  
  std::expected<int, std::error_code> fd = open_file(filename, flags, filemode);
  if(!fd.has_value()) {
    std::cerr << "Error al abrir el archivo\n";
    return EXIT_FAILURE; // no se como otra forma para salir del programa asi qeu supongo que esto es lo que hare
  }

  //fd -> descriptor de archivo, resulta que la funcion open ya está creada

  std::vector<uint8_t> buffer(1024);
  
  std::error_code error = read_file(fd.value(), buffer);

  if (error) {
    close(fd.value());
    return error.value();
  }

  //aqui va el socket y toda la parte del netcpclase.cpp
    
    int fd_socket=socket(AF_INET,SOCK_DGRAM,0); //creamos un socket AF_INET:IPv4 Internet protocols SOCK_DGRAM: Supports datagrams (connectionless, unreliable messages ofa fixed maximum length).
    if(fd_socket<0) {
        std::cerr << "Error en socket" << std::endl;
        return EXIT_FAILURE;
    }

auto src_guard=scope_exit( //esto sale mal pero funciona con g++ -o netcp -std=c++2b netcpclase.cpp
            [fd_socket] { close(fd_socket); }
            ); //si fd socket sale del bloque donde se definio se llama a fd_socket close, por lo que no hay que poner close en cada detección de error.

//la libreria de linux esta escrita en C

// Adress to send to
  sockaddr_in remote_address {}; //en c++ es una inicializacion por valor, automaticamente crea un codigo para generarlo a 0, es decir asi me aseguro que esta a 0, ahora relleno los campos que necesito.
  remote_address.sin_family = AF_INET; //familia af_inet
  remote_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //los protocolos en internet trabaja en bigendian, pero la mayoria de nuestros ordenadores estan en little endian, htonl, hace la conversion a nuestro endian, ya sea little o big
  remote_address.sin_port = htons(8080); //esta vez es htons(network short) pero sigue siendo por big y littl endian
  //funciona bien, solo tengo qeu cambiar lo que hay en testfile2 con el mensaje.

//uso la funcion sendto
//tenemos que hacer una conversion porque sendto coge socketaddr y tenemos socketaddr_in
size_t bytes_sent = sendto(
                fd_socket,
                buffer.data(),
                buffer.size(),
                0,
                reinterpret_cast<const sockaddr*>(&remote_address), //puntero sockaddr a la direccion de remote_addres
                sizeof(remote_address));

if(bytes_sent<0) {
    std::cerr << "Error sendto" << std::endl;
    return EXIT_FAILURE;
}

close(fd_socket);
std::cout << "Fin OK" << std::endl;
//return EXIT_SUCCESS;

  close(fd.value());

  return EXIT_SUCCESS;
}
/*Comprobacion:
dd if=/dev/urandom of=testfile bs=1K count=1 iflag=fullblock //creo un testfile con datos aleatorios menor de 1K
netcat -lu 8080 > testfile2 hago un testfile 2 volcando la info
cmp testfile testfile2 para comprobar si son iguales
*/