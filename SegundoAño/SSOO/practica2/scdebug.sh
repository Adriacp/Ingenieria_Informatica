#!./ptbash

##Constantes
prog=""
sto_option=""
args=""
pid=""
vprog=""
vallprog=""
lista_pids=""
natch_option=""
menos_s=0
menos_g=0
commName=""
stoppids=""
name=0
max_time=0
total_time=0
calls=0
errs=0
sort_opcion="-k5,5n"

#funciones

Main() {
  Comprobar "$@"
  Elección "$@"
  if [ $1 = "-v" ]; then
    shift
    vprog=$1
    OpcionV
  elif [ $1 = "-vall" ]; then
    shift
    vallprog=$1
    OpcionVall
  elif [ $menos_s -eq 1 ]; then
    OpcionesS "$@"
  elif [ $menos_g -eq 1 ]; then
    OpcionesG "$@"
  else
    ProcesosUsuario
    Opciones "$@"
  fi
}

Comprobar() {
  if [ $# -le 0 ]; then
    echo "Error parametros incorrectos, prueba --help"
    exit 1
    fi
}

Elección() {
  while [ $# -gt 0 ]; do
    case "$1" in
      -S)
        menos_s=1;
        shift
      ;;
      -g|-ge|-gc)
        menos_g=1;
        shift
      ;;
      *)
      shift
      ;;

    esac
  done
}

Opciones() {
  while [ $# -gt 0 ]; do
    case "$1" in
      -h |--help)
        Usage
      ;;
      -sto)
      shift
      sto_option=$1
      shift
      ;;
      -natch)
      shift
      Natch "$@"
      shift
      ;;
      -k)
      OpcionK
      shift
      ;;
      -pattch)
      lista_procesos=$(ps -u $USER --no-header --sort=etime | tr -s " " | cut -d ' ' -f 2)
      for pids in $lista_procesos; do
          strace -p $pids
      done
      shift
      ;;
      *)
        prog="$1"
        shift
        args="$@"
        StraceProg
      ;;
    esac
  done
}

OpcionesS() {
  while [ $# -gt 0 ]; do
    case "$1" in
      -h|--help)
        UsageS
      ;;
      -k)
        OpcionK
        shift
      ;;
      -S)
      shift
      ;;
      *)
        commName="$1"
        shift
        prog="$1"
        shift
        args="$@"
        MenosS
        shift
      ;;
    esac
  done
}

OpcionesG() {
  while [ $# -gt 0 ]; do
    case "$1" in
      -h|--help)
        UsageG
      ;;
      -k)
      OpcionK
      shift
      ;;
      -g)
      OpcionG
      shift
      ;;
      -gc|-ge)
      shift
      if [ "$1" == "-inv" ]; then
        sort_opcion="-r $sort_opcion"
      fi
      OpcionGC
      shift
      ;;
      *)
      shift
      prog=$1
      ;;
    esac
  done
}

OpcionG() {
  stoppids=$(pgrep -u $USER -x -t T -f "^traced_") #busco todos los procesos parados del usuario que comiencen por traced_

  if [ -z $stoopid ]; then
    echo "No se encontro ningún proceso stopped que comience por traced_"
    exit 0
  fi

  for stoppid in $stoppids; do
    
    strace -p $stoppid & > $HOME/scdebug/$prog

    sleep 0.1 

    kill -SIGCONT $stoopid > $HOME/scdebug/$prog

  done

  echo procesos traced detenidos han sido reactivados
}

OpcionGC() {
  stoppids=$(pgrep -u $USER -x -t T -f "^traced_") #busco todos los procesos parados del usuario que comiencen por traced_

  if [ -z $stoopid ]; then
    echo "No se encontro ningún proceso stopped que comience por traced_"
    exit 0
  fi

  for stoppid in $stoppids; do
    
    output=$(strace -c -U name,max-time,total-time,calls,errors ls)
    
    variable=$(strace -c ls 2>&1 | tail -n 1 | tr -s ' ' | cut -d ' ' -f2-4)

    name=$(awk '{print $1}' <<< variable )
    max_time=$(awk '{print $2}' <<< variable )
    total_time=$(awk '{print $3}' <<< variable )
    calls=$(awk '{print $4}' <<< variable ) #guardo cada uno en su variable
    errs=$(awk '{print $5}' <<< variable )

    sleep 0.1

    kill -SIGCONT $stoopid

    table+="$stoppid\t$name\t$max_time\t$total_time\t$calls\t$errs\n"

  done

    sorted_table=$(sort $sort_option <<< "$table")

    cat << _EOF_
    PID\tName\tMax-Time\tTotal-time\tCalls\tErrs
    $sorted_table

    Name: $name
    Max-time: $max_time
    Total-Time: $total_time
    Calls: $calls
    Errs: $max_errs
_EOF_
}

