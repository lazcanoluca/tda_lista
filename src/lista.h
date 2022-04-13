#ifndef __LISTA_H__
#define __LISTA_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * Las siguientes estructuras deberían ser privadas y no está permitido el
 * acceso directo a los campos por fuera de la implementación.
 *
 * El motivo por el cual las estructuras son públicas es para asegurarnos de que
 * la implementación realizada es la pedida
 */
typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

typedef struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
	size_t cantidad;
} lista_t;

typedef struct lista_iterador {
	nodo_t *corriente;
	lista_t *lista;
} lista_iterador_t;

/**
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t *lista_crear();

/**
 * Inserta un elemento al final de la lista.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */
lista_t *lista_insertar(lista_t *lista, void *elemento);

/**
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */
lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion);

/**
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 *
 * Devuelve el elemento removido de la lista o NULL en caso de error.
 */
void *lista_quitar(lista_t *lista);

/**
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento de la lista.
 *
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.
 *
 * Devuelve el elemento removido de la lista o NULL en caso de error.
 *
 */
void *lista_quitar_de_posicion(lista_t *lista, size_t posicion);

/**
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void *lista_elemento_en_posicion(lista_t *lista, size_t posicion);

/**
 * Devuelve el primer elemento de la lista que cumple la condición
 * comparador(elemento, contexto) == 0.
 *
 * Si no existe el elemento devuelve NULL.
 */
void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto);

/**
 * Devuelve el primer elemento de la lista o NULL si la lista se
 * encuentra vacía o no existe.
 */
void *lista_primero(lista_t *lista);

/**
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía o no existe.
 */
void *lista_ultimo(lista_t *lista);

/**
 * Devuelve true si la lista está vacía (o no existe) o false en caso contrario.
 */
bool lista_vacia(lista_t *lista);

/**
 * Devuelve la cantidad de elementos almacenados en la lista.
 * Una lista que no existe no puede tener elementos.
 */
size_t lista_tamanio(lista_t *lista);

/**
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t *lista);

/**
 * Libera la memoria reservada por la lista pero además aplica la función
 * destructora dada (si no es NULL) a cada uno de los elementos presentes en la
 * lista.
 */
void lista_destruir_todo(lista_t *lista, void (*funcion)(void *));

/**
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista). 
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t *lista_iterador_crear(lista_t *lista);

/**
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador);

/**
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t *iterador);

/**
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void *lista_iterador_elemento_actual(lista_iterador_t *iterador);

/**
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t *iterador);

/**
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma como primer parámetro. Dicha función puede devolver true si se deben
 * seguir recorriendo elementos o false si se debe dejar de iterar elementos.
 *
 * El puntero contexto se pasa como segundo argumento a la función del usuario.
 *
 * La función devuelve la cantidad de elementos iterados o 0 en caso de error
 * (errores de memoria, función o lista NULL, etc).
 *
 */
size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto);

#endif /* __LISTA_H__ */
