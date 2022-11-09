#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Juego.h"
#include "Struct.h"


//Función para inicializar el tablero
void decodificarTablero(char tablero[6][7], char *aux){
    char  c[2];
    c[1]='\0';
    for(int i = 0; i < 6; i++ ){
        for(int j = 0; j < 7; j++ ){
            c[0] =tablero[i][j];
            if (j != 0){
                strcat(aux,",");
            }
            strcat(aux, c);
        }
        strcat(aux,";");
    }
}

void inicializarTablero(char tablero[6][7]){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            tablero[i][j]='-';
        }
    }
}

//Función para imprimir el tablero
void imprimirTablero(char c[250]){
    if(((strncmp(c, "+Ok. Empieza la partida. ", 25))==0)){
        printf("|1|2|3|4|5|6|7|\n");
        char *array[10]; 
        int k=0;
        char *token;
        token=strtok(c, " ");
        while(token != NULL){
            array[k]=token;
            token=strtok(NULL, " ");
            k++;
        }
        for(k=4; k<10 ; k++){
            char *aux=array[k];
            printf("|");
            for(int l=0; l<(strlen(array[k])); l++){
                if(aux[l]=='-'){
                    aux[l]=' ';
                    printf("%c", aux[l]);
                }
                else if(aux[l]==','){
                    aux[l]='|';
                    printf("%c", aux[l]);
                }
                else if(aux[l]==';'){
                    aux[l]='|';
                    printf("%c\n", aux[l]);
                }

            }  
        }
    }else if(((strncmp(c, "+Ok. Nuevo tablero. ",20)))==0){
       printf("|1|2|3|4|5|6|7|\n");
        char *array1[9]; 
        int k=0;
        char *token;
        token=strtok(c, " ");
        while(token != NULL){
            array1[k]=token;
            token=strtok(NULL, " ");
            k++;
        }
        for(k=3; k<9 ; k++){
            char *aux1=array1[k];
            printf("|");
            for(int l=0; l<(strlen(array1[k])); l++){
                if(aux1[l]=='-'){
                    aux1[l]=' ';
                    printf("%c", aux1[l]);
                }
                else if(aux1[l]==','){
                    aux1[l]='|';
                    printf("%c", aux1[l]);
                }
                else if(aux1[l]=='x'){
                    aux1[l]='x';
                    printf("%c", aux1[l]);
                }
                else if(aux1[l]=='o'){
                    aux1[l]='o';
                    printf("%c", aux1[l]);
                }
                else if(aux1[l]==';'){
                    aux1[l]='|';
                    printf("%c\n", aux1[l]);
                }
            }  
        } 
    }
}

