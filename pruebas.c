#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

#include <string.h>

int main() {
  // pa2m_nuevo_grupo("Pruebas y mas pruebas");
  lista_t *lista_pruebas;
  char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';

  pa2m_nuevo_grupo("Pruebas creación lista.");
  pa2m_afirmar((lista_pruebas = lista_crear()) != NULL, "Se pudo crear una lista.");
  pa2m_afirmar(lista_pruebas->cantidad == 0, "La cantidad inicial es 0.");

  pa2m_nuevo_grupo("Pruebas iterador.");

  pa2m_nuevo_grupo("Pruebas inserción en lista.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &a) != NULL, "Se pudo insertar un elemento en una lista vacía.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &b) != NULL, "Se pudo insertar un elemento en una lista poblada.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &c) != NULL, "Se pudo insertar un elemento en una lista poblada.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &d) != NULL, "Se pudo insertar un elemento en una lista poblada.");
  pa2m_afirmar(lista_insertar_en_posicion(lista_pruebas, &e, 3) != NULL, "Se pudo insertar un elemento al medio de una lista poblada.");
  pa2m_afirmar(lista_pruebas->cantidad == 5, "La cantidad de elementos es la esperada.");

  pa2m_nuevo_grupo("Pruebas obtención elementos.");
  pa2m_afirmar(lista_elemento_en_posicion(lista_pruebas, lista_pruebas->cantidad + 1) == NULL, "No es posible acceder a un elemento fuera de la lista.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 0) == 'a', "El primer elemento corresponde a 'a'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 1) == 'b', "El segundo elemento corresponde a 'b'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 2) == 'c', "El tercer elemento corresponde a 'c'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 3) == 'e', "El cuarto elemento corresponde a 'e'.");
  pa2m_afirmar(*(char *)lista_elemento_en_posicion(lista_pruebas, 4) == 'd', "El quinto elemento corresponde a 'd'.");

  free(lista_pruebas);
  
  return pa2m_mostrar_reporte();
}
