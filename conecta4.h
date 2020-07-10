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
#define COLUMNA_GANADORA_NO_ENCONTRADA -1

int contarArriba(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]);

int contarDerecha(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]);

int contarArribaDerecha(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]);

int contarAbajoDerecha(int x, int y, char jugador, char tablero[FILAS][COLUMNAS]);

int obtenerFilaDesocupada(int columna, char tablero[FILAS][COLUMNAS]);

int colocarPieza(char jugador, int columna, char tablero[FILAS][COLUMNAS]);

void limpiarTablero(char tablero[FILAS][COLUMNAS]);

void dibujarEncabezado(int columnas);

int dibujarTablero(char tablero[FILAS][COLUMNAS]);

int esEmpate(char tablero[FILAS][COLUMNAS]);

char obtenerOponente(char jugador);

void clonarMatriz(char tableroOriginal[FILAS][COLUMNAS], char destino[FILAS][COLUMNAS]);

int obtenerColumnaGanadora(char jugador, char tableroOriginal[FILAS][COLUMNAS]);

int obtenerPrimeraFilaLlena(int columna, char tablero[FILAS][COLUMNAS]);

void obtenerColumnaEnLaQueSeObtieneMayorPuntaje(char jugador, char tableroOriginal[FILAS][COLUMNAS], int *conteo,
                                                int *indice);

int aleatorio_en_rango(int minimo, int maximo);

int obtenerColumnaAleatoria(char jugador, char tableroOriginal[FILAS][COLUMNAS]);

int obtenerColumnaCentral(char jugador, char tableroOriginal[FILAS][COLUMNAS]);

int elegirColumnaCpu(char jugador, char tablero[FILAS][COLUMNAS]);
