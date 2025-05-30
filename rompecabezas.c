//ensenada baja california 29 de mayo del 2025

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

#define SIZE 5
// Estructura para representar el tablero
typedef struct {
    int matriz[SIZE][SIZE];
    int vacioX;
    int vacioY;
} Tablero;

// Inicializa el tablero mezclando los números aleatoriamente
void inicializarTablero(Tablero *t) {
    int total = SIZE * SIZE;
    int *nums = malloc(sizeof(int) * total);

    for (int i = 0; i < total; i++)
        nums[i] = i;

    // Mezclar
    srand(time(NULL));
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    // Cargar al tablero
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            t->matriz[i][j] = nums[k];
            if (nums[k] == 0) {
                t->vacioX = i;
                t->vacioY = j;
            }
            k++;
        }
    }

    free(nums);
}


// Muestra el tablero en pantalla
void mostrarTablero(Tablero *t) {
    printf("\n======== 8 ROMPECABEZAS =========\n");
    printf("    +---+---+---+\n");
    //imprime por la matriz
    for (int i = 0; i < SIZE; i++) {
        printf("    |");
        for (int j = 0; j < SIZE; j++) {
            if (t->matriz[i][j] == 0)
                printf(" _ |");
            else
                printf(" %d |", t->matriz[i][j]);
        }
        printf("\n");
        printf("    +---+---+---+\n");
    }
    printf("\n");
}

// Verifica si el puzzle está resuelto
bool estaResuelto(Tablero *t) {
    int esperado = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1) {
                return t->matriz[i][j] == 0;
            }
            if (t->matriz[i][j] != esperado)
                return false;
            esperado++;
        }
    }
    return true;
}

// Mueve el cursor desde el teclado
void mover(Tablero *t, char direccion) {
    int nx = t->vacioX;
    int ny = t->vacioY;

    switch (direccion) {
        case 'w': nx--; break;
        case 's': nx++; break;
        case 'a': ny--; break;
        case 'd': ny++; break;
        default: return;
    }

    // Verifica que la nueva posición sea válida
    if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
        // Intercambia el número con el espacio vacío
        t->matriz[t->vacioX][t->vacioY] = t->matriz[nx][ny];
        t->matriz[nx][ny] = 0;
        t->vacioX = nx;
        t->vacioY = ny;
    }
}
//la funcion principal
int main() {
    Tablero t;
    char entrada;

    inicializarTablero(&t);

    while (true) {
        system("cls");
        mostrarTablero(&t);

        if (estaResuelto(&t)) {
            printf("🎉 ¡Felicidades! Resolviste el rompecabezas.\n");
            break;
        }

        printf("Mover (WASD): ");
        scanf(" %c", &entrada);
        
        mover(&t, entrada);
    }

    return 0;
}
