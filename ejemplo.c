#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"

#include <stdio.h>
#include <stdlib.h>

bool mostrar_elemento(void *elemento, void *contador)
{
	if (elemento && contador)
		printf("Elemento %i: %c \n", (*(int *)contador)++,
		       *(char *)elemento);
	return true;
}


int elemento_es_d(void *_elemento, void *ignorado)
{
	char *elemento = _elemento;

	if(elemento && *elemento == 'd')
		return 0;

	return -1;
}

int elemento_es_igual_a(void *_a, void *_b)
{
	char *a = _a;
	char *b = _b;

	if(a && b && *a == *b)
		return 0;

	return -1;
}

void probar_operaciones_lista()
{
	lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd', w = 'w';

	lista_insertar(lista, &a);
	lista_insertar(lista, &c);
	lista_insertar_en_posicion(lista, &d, 100);
	lista_insertar_en_posicion(lista, &b, 1);
	lista_insertar_en_posicion(lista, &w, 3);

	char *valor_quitado = lista_quitar_de_posicion(lista, 3);
	printf("Elementos quitado de la posicion 3 de la lista: %c\n",
	       *valor_quitado);

	printf("Elementos en la lista: ");
	for (size_t i = 0; i < lista_tamanio(lista); i++)
		printf("%c ", *(char *)lista_elemento_en_posicion(lista, i));

	printf("\n\n");

	printf("Imprimo TODOS LOS ELEMENTOS DE LA LISTA usando el iterador externo: \n");
	lista_iterador_t *it = NULL;

	for (it = lista_iterador_crear(lista);
	     lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		printf("%c ", *(char *)lista_iterador_elemento_actual(it));
	printf("\n\n");

	lista_iterador_destruir(it);

	int contador = 0;
	size_t elementos_recorridos = 0;
	printf("Imprimo TODOS LOS ELEMENTOS DE LA LISTA usando el iterador interno: \n");
	elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento,
						       (void *)&contador);

	printf("Recorri %lu elementos con el iterador interno y sume %i elementos\n",
	       elementos_recorridos, contador);

	printf("\n");


	printf("Busco el elemento con valor 'd' en la lista: ");
	char *elemento_d = lista_buscar_elemento(lista, elemento_es_d, NULL);
	if(elemento_d && *elemento_d == 'd')
		printf("ENCONTRADO\n");
	else
		printf("NO ENCONTRADO D:\n");

	printf("Busco el elemento con valor 'c' en la lista: ");
	char buscado = 'c';
	char *elemento_c = lista_buscar_elemento(lista, elemento_es_igual_a, &buscado);
	if(elemento_c && elemento_c == &c)
		printf("ENCONTRADO\n");
	else
		printf("NO ENCONTRADO D:\n");


	lista_destruir(lista);
}

void probar_operaciones_destructor_lista()
{
	lista_t *lista = lista_crear();

	//Inserto varios bloques reservados con malloc
	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));
	lista_insertar(lista, malloc(sizeof(int)));

	//Esto debería liberar la lista y cada bloque
	lista_destruir_todo(lista, free);
}

void probar_operaciones_cola()
{
	cola_t *cola = cola_crear();

	int numeros[] = { 1, 2, 3, 4, 5, 6 };

	for (size_t i = 0; i < sizeof(numeros) / sizeof(int); i++) {
		printf("Encolo %i\n", numeros[i]);
		cola_encolar(cola, &numeros[i]);
	}

	printf("\nDesencolo los numeros y los muestro: ");
	while (!cola_vacia(cola)) {
		printf("%i ", *(int *)cola_frente(cola));
		cola_desencolar(cola);
	}
	printf("\n");
	cola_destruir(cola);
}

void probar_operaciones_pila()
{
	pila_t *pila = pila_crear();
	char *algo = "somtirogla";

	for (int i = 0; algo[i] != 0; i++) {
		printf("Apilo %c\n", algo[i]);
		pila_apilar(pila, &algo[i]);
	}

	printf("\nDesapilo y muestro los elementos apilados: ");
	while (!pila_vacia(pila)) {
		printf("%c", *(char *)pila_tope(pila));
		pila_desapilar(pila);
	}
	printf("\n");
	pila_destruir(pila);
}

int main()
{
	printf("Ejemplo del uso de lista\n");
	probar_operaciones_lista();

	printf("\nEjemplo del destructor de lista (no debería perder memoria)\n");
	probar_operaciones_destructor_lista();


	printf("\nEjemplo del uso de cola\n");
	probar_operaciones_cola();

	printf("\nEjemplo del uso de pila\n");
	probar_operaciones_pila();

	return 0;
}
