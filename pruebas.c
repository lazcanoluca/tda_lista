#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

#include <string.h>

void creo_una_lista_y_devuelve_una_lista_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Se pudo crear una lista válida.");
	pa2m_afirmar(lista->cantidad == 0, "La lista contiene 0 elementos.");
	pa2m_afirmar(lista_vacia(lista), "La lista está vacía.");
	pa2m_afirmar(lista->nodo_inicio == NULL, "El head de la lista apunta a NULL.");
	pa2m_afirmar(lista->nodo_fin == NULL, "La tail de la lista apunta a NULL.");
	pa2m_afirmar(lista_primero(lista) == NULL, "Pedir el primer elemento de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "Pedir el último elemento de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 7) == NULL, "Pedir un elemento en una posición arbitraria de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Pedir un elemento la posición 0 de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_quitar(lista) == NULL, "Quitar de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 7) == NULL, "Quitar de una posición arbitraria de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == NULL, "Quitar del inicio de la lista vacía devuelve NULL.");
	lista_destruir(lista);

}

void inserto_elementos_en_una_lista()

{
	lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

	pa2m_afirmar(lista_insertar(lista, &a) != NULL, "Insertar un elemento en una lista vacía devuelve la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 1, "La lista tiene 1 elemento.");
	pa2m_afirmar(lista_insertar(lista, &b) != NULL, "Insertar un elemento en una lista poblada devuelve la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "La lista tiene 2 elementos.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &c, 100) != NULL, "Insertar un elemento en la posición 100 devuelve la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 3, "La lista tiene 3 elementos.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &d, 0) != NULL, "Insertar un elemento al principio devuelve la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 4, "La lista tiene 4 elementos.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &e, 2) != NULL, "Insertar un elemento al medio devuelve la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 5, "La lista tiene 5 elementos.");
	pa2m_afirmar(lista_insertar(NULL, &a) == NULL, "Insertar un elemento válido en una lista inválida devuelve NULL.");
	// pa2m_afirmar(lista_insertar(lista, NULL) == NULL, "Insertar un elemento inválido en una lista válida devuelve NULL.");
	pa2m_afirmar(lista_tamanio(lista) == 5, "La lista sigue existiendo y sigue teniendo 5 elementos.");
	pa2m_afirmar(*(char *)lista_primero(lista), "El primer elemento es 'd'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 0), "El elemento en posición 0 es 'd'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 1), "El elemento en posición 1 es 'a'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 2), "El elemento en posición 2 es 'e'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 3), "El elemento en posición 3 es 'b'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 4), "El elemento en posición 4 es 'c'.");
	pa2m_afirmar(*(char *)lista_ultimo(lista), "El último elemento es 'c'.");

	lista_destruir(lista);
}

