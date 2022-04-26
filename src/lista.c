#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

nodo_t *nodo_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista)) return NULL;

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	if (iterador == NULL) return NULL;

	nodo_t *nodo;

	if (posicion == 0) {
		nodo = iterador->corriente;
		lista_iterador_destruir(iterador);
		return nodo;
	}

	for (int i = 0; i < posicion; i++) {
		lista_iterador_avanzar(iterador);
	}

	nodo = iterador->corriente;
	lista_iterador_destruir(iterador);

	return nodo;
}

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (!lista) return NULL;

	lista->cantidad = 0;
	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista) return NULL;

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo) return NULL;

	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->elemento = elemento;

	if (lista_vacia(lista)) { // lista vacia
		lista->nodo_inicio = nuevo_nodo;
	} else {
		lista->nodo_fin->siguiente = nuevo_nodo;
	}
	lista->nodo_fin = nuevo_nodo;

	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion)
{
	if(!lista) return NULL;

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo) return NULL;

	nuevo_nodo->elemento = elemento;

	// si insertar al principio
	if (posicion == 0) {
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		if (lista_vacia(lista)) lista->nodo_fin = nuevo_nodo;
	} else if (posicion >= lista_tamanio(lista)) { // si instertar al final
		nuevo_nodo->siguiente = NULL;
		lista->nodo_fin->siguiente = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
	} else {
		nodo_t *nodo_anterior = nodo_en_posicion(lista, posicion-1);

		nuevo_nodo->siguiente = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nuevo_nodo;
	}

	lista->cantidad++;
	// error:
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || lista_vacia(lista)) return NULL;

	nodo_t *aux = lista->nodo_fin;
	void *elemento = aux->elemento;

	if (lista_tamanio(lista) == 1) {
		lista->nodo_fin = NULL;
		lista->nodo_inicio = NULL;
	} else {
		nodo_t *penultimo_nodo = nodo_en_posicion(lista, lista_tamanio(lista)-2);
		lista->nodo_fin = penultimo_nodo;
		penultimo_nodo->siguiente = NULL;
	}
	free(aux);

	lista->cantidad--;
	
	return (elemento != NULL) ? elemento : NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista)) return NULL;

	nodo_t *aux;
	void *elemento;

	if (posicion == 0) {
		aux = lista->nodo_inicio;

		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		if (lista_tamanio(lista) == 1) lista->nodo_fin = NULL;
	} else if (posicion >= lista_tamanio(lista)) {
		return lista_quitar(lista);
	} else {
		nodo_t *nodo_anterior = nodo_en_posicion(lista, posicion-1);

		aux = nodo_anterior->siguiente;

		nodo_anterior->siguiente = aux->siguiente;
	}

	elemento = aux->elemento;
	free(aux);

	lista->cantidad--;

	return (elemento != NULL) ? elemento : NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista) || posicion >= lista_tamanio(lista)) return NULL;

	if (posicion == 0) return lista_primero(lista);
	if (posicion == lista_tamanio(lista)-1) return lista_ultimo(lista);

	nodo_t *nodo = nodo_en_posicion(lista, posicion);
	return nodo->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	if (!iterador) return NULL;

	for (int i = 0; i < lista_tamanio(lista); i++) {
		if (!comparador(lista_iterador_elemento_actual(iterador), contexto)) {
			lista_iterador_destruir(iterador);
			return lista_iterador_elemento_actual(iterador);
		}
		lista_iterador_avanzar(iterador);
	}
	lista_iterador_destruir(iterador);
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
	if (!lista || lista->cantidad == 0) return true;
	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if (!lista) return 0;
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	while (!lista_vacia(lista)) {
		lista_quitar(lista);
	}

	free(lista);
	return;
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	lista_iterador_t *iterador = lista_iterador_crear(lista);
	if (!iterador) return;

	for (int i = 0; i < lista_tamanio(lista); i++) {
		funcion(lista_iterador_elemento_actual(iterador));
		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
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
	return iterador->corriente->siguiente != NULL ? true : false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!lista_iterador_tiene_siguiente(iterador)) {
		iterador->corriente = NULL;
		return false;
	}
	iterador->corriente = iterador->corriente->siguiente;
	return true;
	// return iterador->corriente != NULL ? true : false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return !iterador->corriente ? NULL : iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	// free(iterador->corriente);
	// free(iterador->lista);
	free(iterador);
	return;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion) return 0;

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	if (!iterador) return 0;

	size_t i = 0;

	while (lista_iterador_elemento_actual(iterador) != NULL && funcion(lista_iterador_elemento_actual(iterador), contexto)) {
		lista_iterador_avanzar(iterador);
		i++;
	}

	lista_iterador_destruir(iterador);

	return i;
}
