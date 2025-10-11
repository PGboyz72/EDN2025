#include "pasajero.h"

void mostrar_menu() {
    printf("  GESTOR DE TIQUETES Y ABORDAJE DE AVIÓN (C)\n");
    if (capacidad_maxima > 0) {
        printf(">> Estado: Capacidad: %d | Vendidos: %d | Límite: %d\n",
               capacidad_maxima, tiquetes_vendidos, limite_sobreventa);
        printf(">> Abordaje: %s\n", abordaje_iniciado ? "INICIADO" : "NO INICIADO");
    } else {
        printf(">> Estado: Capacidad NO definida.\n");
    }
    printf("1. Establecer Capacidad\n");
    printf("2. Vender Tiquete\n");
    printf("3. Iniciar Abordaje\n");
    printf("4. Ver Abordados\n");
    printf("5. Ver No Abordados\n");
    printf("6. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    int opcion;

    do {
        mostrar_menu();

        if (scanf("%d", &opcion) != 1) {
            opcion = 0;
            while (getchar() != '\n');
        } else{
            while (getchar() != '\n');
        }

        switch (opcion) {
            case 1:
                establecer_capacidad();
                break;
            case 2:
                vender_tiquete();
                break;
            case 3:
                iniciar_abordaje();
                break;
            case 4:
                ver_abordados();
                break;
            case 5:
                ver_no_abordados();
                break;
            case 6:
                printf("\nSaliendo del programa. ¡Memoria liberada!\n");
                break;
            default:
                printf("\nOpción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    liberar_lista(&abordados);
    liberar_lista(&no_abordados);
    liberar_lista(&cabeza_vendidos);

    return 0;
}