MenosS() {
  comm=$( ps -o comm --no-header | head -1)
  echo -n "traced_$commName" > /proc/$$/$comm

  kill -SIGSTOP $$

  LaunchProg=$($prog $args)

  exec $LaunchProg
}

Usage() {
  echo "scdebug [-h] [-sto arg] [-v|-vall] [-nattch progtoattach] [prog[arg1 ...]]"
  exit 1
}

UsageS(){
  echo "scdebug [-h] [-k] -S commName prog [arg...]"
  exit 1
}

UsageG(){
  echo "scdebug [-h] [-k] -g | -gc | -ge [-inv]"
  exit 1
}

OpcionK() {
  procesos_user=$(ps -u $USER -o pid --sort=start_time --no-header | tr -s " " | cut -d ' ' -f 2)
  for pid in $procesos_user; do
      if [ "$pid" -gt 1 ]; then
        if [ -f /proc/$pid/status ]; then
          tracer_pid=$(cat /proc/$pid/status | grep "TracerPid" | tr -d " " | cut -d ':' -f 2)
          if [[ "$tracer_pid" == 1 ]]; then
            kill -9 $pid
            kill -9 $tracer_pid
          fi
        fi
      fi
  done
  echo "Todos los procesos trazadores del usuario: $USER terminados"
}

OpcionV() {
  directorio=${HOME}/.scdebug/$vprog
  nombretrace=$(ls $directorio -t | head -1)
  timefile=$(ls -l $directorio | grep "$nombretrace" | cut -d ' ' -f6-9)
  cat << _EOF_
=============== COMMAND: $vprog =======================
=============== TRACE FILE: $nombretrace =================
=============== TIME: $timefile ==============
_EOF_
}

OpcionVall() {
  directorio=${HOME}/.scdebug/$vallprog
  nombrestrace=$(ls $directorio)
  for trace in $nombrestrace; do
  timefile=$(ls -l $directorio | grep "$trace" | cut -d ' ' -f6-9)
    cat << _EOF_
=============== COMMAND: $vallprog =======================
=============== TRACE FILE: $trace =================
=============== TIME: $timefile ==============

_EOF_
done
}


StraceProg() {
  uuid=$(uuidgen)
  
  dir="${HOME}/.scdebug/${prog}"
  archivo=${dir}/trace_${uuid}.txt
  mkdir -p "$dir"
  
  command="strace ${sto_option} -o ${archivo} ${prog} ${args}"

  $command 2> $archivo & 
  $command 2> error.log & #salida del error de strace
}

#Natch() {
#  BuscarPID
#  uuid=$(uuidgen)
#  
#  dir="${HOME}/.scdebug/${prog}"
#  archivo=${dir}/trace_${uuid}.txt
#  mkdir -p "$dir"
#  
#  command="strace $sto_option -p $pid -o $archivo $prog $args"
#
#  $command 2> $archivo & 
#  $command 2> error.log & #salida del error de strace
#}

#Nueva implementacion de Natch()
Natch() {
    while [ $# -gt 0 ]; do
      nattch_option="$1"
      BuscarPIDNatch
      uuid=$(uuidgen)
      #direccion del directorio
      dir="$HOME/.scdebug/$nattch_option"
      #directorio
      mkdir -p "$dir"
      if [ -z "$nattch_option" ]; then
        #Ejecutamos sin nattch
        command1="strace $sto_option -o $dir/trace_${uuid}.txt $nattch_option"
        $command1  2>&1 /dev/null &
      else
        #ejecutamos con nattch
        command2="strace ${sto_option} -p ${pid} -o ${dir}/trace_${uuid}.txt"
        ${command2}  2>&1 /dev/null &
      fi
      shift
    done
}

BuscarPID() {
  pid=$(ps -u $USER --no-header --sort=etime | grep "$prog" | tr -s " " | cut -d ' ' -f 2 | head -1)
}

BuscarPIDNatch() {
  pid=$(ps -u $USER --no-header --sort=etime | grep "$nattch_option" | tr -s " " | cut -d ' ' -f 2 | head -1)
}

ProcesosUsuario() {
  lista_pids=$(ps -u $USER --no-header --sort=etime | tr -s " " | cut -d ' ' -f 2)
  
  for pids in $lista_pids; do
  TracerPid=$(cat /proc/$pids/status | grep TracerPid | tr -s " " | cut -d ':' -f 2)  
  pid_procesos=$(ps -u $USER --no-header --sort=etime | grep $pids |  tr -s " " | cut -d ' ' -f 5)
  echo $pids $pid_procesos $TracerPid
  done
}

Main "$@"