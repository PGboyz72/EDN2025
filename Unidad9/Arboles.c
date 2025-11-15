#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int clave;
    struct nodo* izq;
    struct nodo* der;
} nodo;

#define MAX 100

nodo* nuevo(int clave) {
    nodo* nuevo = (nodo*) malloc(sizeof(nodo));
    if (!nuevo) return NULL;
    nuevo->clave = clave;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

nodo* minimo(nodo* r) {
    nodo* actual = r;
    while (actual && actual->izq != NULL)
        actual = actual->izq;
    return actual;
}

nodo* insertar(nodo* r, int x) {
    if (r == NULL) return nuevo(x);
    if (x < r->clave) {
        r->izq = insertar(r->izq, x);
    } 
    else if (x > r->clave) {
        r->der = insertar(r->der, x);
    }
    return r;
}

nodo* eliminar(nodo* raiz, int x) {
    if (raiz == NULL) return raiz;

    if (x < raiz->clave) {
        raiz->izq = eliminar(raiz->izq, x);
    } else if (x > raiz->clave) {
        raiz->der = eliminar(raiz->der, x);
    } else {
        if (raiz->izq == NULL) {
            nodo* temp = raiz->der;
            free(raiz);
            return temp;
        } else if (raiz->der == NULL) {
            nodo* temp = raiz->izq;
            free(raiz);
            return temp;
        }
        
        nodo* temp = minimo(raiz->der);
        raiz->clave = temp->clave;
        raiz->der = eliminar(raiz->der, temp->clave);
    }
    return raiz;
}

void inorden(nodo* r) {
    if (r == NULL) return;
    inorden(r->izq);
    printf("%d ", r->clave);
    inorden(r->der);
}

void preorden(nodo* r) {
    if (r == NULL) return;
    printf("%d ", r->clave);
    preorden(r->izq);
    preorden(r->der);
}

void postorden(nodo* r) {
    if (r == NULL) return;
    postorden(r->izq);
    postorden(r->der);
    printf("%d ", r->clave);
}

void porNiveles(nodo* raiz) {
    if (!raiz) return;

    nodo* cola[MAX];
    int ini = 0, fin = 0;
    
    cola[fin++] = raiz;

    while (ini < fin) {
        nodo* actual = cola[ini++];
        printf("%d ", actual->clave);

        if (actual->izq) cola[fin++] = actual->izq;
        if (actual->der) cola[fin++] = actual->der;
    }
}

void liberarArbol(nodo* r) {
    if (r == NULL) return;
    liberarArbol(r->izq);
    liberarArbol(r->der);
    free(r);
}

void mostrarMenu() {
    printf("\nMENU PRINCIPAL\n");
    printf("1. Registrar Nodo\n");
    printf("2. Mostrar Nodos\n");
    printf("3. Eliminar Nodo\n");
    printf("4. Salir\n");
    printf("Digite la opcion: ");
}

nodo* RegistrarNodo(nodo* raiz) {
    int valor;
    printf("Digite el valor del nodo: ");
    if (scanf("%d", &valor) != 1) {
        while (getchar() != '\n');
        printf("Error: Entrada invalida. Intente de nuevo.\n");
        return raiz;
    }
    raiz = insertar(raiz, valor);
    printf("Nuevo nodo (%d) registrado.\n", valor);
    return raiz;
}

void MostrarNodos(nodo* raiz) {
    if (raiz == NULL) {
        printf("El arbol esta vacio. Registre nodos primero.\n");
        return;
    }
    printf("\nRECORRIDOS\n");
    printf("Inorden: ");
    inorden(raiz);
    printf(" (Orden Ascendente)\n");
    
    printf("Preorden: ");
    preorden(raiz);
    printf("\n");
    
    printf("Postorden: ");
    postorden(raiz);
    printf("\n");
    
    printf("Por Niveles: ");
    porNiveles(raiz);
    printf("\n");
}

int main() {
    nodo* raiz = NULL;
    int opcion;
    
    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 0;
        } else {
            while (getchar() != '\n'); 
        }

        switch (opcion) {
            case 1:
                raiz = RegistrarNodo(raiz);
                break;
            case 2:
                MostrarNodos(raiz);
                break;
            case 3:
                if (raiz != NULL) {
                    int valor_a_eliminar;
                    printf("Digite la clave del nodo a eliminar: ");
                    if (scanf("%d", &valor_a_eliminar) == 1) {
                        raiz = eliminar(raiz, valor_a_eliminar);
                        printf("Intento de eliminacion de %d realizado. Verifique con el Recorrido.\n", valor_a_eliminar);
                    } else {
                        while (getchar() != '\n');
                        printf("Error: Entrada invalida para la eliminacion.\n");
                    }
                } else {
                    printf("El arbol esta vacio.\n");
                }
                break;
            case 4:
                printf("\nSaliendo del programa. Liberando memoria...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 4);

    liberarArbol(raiz);
    return 0;
}