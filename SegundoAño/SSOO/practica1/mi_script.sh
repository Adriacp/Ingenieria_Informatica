#!/bin/bash

# sysinfo - Un script que informa del estado del sistema

#### Constantes
PROGNAME=$(basename $0)

TITLE="Información del sistema"
RIGHT_NOW=$(date +"%x %r%z")
TIME_STAMP="Actualizada el $RIGHT_NOW por $USER"
TEXT_ULINE=$(tput sgr 0 1)

#### Estilo
TEXT_BOLD=$(tput bold)
TEXT_GREEN=$(tput setaf 2)
TEXT_RESET=$(tput sgr0)

#### Funciones
error_exit() {
    echo "${PROGNAME}: ${1:-"Error desconocido"}" 1>&2
    exit 1
}
system_info()
{
    # Función de stub temporal
    echo "${TEXT_ULINE}Versión del sistema${TEXT_RESET}"
    uname -a
}

show_uptime()
{
    echo "${TEXT_ULINE}Tiempo de encendido del sistema${TEXT_RESET}"
    uptime -p
}

drive_space()
{
    echo "${TEXT_ULINE}Espacio en el disco duro${TEXT_RESET}"
    df -h
}

home_space()
{
    echo "${TEXT_ULINE}Espacio usado de los directorios${TEXT_RESET}"
    if [ "$USER" == "root" ]; then
        echo "${TEXT_ULINE}Espacio en home por usuarios${TEXT_RESET}"
        echo
        echo "Bytes Directorio"
        du -s /home/* | sort -nr
    fi
}

usage() {
    
    echo "Usage: sysinfo [-f file ] [-i] [-h]"
}

write_page() {

    cat << _EOF_
$TEXT_BOLD$TITLE$TEXT_RESET

$TEXT_GREEN$TIME_STAMP$TEXT_RESET
_EOF_

system_info
echo
show_uptime
echo
drive_space
echo
home_space

}

interactive=
filename=~/sysinfo.txt

while [ "$1" != "" ]; do
    case $1 in
        -f | --file )
            shift
            filename=$1
            ;;
        -i | --interactive )
            interactive=1
            ;;
        -h | --help )
            usage
            exit
            ;;
        * )
            usage
            error_exit "Opcion desconocida"
    esac
    shift
done
if [ "$interactive" = 1 ]; then #-z compueba que este vacio, es decir es lo mismo que interactive==0;
    echo -n "¿En que archivo quieres guardar la salida? "
    read filename
fi


write_page > $filename

#### Programa principal

