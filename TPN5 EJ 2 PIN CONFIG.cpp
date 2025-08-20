#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Definición de la estructura del nodo
typedef struct Nodo {
	char TAG[20];
	int NumeroPIN;
	char ESTADO[6];
	struct Nodo* siguiente;
} Nodo;

// Punteros al principio y al final de la cola
Nodo* inicio = NULL;
Nodo* fin = NULL;


// Función para agregar un valor a la cola
void agregar(char TAGadd[20], int NumeroPINadd, char ESTADOadd[6]) {
	//printf("DEBUG - Recibiendo: TAG='%s', PIN=%d, ESTADO='%s'\n", TAGadd, NumeroPINadd, ESTADOadd);
	
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	if (nuevo == NULL) {
		printf("Error: No se pudo asignar memoria.\n");
		return;
	}
	
	strcpy(nuevo->TAG, TAGadd);
	nuevo->NumeroPIN = NumeroPINadd;
	strcpy(nuevo->ESTADO, ESTADOadd);
	nuevo->siguiente = NULL;
	
	//printf("DEBUG - Guardado en nodo: TAG='%s', PIN=%d, ESTADO='%s'\n", nuevo->TAG, nuevo->NumeroPIN, nuevo->ESTADO);
	
	if (inicio == NULL) {
		inicio = fin = nuevo;
	} else {
		fin->siguiente = nuevo;
		fin = nuevo;
	}
	printf("Datos de PIN agregados.\n");
}

