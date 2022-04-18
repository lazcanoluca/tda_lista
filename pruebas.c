#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

int main() {
  // pa2m_nuevo_grupo("Pruebas y mas pruebas");

  pa2m_nuevo_grupo("Pruebas creación lista.");
  pa2m_afirmar(lista_crear() != NULL, "Se pudo crear una lista.");

  pa2m_nuevo_grupo("Pruebas inserción en lista.");
  lista_t *lista_pruebas = lista_crear();
  char a = 'a', b = 'b';
  pa2m_afirmar(lista_insertar(lista_pruebas, &a) != NULL, "Se pudo insertar un elemento en una lista vacía.");
  pa2m_afirmar(lista_insertar(lista_pruebas, &b) != NULL, "Se pudo insertar un elemento en una lista poblada.");
  pa2m_afirmar(lista_pruebas->cantidad == 2, "La cantidad de elementos es la esperada.");
  
  return pa2m_mostrar_reporte();
}
