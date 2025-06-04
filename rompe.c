//ensenada baja california  4 de junio del 2025
//alejandro huerta pimentel

//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

//estructuras de datos para el tablero
typedef struct {
    int **matriz; //un puntero doble para representar una matriz de tamaño dinamico
    int size; //establece el tamaño del tablero
    int vacioX; //posicion x del espacio
    int vacioY; //posicion y del espacio
} Tablero;

//inicializa el tablero, generando el panel aleatorio y los distribuye tambien aleatoriamente
void inicializarTablero(Tablero *t, int size) {
    t->size = size; //de la estructura t guarda el valor escogido en el main para definir el nivel

    //puntero a un arreglo de punteros cada uno de esos apunta a un arreglo de enteros define las filas de la matriz
    t->matriz = (int **)malloc(size * sizeof(int *));
    
    for (int i = 0; i < size; i++) { /*asigna a cada columna su propio arreglo de enteros con su tamaño size*/
        t->matriz[i] = (int *)malloc(size * sizeof(int));
    }
    
    int total = size * size; //toma el nivel y lo multiplica dinamicamente y toma el tamaño del tablero
    int *nums = malloc(sizeof(int) * total); //define el tamaño de la matriz
    //llena el arreglo con los numeros del 0 al total
    for (int i = 0; i < total; i++){
        nums[i] = i;
    }
        
    //inicializa la semilla
    srand(time(NULL));

    //mezcla aleatoriamente el arreglo de los numeros
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1); //elige un indice aleatorio entre 0 e i
        int tmp = nums[i];  //intercambia nums[i] con nums[j] esto provoca que haya intercambio de posiciones
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    //copia los valores mezclados del arreglo a la matriz del tablero
    int k = 0;//indice para recorrer el arreglo nums
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            t->matriz[i][j] = nums[k]; //asigna el valor mezclado a la celda de la matriz

            //si el valor es 0, guarda su posicion como el espacio vacio
            if (nums[k] == 0) {
                t->vacioX = i;
                t->vacioY = j;
            }
            k++; //y avansa al siguiente numero
        }
    }
    //libera la memoria del arreglo temporal que contenia los numeros mezclados
    free(nums);
}
//Muestra el tablero en la consola con un formato
void mostrarTablero(Tablero *t) { //recible la estructura t
    printf("\n======== ROMPECABEZAS %dx%d =========\n", t->size, t->size); //imprime el nombre
    for (int i = 0; i < t->size; i++) {
        //imprime la linea superior de cada fila
        printf("    ");
        for (int j = 0; j < t->size; j++) {
            printf("+----");
        }
        printf("+\n    ");
        //imprimir los valores o el espacio vacio
        for (int j = 0; j < t->size; j++) {
            if (t->matriz[i][j] == 0)
                printf("| __"); //el indice con el que se mueve
            else
                printf("| %2d", t->matriz[i][j]);
        }
        printf("|\n");
    }
    //imprimir la ultima linea inferior del tablero
    printf("    ");
    for (int j = 0; j < t->size; j++) {
        printf("+----");
    }
    printf("+\n");
}
//funcion que verifica si el tablero esta en orden ascendente y el espacio vacio al final
bool estaResuelto(Tablero *t) {
    int esperado = 1;
    for (int i = 0; i < t->size; i++) {
        for (int j = 0; j < t->size; j++) {
            //ultima casilla debe ser 0
            if (i == t->size - 1 && j == t->size - 1) {
                return t->matriz[i][j] == 0;
            }
            //si algun numero no esta en orden, no esta resuelto
            if (t->matriz[i][j] != esperado)
                return false;
            esperado++;
        }
    }
    return true;
}
//funcion para mover el indice o dicho el espacio vacio segun la direccion WASD
void mover(Tablero *t, char direccion) {
    int nx = t->vacioX; //mueve posicion en x
    int ny = t->vacioY; //mueve su posicion en y

    //cambia de posicion segun la caracter ingresado
    switch (direccion) {
        case 'w': nx--; break;
        case 's': nx++; break;
        case 'a': ny--; break;
        case 'd': ny++; break;
        default: return;
    }
    //verifica que la nueva posicion este dentro del tablero y si no, no sobrepasa esa barrera
    if (nx >= 0 && nx < t->size && ny >= 0 && ny < t->size) {
        //intercambiar el espacio vacio con el numero adyacente
        t->matriz[t->vacioX][t->vacioY] = t->matriz[nx][ny];
        t->matriz[nx][ny] = 0;
        //Actualizar la posicion del espacio vacio
        t->vacioX = nx;
        t->vacioY = ny;
    }
}
//libera la memoria asignada dinamicamente a la matriz
void liberarMemoria(Tablero *t) {
    for (int i = 0; i < t->size; i++) {
        free(t->matriz[i]);
    }
    free(t->matriz);
}
//funcion principal
int main(int arg, char *argv) {
    Tablero t; //crea la estructura del tablero
    char entrada; //variable para mover el espacio en blanco
    int nivel, size; //nivel de dificultad y el tamaño del tablero

    printf("=== ROMPECABEZAS DESLIZANTE ===\n");
    printf("Selecciona nivel de dificultad:\n");
    printf("1. Facil (3x3)\n");
    printf("2. Medio (4x4)\n");
    printf("3. Dificil (5x5)\n");
    printf("Nivel: ");
    scanf("%d", &nivel);
    //el nivel del juego
    switch (nivel) {
        case 1: size = 3; break;
        case 2: size = 4; break;
        case 3: size = 5; break;
        default: printf("Nivel no valido. Se usara 3x3.\n"); size = 3; break;
    }

    inicializarTablero(&t, size); //crea el tablero con el nivel que el usuario ingreso

    //ciclo principal
    while (true) {
        system("cls");//cada que ingresa limpia la pantalla
        mostrarTablero(&t); //muestra el tablero

        if (estaResuelto(&t)) { //verifica si esta resuelto
            printf("¡Felicidades! Resolviste el rompecabezas.\n");
            break;
        }

        printf("Mover (W A S D): ");
        scanf(" %c", &entrada); //lee la tecla de movimiento

        mover(&t, entrada); //aplica el movimiento
    }

    liberarMemoria(&t); //libera recursos anteriormente utilizadas en la funcion mostrarTablero

    return 0;
}