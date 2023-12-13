#include <iostream>
#include <vector>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

    if(argc<3) {
        std::cerr<<"Wrong number of arguments\n";
        return EXIT_FAILURE;
    }
    std::string fileName(argv[1]); //nombre del archivo
    std::vector<std::string> command_args;
    for(int i = 2; i<argc; i++) 
        command_args.emplace_back(argv[i]); //resto de argumentos del comando


    mode_t mode=S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd=open(fileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, mode);
    if(fd<0) {
        std::cerr<<"Error at open\n";
        return EXIT_FAILURE;
    }
    //creamos la tuberia antes del proceso hijo para que el proceso hijo la vea
    
    int fds[2]; //un array de tamaño 2
    int return_code=pipe(fds); // fds[0] es el extremo de lectura fds[1] el extremo de escritura
    if(return_code<0) {
        std::cerr<<"Error at pipe\n";
        close(fd);
        return EXIT_FAILURE;
    }

    pid_t pid=fork(); //fork sirve para crear un proceso hijo

    if(pid>0) {

        close(fds[1]); //ya que no voy a usar el de escritura
        char buffer[256]; //esto seria mi buffer
        int nbytes=0;
        do{
            nbytes=read(fds[0], buffer, 256); //read_file
            write(fd, buffer, nbytes); //send to //habria que usar el write sobre fds[1] en caso de recepcion;           
        } while(nbytes>0);
        if(nbytes<0)
            std::cerr<<"Error at READ\n";
        close(fds[0]);
        int status;
        // lo ejecuta solamente el proceso padre, ese pid es el valor pid del hijo creado correctamente, nuevo proceso
        bool flag=true;
        while(flag) {
        int res = waitpid(pid, &status,WNOHANG); //esto hace que el proceso se que da a la espera hasta que se cierre el hijo, ahroa no se bloquea(WHOHANG)       
        if(res!=0)
            flag=false;
        } //con esta funcion puedo consultar si el proceso hijo ha terminado o no. ahora el proceso padre no se bloquea y podría hacer otras cosas dentro de ese bucle
        close(fd);
        return EXIT_SUCCESS; //el proceso padre no se puede desentender del proceso hijo

    }
    else if(pid == 0) {
        // Estoy en el hijo, este codigo solo lo va a ejecutar el hijo, la variable pid para el hijo va a ser 0
        // el proceso hijo usa el extremo de escritura del pipe

        close(fds[0]); // porque vamos a usar el extremo de escritura por lo que podemos quitar el de lectura
        dup2(fds[1],STDOUT_FILENO);
        //en case de recepcion
        //dup2(fds[0],STDIN_FILENO); // al reves que en el otro modo
        close(fds[1]);

        std::vector<const char *> exec_args;
        for(auto &str : command_args) {
            exec_args.push_back(str.c_str()); //vector de cadenas de c este vector es el que paso por argumentos pero no esta terminado
        }
        //add nullptr, añadir un puntero nulo al final del vector para saber cuando no quedan argumentos
        exec_args.push_back(nullptr);

        int exec_result=execvp(exec_args[0], const_cast<char * const *>(exec_args.data())); //paso el programa (ls) seria la primera posicion de exec_args
        // si llego a esta linea ha habido un error por que exec sustituye el programa por oto, por lo que puedo poner un error
        std::cerr<<"Error at EXEC\n";
        return errno;
    }
    else { //en caso de pid negativo, error no ha funcionado el fork
        std::cerr<<"Error at fork\n";
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}