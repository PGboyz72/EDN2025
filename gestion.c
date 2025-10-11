#include "pasajero.h"

Pasajero *cabeza_vendidos = NULL;
Pasajero *cola_vendidos = NULL;
Pasajero *abordados = NULL;
Pasajero *no_abordados = NULL;

int capacidad_maxima = 0;
int tiquetes_vendidos = 0;
int limite_sobreventa = 0;
int abordaje_iniciado = 0;

const char* genero_a_cadena(Genero g) {
    switch (g) {
        case FEMENINO: return "Femenino";
        case MASCULINO: return "Masculino";
        case NO_BINARIO: return "No Binario";
        default: return "Desconocido";
    }
}

void liberar_lista(Pasajero **cabeza) {
    Pasajero *actual = *cabeza;
    Pasajero *siguiente;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}

void establecer_capacidad() {
    if (capacidad_maxima > 0) {
        printf("\nLa capacidad ya ha sido establecida en %d. No se puede cambiar.\n", capacidad_maxima);
        return;
    }

    int cap;
    printf("\nIngrese la capacidad máxima de pasajeros del avión: ");
    if (scanf("%d", &cap) != 1 || cap <= 0) {
        printf("Entrada inválida. La capacidad debe ser un número entero positivo.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    capacidad_maxima = cap;
    limite_sobreventa = capacidad_maxima + (capacidad_maxima / 10);
    printf("Capacidad establecida: %d pasajeros.\n", capacidad_maxima);
    printf("Límite de venta por sobreventa (10%%): %d tiquetes.\n", limite_sobreventa);
}

void vender_tiquete() {
    if (capacidad_maxima == 0) {
        printf("\nDebe establecer primero la capacidad del avión (Opción 1).\n");
        return;
    }
    if (abordaje_iniciado) {
        printf("\nEl proceso de abordaje ya ha iniciado. No se pueden vender más tiquetes.\n");
        return;
    }
    if (tiquetes_vendidos >= limite_sobreventa) {
        printf("\nLímite de sobreventa (%d) alcanzado! No se pueden vender más tiquetes.\n", limite_sobreventa);
        return;
    }

    Pasajero *nuevo_pasajero = (Pasajero *)malloc(sizeof(Pasajero));
    if (nuevo_pasajero == NULL) {
        perror("Error de asignación de memoria");
        return;
    }

    int opcion_genero;
    printf("\n--- Venta de Tiquete #%d ---\n", tiquetes_vendidos + 1);

    printf("Seleccione Género:\n");
    printf("  1. Femenino\n");
    printf("  2. Masculino\n");
    printf("  3. No Binario\n");
    printf("Opción: ");
    if (scanf("%d", &opcion_genero) != 1 || opcion_genero < 1 || opcion_genero > 3) {
        printf("Opción de género inválida. Venta cancelada.\n");
        free(nuevo_pasajero);
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    switch (opcion_genero) {
        case 1: nuevo_pasajero->genero = FEMENINO; break;
        case 2: nuevo_pasajero->genero = MASCULINO; break;
        case 3: nuevo_pasajero->genero = NO_BINARIO; break;
    }

    printf("Ingrese Primer Apellido: ");
    if (scanf("%49s", nuevo_pasajero->primer_apellido) != 1) {
        printf("Error al leer el apellido. Venta cancelada.\n");
        free(nuevo_pasajero);
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    nuevo_pasajero->siguiente = NULL;

    if (cabeza_vendidos == NULL) {
        cabeza_vendidos = nuevo_pasajero;
        cola_vendidos = nuevo_pasajero;
    } else {
        cola_vendidos->siguiente = nuevo_pasajero;
        cola_vendidos = nuevo_pasajero;
    }

    tiquetes_vendidos++;
    printf("Tiquete vendido con éxito a %s (%s). Tiquetes totales: %d.\n",
           nuevo_pasajero->primer_apellido, genero_a_cadena(nuevo_pasajero->genero), tiquetes_vendidos);
}


void iniciar_abordaje() {
if (capacidad_maxima == 0) {
        printf("\nDebe establecer primero la capacidad del avión (Opción 1).\n");
        return;
    }
    if (abordaje_iniciado) {
        printf("\nEl proceso de abordaje ya había finalizado.\n");
        return;
    }
    if (cabeza_vendidos == NULL) {
        printf("\nNo hay tiquetes vendidos para iniciar el abordaje.\n");
        return;
    }

    abordaje_iniciado = 1;
    int abordados_count = 0;
    Pasajero *actual;
    Pasajero *temp;

    printf("\n--- INICIANDO PROCESO DE ABORDAJE ---\n");
    printf("Capacidad máxima del avión: %d pasajeros.\n", capacidad_maxima);

    while (cabeza_vendidos != NULL && abordados_count < capacidad_maxima) {
        actual = cabeza_vendidos;
        cabeza_vendidos = cabeza_vendidos->siguiente;
        
        actual->siguiente = NULL;

        actual->siguiente = abordados;
        abordados = actual;
        
        printf("Abordado #%d: %s\n", abordados_count + 1, actual->primer_apellido);
        abordados_count++;
    }

    Pasajero *prev = NULL;
    Pasajero *curr = abordados;
    Pasajero *next = NULL;
    while (curr != NULL) {
        next = curr->siguiente;
        curr->siguiente = prev;
        prev = curr;
        curr = next;
    }
    abordados = prev;

    printf("\n--- ABORDAJE COMPLETADO ---\n");
    printf("Total de pasajeros que lograron abordar: %d.\n", abordados_count);

    if (cabeza_vendidos != NULL) {
        no_abordados = cabeza_vendidos;
        cabeza_vendidos = NULL;
        cola_vendidos = NULL;
        printf(" %d tiquetes vendidos quedaron sin abordar debido a la capacidad máxima.\n", tiquetes_vendidos - abordados_count);
    } else {
        no_abordados = NULL;
    }
}

void mostrar_lista(Pasajero *cabeza, const char *titulo) {
    printf("\n--- %s ---\n", titulo);
    if (cabeza == NULL) {
        printf("  (Lista vacía)\n");
        return;
    }

    Pasajero *actual = cabeza;
    int contador = 1;
    while (actual != NULL) {
        printf("  %d. Apellido: %-15s | Género: %s\n",
               contador++,
               actual->primer_apellido,
               genero_a_cadena(actual->genero));
        actual = actual->siguiente;
    }
}

void ver_abordados() {
    if (!abordaje_iniciado) {
        printf("\nEl proceso de abordaje aún no ha iniciado (Opción 3).\n");
        return;
    }
    mostrar_lista(abordados, "LISTA DE PASAJEROS ABORDADOS");
}

void ver_no_abordados() {
    if (!abordaje_iniciado) {
        printf("\nEl proceso de abordaje aún no ha iniciado (Opción 3).\n");
        return;
    }
    mostrar_lista(no_abordados, "LISTA DE PASAJEROS NO ABORDADOS (OVERBOOKING)");
}