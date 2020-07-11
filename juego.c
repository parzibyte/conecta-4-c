#include "conecta4.h"

void jugar(int modo) {
    char tablero[FILAS][COLUMNAS];
    limpiarTablero(tablero);
    char jugadorActual = elegirJugadorAlAzar();
    printf("Comienza el jugador %c\n", jugadorActual);
    while (1) {
        int columna = 0;
        printf("\nTurno del jugador %c\n", jugadorActual);
        dibujarTablero(tablero);
        if (modo == MODO_HUMANO_CONTRA_CPU) {
            if (jugadorActual == JUGADOR_CPU_2) {
                printf("CPU 2 pensando...");
                columna = elegirColumnaCpu(jugadorActual, tablero);
            } else {
                columna = solicitarColumnaAJugador();
            }
        } else if (modo == MODO_CPU_CONTRA_CPU) {
            printf("CPU %d pensando...", jugadorActual == JUGADOR_CPU_1 ? 1 : 2);
            columna = elegirColumnaCpu(jugadorActual, tablero);
        } else if (modo == MODO_HUMANO_CONTRA_HUMANO) {
            columna = solicitarColumnaAJugador();
        }
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
        jugadorActual = obtenerOponente(jugadorActual);
    }
}