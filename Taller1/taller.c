#include <stdio.h>
#define MAX 10

void llenarArray(int vector[MAX], int n);
void mostrarArray(int vector[MAX], int n);
void selectionSort(int array[MAX], int n);
void insertionSort(int arr[MAX], int n);

int main() {
    int arreglo[MAX];
    int opc; 
    do {
        printf("\n==== MENU ====\n");
        printf("1. Llenar array\n");
        printf("2. Mostrar array\n");
        printf("3. Ordenar array (Selection Sort)\n");
        printf("4. Ordenar array (Insertion Sort)\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: 
                llenarArray(arreglo, MAX);
            break;
            case 2:
                mostrarArray(arreglo, MAX);
            break;
            case 3:
                selectionSort(arreglo, MAX);
            break;
            case 4:
                insertionSort(arreglo, MAX);
            break;
        }
    } while(opc != 5);

    printf("Muchas Gracias\n");
    return 0;
}

void llenarArray(int vector[MAX], int n) {
    for(int i = 0; i < n; i++) {
        printf("Ingrese el valor de la posicion %d: ", i);
        scanf("%d", &vector[i]);
        while (vector[i] < 0) {
             printf("Error, ingrese un valor positivo %d: ", i);
             scanf("%d", &vector[i]);
        }
    }
}

void mostrarArray(int vector[MAX], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d  ", vector[i]);
    }
    printf("\n");
}

void selectionSort(int array[MAX], int n) { 
    for (int i = 0; i < n - 1; i++) { 
        int minIndex = i;
        for (int j = i + 1; j < n; j++) { 
            if (array[j] < array[minIndex]) { 
                minIndex = j; 
            } 
        }
        int temp = array[i]; 
        array[i] = array[minIndex]; 
        array[minIndex] = temp;

        printf("\nIntercambio en paso %d:\n", i + 1);
        mostrarArray(array, n);
    } 
} 

void insertionSort(int arr[MAX], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  
            j--;
        }
        arr[j + 1] = key;

        printf("\nPaso %d:\n", i);
        mostrarArray(arr, n);
    }
}