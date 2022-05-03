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
	if (!nuevo_nodo) {
		free(lista);
		return NULL;
	}

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

	if (posicion >= lista_tamanio(lista) || lista_vacia(lista)) {
		return lista_insertar(lista, elemento);
	}

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo) return NULL;

	nuevo_nodo->elemento = elemento;

	// si insertar al principio
	if (posicion == 0) {
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		// if (lista_vacia(lista)) lista->nodo_fin = nuevo_nodo;
	} else {
		nodo_t *nodo_anterior = nodo_en_posicion(lista, posicion-1);
		nuevo_nodo->siguiente = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nuevo_nodo;
	}

	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || lista_vacia(lista)) return NULL;

	nodo_t *nodo_a_quitar = lista->nodo_fin;
	void *elemento = nodo_a_quitar->elemento;

	if (lista_tamanio(lista) == 1) {
		lista->nodo_fin = NULL;
		lista->nodo_inicio = NULL;
	} else {
		nodo_t *penultimo_nodo = nodo_en_posicion(lista, lista_tamanio(lista)-2);
		lista->nodo_fin = penultimo_nodo;
		penultimo_nodo->siguiente = NULL;
	}
	
	free(nodo_a_quitar);
	lista->cantidad--;

	return elemento;

}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista)) return NULL;

	if (posicion >= lista_tamanio(lista)-1) {
		return lista_quitar(lista);
	}

	nodo_t *nodo_a_quitar;
	void *elemento;

	if (posicion == 0) {
		nodo_a_quitar = lista->nodo_inicio; /* ????? */
		nodo_t *nuevo_inicio = lista->nodo_inicio->siguiente;
		lista->nodo_inicio = nuevo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		if (lista_tamanio(lista) == 1) lista->nodo_fin = NULL;
	} else {
		nodo_t *nodo_anterior = nodo_en_posicion(lista, posicion-1);
		nodo_a_quitar = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo_a_quitar->siguiente;
	}

	elemento = nodo_a_quitar->elemento;
	free(nodo_a_quitar);
	lista->cantidad--;

	return elemento;
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
	if (!lista || !comparador || lista_vacia(lista)) return NULL;

	for (size_t i = 0; i < lista_tamanio(lista); i++) {
		if (comparador(lista_elemento_en_posicion(lista, i), contexto) == 0) {
			return lista_elemento_en_posicion(lista, i);
		}
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return (!lista || lista_vacia(lista)) ? NULL : lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	return (!lista || lista_vacia(lista)) ? NULL : lista->nodo_fin->elemento;
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
	if (!lista) return;

	while (!lista_vacia(lista)) {
		lista_quitar(lista);
	}

	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(!lista) return;

	if(funcion) {
		nodo_t *aux = lista->nodo_inicio;
		int i = 0;

		while(i < lista_tamanio(lista)){
			funcion(aux->elemento);
			aux = aux->siguiente;
			i++;
		}
	}

	lista_destruir(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista) return NULL;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador) return NULL;

	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador || lista_vacia(iterador->lista) || !iterador->corriente) return false;

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador || !lista_iterador_tiene_siguiente(iterador)) return false;

	iterador->corriente = iterador->corriente->siguiente;
	if (!iterador->corriente) return false;

	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente || lista_vacia(iterador->lista)) return NULL;
	
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador) return;

	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion || lista_vacia(lista)) return 0;

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	if (!iterador) return 0;

	size_t i = 1;

	while (lista_iterador_elemento_actual(iterador) != NULL && funcion(lista_iterador_elemento_actual(iterador), contexto)) {
		lista_iterador_avanzar(iterador);
		i++;
	}

	if (!lista_iterador_elemento_actual(iterador)) i--;

	lista_iterador_destruir(iterador);

	return i;
}
