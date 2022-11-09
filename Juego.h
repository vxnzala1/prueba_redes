#ifndef __Juego_H
#define __Juego_H

#include <stdio.h>
#include "Struct.h"
#include "Funciones.h"

void decodificarTablero(char tablero[6][7], char *aux);
void imprimirTablero(char c[250]);
void inicializarTablero(char tablero[6][7]);
int comprobarGanador(char tablero[6][7]);
int colocarFicha(char tablero[6][7],int columna, int *fila, int turno);
int comprobarTableroLleno(int tablero[6][7]);
int comprobarColumnaLlena(int tablero[6][7], int columna);
int comprobarColumnaValida(int columna);

#endif