#ifndef __Struct_H
#define __Struct_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct juego{
	char tablero[6][7];
	int fila;		//Varible que almacena la fila de la colocacion de la ficha
	int columna;  	//Variable que almacena la columna de la colocacion de la ficha
	int turno;		//Varibale para el turno, 1 para jugador 1 'o', 2 para el jugador 2 'x'
	int posicion1;  
	int posicion2;
}Juego;

typedef struct jugador{
	char* nombre;
	char* password;
	int estado;
	int socket;
	int id_partida;
}Jugador;

#endif