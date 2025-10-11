#include <stdio.h>
#define MAX 5


typedef struct {
    int codigo;
    float nota;
} Estudiante;


void mostrarEstudiantes(Estudiante arr[MAX], int n);
float notaMaxima(Estudiante arr[MAX], int n, int i, float max);
float promedioNotas(Estudiante arr[MAX], int n, int i, float suma);
void selectionSort(Estudiante arr[MAX], int n, int i);


int main() {
    Estudiante estudiantes[MAX] = {
        {2024105, 4.0},
        {2024102, 3.2},
        {2024104, 5.0},
        {2024101, 4.5},
        {2024103, 2.8}
    };

    int opcion;
    do {
        printf("\n==== MENU ====\n");
        printf("1. Mostrar estudiantes\n");
        printf("2. Buscar la nota máxima (recursivo)\n");
        printf("3. Calcular el promedio (recursivo)\n");
        printf("4. Ordenar estudiantes por codigo (Selection Sort recursivo)\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarEstudiantes(estudiantes, MAX);
                break;
            case 2:
                printf("Nota máxima: %.2f\n", notaMaxima(estudiantes, MAX, 0, estudiantes[0].nota));
                break;
            case 3:
                printf("Promedio: %.2f\n", promedioNotas(estudiantes, MAX, 0, 0) / MAX);
                break;
            case 4:
                selectionSort(estudiantes, MAX, 0);
                mostrarEstudiantes(estudiantes, MAX);
                break;
        }
    } while (opcion != 5);

    return 0;
}

void mostrarEstudiantes(Estudiante arr[MAX], int n) {
    for (int i = 0; i < n; i++) {
        printf("Codigo: %d - Nota: %.2f\n", arr[i].codigo, arr[i].nota);
    }
}

float notaMaxima(Estudiante arr[MAX], int n, int i, float max) {
    if (i == n) return max;
    if (arr[i].nota > max) max = arr[i].nota;
    return notaMaxima(arr, n, i + 1, max);
}

float promedioNotas(Estudiante arr[MAX], int n, int i, float suma) {
    if (i == n) return suma;
    return promedioNotas(arr, n, i + 1, suma + arr[i].nota);
}

void selectionSort(Estudiante arr[MAX], int n, int i) {
    if (i >= n - 1) return;

    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
        if (arr[j].codigo < arr[minIndex].codigo) {
            minIndex = j;
        }
    }

    Estudiante temp = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = temp;

    selectionSort(arr, n, i + 1);
}