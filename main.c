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
Creado por Parzibyte (https://parzibyte.me). Este encabezado debe mantenerse intacto,
excepto si este es un proyecto de un estudiante.
*/
#include <stdio.h>
#include <stdlib.h> // rand y RAND_MAX
#include <unistd.h> // getpid

#include "conecta4.h"
#include "conteo.c"
#include "tablero.c"
#include "ia.c"
#include "misc.c"


int main() {
    // Hay que alimentar a rand, solamente una vez (seed rand)
    srand(getpid());
    char tablero[FILAS][COLUMNAS];
    int turnoDelJugador2 = 1;
    int juegaCpu;
    printf("¿Jugador Vs Jugador [0] o Jugador vs CPU[1]? ");
    scanf("%d", &juegaCpu);
    limpiarTablero(tablero);
    while (1) {
        char jugadorActual;
        if (turnoDelJugador2) {
            jugadorActual = JUGADOR_1;
            turnoDelJugador2 = 0;
        } else {
            jugadorActual = JUGADOR_2;
            turnoDelJugador2 = 1;
        }
        int columna;
        printf("\nTurno del jugador %c\n", jugadorActual);
        if (juegaCpu && turnoDelJugador2) {
            printf("CPU pensando...\n");
            columna = elegirColumnaCpu(jugadorActual, tablero);
        } else {
            dibujarTablero(tablero);
            printf("Escribe la columna: ");
            scanf("%d", &columna);
            // Necesitamos índices de arreglos
            columna--;
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
    }
    return 0;
}
