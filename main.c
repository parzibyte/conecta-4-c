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
#include "juego.c"


int main() {
    // Hay que alimentar a rand, solamente una vez (seed rand)
    srand(getpid());
    printf("*** Conecta 4 ***\n\nBy Parzibyte\n\t\thttps://parzibyte.me/blog\n");
    int modo;
    printf("1 => Humano contra Humano\n"
           "2 => Humano contra CPU\n"
           "3 => CPU contra CPU\n"
           "4 => Salir\n"
           "Seleccione una opción: ");
    scanf("%d", &modo);
    if (modo <= 0 || modo > 3) {
        return 0;
    }
    jugar(modo);
    return 0;
}
