#include "pasajero.h"

void mostrar_menu() {
    printf("\nGESTOR DE TIQUETES Y ABORDAJE\n");
    if (capacidad_maxima > 0) {
        printf("Capacidad: %d | Vendidos: %d | Limite: %d | Abordaje: %s\n",
               capacidad_maxima, tiquetes_vendidos, limite_sobreventa,
               abordaje_iniciado ? "INICIADO" : "NO INICIADO");
    } else {
        printf("Capacidad no definida aun.\n");
    }
    printf("1. Establecer Capacidad\n");
    printf("2. Vender Tiquete\n");
    printf("3. Iniciar Abordaje\n");
    printf("4. Ver Abordados\n");
    printf("5. Ver No Abordados\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    int opcion;
    do {
        mostrar_menu();

        if (scanf("%d", &opcion) != 1) {
            opcion = 0;
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
        }

        switch (opcion) {
            case 1: establecer_capacidad(); break;
            case 2: vender_tiquete(); break;
            case 3: iniciar_abordaje(); break;
            case 4: ver_abordados(); break;
            case 5: ver_no_abordados(); break;
            case 6: printf("\nSaliendo del programa...\n"); break;
            default: printf("\nOpcion invalida, intente de nuevo.\n");
        }
    } while (opcion != 6);

    liberar_lista(&abordados);
    liberar_lista(&no_abordados);
    liberar_lista(&cabeza_vendidos);

    return 0;
}