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
#include "conecta4.h"
#include <string.h>
#include <stdio.h>

void clonarMatriz(char tableroOriginal[FILAS][COLUMNAS], char destino[FILAS][COLUMNAS]) {
    memcpy(destino, tableroOriginal, TAMANIO_MATRIZ);
}

int obtenerColumnaGanadora(char jugador, char tableroOriginal[FILAS][COLUMNAS]) {
    char tablero[FILAS][COLUMNAS];
    int i;
    for (i = 0; i < COLUMNAS; i++) {
        clonarMatriz(tableroOriginal, tablero);
        int resultado = colocarPieza(jugador, i, tablero);
        if (resultado == ERROR_NINGUNO) {
            int gana = ganador(jugador, tablero);
            if (gana != NO_CONECTA) {
                return i;
            }
        }
    }
    return COLUMNA_GANADORA_NO_ENCONTRADA;
}

int obtenerPrimeraFilaLlena(int columna, char tablero[FILAS][COLUMNAS]) {
    int i;
    for (i = 0; i < FILAS; ++i) {
        if (tablero[i][columna] != ESPACIO_VACIO) {
            return i;
        }
    }
    return FILA_NO_ENCONTRADA;
}

/*
 * Los dos últimos apuntadores son porque no podemos regresar dos variables
 * */
void obtenerColumnaEnLaQueSeObtieneMayorPuntaje(char jugador, char tableroOriginal[FILAS][COLUMNAS], int *conteo,
                                                int *indice) {

    int conteoMayor = 0,
            indiceColumnaConConteoMayor = -1;
    char tablero[FILAS][COLUMNAS];
    int i;
    for (i = 0; i < COLUMNAS; ++i) {
        clonarMatriz(tableroOriginal, tablero);
        int estado = colocarPieza(jugador, i, tablero);
        if (estado == ERROR_NINGUNO) {
            int filaDePiezaRecienColocada = obtenerPrimeraFilaLlena(i, tablero);
            if (filaDePiezaRecienColocada != FILA_NO_ENCONTRADA) {
                int c = contarArriba(i, filaDePiezaRecienColocada, jugador, tablero);
                if (c > conteoMayor) {
                    conteoMayor = c;
                    indiceColumnaConConteoMayor = i;
                }
                c = contarArribaDerecha(i, filaDePiezaRecienColocada, jugador, tablero);
                if (c > conteoMayor) {
                    conteoMayor = c;
                    indiceColumnaConConteoMayor = i;
                }
                c = contarDerecha(i, filaDePiezaRecienColocada, jugador, tablero);
                if (c > conteoMayor) {
                    conteoMayor = c;
                    indiceColumnaConConteoMayor = i;
                }
                c = contarAbajoDerecha(i, filaDePiezaRecienColocada, jugador, tablero);
                if (c > conteoMayor) {
                    conteoMayor = c;
                    indiceColumnaConConteoMayor = i;
                }
            }
        }
    }
    *conteo = conteoMayor;
    *indice = indiceColumnaConConteoMayor;
}

int obtenerColumnaAleatoria(char jugador, char tableroOriginal[FILAS][COLUMNAS]) {
    while (1) {
        char tablero[FILAS][COLUMNAS];
        clonarMatriz(tableroOriginal, tablero);
        int columna = aleatorio_en_rango(0, COLUMNAS - 1);
        int resultado = colocarPieza(jugador, columna, tablero);
        if (resultado == ERROR_NINGUNO) {
            return columna;
        }
    }
}

int obtenerColumnaCentral(char jugador, char tableroOriginal[FILAS][COLUMNAS]) {
    char tablero[FILAS][COLUMNAS];
    clonarMatriz(tableroOriginal, tablero);
    int mitad = (COLUMNAS - 1) / 2;
    int resultado = colocarPieza(jugador, mitad, tablero);
    if (resultado == ERROR_NINGUNO) {
        return mitad;
    }
    return COLUMNA_GANADORA_NO_ENCONTRADA;
}

int elegirColumnaCpu(char jugador, char tablero[FILAS][COLUMNAS]) {
    // Voy a comprobar si puedo ganar...
    int posibleColumnaGanadora = obtenerColumnaGanadora(jugador, tablero);
    if (posibleColumnaGanadora != COLUMNA_GANADORA_NO_ENCONTRADA) {
        printf("*elijo ganar*\n");
        return posibleColumnaGanadora;
    }
    // Si no, voy a comprobar si mi oponente gana con el siguiente movimiento, para evitarlo
    char oponente = obtenerOponente(jugador);
    int posibleColumnaGanadoraDeOponente = obtenerColumnaGanadora(oponente, tablero);
    if (posibleColumnaGanadoraDeOponente != COLUMNA_GANADORA_NO_ENCONTRADA) {
        printf("*elijo evitar que mi oponente gane*\n");
        return posibleColumnaGanadoraDeOponente;
    }
    // En caso de que nadie pueda ganar en el siguiente movimiento, buscaré en dónde se obtiene el mayor
    // puntaje al colocar la pieza
    int conteoCpu, columnaCpu;
    obtenerColumnaEnLaQueSeObtieneMayorPuntaje(jugador, tablero, &conteoCpu, &columnaCpu);
    int conteoOponente, columnaOponente;
    obtenerColumnaEnLaQueSeObtieneMayorPuntaje(oponente, tablero, &conteoOponente, &columnaOponente);
    if (conteoOponente > conteoCpu) {
        printf("*elijo quitarle el puntaje a mi oponente*\n");
        return columnaOponente;
    } else if (conteoCpu > 1) {
        printf("*elijo colocarla en donde obtengo un mayor puntaje*\n");
        return columnaCpu;
    }
    // Si no, regresar la central por si está desocupada

    int columnaCentral = obtenerColumnaCentral(jugador, tablero);
    if (columnaCentral != COLUMNA_GANADORA_NO_ENCONTRADA) {
        printf("*elijo ponerla en el centro*\n");
        return columnaCentral;
    }
    // Finalmente, devolver la primera disponible de manera aleatoria
    int columna = obtenerColumnaAleatoria(jugador, tablero);
    if (columna != FILA_NO_ENCONTRADA) {
        printf("*elijo la primera vacía aleatoria*\n");
        return columna;
    }
    printf("Esto no debería suceder\n");
    return 0;
}