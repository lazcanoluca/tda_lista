#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL) return NULL;

	lista->cantidad = 0;
	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) return NULL;

	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->elemento = elemento;

	if (lista->cantidad == 0) { // lista vacia
		lista->nodo_inicio = nuevo_nodo;
	} else {
		lista->nodo_fin->siguiente = nuevo_nodo;
	}
	lista->nodo_fin = nuevo_nodo;

	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) return NULL;

	nuevo_nodo->elemento = elemento;

	// si insertar al principio
	if (posicion == 0) {
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		if (lista->cantidad == 0) lista->nodo_fin = nuevo_nodo;
	} else if (posicion >= lista->cantidad) { // si instertar al final
		nuevo_nodo->siguiente = NULL;
		lista->nodo_fin->siguiente = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
	} else {
		lista_iterador_t *iterador = lista_iterador_crear(lista);
		if (iterador == NULL) return NULL;
	
		for (int i = 0; i < posicion-1; i++) {
			lista_iterador_avanzar(iterador);
			// printf("%i\n", i);
		}

		nuevo_nodo->siguiente = iterador->corriente->siguiente;
		iterador->corriente->siguiente = nuevo_nodo;

		free(iterador);
	}

	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista) {
		printf("Can't retrieve element from empty list.\n");
		return NULL;
	}

	if (posicion > lista->cantidad) {
		//printf("Can't retrieve element from position higher than list amount.\n");
		return NULL;
	}

	if (posicion == 0) return lista_primero(lista);
	if (posicion == lista->cantidad) return lista_ultimo(lista);

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	if (iterador == NULL) return NULL;

	for (int i = 0; i < posicion; i++) {
		lista_iterador_avanzar(iterador);
		// printf("Posicion del iterador: %i\n", i);
		// printf("Contenido %c\n", *(char*)lista_iterador_elemento_actual(iterador));
	}

	return lista_iterador_elemento_actual(iterador);
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	// return (!lista) ? NULL : lista->nodo_inicio->elemento;
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	return 0;
}

void lista_destruir(lista_t *lista)
{

}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{

}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (iterador == NULL) return NULL;
	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return iterador->corriente->siguiente == NULL ? false : true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (lista_iterador_tiene_siguiente(iterador)) iterador->corriente = iterador->corriente->siguiente;
	return !iterador->corriente ? false : true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