//Función para comprobar si hay un ganador
/*int comprobarGanador(char tablero[6][7]){
    int i,j;
    //Comprobamos si hay 4 fichas iguales en horizontal
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(tablero[i][j]!='o' && tablero[i][j]==tablero[i][j+1] && tablero[i][j]==tablero[i][j+2] && tablero[i][j]==tablero[i][j+3]
            || tablero[i][j]!='x' && tablero[i][j]==tablero[i][j+1] && tablero[i][j]==tablero[i][j+2] && tablero[i][j]==tablero[i][j+3]){
                return 1;
            }
        }
    }
    //Comprobamos si hay 4 fichas iguales en vertical
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(tablero[i][j]!='o' && tablero[i][j]==tablero[i+1][j] && tablero[i][j]==tablero[i+2][j] && tablero[i][j]==tablero[i+3][j]
            || tablero[i][j]!='x' && tablero[i][j]==tablero[i+1][j] && tablero[i][j]==tablero[i+2][j] && tablero[i][j]==tablero[i+3][j]){
                return 1;
            }
        }
    }
    //Comprobamos si hay 4 fichas iguales en diagonal
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(tablero[i][j]!='o' && tablero[i][j]==tablero[i+1][j+1] && tablero[i][j]==tablero[i+2][j+2] && tablero[i][j]==tablero[i+3][j+3]
            || tablero[i][j]!='x' && tablero[i][j]==tablero[i+1][j+1] && tablero[i][j]==tablero[i+2][j+2] && tablero[i][j]==tablero[i+3][j+3]){
                return 1;
            }
        }
    }
    //Comprobamos si hay 4 fichas iguales en diagonal inversa
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(tablero[i][j]!='o' && tablero[i][j]==tablero[i+1][j-1] && tablero[i][j]==tablero[i+2][j-2] && tablero[i][j]==tablero[i+3][j-3]
            || tablero[i][j]!='x' && tablero[i][j]==tablero[i+1][j-1] && tablero[i][j]==tablero[i+2][j-2] && tablero[i][j]==tablero[i+3][j-3]){
                return 1;
            }
        }
    }
    return 0;
}*/
int comprobarGanador(char tablero[6][7]){
    int i,j;
    //Comprobamos si hay 4 fichas iguales en horizontal
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            if(tablero[i][j]=='o' && tablero[i][j]==tablero[i][j+1] && tablero[i][j]==tablero[i][j+2] && tablero[i][j]==tablero[i][j+3]
            || tablero[i][j]=='x' && tablero[i][j]==tablero[i][j+1] && tablero[i][j]==tablero[i][j+2] && tablero[i][j]==tablero[i][j+3]){
                return 1;
            }
        }
    }
    //Comprobamos si hay 4 fichas iguales en vertical
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            if(tablero[i][j]=='o' && tablero[i][j]==tablero[i+1][j] && tablero[i][j]==tablero[i+2][j] && tablero[i][j]==tablero[i+3][j]
            || tablero[i][j]=='x' && tablero[i][j]==tablero[i+1][j] && tablero[i][j]==tablero[i+2][j] && tablero[i][j]==tablero[i+3][j]){
                return 1;
            }
        }
    }
    //Comprobamos si hay 4 fichas iguales en diagonal
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            if(tablero[i][j]=='o' && tablero[i][j]==tablero[i+1][j+1] && tablero[i][j]==tablero[i+2][j+2] && tablero[i][j]==tablero[i+3][j+3]
            || tablero[i][j]=='x' && tablero[i][j]==tablero[i+1][j+1] && tablero[i][j]==tablero[i+2][j+2] && tablero[i][j]==tablero[i+3][j+3]){
                return 1;
            }
        }
    }
    //Comprobamos si hay 4 fichas iguales en diagonal inversa
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            if(tablero[i][j]=='o' && tablero[i][j]==tablero[i+1][j-1] && tablero[i][j]==tablero[i+2][j-2] && tablero[i][j]==tablero[i+3][j-3]
            || tablero[i][j]=='x' && tablero[i][j]==tablero[i+1][j-1] && tablero[i][j]==tablero[i+2][j-2] && tablero[i][j]==tablero[i+3][j-3]){
                return 1;
            }
        }
    }
    return 0;
}


//Funcion que pone "o" en el turno del jugador 1 y "x" en el turno del jugador 2
int colocarFicha(char tablero[6][7], int columna, int *fila, int turno){
    if(turno==1){
		for(int i=6;i>=0;i--){
	        if(tablero[i][columna-1]=='-'){
	            tablero[i][columna-1]='o';
	            *fila=i;
	            return 0;
	        }
	    }
	    return -1;
	}

	if(turno==2){
	    for(int i=6;i>=0;i--){
	        if(tablero[i][columna-1]=='-'){
	            tablero[i][columna-1]='x';
	            *fila=i;
	            return 0;
	        }
	    }
	    return -1;
	} 
}

//Función para comprobar si la columna es válida
int comprobarColumnaValida(int columna){
    if (columna >= 0 && columna <= 6){
        return 1;
    }
    else{
        return 0;
    }
}

/*
//Función para comprobar si el tablero está lleno
int comprobarTableroLleno(int tablero[6][7]){
    int i, j;
    for (i = 0; i < 6; i++){
        for (j = 0; j < 7; j++){
            if (tablero[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

//Función para comprobar si la columna está llena
int comprobarColumnaLlena(int tablero[6][7], int columna){
    if (tablero[0][columna] != 0){
        return 1;
    }
    else{
        return 0;
    }
}
*/

