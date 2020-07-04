/*

  ____          _____               _ _           _       
 |  _ \        |  __ \             (_) |         | |      
 | |_) |_   _  | |__) |_ _ _ __ _____| |__  _   _| |_ ___ 
 |  _ <| | | | |  ___/ _` | '__|_  / | '_ \| | | | __/ _ \
 | |_) | |_| | | |  | (_| | |   / /| | |_) | |_| | ||  __/
 |____/ \__, | |_|   \__,_|_|  /___|_|_.__/ \__, |\__\___|
         __/ |                               __/ |        
        |___/                               |___/         
    
____________________________________
/ Si necesitas ayuda, contáctame en \
\ https://parzibyte.me               /
 ------------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 4
#define COLUMNAS 6
#define TAMANIO_MATRIZ sizeof(char)*FILAS*COLUMNAS
#define JUGADOR_1 'o'
#define JUGADOR_2 'x'
#define ESPACIO_VACIO ' '
#define FILA_NO_ENCONTRADA -1
#define ERROR_COLUMNA_LLENA 2
#define ERROR_FILA_INVALIDA 4
#define ERROR_NINGUNO 3

int hacercosa(char tableroOriginal[FILAS][COLUMNAS]) {
    char matriz[FILAS][COLUMNAS];
    memcpy(matriz, tableroOriginal, TAMANIO_MATRIZ);
    printf("Inside function: %d\n", matriz[0][0]);
    matriz[0][0] = '_';
    printf("Inside function (later): %d\n", matriz[0][0]);
    return 0;
}

int obtenerFilaDesocupada(int columna, char tablero[FILAS][COLUMNAS]) {
    for (int i = FILAS - 1; i >= 0; i--) {
        if (tablero[i][columna] == ESPACIO_VACIO) {
            return i;
        }
    }
    return FILA_NO_ENCONTRADA;
}

int colocarPieza(char jugador, int columna, char tablero[FILAS][COLUMNAS]) {
    if (columna < 0 || columna >= COLUMNAS) {
        return ERROR_FILA_INVALIDA;
    }
    int fila = obtenerFilaDesocupada(columna, tablero);
    if (fila == FILA_NO_ENCONTRADA) {
        return ERROR_COLUMNA_LLENA;
    }
    tablero[fila][columna] = jugador;
    return ERROR_NINGUNO;
}


void limpiarTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            tablero[i][j] = ESPACIO_VACIO;
        }
        printf("\n");
    }
}

void dibujarEncabezado(int columnas) {
    for (int i = 0; i < columnas; ++i) {
        printf("|%d", i + 1);
        if (i + 1 >= columnas) {
            printf("|");
        }

    }
}

int dibujarTablero(char tablero[FILAS][COLUMNAS]) {
    dibujarEncabezado(COLUMNAS);
    printf("\n");
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            printf("|%c", tablero[i][j]);
            if (j + 1 >= COLUMNAS) {
                printf("|");
            }
        }
        printf("\n");
    }
    return 0;
}

int main() {
    char tablero[FILAS][COLUMNAS];
    int bandera = 1;
    limpiarTablero(tablero);
    while (1) {
        dibujarTablero(tablero);
        int columna;
        printf("Escribe la columna: ");
        scanf("%d", &columna);
        // Necesitamos índices de arreglos
        columna--;
        char jugador;
        if (bandera) {
            jugador = JUGADOR_1;
            bandera = 0;
        } else {
            jugador = JUGADOR_2;
            bandera = 1;
        }
        int estado = colocarPieza(jugador, columna, tablero);
        if (estado == ERROR_COLUMNA_LLENA) {
            printf("Error: columna llena");
        } else if (estado == ERROR_FILA_INVALIDA) {
            printf("Fila no correcta");
        }
    }
    return 0;
}
