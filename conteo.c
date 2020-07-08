#include "conecta4.h"

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
