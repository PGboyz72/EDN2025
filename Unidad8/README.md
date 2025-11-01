📚 Planificación de Procesos: Algoritmo Round Robin (RR)
Este proyecto contiene la implementación en lenguaje C del algoritmo de planificación de procesos Round Robin, utilizando una Cola Circular implementada con un arreglo.

El código cumple con las restricciones de usar únicamente las librerías estándar: stdio.h, stdlib.h, y string.h (omitiendo stdbool.h).

-Curso: Estructura de Datos

Integrante:

-Andrick Alain Preciado Gonzalez

💻 Ejercicio Integrado (Unidad 8)
El objetivo es simular un sistema de planificación de CPU basado en las siguientes reglas:


Estructura de Datos: Cola Circular.


Proceso: Cada proceso tiene un identificador (ID) y un tiempo de ejecución restante (burst_time).


Planificación: La CPU atiende a cada proceso por un tiempo fijo conocido como quantum (definido como TIME_QUANTUM = 2).


Rotación: Si un proceso no termina en ese tiempo, se interrumpe y vuelve al final de la cola.

⚙️ Cómo Compilar y Ejecutar
Estas instrucciones son válidas si tienes el compilador GCC (GNU Compiler Collection, usualmente parte de MinGW en Windows) instalado y su ruta configurada en la variable de entorno PATH.

Asegúrate de ejecutar todos los comandos desde la terminal de Windows (cmd) dentro del directorio donde se encuentra el archivo round_robin.c, que, según la estructura de tu sistema, es Unidad8.

-gcc round_robin.c -o rr
-rr.exe
-rr