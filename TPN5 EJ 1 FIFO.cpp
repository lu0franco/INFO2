#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo
typedef struct Nodo {
	int valor;
	struct Nodo* siguiente;
} Nodo;

// Punteros al principio y al final de la cola
Nodo* inicio = NULL;
Nodo* fin = NULL;

// Función para agregar un valor a la cola
void agregar(int valor) {
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	nuevo->valor = valor;
	nuevo->siguiente = NULL;
	
	if (inicio == NULL) {
		inicio = fin = nuevo;
	} else {
		fin->siguiente = nuevo;
		fin = nuevo;
	}
	printf("Valor %d agregado.\n", valor);
}

// Función para borrar el primer valor de la cola
void borrar() {
	if (inicio == NULL) {
		printf("La lista está vacía.\n");
		return;
	}
	
	int pos;
	printf ("Ingrese Posición a borrar");
	scanf("%d", &pos);
	
	Nodo* actual = inicio; //selecciono el inicio como nodo a analizar
	Nodo* anterior = NULL; //el anterior al inicio no existe por eso es NULL
	int index = 1;
	
	while (actual != NULL) {
		if (index==pos){
			if (anterior == NULL) {//Si es así selecciono el primer Nodo para borrar
				inicio = actual->siguiente;
				if (inicio == NULL) {
					fin = NULL; // la lista quedó vacía
				}
			}
			else{
				anterior->siguiente=actual->siguiente; //paso de largo el nodo actual
				if (actual== fin){ // Si voy a borrar el ultimo actualizo el final de la lista
					fin=anterior;
				}
				
			}		
			printf("Valor %d borrado.\n", actual->valor);
			free(actual); //RECIEN ACA BORRO EL NODO SELECCIONADO
			return;
		}
		anterior = actual; //ahora el nodo que comprobamos es el anterior en la lista
		actual = actual->siguiente; //ahora apunto el nodo actual como el que le sigue al anterior para el nuevo ciclo
		index++;
	}
	printf("Esa posición no existe en la lista.\n");
}
// Función para mostrar todos los valores de la lista
void mostrar() {
	if (inicio == NULL) {
		printf("La lista está vacía.\n");
		return;
	}
	Nodo* actual = inicio; // apunto al inicio
	int pos = 1;
	printf("Contenido de la lista:\n");
	while (actual != NULL) { //recorro toda la lista hasta el NULL que marca el fin
		printf("Posición %d: %d\n", pos, actual->valor);//hago un print del nodo
		actual = actual->siguiente;//cambio al nodo que le sigue al actual
		pos++;
	}
}

// Función para contar los elementos de la lista
int contar() {
	int count = 0;
	Nodo* actual = inicio;// apunto al inicio
	while (actual != NULL) {//recorro toda la lista hasta el NULL que marca el fin
		count++; //sumo contador
		actual = actual->siguiente;//cambio al nodo que le sigue al actual
	}
	return count;
}

// Buscar valor exacto
void buscarExacto(int buscado) {
	Nodo* actual = inicio;// apunto al inicio
	int pos = 1;
	int encontrado = 0;
	while (actual != NULL) {//recorro toda la lista hasta el NULL que marca el fin
		if (actual->valor == buscado) { //si el valor del nodo actual es igual al buscado hago print
			printf("Valor %d encontrado en la posición %d.\n", buscado, pos);
			encontrado = 1;
		}
		actual = actual->siguiente;//cambio al nodo que le sigue al actual
		pos++;//cambio posicion
	}
	if (!encontrado) //no se encontro buscado
		printf("Valor %d no se encontró en la lista.\n", buscado);
}

// Mostrar elementos mayores a un valor
void buscarMayores(int limite) {
	Nodo* actual = inicio;
	int pos = 1;
	int hayMayores = 0;
	while (actual != NULL) {
		if (actual->valor > limite) {
			printf("Valor %d en posición %d es mayor que %d.\n", actual->valor, pos, limite);
			hayMayores = 1;
		}
		actual = actual->siguiente;
		pos++;
	}
	if (!hayMayores)
		printf("No hay elementos mayores que %d.\n", limite);
}

// Mostrar elementos menores a un valor
void buscarMenores(int limite) {
	Nodo* actual = inicio;
	int pos = 1;
	int hayMenores = 0;
	while (actual != NULL) {
		if (actual->valor < limite) {
			printf("Valor %d en posición %d es menor que %d.\n", actual->valor, pos, limite);
			hayMenores = 1;
		}
		actual = actual->siguiente;
		pos++;
	}
	if (!hayMenores)
		printf("No hay elementos menores que %d.\n", limite);
}

// Menú principal
void menu() {
	int opcion, valor;
	
	do {
		printf("\n---- MENU ----\n");
		printf("1. Agregar valor\n");
		printf("2. Borrar valor\n");
		printf("3. Mostrar lista\n");
		printf("4. Contar elementos\n");
		printf("5. Buscar valor exacto\n");
		printf("6. Mostrar mayores a un valor\n");
		printf("7. Mostrar menores a un valor\n");
		printf("0. Salir\n");
		printf("Seleccione una opción: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
		case 1:
			printf("Ingrese un valor a agregar: ");
			scanf("%d", &valor);
			agregar(valor);
			break;
		case 2:
			borrar();
			break;
		case 3:
			mostrar();
			break;
		case 4:
			printf("La lista tiene %d elementos.\n", contar());
			break;
		case 5:
			printf("Ingrese el valor a buscar: ");
			scanf("%d", &valor);
			buscarExacto(valor);
			break;
		case 6:
			printf("Ingrese el valor límite: ");
			scanf("%d", &valor);
			buscarMayores(valor);
			break;
		case 7:
			printf("Ingrese el valor límite: ");
			scanf("%d", &valor);
			buscarMenores(valor);
			break;
		case 0:
			printf("Saliendo...\n");
			break;
		default:
			printf("Opción inválida.\n");
		}
		
	} while (opcion != 0);
}

// Función principal
int main() {
	menu();
	return 0;
}
