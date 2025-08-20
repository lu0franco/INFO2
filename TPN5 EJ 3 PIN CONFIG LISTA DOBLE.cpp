#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definici�n de la estructura del nodo para lista doble
typedef struct NodoDoble {
	char TAG[20];
	int NumeroPIN;
	char ESTADO[7];
	struct NodoDoble* siguiente;
	struct NodoDoble* anterior;
} NodoDoble;

// Punteros al principio y al final de la lista
NodoDoble* inicio = NULL;
NodoDoble* fin = NULL;

// Funci�n para agregar un valor a la lista doble
void agregar(char TAGadd[20], int NumeroPINadd, char ESTADOadd[7]) {
	// printf("DEBUG - Recibiendo: TAG='%s', PIN=%d, ESTADO='%s'\n", TAGadd, NumeroPINadd, ESTADOadd);
	
	NodoDoble* nuevo = (NodoDoble*)malloc(sizeof(NodoDoble));
	if (!nuevo) {
		printf("Error: No se pudo asignar memoria.\n");
		return;
	}
	
	strcpy(nuevo->TAG, TAGadd);
	nuevo->NumeroPIN = NumeroPINadd;
	strcpy(nuevo->ESTADO, ESTADOadd);
	nuevo->siguiente = NULL;
	nuevo->anterior = NULL;
	
	// printf("DEBUG - Guardado en nodo: TAG='%s', PIN=%d, ESTADO='%s'\n", nuevo->TAG, nuevo->NumeroPIN, nuevo->ESTADO);
	
	if (!inicio) {
		inicio = fin = nuevo;
	} else {
		fin->siguiente = nuevo;
		nuevo->anterior = fin;
		fin = nuevo;
	}
	
	printf("Datos de PIN agregados.\n");
}
// Funci�n para borrar un nodo por posici�n
void borrar() {
	if (!inicio) {
		printf("La lista est� vac�a.\n");
		return;
	}
	
	int pos;
	printf("Ingrese Posici�n a borrar: ");
	scanf("%d", &pos);
	fflush(stdin);
	
	NodoDoble* actual = inicio;
	int index = 1;
	
	while (actual) {
		if (index == pos) {
			if (actual->anterior) {
				actual->anterior->siguiente = actual->siguiente;
			} else {
				inicio = actual->siguiente;
			}
			
			if (actual->siguiente) {
				actual->siguiente->anterior = actual->anterior;
			} else {
				fin = actual->anterior;
			}
			
			free(actual);
			printf("PIN borrado.\n");
			return;
		}
		actual = actual->siguiente;
		index++;
	}
	
	printf("Esa posici�n no existe en la lista.\n");
}
// Funci�n para mostrar todos los valores de la lista
void mostrar() {
	if (!inicio) {
		printf("La lista est� vac�a.\n");
		return;
	}
	
	NodoDoble* actual = inicio;
	int pos = 1;
	printf("Contenido de la lista:\n");
	printf("\n|INDICE|      ETIQUETA      |NUMERO PIN|  MODO |\n");
	printf("------------------------------------------------\n");
	
	while (actual) {
		printf("|    %-2d|%-20s|        %-2d| %-6s|\n", pos, actual->TAG, actual->NumeroPIN, actual->ESTADO);
		actual = actual->siguiente;
		pos++;
	}
}

// Funci�n para mostrar la lista de fin a inicio
void mostrarInverso() {
	if (!fin) {
		printf("La lista est� vac�a.\n");
		return;
	}
	
	NodoDoble* actual = fin;
	int pos = 1;
	printf("Contenido de la lista (invertido):\n");
	printf("\n|INDICE|      ETIQUETA      |NUMERO PIN|  MODO |\n");
	printf("------------------------------------------------\n");
	
	// Contar para que el �ndice empiece desde el final
	int total = 0;
	NodoDoble* temp = inicio;
	while (temp) { total++; temp = temp->siguiente; }
	pos = total;
	
	while (actual) {
		printf("|    %-2d|%-20s|        %-2d| %-6s|\n", pos, actual->TAG, actual->NumeroPIN, actual->ESTADO);
		actual = actual->anterior;
		pos--;
	}
}

// Funci�n para contar elementos de la lista
int contar() {
	int count = 0;
	NodoDoble* actual = inicio;
	while (actual) {
		count++;
		actual = actual->siguiente;
	}
	return count;
}

