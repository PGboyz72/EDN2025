#ifndef PASAJERO_H
#define PASAJERO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FEMENINO,
    MASCULINO,
    NO_BINARIO
} Genero;

typedef struct Pasajero {
    Genero genero;
    char primer_apellido[50];
    struct Pasajero *siguiente;
} Pasajero;

extern Pasajero *cabeza_vendidos;
extern Pasajero *cola_vendidos;
extern Pasajero *abordados;
extern Pasajero *no_abordados;

extern int capacidad_maxima;
extern int tiquetes_vendidos;
extern int limite_sobreventa;
extern int abordaje_iniciado;

const char* genero_a_cadena(Genero g);
void liberar_lista(Pasajero **cabeza);

void establecer_capacidad();
void vender_tiquete();
void iniciar_abordaje();
void ver_abordados();
void ver_no_abordados();

#endif