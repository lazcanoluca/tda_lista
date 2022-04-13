#ifndef PILA_H_
#define PILA_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct _pila_t pila_t;

/**
 * Crea una pila vacía y la devuelve.
 *
 * En caso de error devuelve NULL
 */
pila_t *pila_crear();

/**
 * Apila un elemento en la pila.
 *
 * Devuelve la pila o NULL en caso de error.
 */
pila_t *pila_apilar(pila_t *pila, void *elemento);

/**
 * Desapila un elemento de la pila y lo devuelve.
 *
 * Devuelve NULL en caso de error.
 */
void *pila_desapilar(pila_t *pila);

/**
 * Devuelve el elemento en el tope de la pila o NULL en caso de que no exista.
 */
void *pila_tope(pila_t *pila);

/**
 * Devuelve la cantidad de elementos de la pila o 0 si no existe.
 */
size_t pila_tamanio(pila_t *pila);

/**
 * Devuelve true si la pila tiene 0 elementos.
 */
bool pila_vacia(pila_t *pila);

/**
 * Libera la memoria reservada por la pila.
 */
void pila_destruir(pila_t *pila);

#endif // PILA_H_