// Funci�n para buscar datos
void buscarDatos() {
	NodoDoble* actual = inicio;
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
	printf("Seleccione una opci�n: ");
	scanf("%d", &opcionsubmenu);
	fflush(stdin);
	
	switch (opcionsubmenu) {
	case 1:
		printf("Ingrese un TAG a buscar: ");
		scanf("%19s", TAGsearch);
		fflush(stdin);
		while (actual) {
			if (strcmp(actual->TAG, TAGsearch) == 0) {
				printf("TAG %s encontrado en la posici�n %d.\n", TAGsearch, pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("TAG %s no se encontr� en la lista.\n", TAGsearch);
		break;
	case 2:
		printf("Ingrese un Numero de PIN a buscar: ");
		scanf("%d", &NumeroPINsearch);
		fflush(stdin);
		while (actual) {
			if (actual->NumeroPIN == NumeroPINsearch) {
				printf("Numero de PIN %d encontrado en la posici�n %d.\n", NumeroPINsearch, pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("Numero de PIN %d no se encontr� en la lista.\n", NumeroPINsearch);
		break;
	case 3:
		while (actual) {
			if (strcmp(actual->ESTADO, "INPUT") == 0) {
				printf("INPUT encontrado en la posici�n %d.\n", pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("INPUT no se encontr� en la lista.\n");
		break;
	case 4:
		while (actual) {
			if (strcmp(actual->ESTADO, "OUTPUT") == 0) {
				printf("OUTPUT encontrado en la posici�n %d.\n", pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("OUTPUT no se encontr� en la lista.\n");
		break;
	default:
		printf("Opci�n inv�lida.\n");
	}
}

// Funci�n para verificar si un PIN ya existe
int CheckPIN(int NumeroPINadd) {
	NodoDoble* actual = inicio;
	while (actual) {
		if (actual->NumeroPIN == NumeroPINadd) {
			printf("Ya se ha definido ese PIN anteriormente\n");
			return 0;
		}
		actual = actual->siguiente;
	}
	return 1;
}

// Funci�n para ordenar la lista por NumeroPIN (Bubble sort)
void OrdenarLista() {
	if (!inicio || !inicio->siguiente) {
		printf("La lista est� vac�a o tiene un solo elemento, no necesita ordenarse.\n");
		return;
	}
	
	int cambiado;
	NodoDoble* actual;
	NodoDoble* ultimo = NULL;
	
	do {
		cambiado = 0;
		actual = inicio;
		
		while (actual->siguiente != ultimo) {
			if (actual->NumeroPIN > actual->siguiente->NumeroPIN) {
				char tempTAG[20];
				int tempPIN;
				char tempESTADO[7];
				
				strcpy(tempTAG, actual->TAG);
				strcpy(actual->TAG, actual->siguiente->TAG);
				strcpy(actual->siguiente->TAG, tempTAG);
				
				tempPIN = actual->NumeroPIN;
				actual->NumeroPIN = actual->siguiente->NumeroPIN;
				actual->siguiente->NumeroPIN = tempPIN;
				
				strcpy(tempESTADO, actual->ESTADO);
				strcpy(actual->ESTADO, actual->siguiente->ESTADO);
				strcpy(actual->siguiente->ESTADO, tempESTADO);
				
				cambiado = 1;
			}
			actual = actual->siguiente;
		}
		ultimo = actual;
	} while (cambiado);
	
	printf("La lista fue ordenada por Numero de PIN.\n");
}

// Funci�n de despedida
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

// Men� principal
void menu() {
	int opcion;
	int NumeroPINadd, ESTADOaddflag;
	
	do {
		printf("\n---- MENU ----\n");
		printf("1. Agregar Nueva configuraci�n de PIN\n");
		printf("2. Borrar configuraci�n de PIN existente\n");
		printf("3. Mostrar lista\n");
		printf("4. Contar elementos\n");
		printf("5. Buscar configuraci�n de PIN por datos\n");
		printf("6. Ordenar lista por PINES\n");
		printf("7. Mostrar lista inversa\n");
		printf("0. Salir\n");
		printf("Seleccione una opci�n: ");
		scanf("%d", &opcion);
		fflush(stdin);
		
		switch (opcion) {
		case 1: {
			char TAGadd[20];
			char ESTADOadd[7];
			
			printf("Ingrese un TAG a agregar: ");
			scanf("%19s", TAGadd);
			fflush(stdin);
			// printf("DEBUG - TAG le�do: '%s'\n", TAGadd);
			
			do {
				printf("Ingrese un numero de PIN para %s: ", TAGadd);
				while (scanf("%d", &NumeroPINadd) != 1) {
					printf("Por favor ingrese un n�mero v�lido: ");
					fflush(stdin);
				}
				fflush(stdin);
			} while (!CheckPIN(NumeroPINadd));
			
			do {
				printf("�Ser� ENTRADA o SALIDA? (0 para ENTRADA, 1 para SALIDA): ");
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
					printf("Opci�n inv�lida, ingrese 0 o 1.\n");
				}
			} while (ESTADOaddflag != 0 && ESTADOaddflag != 1);
			
			// printf("DEBUG - Antes de llamar agregar: TAG='%s', PIN=%d, ESTADO='%s'\n", TAGadd, NumeroPINadd, ESTADOadd);
			agregar(TAGadd, NumeroPINadd, ESTADOadd);
			break;
		}
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
		case 7:
			mostrarInverso();
			break;
		case 0:
			printf("Saliendo...\n");
			GoodBye();
			break;
		default:
			printf("Opci�n inv�lida.\n");
		}
		
	} while (opcion != 0);
}

// Funci�n principal
int main() {
	menu();
	return 0;
}
