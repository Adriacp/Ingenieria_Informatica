#include <iostream>
#include <string>

#include <sys/socket.h> //include socket
#include <arpa/inet.h> //include htonl
#include <sys/types.h> //inclyde tipos para resolver problema direccion
#include <unistd.h>
#include <experimental/scope>

using std::experimental::scope_exit;

int main(int argc, char ** argv) {
  
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

std::string message_text("Hola, mundo!\n"); //esto es el mensaje a pasar, en este caso le mandaria el archivo

//uso la funcion sendto
//tenemos que hacer una conversion porque sendto coge socketaddr y tenemos socketaddr_in
size_t bytes_sent = sendto(
                fd_socket,
                message_text.data(),
                message_text.size(),
                0,
                reinterpret_cast<const sockaddr*>(&remote_address), //puntero sockaddr a la direccion de remote_addres
                sizeof(remote_address));

if(bytes_sent<0) {
    std::cerr << "Error sendto" << std::endl;
    return EXIT_FAILURE;
}

close(fd_socket);
std::cout << "Fin OK" << std::endl;
return EXIT_SUCCESS;

}

//dd if=/dev/urandom of=archivo.txt bs=1K count=1
//cmp archivo.txt archivo1.txt && echo OK || echo No Ok comprobar si dos archivos son iguales