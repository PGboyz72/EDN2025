#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Pedido {
    char nombre_destino[50];
    int cantidad_solicitada;
    struct Pedido *siguiente;
} Pedido;

typedef struct Lote {
    long fecha_vencimiento;
    int stock_total;
    char nombre_producto[50];
    struct Lote *izquierda;
    struct Lote *derecha;
    int altura;
    Pedido *cabeza_pedidos;
} Lote;

int obtenerAltura(Lote *lote) {
    if (lote == NULL) {
        return 0;
    }
    return lote->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Lote *nuevoLote(long fecha, int stock, const char *producto) {
    Lote *lote = (Lote *)malloc(sizeof(Lote));
    if (lote == NULL) {
        exit(EXIT_FAILURE);
    }
    lote->fecha_vencimiento = fecha;
    lote->stock_total = stock;
    strncpy(lote->nombre_producto, producto, 49);
    lote->nombre_producto[49] = '\0';
    lote->izquierda = NULL;
    lote->derecha = NULL;
    lote->altura = 1;
    lote->cabeza_pedidos = NULL;
    return lote;
}

Lote *rotacionDerecha(Lote *y) {
    Lote *x = y->izquierda;
    Lote *T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

    return x;
}

Lote *rotacionIzquierda(Lote *x) {
    Lote *y = x->derecha;
    Lote *T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

    return y;
}

int obtenerFactorBalanceo(Lote *lote) {
    if (lote == NULL) {
        return 0;
    }
    return obtenerAltura(lote->izquierda) - obtenerAltura(lote->derecha);
}

Lote *insertarLote(Lote *nodo, long fecha, int stock, const char *producto) {
    if (nodo == NULL)
        return nuevoLote(fecha, stock, producto);

    if (fecha < nodo->fecha_vencimiento)
        nodo->izquierda = insertarLote(nodo->izquierda, fecha, stock, producto);
    else if (fecha > nodo->fecha_vencimiento)
        nodo->derecha = insertarLote(nodo->derecha, fecha, stock, producto);
    else {
        printf("ADVERTENCIA: ya existe un lote con la fecha %ld. no se procesa la insercion.\n", fecha);
        return nodo;
    }

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

    int balance = obtenerFactorBalanceo(nodo);

    if (balance > 1 && fecha < nodo->izquierda->fecha_vencimiento)
        return rotacionDerecha(nodo);

    if (balance < -1 && fecha > nodo->derecha->fecha_vencimiento)
        return rotacionIzquierda(nodo);

    if (balance > 1 && fecha > nodo->izquierda->fecha_vencimiento) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && fecha < nodo->derecha->fecha_vencimiento) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

Lote *buscarLote(Lote *raiz, long fecha) {
    if (raiz == NULL || raiz->fecha_vencimiento == fecha) {
        return raiz;
    }

    if (fecha < raiz->fecha_vencimiento) {
        return buscarLote(raiz->izquierda, fecha);
    } else {
        return buscarLote(raiz->derecha, fecha);
    }
}

Lote *encontrarMinValorLote(Lote *lote) {
    Lote *actual = lote;
    if (actual == NULL) return NULL;
    while (actual->izquierda != NULL) {
        actual = actual->izquierda;
    }
    return actual;
}

void encolarPedido(Lote *lote, const char *destino, int cantidad) {
    Pedido *nuevo = (Pedido *)malloc(sizeof(Pedido));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria para el pedido.\n");
        return;
    }
    strncpy(nuevo->nombre_destino, destino, 49);
    nuevo->nombre_destino[49] = '\0';
    nuevo->cantidad_solicitada = cantidad;
    nuevo->siguiente = NULL;

    if (lote->cabeza_pedidos == NULL) {
        lote->cabeza_pedidos = nuevo;
    } else {
        Pedido *actual = lote->cabeza_pedidos;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    printf("Pedido para %s (Cant: %d) registrado en el lote %ld.\n", destino, cantidad, lote->fecha_vencimiento);
}

int contarPedidos(Pedido *cabeza) {
    int contador = 0;
    Pedido *actual = cabeza;
    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

void liberarColaPedidos(Pedido *cabeza) {
    Pedido *actual = cabeza;
    Pedido *siguiente;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

Lote *eliminarLote(Lote *raiz, long fecha) {
    if (raiz == NULL)
        return raiz;

    if (fecha < raiz->fecha_vencimiento)
        raiz->izquierda = eliminarLote(raiz->izquierda, fecha);
    else if (fecha > raiz->fecha_vencimiento)
        raiz->derecha = eliminarLote(raiz->derecha, fecha);
    else {
        printf("Lote encontrado para eliminar: Fecha %ld. Liberando memoria...\n", raiz->fecha_vencimiento);

        liberarColaPedidos(raiz->cabeza_pedidos);

        if ((raiz->izquierda == NULL) || (raiz->derecha == NULL)) {
            Lote *temp = raiz->izquierda ? raiz->izquierda : raiz->derecha;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            Lote *temp = encontrarMinValorLote(raiz->derecha);

            raiz->fecha_vencimiento = temp->fecha_vencimiento;
            raiz->stock_total = temp->stock_total;
            strncpy(raiz->nombre_producto, temp->nombre_producto, 49);
            raiz->nombre_producto[49] = '\0';
            
            raiz->derecha = eliminarLote(raiz->derecha, temp->fecha_vencimiento);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + max(obtenerAltura(raiz->izquierda), obtenerAltura(raiz->derecha));

    int balance = obtenerFactorBalanceo(raiz);

    if (balance > 1 && obtenerFactorBalanceo(raiz->izquierda) >= 0)
        return rotacionDerecha(raiz);

    if (balance > 1 && obtenerFactorBalanceo(raiz->izquierda) < 0) {
        raiz->izquierda = rotacionIzquierda(raiz->izquierda);
        return rotacionDerecha(raiz);
    }

    if (balance < -1 && obtenerFactorBalanceo(raiz->derecha) <= 0)
        return rotacionIzquierda(raiz);

    if (balance < -1 && obtenerFactorBalanceo(raiz->derecha) > 0) {
        raiz->derecha = rotacionDerecha(raiz->derecha);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

int cancelarPedido(Lote *lote, const char *destino, int cantidad) {
    if (lote == NULL || lote->cabeza_pedidos == NULL) {
        return FALSE; 
    }

    Pedido *actual = lote->cabeza_pedidos;
    Pedido *previo = NULL;

    while (actual != NULL) {
        if (strcmp(actual->nombre_destino, destino) == 0 && actual->cantidad_solicitada == cantidad) {
            if (previo == NULL) {
                lote->cabeza_pedidos = actual->siguiente;
            } else {
                previo->siguiente = actual->siguiente;
            }
            lote->stock_total += cantidad;
            free(actual);
            printf("Pedido cancelado y stock (%d) restablecido para el lote %ld.\n", cantidad, lote->fecha_vencimiento);
            return TRUE;
        }
        previo = actual;
        actual = actual->siguiente;
    }
    return FALSE;
}

void reporteInOrder(Lote *lote) {
    if (lote != NULL) {
        reporteInOrder(lote->izquierda);

        printf("Fecha vencimiento: %ld\n", lote->fecha_vencimiento);
        printf("Producto: %s\n", lote->nombre_producto);
        printf("Stock disponible: %d\n", lote->stock_total);
        int numPedidos = contarPedidos(lote->cabeza_pedidos);
        printf("Pedidos en espera (FIFO): %d\n", numPedidos);

        if (numPedidos > 0) {
            printf("   Detalle de la cola de pedidos:\n");
            Pedido *p = lote->cabeza_pedidos;
            int i = 1;
            while (p != NULL) {
                printf("    %d. Destino: %s, Cantidad: %d\n", i++, p->nombre_destino, p->cantidad_solicitada);
                p = p->siguiente;
            }
        }

        reporteInOrder(lote->derecha);
    }
}

void liberarArbol(Lote *raiz) {
    if (raiz == NULL)
        return;

    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);

    printf("Liberando lote %ld y su cola de pedidos...\n", raiz->fecha_vencimiento);
    liberarColaPedidos(raiz->cabeza_pedidos);
    free(raiz);
}

void mostrarMenu() {
    printf("\nSISTEMA LOGISTICO DE ALIMENTOS\n");
    printf("1. Recepcion de mercancia\n");
    printf("2. Registrar pedido de despacho\n");
    printf("3. Baja de producto/Lote\n");
    printf("4. Cancelar pedido\n");
    printf("5. Reporte de estado\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    Lote *raiz = NULL; 

    int opcion;
    long fecha;
    int stock;
    char producto[50];
    char destino[50];
    int cantidad;
    Lote *loteEncontrado;

    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada no valida. Intente de nuevo.\n");
            while (getchar() != '\n');
            opcion = 0;
            continue;
        }

        switch (opcion) {
            case 1:
                printf("\nRecepcion de mercancia\n");
                printf("Ingrese fecha de vencimiento (AAAAMMDD): ");
                scanf("%ld", &fecha);
                printf("Ingrese Cantidad (Stock): ");
                scanf("%d", &stock);
                printf("Ingrese nombre del producto: ");
                scanf("%s", producto); 
                
                if (buscarLote(raiz, fecha) != NULL) {
                    printf("ERROR: Un lote con la fecha %ld ya existe. El producto no puede procesarse.\n", fecha);
                } else {
                    raiz = insertarLote(raiz, fecha, stock, producto);
                    printf("Lote %ld de %s registrado con exito.\n", fecha, producto);
                }
                break;

            case 2:
                printf("\nRegistrar pedido de despacho\n");
                loteEncontrado = encontrarMinValorLote(raiz);

                if (loteEncontrado == NULL) {
                    printf("ERROR: No hay productos en inventario.\n");
                    break;
                }
                
                printf("Lote encontrado para el pedido (Proximo a Vencer): %ld (%s), Stock: %d\n", 
                       loteEncontrado->fecha_vencimiento, loteEncontrado->nombre_producto, loteEncontrado->stock_total);
                
                printf("Ingrese destino del pedido: ");
                scanf("%s", destino);
                printf("Ingrese cantidad solicitada: ");
                scanf("%d", &cantidad);
                
                if (cantidad <= 0) {
                    printf("ERROR: La cantidad debe ser positiva.\n");
                } else if (loteEncontrado->stock_total >= cantidad) {
                    encolarPedido(loteEncontrado, destino, cantidad);
                    loteEncontrado->stock_total -= cantidad; 
                    printf("Stock de %s reducido en %d unidades. Nuevo Stock: %d\n", 
                           loteEncontrado->nombre_producto, cantidad, loteEncontrado->stock_total);
                } else {
                    printf("ERROR: Stock insuficiente. Disponible: %d, Solicitado: %d\n", 
                           loteEncontrado->stock_total, cantidad);
                }
                break;

            case 3:
                printf("\nBaja de Producto/Lote Podrido\n");
                printf("Ingrese Fecha de Vencimiento (AAAAMMDD) del lote a eliminar: ");
                scanf("%ld", &fecha);

                if (buscarLote(raiz, fecha) != NULL) {
                    raiz = eliminarLote(raiz, fecha);
                    printf("Lote %ld eliminado y memoria liberada con exito. Arbol balanceado.\n", fecha);
                } else {
                    printf("ERROR: No se encontro un lote con la fecha %ld.\n", fecha);
                }
                break;

            case 4:
                printf("\nCancelar Pedido\n");
                printf("Ingrese Fecha de Vencimiento (AAAAMMDD) del lote del pedido: ");
                scanf("%ld", &fecha);
                
                loteEncontrado = buscarLote(raiz, fecha);
                if (loteEncontrado == NULL) {
                    printf("ERROR: No se encontro un lote con la fecha %ld.\n", fecha);
                    break;
                }
                
                printf("Ingrese destino del pedido a cancelar: ");
                scanf("%s", destino);
                printf("Ingrese cantidad solicitada del pedido a cancelar: ");
                scanf("%d", &cantidad);

                if (cancelarPedido(loteEncontrado, destino, cantidad) == TRUE) {
                    printf("Pedido para %s de %d unidades en lote %ld CANCELADO.\n", destino, cantidad, fecha);
                } else {
                    printf("ERROR: Pedido no encontrado en el lote %ld o parametros incorrectos.\n", fecha);
                }
                break;

            case 5:
                printf("\nREPORTE DE ESTADO (Inventario In-Order)\n");
                printf("Ordenado desde la fecha mas proxima a vencer hasta la mas lejana.\n");
                if (raiz == NULL) {
                    printf("El inventario esta vacio.\n");
                } else {
                    reporteInOrder(raiz);
                }
                break;

            case 6:
                printf("\nSaliendo del sistema\n");
                liberarArbol(raiz); 
                break;

            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}