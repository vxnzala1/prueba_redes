#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Funciones.h"

void salirCliente(int socket, fd_set * readfds, int * numClientes, Jugador arrayClientes[]){
	//Sobreescribimos el socket del cliente que se ha desconectado con el último socket del array
	int i;
	for(i=0; i<(*numClientes); i++){
		if(arrayClientes[i].socket==socket){
			arrayClientes[i]=arrayClientes[(*numClientes)-1];
			break;
		}
	}
	(*numClientes)--;
	//Borramos el socket del cliente que se ha desconectado
	FD_CLR(socket, readfds);
	//Cerramos el socket del cliente que se ha desconectado
	close(socket);
}

//Dado el fichero "fichero.txt", utilizando fopen y recorriendo el fichero, 
//teniendo en cada línea con formato "Usuario, Contraseña" y dado un usuario 
//la función devuelve 1 si el usuario existe y 0 si no existe
int existeUsuario(char *user){
    if(user[strlen(user)-1]=='\n'){
        user[strlen(user)-1]='\0';
    }
    if(user[strlen(user)-1]=='\0'){
        strcpy(user, strtok(user, " "));
    }
    FILE *f;
    f = fopen("fichero.txt","r");
    if(f == NULL){
        perror("Error al abrir el fichero");
    }
    //Buscamos el usuario en el fichero
    char linea[250];
    while(fgets(linea,250,f) != NULL){
        if(strncmp(linea,user,strlen(user))==0){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

/*int comprobarPass(char *password){
    FILE *fichero;
    fichero=fopen("fichero.txt","r");
    char passwordFichero[20];
    fscanf(fichero,"%s",passwordFichero);
    if(strcmp(password,passwordFichero)==0){
        return 1;
    }
    return 0;
}*/

int comprobarPass(char *password){
    FILE *f;
    f = fopen("fichero.txt","r");
    if(f == NULL){
        perror("Error al abrir el fichero");
    }
    //Buscamos el usuario en el fichero
    char linea[20];
    while(fgets(linea,20,f) != NULL){
        if(strcmp(linea,password),strlen(password)){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

//Dado el socket devolver el array de usuarios
int buscarUsuario(int socket,Jugador arrayClientes[],int numUsuarios){
    int i;
    for(i=0; i<numUsuarios; i++){
        if(arrayClientes[i].socket == socket){
            return i;
        }
    }
    return -1;
}

//Funcion que inicializa el struct de usuarios
void inicializarStruct(Jugador* jugador,int new_sd){
	jugador->socket = new_sd;
	jugador->nombre = NULL;
	jugador->password = NULL;
	jugador->estado = 2;
    jugador->id_partida=-1;
}


//Función que guarda en el fichero el usuario y la contraseña del nuevo usuario
void registroUsuario(char *user, char *password){
    FILE *f;
    f = fopen("fichero.txt","a");
    if(f == NULL){
        perror("Error al abrir el fichero");
    }
    fprintf(f,"%s,%s",user,password);
    fclose(f);
}  
 
int asignarJugadoresPartida(Jugador arrayClientes[], int i, int posicion, Juego arrayJuegos[10]){
   for(int v=0; v<10; v++){
        if(arrayJuegos[v].turno==0){
            arrayJuegos[v].posicion1=i;
            arrayJuegos[v].posicion2=posicion;
            arrayClientes[i].id_partida=v;
            arrayClientes[posicion].id_partida=v;
            arrayJuegos[v].turno=1;
            return 0;
        }
    }
    return 1;
}