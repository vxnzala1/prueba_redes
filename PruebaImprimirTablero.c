#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void inicializarTablero(char tablero[6][7]){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            tablero[i][j]='-';
        }
    }
}

/*void decodificarTablero(char tablero[6][7], char *buffer){
    char  c;
    for(int i = 0; i < 6; i++ ){
        for(int j = 0; j < 7; j++ ){
            c = tablero[i][j];
            if (j != 0){
                strcat(buffer,",");
            }
            strcat(buffer,&c);
        }
        strcat(buffer,";");
        strcat(buffer," ");
    }
}*/
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

void imprimir(char c[250]){
    if(((strncmp(c, "+Ok. Empieza la partida.",24))==0)|| (((strncmp(c, "+Ok. Nuevo tablero.",19)))==0)){
        char *token;
        token=strtok(c, ".");
        printf("%s",token);
        token=strtok(NULL, ".");
        printf("%s\n",token);
        printf("|1|2|3|4|5|6|7|\n|");
        token=strtok(NULL, "\n");
            for(int l=0; l<(strlen(token)-1); l++){
                if(token[l]=='-'){
                    token[l]=' ';
                    printf("%c", token[l]);
                }
                else if(token[l]==','){
                    token[l]='|';
                    printf("%c", token[l]);
                }
                else if(token[l]=='x'){
                    token[l]='x';
                    printf("%c", token[l]);
                }
                else if(token[l]=='o'){
                    token[l]='o';
                    printf("%c", token[l]);
                }
                else if(token[l]==';'){
                    token[l]='|';
                    printf("%c\n|", token[l]);
                }
            }  
            printf("|\n");
    }else{
        printf("%s\n",c);
    }
}

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

int main(){
    char buffer[250];
    strcpy(buffer, "+Ok. Empieza la partida.");
    char tablero[6][7]={{'-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-'}};
    decodificarTablero(tablero,buffer);
    printf("RawBuffer=[%s]\n",buffer);
    imprimir(buffer);

    strcpy(buffer, "+Ok. Nuevo tablero. ");
    decodificarTablero(tablero,buffer);
    printf("RawBuffer=[%s]\n",buffer);
    imprimir(buffer);
}