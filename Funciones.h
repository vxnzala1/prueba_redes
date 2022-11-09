//Fichero que usara el servidor para ejecutar funciones necesarias para su funcionamiento
#ifndef __Funciones_H
#define __Funciones_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "Funciones.h"

#define MSG_SIZE 250

int buscarUsuario(int socket,Jugador arrayClientes[],int numUsuarios);
void inicializarStruct(Jugador* jugador,int new_sd);
int existeUsuario(char *user);
void salirCliente(int socket, fd_set * readfds, int * numClientes, Jugador arrayClientes[]);
int comprobarPass(char* password); //Falta por implementar
void registroUsuario(char *user, char *password);
int asignarJugadoresPartida(Jugador arrayClientes[], int i, int posicion, Juego arrayJuegos[10]);

#endif