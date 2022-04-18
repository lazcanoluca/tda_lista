#include "pila.h"
#include "lista.h"

struct _pila_t {
	lista_t *lista;
};

pila_t *pila_crear()
{
	pila_t *pila = malloc(sizeof(pila_t));
	if (pila == NULL) return NULL;
	pila->lista->cantidad = 0;
	pila->lista->nodo_fin = NULL;
	return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) return NULL;

	nuevo_nodo->siguiente = pila->lista->nodo_fin;
	pila->lista->nodo_fin = nuevo_nodo;
	nuevo_nodo->elemento = elemento;

	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	nodo_t *aux = malloc(sizeof(nodo_t));
	if (aux == NULL) return NULL;

	aux = pila->lista->nodo_fin;
	pila->lista->nodo_fin = pila->lista->nodo_fin->siguiente;


	return aux;
}

void *pila_tope(pila_t *pila)
{
	return NULL;
}

size_t pila_tamanio(pila_t *pila)
{
	return 0;
}

bool pila_vacia(pila_t *pila)
{
	return false;
}

void pila_destruir(pila_t *pila)
{

}