void quito_elementos_de_una_lista()
{
	lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

	pa2m_afirmar(lista_quitar(lista) == NULL, "Quitar de una lista vacía devuelve NULL.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 7) == NULL, "Quitar de una posición arbitraria de una lista vacía devuelve NULL.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == NULL, "Quitar de posición 0 de una lista vacía devuelve NULL.");

	lista_insertar(lista, &a);

	pa2m_afirmar(*(char *)lista_quitar(lista) == 'a', "Quitar un elemento de una lista con un elemento devuelve el elemento.");
	pa2m_afirmar(lista_vacia(lista), "La lista quedó vacía.");
	pa2m_afirmar(lista_tamanio(lista) == 0, "El tamaño de la lista es 0.");
	pa2m_afirmar(lista_primero(lista) == NULL, "Pedir el primer elemento de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "Pedir el último elemento de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 7) == NULL, "Pedir un elemento en una posición arbitraria de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "Pedir un elemento la posición 0 de la lista vacía devuelve NULL.");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);

	pa2m_afirmar(!lista_vacia(lista), "Se puede volver a llenar una lista después de haberla vaciado.");
	pa2m_afirmar(lista_tamanio(lista) == 5, "La lista rellenada tiene 5 elementos.");
	pa2m_afirmar(*(char *)lista_primero(lista) == 'a', "El primer elemento es 'a'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 0) == 'a', "El elemento en posición 0 es 'a'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 1) == 'b', "El elemento en posición 1 es 'b'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 2) == 'c', "El elemento en posición 2 es 'c'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 3) == 'd', "El elemento en posición 3 es 'd'.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 4) == 'e', "El elemento en posición 4 es 'e'.");
	pa2m_afirmar(*(char *)lista_ultimo(lista), "El último elemento es 'e'.");

	pa2m_afirmar(*(char *)lista_quitar(lista) == 'e', "Quitar el último elemento de la lista poblada devuelve 'e'.");
	pa2m_afirmar(*(char *)lista_ultimo(lista) == 'd', "El último elemento es 'd'.");
	pa2m_afirmar(lista_tamanio(lista) == 4, "El tamaño de la lista es 4.");
	pa2m_afirmar(*(char *)lista_quitar_de_posicion(lista, 2) == 'c', "Se pudo quitar el elemento en la posición 2.");
	pa2m_afirmar(lista_tamanio(lista) == 3, "El tamaño de la lista es 3.");
	pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista, 2) != 'c', "El elemento en la posición 2 ya no es 'c'.");
	pa2m_afirmar(*(char *)lista_quitar_de_posicion(lista, 0) == 'a', "Se pudo quitar el elemento en la posición 0.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño de la lista es 2.");
	pa2m_afirmar(*(char *)lista_primero(lista) == 'b', "El primer elemento es 'b'.");
	pa2m_afirmar(*(char *)lista_quitar_de_posicion(lista, 100) == 'd', "Quitar el elemento de la posición 100 devuelve 'd'.");
	pa2m_afirmar(lista_tamanio(lista) == 1, "El tamaño de la lista es 1.");
	pa2m_afirmar(lista_primero(lista) == lista_ultimo(lista), "El elemento restante es el primero y el último.");
	pa2m_afirmar(*(char *)lista_primero(lista) == 'b', "El elemento restante es 'b'.");
	pa2m_afirmar(*(char *)lista_quitar_de_posicion(lista, 0) == 'b', "Quitar el elemento de la posición 0 devuelve 'b'.");
	pa2m_afirmar(lista_vacia(lista), "La lista quedó vacía.");
	pa2m_afirmar(lista_primero(lista) == NULL, "Pedir el primer elemento de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "Pedir el último elemento de la lista vacía devuelve NULL.");
	pa2m_afirmar(lista_quitar(lista) == NULL, "Quitar un elemento de una lista vacía devuelve NULL.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 7) == NULL, "Quitar un elemento de una posición arbitraria de una lista vacía devuelve NULL");

	lista_destruir(lista);
}

void pruebas_muchos_elementos()
{
	lista_t *lista = lista_crear();

	for (int i = 0; i < 10000; i++) {
		lista_insertar(lista, &i);
	}

	pa2m_afirmar(lista_tamanio(lista) == 10000, "Se puede crear una lista con 10k elementos.");

	for (int i = 0; i < 5000; i++) {
		lista_quitar_de_posicion(lista, 3000);
	}

	pa2m_afirmar(lista_tamanio(lista) == 5000, "Se pueden sacar 5k elementos del medio de la lista.");

	for (int i = 0; i < 3000; i++) {
		lista_quitar(lista);
	}

	pa2m_afirmar(lista_tamanio(lista) == 2000, "Se pueden sacar 3k elementos del final de la lista.");

	for (int i = 0; i < 2000; i++) {
		lista_quitar_de_posicion(lista, 0);
	}

	pa2m_afirmar(lista_tamanio(lista) == 0, "Se pueden sacar 2k elementos del principio de la lista.");

	pa2m_afirmar(lista_vacia(lista), "La lista quedó vacía.");

	lista_destruir(lista);

}

void pruebas_de_iterador_externo()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador_vacio = lista_iterador_crear(lista);
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

	pa2m_afirmar(lista_iterador_crear(NULL) == NULL, "No se puede crear un iterador con una lista inexistente.");
	pa2m_afirmar(iterador_vacio != NULL, "Se pudo crear un iterador con una lista vacía.");
	pa2m_afirmar(lista_vacia(iterador_vacio->lista) == true, "La lista está vacía.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_vacio) == false, "El iterador de la lista vacía no tiene siguiente.");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador_vacio) == NULL, "El elemento actual de un iterador con lista vacía es NULL.");
	pa2m_afirmar(lista_iterador_avanzar(iterador_vacio) == false, "El iterador con lista vacía no puede avanzar.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_vacio) == false, "El iterador de la lista vacía sigue sin tener siguiente.");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador_vacio) == NULL, "El elemento actual de un iterador con lista vacía sigue siendo NULL.");

	lista_iterador_destruir(iterador_vacio);

	// pa2m_afirmar(iterador_vacio == NULL, "El iterador ya no existe.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false, "Un iterador inexistente no tiene siguiente.");
	pa2m_afirmar(lista_iterador_elemento_actual(NULL) == NULL, "El elemento actual de un iterador inexistente es NULL");
	pa2m_afirmar(lista_iterador_avanzar(NULL) == false, "No se puede avanzar un iterador inexistente.");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);

	lista_iterador_t *iterador_lleno = lista_iterador_crear(lista);
	pa2m_afirmar(iterador_lleno != NULL, "Se pudo crear un iterador con una lista poblada.");
	pa2m_afirmar(lista_tamanio(iterador_lleno->lista) == 5, "La lista del iterador tiene 5 elementos.");
	pa2m_afirmar(*(char *)lista_iterador_elemento_actual(iterador_lleno) == 'a', "El iterador apunta al primer elemento, 0.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_lleno), "El iterador tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador_lleno), "El iterador pudo avanzar.");
	pa2m_afirmar(*(char *)lista_iterador_elemento_actual(iterador_lleno) == 'b', "El iterador apunta al elemento 1.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_lleno), "El iterador tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador_lleno), "El iterador pudo avanzar.");
	pa2m_afirmar(*(char *)lista_iterador_elemento_actual(iterador_lleno) == 'c', "El iterador apunta al elemento 2.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_lleno), "El iterador tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador_lleno), "El iterador pudo avanzar.");
	pa2m_afirmar(*(char *)lista_iterador_elemento_actual(iterador_lleno) == 'd', "El iterador apunta al elemento 3.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_lleno), "El iterador tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador_lleno), "El iterador pudo avanzar.");
	pa2m_afirmar(*(char *)lista_iterador_elemento_actual(iterador_lleno) == 'e', "El iterador apunta al último elemento, 4.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_lleno) == true, "El iterador tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador_lleno) == false, "El iterador ya no puede avanzar.");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador_lleno) == NULL, "El iterador ahora apunta a NULL.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_lleno) == false, "El iterador no tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador_lleno) == false, "El iterador no pudo avanzar.");
}

