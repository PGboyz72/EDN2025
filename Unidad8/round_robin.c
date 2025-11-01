#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2 

#define TRUE 1
#define FALSE 0

typedef struct {
    int id;
    int burst_time;
} Proceso;

typedef struct {
    Proceso items[MAX_PROCESSES];
    int front;
    int rear;
    int size;
} ColaCircular;

void initialize(ColaCircular* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(ColaCircular* q) {
    return (q->size == 0) ? TRUE : FALSE;
}

int isFull(ColaCircular* q) {
    return (q->size == MAX_PROCESSES) ? TRUE : FALSE;
}

void enqueue(ColaCircular* q, Proceso p) {
    if (isFull(q)) {
        printf("ERROR: La cola está llena. No se puede agregar el Proceso %d.\n", p.id);
        return;
    }
    q->rear = (q->rear + 1) % MAX_PROCESSES;
    q->items[q->rear] = p;
    q->size++;
}

Proceso dequeue(ColaCircular* q) {
    if (isEmpty(q)) {
        printf("ERROR: La cola está vacía.\n");
        return (Proceso){-1, -1}; 
    }
    Proceso p = q->items[q->front];
    q->front = (q->front + 1) % MAX_PROCESSES;
    q->size--;
    return p;
}

void round_robin_scheduler(ColaCircular* q) {
    int tiempo_actual = 0;
    printf("\n--- Simulación de Planificación Round Robin (Quantum = %d) ---\n", TIME_QUANTUM);

    while (!isEmpty(q)) {
        Proceso p = dequeue(q);
        
        int tiempo_ejecutado = (p.burst_time > TIME_QUANTUM) ? TIME_QUANTUM : p.burst_time;

        p.burst_time -= tiempo_ejecutado;
        tiempo_actual += tiempo_ejecutado;

        printf("Tiempo %d-%d: Proceso %d ejecutado por %d unidades. (Restante: %d)\n",
               tiempo_actual - tiempo_ejecutado, tiempo_actual, p.id, tiempo_ejecutado, p.burst_time);

        if (p.burst_time> 0) {
            enqueue(q, p); 
        } else {
            printf("--- Proceso %d COMPLETADO en el tiempo total %d ---\n", p.id, tiempo_actual);
        }
    }
    printf("\n--- Todos los procesos completados. Tiempo total de ejecución: %d ---\n", tiempo_actual);
}

int main() {
    ColaCircular cola_procesos;
    initialize(&cola_procesos);

    Proceso p1 = {1, 10};
    Proceso p2 = {2, 6};
    Proceso p3 = {3, 3};
    Proceso p4 = {4, 5};

    printf("Ingresando procesos a la cola de listos...\n");
    enqueue(&cola_procesos, p1);
    enqueue(&cola_procesos, p2);
    enqueue(&cola_procesos, p3);
    enqueue(&cola_procesos, p4);

    round_robin_scheduler(&cola_procesos);

    return 0;
}