// Función para borrar el primer valor de la cola
void borrar() {
	if (inicio == NULL) {
		printf("La lista está vacía.\n");
		return;
	}
	
	int pos;
	printf ("Ingrese Posición a borrar: ");
	scanf("%d", &pos);
	fflush(stdin);
	
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
			printf("PIN borrado.\n");
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
	printf("\n|INDICE|      ETIQUETA      |NUMERO PIN|  MODO |\n");
	printf("------------------------------------------------\n");
	while (actual != NULL) { //recorro toda la lista hasta el NULL que marca el fin
		printf("|    %-2d|%-20s|        %-2d| %-6s|\n" ,pos, actual->TAG, actual->NumeroPIN, actual->ESTADO);//hago un print del nodo
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

// Buscar datos
void buscarDatos() {
	Nodo* actual = inicio;// apunto al inicio
	int pos = 1;
	int encontrado = 0;
	int opcionsubmenu;
	char TAGsearch[20];
	int NumeroPINsearch;
	
	printf("\n---- SUBMENU DE BUSQUEDA ----\n");
	printf("1. Buscar por TAG\n");
	printf("2. Buscar por Numero de PIN\n");
	printf("3. Buscar por INPUT\n");
	printf("4. Buscar por OUTPUT\n");
	printf("Seleccione una opción: ");
	scanf("%d", &opcionsubmenu);
	fflush(stdin);
	
	switch (opcionsubmenu) {
	case 1:
		printf("Ingrese un TAG a buscar: ");
		scanf("%19s", TAGsearch);
		fflush(stdin);
		while (actual != NULL) {//recorro toda la lista hasta el NULL que marca el fin
			if (strcmp(actual->TAG, TAGsearch) == 0) { //si el valor del nodo actual es igual al buscado hago print
				printf("TAG %s encontrado en la posición %d.\n", TAGsearch, pos);
				encontrado = 1;
			}
			actual = actual->siguiente;//cambio al nodo que le sigue al actual
			pos++;//cambio posicion
		}
		if (!encontrado) {//no se encontro buscado
			printf("TAG %s no se encontró en la lista.\n", TAGsearch);
		}
		break;
	case 2:
		printf("Ingrese un Numero de PIN a buscar: ");
		scanf("%d", &NumeroPINsearch);
		fflush(stdin);
		while (actual != NULL) {//recorro toda la lista hasta el NULL que marca el fin
			if (actual->NumeroPIN == NumeroPINsearch) { //si el valor del nodo actual es igual al buscado hago print
				printf("Numero de PIN %d encontrado en la posición %d.\n", NumeroPINsearch, pos);
				encontrado = 1;
			}
			actual = actual->siguiente;//cambio al nodo que le sigue al actual
			pos++;//cambio posicion
		}
		if (!encontrado) {//no se encontro buscado
			printf("Numero de PIN %d no se encontró en la lista.\n", NumeroPINsearch);
		}
		break;
	case 3:
		while (actual != NULL) {//recorro toda la lista hasta el NULL que marca el fin
			if (strcmp(actual->ESTADO, "INPUT") == 0) { //si el valor del nodo actual es igual al buscado hago print
				printf("INPUT encontrado en la posición %d.\n", pos);
				encontrado = 1;
			}
			actual = actual->siguiente;//cambio al nodo que le sigue al actual
			pos++;//cambio posicion
		}
		if (!encontrado) {//no se encontro buscado
			printf("INPUT no se encontró en la lista.\n");
		}
		break;
	case 4:
		while (actual != NULL) {//recorro toda la lista hasta el NULL que marca el fin
			if (strcmp(actual->ESTADO, "OUTPUT") == 0) { //si el valor del nodo actual es igual al buscado hago print
				printf("OUTPUT encontrado en la posición %d.\n", pos);
				encontrado = 1;
			}
			actual = actual->siguiente;//cambio al nodo que le sigue al actual
			pos++;//cambio posicion
		}
		if (!encontrado) {//no se encontro buscado
			printf("OUTPUT no se encontró en la lista.\n");
		}
		break;
	default:
		printf("Opción inválida.\n");
		break;
	}
}

int CheckPIN(int NumeroPINadd) {
	Nodo* actual = inicio;// apunto al inicio
	while (actual != NULL) {//recorro toda la lista hasta el NULL que marca el fin
		if (actual->NumeroPIN == NumeroPINadd) { //si el valor del nodo actual es igual al buscado hago print
			printf("Ya se ha definido ese PIN anteriormente\n");
			return 0;
		}
		actual = actual->siguiente;//cambio al nodo que le sigue al actual
	}
	return 1;
}

// Función para ordenar la lista por NumeroPIN (Bubble sort)
void OrdenarLista() {
	if (inicio == NULL || inicio->siguiente == NULL) {
		printf("La lista está vacía o tiene un solo elemento, no necesita ordenarse.\n");
		return;
	}
	
	int cambiado;
	Nodo* actual;
	Nodo* ultimo = NULL;
	
	do {
		cambiado = 0;
		actual = inicio;
		
		while (actual->siguiente != ultimo) {
			if (actual->NumeroPIN > actual->siguiente->NumeroPIN) {
				// Intercambiamos TAG
				char tempTAG[20];
				strcpy(tempTAG, actual->TAG);
				strcpy(actual->TAG, actual->siguiente->TAG);
				strcpy(actual->siguiente->TAG, tempTAG);
				
				// Intercambiamos NumeroPIN
				int tempPIN = actual->NumeroPIN;
				actual->NumeroPIN = actual->siguiente->NumeroPIN;
				actual->siguiente->NumeroPIN = tempPIN;
				
				// Intercambiamos ESTADO
				char tempESTADO[6];
				strcpy(tempESTADO, actual->ESTADO);
				strcpy(actual->ESTADO, actual->siguiente->ESTADO);
				strcpy(actual->siguiente->ESTADO, tempESTADO);
				
				cambiado = 1;
			}
			actual = actual->siguiente;
		}
		ultimo = actual; // cada pasada deja el mayor al final
	} while (cambiado);
	
	printf("La lista fue ordenada por Numero de PIN.\n");
}

void GoodBye() {
	printf(" _____  _________________  ___   _   _______ _____        _____ _____ _____ _____ ________  ___  ___   _____ \n");
	printf("/  __ \\|  ___| ___ \\ ___ \\/ _ \\ | \\ | |  _  \\  _  |      /  ___|_   _/  ___|_   _|  ___|  \\/  | / _ \\ /  ___|\n");
	printf("| /  \\/| |__ | |_/ / |_/ / /_\\ \\|  \\| | | | | | | |      \\ `--.  | | \\ `--.  | | | |__ | .  . |/ /_\\ \\\\ `--. \n");
	printf("| |    |  __||    /|    /|  _  || . ` | | | | | | |       `--. \\ | |  `--. \\ | | |  __|| |\\/| ||  _  | `--. \\\n");
	printf("| \\__/\\| |___| |\\ \\| |\\ \\| | | || |\\  | |/ /\\ \\_/ /      /\\__/ /_| |_\\/__/ / | | | |___| |  | || | | |/\\__/ /\n");
	printf(" \\____/\\____/\\_| \\_\\_| \\_\\_| |_\\/| \\_/___/  \\___/       \\____/ \\___/\\____/  \\_/ \\____/\\_|  |_\\/\\_| |_\\/\\____/ \n");
	printf("                                                                                                       \n");
	printf("EL PROGRAMA SE FINALIZO\n");
	return;
}

// Menú principal
void menu() {
	int opcion;

	int NumeroPINadd, ESTADOaddflag;
	
	do {
		printf("\n---- MENU ----\n");
		printf("1. Agregar Nueva configuración de PIN\n");
		printf("2. Borrar configuración de PIN existente\n");
		printf("3. Mostrar lista\n");
		printf("4. Contar elementos\n");
		printf("5. Buscar configuración de PIN por datos\n");
		printf("6. Ordenar lista por PINES\n");
		printf("0. Salir\n");
		printf("Seleccione una opción: ");
		scanf("%d", &opcion);
		fflush(stdin);
		
		switch (opcion) {
		case 1:
			char TAGadd[20];
			char ESTADOadd[7];
			
			printf("Ingrese un TAG a agregar: ");
			if (scanf("%19s", TAGadd) != 1) {
				printf("Error al leer el TAG.\n");
				fflush(stdin);
				break;
			}
			fflush(stdin);
			
			//printf("DEBUG - TAG leído: '%s'\n", TAGadd);
			
			do{
				printf("Ingrese un numero de PIN para %s: ", TAGadd);
				//printf("DEBUG - TAG antes del scanf PIN: '%s'\n", TAGadd);
				while (scanf("%d", &NumeroPINadd) != 1) {
					printf("Por favor ingrese un número válido: ");
					fflush(stdin);
				}
				fflush(stdin);
				//printf("DEBUG - TAG después del scanf PIN: '%s'\n", TAGadd);
			} while (CheckPIN(NumeroPINadd) == 0);
			
			//printf("DEBUG - TAG después de CheckPIN: '%s'\n", TAGadd);
			
			do {
				printf("¿Será ENTRADA o SALIDA? (0 para ENTRADA, 1 para SALIDA): ");
				while (scanf("%d", &ESTADOaddflag) != 1) {
					printf("Por favor ingrese 0 o 1: ");
					fflush(stdin);
				}
				fflush(stdin);
				
				if (ESTADOaddflag == 0) {
					strcpy(ESTADOadd, "INPUT");
				} else if (ESTADOaddflag == 1) {
					strcpy(ESTADOadd, "OUTPUT");
				} else {
					printf("Opción inválida, ingrese 0 o 1.\n");
				}
			} while (ESTADOaddflag != 0 && ESTADOaddflag != 1);
			
			//printf("DEBUG - Antes de llamar agregar: TAG='%s', PIN=%d, ESTADO='%s'\n", TAGadd, NumeroPINadd, ESTADOadd);
			agregar(TAGadd,NumeroPINadd,ESTADOadd);
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
			buscarDatos();
			break;
		case 6:
			OrdenarLista();
			break;
		case 0:
			printf("Saliendo...\n");
			GoodBye();
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