void pruebas_de_iterador_interno()
{
	lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &d), "No se puede iterar sin una función");

	lista_destruir(lista);
}

void pruebas_de_busqueda()
{
	// pa2m_afirmar(lista_buscar_elemento(NULL, NULL, NULL), "Buscar un elemento ")
}


int main() {
  // pa2m_nuevo_grupo("Pruebas y mas pruebas");
  lista_t *lista_pruebas;
  char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

  pa2m_nuevo_grupo("Pruebas creación lista.");
  pa2m_afirmar((lista_pruebas = lista_crear()) != NULL, "Se pudo crear una lista.");
  pa2m_afirmar(lista_pruebas->cantidad == 0, "La cantidad inicial es 0.");

  pa2m_nuevo_grupo("Pruebas inserción en lista.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &a) != NULL, "Se pudo insertar un elemento en una lista vacía.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &b) != NULL, "Se pudo insertar un elemento en una lista poblada.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &c) != NULL, "Se pudo insertar un elemento en una lista poblada.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &d) != NULL, "Se pudo insertar un elemento en una lista poblada.");
  pa2m_afirmar(lista_insertar_en_posicion(lista_pruebas, &e, 3) != NULL, "Se pudo insertar un elemento al medio de una lista poblada.");
  pa2m_afirmar(lista_pruebas->cantidad == 5, "La cantidad de elementos es la esperada.");

  pa2m_nuevo_grupo("Pruebas iterador.");
  lista_iterador_t *iterador_pruebas = lista_iterador_crear(lista_pruebas);
  pa2m_afirmar(iterador_pruebas != NULL, "Se crea el iterador.");
  pa2m_afirmar(*(char *)lista_iterador_elemento_actual(iterador_pruebas) == 'a', "El iterador creado apunta al primer elemento.");
  lista_iterador_destruir(iterador_pruebas);

  pa2m_nuevo_grupo("Pruebas obtención elementos.");
  pa2m_afirmar(lista_elemento_en_posicion(lista_pruebas, lista_pruebas->cantidad + 1) == NULL, "No es posible acceder a un elemento fuera de la lista.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 0) == 'a', "El primer elemento corresponde a 'a'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 1) == 'b', "El segundo elemento corresponde a 'b'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 2) == 'c', "El tercer elemento corresponde a 'c'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 3) == 'e', "El cuarto elemento corresponde a 'e'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 4) == 'd', "El quinto elemento corresponde a 'd'.");

  pa2m_nuevo_grupo("Pruebas quitar.");
  pa2m_afirmar(*(char *)lista_quitar(lista_pruebas) == 'd', "El elemento quitado es 'd'.");
  pa2m_afirmar(*(char *)lista_ultimo(lista_pruebas) == 'e', "El ultimo elemento es 'e'.");
  pa2m_afirmar(lista_pruebas->cantidad == 4, "La cantidad de elementos es la esperada.");
  pa2m_afirmar(*(char *)lista_quitar_de_posicion(lista_pruebas, 2) == 'c', "El elemento quitado es 'c'.");
  pa2m_afirmar(lista_pruebas->cantidad == 3, "La cantidad de elementos es la esperada.");
  pa2m_afirmar(*(char *)lista_quitar_de_posicion(lista_pruebas, 0) == 'a', "El elemento quitado es 'a'.");
  pa2m_afirmar(lista_pruebas->cantidad == 2, "La cantidad de elementos es la esperada.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 1) == 'e', "El segundo elemento corresponde a 'e'.");
  pa2m_afirmar(*(char *)lista_quitar(lista_pruebas) == 'e', "El elemento quitado es 'e'.");
  pa2m_afirmar(lista_pruebas->cantidad == 1, "La cantidad de elementos es la esperada.");
  pa2m_afirmar(*(char *)lista_quitar(lista_pruebas) == 'b', "El elemento quitado es 'b'.");
  pa2m_afirmar(lista_pruebas->cantidad == 0, "La cantidad de elementos es la esperada.");
  pa2m_afirmar(lista_vacia(lista_pruebas), "La lista quedó vacía.");

  lista_destruir(lista_pruebas);

  creo_una_lista_y_devuelve_una_lista_vacia();
  inserto_elementos_en_una_lista();
  quito_elementos_de_una_lista();
  pruebas_muchos_elementos();
  pruebas_de_iterador_externo();
  
  return pa2m_mostrar_reporte();
}
