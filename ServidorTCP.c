#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "Struct.h"
#include "Funciones.h"
#include "Juego.h"

#define MSG_SIZE 250
#define MAX_CLIENTS 50
char *user;
char *password;
/*
 *Creamos función que separe cualquier valor del buffer y me devuelva un array
 */
void separar(char *buffer, char *array[]){
    char *token;
    int i = 0;
    token = strtok(buffer, " ");
    while(token != NULL){
        array[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
}

int main (){
    /*---------------------------------------------------- 
        Descriptor del socket y buffer de datos                
    -----------------------------------------------------*/
    int sd, new_sd;
    struct sockaddr_in sockname, from;
    char buffer[MSG_SIZE];
    socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    Jugador arrayClientes[MAX_CLIENTS];
    Juego arrayJuegos[10];
        for(int v=0; v<10; v++){
            arrayJuegos[v].turno=0;
        }
    int numClientes = 0;
    //contadores
    int i,j,k;
    int recibidos;
    char identificador[MSG_SIZE];

    int on, ret;

    /* --------------------------------------------------
        Se abre el socket 
    ---------------------------------------------------*/
    sd = socket (AF_INET, SOCK_STREAM, 0); //Familia de direcciones, tipo de socket, protocolo
    if (sd == -1){
        perror("No se puede abrir el socket cliente\n");
        exit (1);   
    }
    
    // Activaremos una propiedad del socket para permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permite· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on=1; //No hay tiempo de espera
    ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); //socket, nivel, nombre, valor, longitud

    sockname.sin_family = AF_INET; //Familia de direcciones
    sockname.sin_port = htons(2000); //Puerto
    sockname.sin_addr.s_addr =  INADDR_ANY; //Dirección IP

    if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1){ //Unir socket a una dirección
        perror("Error en la operación bind");
        exit(1);
    }

    /*---------------------------------------------------------------------
        Del las peticiones que vamos a aceptar sólo necesitamos el 
        tamaño de su estructura, el resto de información (familia, puerto, 
        ip), nos la proporcionará el método que recibe las peticiones.
    ----------------------------------------------------------------------*/
    from_len = sizeof (from); //Tamaño de la estructura

    if(listen(sd,1) == -1){ //Ponemos el socket a escuchar
        perror("Error en la operación de listen");
        exit(1);
    }
    //Inicializar los conjuntos fd_set
    //Inicializa la estructura fd_set readfds con todos los bits a 0 para la espera de datos
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);
    
    /*-----------------------------------------------------------------------
        El servidor acepta una petición
    ------------------------------------------------------------------------ */
    while(1){
        //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
        auxfds = readfds; //Copia readfds en auxfds, la estructua que utiliza el select la vuelve a poner a los valores por defecto
        
        salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL); //Espera a que se produzca un evento en alguno de los descriptores de los conjuntos readfds, writefds o exceptfds
        
        if(salida > 0){
            for(i=0; i<FD_SETSIZE; i++){ //Recorremos todos los descriptores
                //Buscamos el socket por el que se ha establecido la comunicación y lo atendemos
                if(FD_ISSET(i, &auxfds)) { //Solo me mantengo en el if si tengo algo que leer
                    if( i == sd){ //Entra un cliente nuevo
                        //Aqui se acepta la conexion con el cliente
                        if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){ //Le doy un nuevo descriptor de socket
                            perror("Error aceptando peticiones");
                        }else{
                            if(numClientes < MAX_CLIENTS){ //Si hay hueco para mas clientes
                                //Limpio el struct status
                                inicializarStruct(&(arrayClientes[numClientes]),new_sd); //Inicializo el struct
                                numClientes++; //Aumento el numero de clientes
                                FD_SET(new_sd,&readfds); //Añado el nuevo socket al conjunto de descriptores
                                bzero(buffer,sizeof(buffer)); //Limpio el buffer
                                strcpy(buffer,"Usuario conectado al servidor\n"); //Mensaje de bienvenida
                                send(new_sd,buffer,sizeof(buffer),0); //Envio el mensaje
                            }else{
                                bzero(buffer,sizeof(buffer)); //Limpio el buffer
                                strcpy(buffer,"Demasiados clientes conectados\n"); //Mensaje de bienvenida
                                send(new_sd,buffer,sizeof(buffer),0); //Envio el mensaje
                                close(new_sd); //Cierro el socket
                            }
                        }
                    }else if (i == 0){ //Ha escrito el servidor
                        //Se ha introducido información de teclado por lo que se lee
                        bzero(buffer, sizeof(buffer)); //Limpio el buffer
                        fgets(buffer, sizeof(buffer),stdin); //Leo del teclado

                        //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                        if(strcmp(buffer,"SALIR\n") == 0){
                            for (j = 0; j < numClientes; j++){
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer,"Desconexión servidor\n"); 
                                send(arrayClientes[j].socket,buffer , sizeof(buffer),0);
                                close(arrayClientes[j].socket);
                                FD_CLR(arrayClientes[j].socket,&readfds);
                            }
                            close(sd);
                            exit(-1); 
                        }
                        //Mensajes que se quieran mandar a los clientes (implementar)
                        else{
                            for (j = 0; j < numClientes; j++){
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer,"Mensaje del servidor: "); 
                                fgets(buffer+strlen(buffer), sizeof(buffer)-strlen(buffer),stdin);
                                send(arrayClientes[j].socket,buffer , sizeof(buffer),0);
                            }
                        }
                    }else{ //Ha escrito un cliente que ya estaba conectado
                        bzero(buffer,sizeof(buffer));
                        recibidos = recv(i,buffer,sizeof(buffer),0);
                        if(recibidos > 0){
                            int posicion = buscarUsuario(i,arrayClientes,numClientes); //Esto me devuelve la posición dentro del array de usuarios
                            //Miramos si he recibido un Usuario
                            if((strncmp(buffer,"USUARIO ",8) == 0)&&(arrayClientes[posicion].estado == 0)){
                                //Comprobamos si el usuario ya existe
                                char *array[2];
                                char *token;
                                int j = 0;
                                token = strtok(buffer, " ");
                                while(token != NULL){
                                    array[j] = token;
                                    token = strtok(NULL, " ");
                                    j++;
                                }//while
                                user=array[1];
                                if(existeUsuario(user) == 0){
                                    bzero(buffer, sizeof(buffer));
                                    strcpy(buffer,"-Err. Usuario incorrecto\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }else{
                                    arrayClientes[posicion].estado = 1;
                                    arrayClientes[posicion].nombre=&(user[0]);
                                    
                                    //printf("%s\n", arrayClientes[posicion].nombre);

                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer, "+OK. Usuario correcto\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }

                            }else if(strncmp(buffer,"PASSWORD ",9) == 0){//Miramos si el usuario recibido Existe
                                //Comprobamos si el usuario existe
                                if(arrayClientes[posicion].estado == 1){  
                                    char *array[2];
                                    char *token;
                                    int j = 0;
                                    token = strtok(buffer, " ");
                                    while(token != NULL){
                                        array[j] = token;
                                        token = strtok(NULL, " ");
                                        j++;
                                    }//while
                                    password=array[1];  
                                    if(existeUsuario(user) == 1){
                                        //Comprobamos si la contraseña es correcta
                                        if(comprobarPass(password) == 1){
                                            arrayClientes[posicion].estado = 2; //Cambiamos el estado del usuario a conectado si la contraseña se hace bien
                                            arrayClientes[posicion].password=&(password[0]);

                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"+OK.Usuario validado\n");
                                            send(i,buffer,sizeof(buffer),0);
                                        }else{
                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"-Err.Usuario en la validacion\n");
                                            send(i,buffer,sizeof(buffer),0);
                                        }
                                    }else{
                                        bzero(buffer,sizeof(buffer));
                                        strcpy(buffer,"El usuario no existe\n");
                                        send(i,buffer,sizeof(buffer),0);
                                    }
                                    
                                }
                            }else if(strncmp(buffer,"REGISTRO ", 9)==0){
                                //Mensaje mediante el cual el usuario solicita registrarse para acceder al "Juego.c"
                                //Comprobamos si el usuario existe
                                char *array[4];
                                char *token;
                                int k = 0;
                                token = strtok(buffer, " ");
                                while(token != NULL){
                                    array[k] = token;
                                    token = strtok(NULL, " ");
                                    k++;
                                }
                                user=array[2];
                                password=array[4];

                                //printf("%s %s\n", array[2], array[4]);

                                if(existeUsuario(user) == 0){
                                    //Si no existe lo añadimos y le asinamos el nombre
                                    registroUsuario(user,password);
                                    bzero(buffer,sizeof(buffer));
                                    arrayClientes[posicion].nombre=&(user[0]);
                                    arrayClientes[posicion].password=&(password[0]);
                                    //strcpy(arrayClientes[posicion].password, password);
                                    arrayClientes[posicion].estado = 2; // Si se hace bien el registro se pone a 2
                                    numClientes++;
                                    //printf("%s\n", user);
                                    strcpy(buffer,"+OK. Usuario registrado correctamente\n");
                                    //Cambiamos el estado del usuario a conectado
                                    send(i,buffer,sizeof(buffer),0);
                                }else{
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"-Err. El usuario ya existe\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }
                            }else if(strncmp(buffer,"INICIAR-PARTIDA",15) == 0){
                                int find=0;
                                //Mensaje para solicitar una partida /*HAY QUE TOQUETEAR AQUÍ*/
                                if(arrayClientes[posicion].estado == 2){ //Si el usuario está logueado
                                    for(int i=0; i<numClientes; i++){ //tenemos que buscar a alguien que esté en estado 3 y devolver el socket
                                        //Si hay dos clientes conectados se inicia la partida con el primer jugador que estaba esperando
                                        if((arrayClientes[i].estado==3) && (asignarJugadoresPartida(arrayClientes,i,posicion,arrayJuegos)==0)){
                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"+Ok. Empieza la partida.");
                                            inicializarTablero(arrayJuegos[arrayClientes[posicion].id_partida].tablero);
                                            decodificarTablero(arrayJuegos[arrayClientes[posicion].id_partida].tablero,buffer);
                                            send(arrayClientes[posicion].socket,buffer,sizeof(buffer),0);
                                            send(arrayClientes[i].socket,buffer,sizeof(buffer),0);
                                            bzero(buffer,sizeof(buffer));
                                            arrayClientes[posicion].estado = 4; //Están jugando
                                            arrayClientes[i].estado=4;
                                            strcpy(buffer, "OK.Turno de partida\n");
                                            send(arrayClientes[i].socket, buffer, sizeof(buffer),0);
                                            find=1;
                                       }else if(asignarJugadoresPartida(arrayClientes,i,posicion,arrayJuegos)==1){
                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer, "-Err. No hay partidas para asignar, todas las sesiones llenas\n");
                                            send(arrayClientes[posicion].socket, buffer, sizeof(buffer),0);
                                            send(arrayClientes[i].socket, buffer, sizeof(buffer),0);
                                            find=0;
                                            arrayClientes[posicion].estado = 3; //Están esperando
                                            arrayClientes[i].estado=3;
                                        }
                                    }//foR
                                    if(find==0){
                                        bzero(buffer, sizeof(buffer));
                                        strcpy(buffer, "+Ok. Esperando jugadores\n");
                                        send(arrayClientes[posicion].socket, buffer, sizeof(buffer),0);
                                        arrayClientes[posicion].estado=3; //Jugador en espera
                                    }
                                }else{ //Si no hay dos clientes conectados se espera a que se conecte otro
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"-Err. Instrucción no válida\n");
                                    send(i,buffer,sizeof(buffer),0);
                                }
                            }else if(strncmp(buffer,"COLOCAR-FICHA ",14) == 0){
                                Juego *juego;
                                juego=&(arrayJuegos[arrayClientes[posicion].id_partida]);
                                int fila=0;
                                char *array[2];
                                char *token;
                                int j = 0;
                                token = strtok(buffer, " ");
                                while(token != NULL){
                                    array[j] = token;
                                    token = strtok(NULL, " ");
                                    j++;
                                }//while
                                juego->columna=atoi(array[1]);
                                int sol=1;
                                sol=colocarFicha(juego->tablero, juego->columna,  &fila, juego->turno);
                                if(sol==0){                         
                                    bzero(buffer, sizeof(buffer));
                                    char r[MSG_SIZE];
                                    bzero(r, sizeof(r));
                                    decodificarTablero(juego->tablero, r);
                                    strcpy(buffer, "+Ok. Nuevo tablero. ");
                                    strcat(buffer, r);
                                    send(arrayClientes[juego->posicion2].socket, buffer, sizeof(buffer),0);
                                    send(arrayClientes[juego->posicion1].socket, buffer, sizeof(buffer),0);
                                    int ganador=comprobarGanador(juego->tablero);
                                    if(ganador==1){
                                        if(juego->turno==1){
                                            bzero(buffer, sizeof(buffer));
                                            char *nombre=arrayClientes[juego->posicion2].nombre;
                                            strcpy(buffer,"+Ok. Jugador ");
                                            strcat(buffer, nombre);
                                            strcat(buffer, " ha ganado la partida\n");
                                            send(arrayClientes[juego->posicion2].socket, buffer, sizeof(buffer), 0);
                                            send(arrayClientes[juego->posicion1].socket, buffer, sizeof(buffer), 0);
                                        }
                                        else if(juego->turno==2){
                                            bzero(buffer, sizeof(buffer));
                                            char *nombre=arrayClientes[juego->posicion1].nombre;
                                            strcpy(buffer,"+Ok. Jugador ");
                                            strcat(buffer, nombre);
                                            strcat(buffer, " ha ganado la partida\n");
                                            send(arrayClientes[juego->posicion2].socket, buffer, sizeof(buffer), 0);
                                            send(arrayClientes[juego->posicion1].socket, buffer, sizeof(buffer), 0);
                                        }
                                    }else if(ganador==0){
                                        if(juego->turno==1){
                                            juego->turno=2;
                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"+Ok. Turno de partida\n");
                                            send(arrayClientes[juego->posicion2].socket, buffer, sizeof(buffer),0);
                                        }else if(juego->turno==2){                                  
                                            juego->turno=1;
                                            bzero(buffer,sizeof(buffer));
                                            strcpy(buffer,"+Ok. Turno de partida\n");
                                            send(arrayClientes[juego->posicion1].socket, buffer, sizeof(buffer),0);
                                        }
                                    }

                                }else if(sol==-1){
                                    if(juego->turno==1){
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"-Err. Casilla no valida\n");
                                    send(arrayClientes[juego->posicion2].socket, buffer, sizeof(buffer),0);
                                }
                                    else if(juego->turno==2){                                   
                                        bzero(buffer,sizeof(buffer));
                                        strcpy(buffer,"-Err. Casilla no valida\n");
                                        send(arrayClientes[juego->posicion1].socket, buffer, sizeof(buffer),0);
                                }
                            }
                            }else if(strcmp(buffer,"SALIR\n") == 0){//Miramos si el cliente quiere salir
                                //Una vez salga el usuario de la partida vuelve al estado 2
                                arrayClientes[1].estado = 2;
                                salirCliente(i,&readfds,&numClientes,arrayClientes);
                            }else{
                                bzero(buffer,sizeof(buffer));
                                strcpy(buffer,"-Err. Instrucción no válida.\n");
                                send(i,buffer,sizeof(buffer),0);
                            } 
                        }
                        //Si el cliente introdujo ctrl+c
                        if(recibidos== 0){
                            printf("El socket %d, ha introducido ctrl+c\n", i);
                            //Eliminar ese socket
                            salirCliente(i,&readfds,&numClientes,arrayClientes);
                        }
                    }
                }
            }
        }
    }
    close(sd);
    return 0;
}
