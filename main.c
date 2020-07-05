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
#include <string.h>

#define FILAS 9
#define COLUMNAS 9
#define TAMANIO_MATRIZ sizeof(char)*FILAS*COLUMNAS
#define JUGADOR_1 'o'
#define JUGADOR_2 'x'
#define ESPACIO_VACIO ' '
#define FILA_NO_ENCONTRADA -1
#define ERROR_COLUMNA_LLENA 2
#define ERROR_FILA_INVALIDA 4
#define ERROR_NINGUNO 3
#define CONECTA 4
#define CONECTA_ARRIBA 1
#define CONECTA_DERECHA 2
#define CONECTA_ABAJO_DERECHA 3
#define CONECTA_ARRIBA_DERECHA 4
#define NO_CONECTA 0

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
    printf("\n");
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



int contarArriba(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]) {
    int yInicio = (y - CONECTA >= 0) ? y - CONECTA + 1 : 0;
    int contador = 0;
    for (; yInicio <= y; yInicio++) {
        if (tablero[yInicio][x] == jugador) {
            contador++;
        } else {
            contador = 0;
        }
    }
    return contador;
}

int contarDerecha(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]) {
    int xFin = (x + CONECTA < COLUMNAS) ? x + CONECTA - 1 : COLUMNAS - 1;
    int contador = 0;
    for (; x <= xFin; x++) {
        if (tablero[y][x] == jugador) {
            contador++;
        } else {
            contador = 0;
        }
    }
    return contador;
}

int contarArribaDerecha(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]) {
    int xFin = (x + CONECTA < COLUMNAS) ? x + CONECTA - 1 : COLUMNAS - 1;
    int yInicio = (y - CONECTA >= 0) ? y - CONECTA + 1 : 0;
    int contador = 0;
    while (x <= xFin && yInicio <= y) {
        if (tablero[y][x] == jugador) {
            contador++;
        } else {
            contador = 0;
        }
        x++;
        y--;
    }
    return contador;
}

int contarAbajoDerecha(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]) {
    int xFin = (x + CONECTA < COLUMNAS) ? x + CONECTA - 1 : COLUMNAS - 1;
    int yFin = (y + CONECTA < FILAS) ? y + CONECTA - 1 : FILAS - 1;
    int contador = 0;
    while (x <= xFin && y <= yFin) {
        if (tablero[y][x] == jugador) {
            contador++;
        } else {
            contador = 0;
        }
        x++;
        y++;
    }
    return contador;
}

int ganador(char jugador, char tablero[FILAS][COLUMNAS]) {
/*
 * Solo necesitamos
 * Arriba
 * Derecha
 * Arriba derecha
 * Abajo derecha
 *
 * */
    for (int y = 0; y < FILAS; y++) {
        for (int x = 0; x < COLUMNAS; x++) {
            int conteoArriba = contarArriba(x, y, jugador, tablero);
            if (conteoArriba >= CONECTA) {
                return CONECTA_ARRIBA;
            }
            if (contarDerecha(x, y, jugador, tablero) >= CONECTA) {
                return CONECTA_DERECHA;
            }
            if (contarArribaDerecha(x, y, jugador, tablero) >= CONECTA) {
                return CONECTA_ARRIBA_DERECHA;
            }
            if (contarAbajoDerecha(x, y, jugador, tablero) >= CONECTA) {
                return CONECTA_ABAJO_DERECHA;
            }
        }
    }
    return NO_CONECTA;
}


int esEmpate(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < COLUMNAS; ++i) {
        int resultado = obtenerFilaDesocupada(i, tablero);
        if (resultado != FILA_NO_ENCONTRADA) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char tablero[FILAS][COLUMNAS];
    int bandera = 1;
    limpiarTablero(tablero);
    while (1) {
        char jugadorActual;
        if (bandera) {
            jugadorActual = JUGADOR_1;
            bandera = 0;
        } else {
            jugadorActual = JUGADOR_2;
            bandera = 1;
        }
        printf("Turno del jugador %c\n", jugadorActual);
        dibujarTablero(tablero);
        int columna;
        printf("Escribe la columna: ");
        scanf("%d", &columna);
        // Necesitamos índices de arreglos
        columna--;
        int estado = colocarPieza(jugadorActual, columna, tablero);
        if (estado == ERROR_COLUMNA_LLENA) {
            printf("Error: columna llena");
        } else if (estado == ERROR_FILA_INVALIDA) {
            printf("Fila no correcta");
        } else if (estado == ERROR_NINGUNO) {
            int g = ganador(jugadorActual, tablero);
            if (g != NO_CONECTA) {
                dibujarTablero(tablero);
                printf("Gana el jugador %c.", jugadorActual);
                break;
            } else if (esEmpate(tablero)) {
                printf("Empate");
                break;
            }
        }
    }
    return 0;
}
