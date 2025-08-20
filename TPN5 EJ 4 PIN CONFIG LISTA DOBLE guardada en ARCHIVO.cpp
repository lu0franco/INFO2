#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>   // Para listar archivos
#include <windows.h>  // Para GetModuleFileName (ruta del exe)
typedef struct NodoDoble {
	char TAG[20];
	int NumeroPIN;
	char ESTADO[7];
	struct NodoDoble* siguiente;
	struct NodoDoble* anterior;
} NodoDoble;

NodoDoble* inicio = NULL;
NodoDoble* fin = NULL;

//FUNCION PARA AGREGAR NODOS A LA LISTA
void agregar(char TAGadd[20], int NumeroPINadd, char ESTADOadd[7]) {
	NodoDoble* nuevo = (NodoDoble*)malloc(sizeof(NodoDoble));
	if (!nuevo) {
		printf("Error: No se pudo asignar memoria.\n");
		return;
	}
	strcpy(nuevo->TAG, TAGadd);
	nuevo->NumeroPIN = NumeroPINadd;
	strcpy(nuevo->ESTADO, ESTADOadd);
	nuevo->siguiente = NULL;
	nuevo->anterior = fin;
	if (!inicio) {
		inicio = fin = nuevo;
	} else {
		fin->siguiente = nuevo;
		fin = nuevo;
	}
	printf("Datos de PIN agregados.\n");
}
// FUNCION DE BORRADO DE NODOS
void borrar() {
	if (!inicio) {
		printf("La lista está vacía.\n");
		return;
	}
	
	int pos;
	printf("Ingrese Posición a borrar: ");
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
	
	printf("Esa posición no existe en la lista.\n");
}
// FUNCION PARA MOSTRAR LOS NODOS, FORMATO TABLA
void mostrar() {
	if (!inicio) {
		printf("La lista está vacía.\n");
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
//FUNCION IGUAL A LA ANTERIOR PERO USANDO LA VENTAJA DE LA LISTA ENLAZADA DE SER BILATERAL
void mostrarInverso() {
	if (!fin) {
		printf("La lista está vacía.\n");
		return;
	}
	
	NodoDoble* actual = fin;
	int pos = 1;
	printf("Contenido de la lista (invertido):\n");
	printf("\n|INDICE|      ETIQUETA      |NUMERO PIN|  MODO |\n");
	printf("------------------------------------------------\n");
	
	// INVERTIR EL INDICE PARA CONTAR DEL FINAL
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

// FUNCION DE CONTADO DE NODOS
int contar() {
	int count = 0;
	NodoDoble* actual = inicio;
	while (actual) {
		count++;
		actual = actual->siguiente;
	}
	return count;
}

// FUNCION DE BUSQUEDA DE DATOS
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
	printf("Seleccione una opción: ");
	scanf("%d", &opcionsubmenu);
	fflush(stdin);
	
	switch (opcionsubmenu) {
	case 1:
		printf("Ingrese un TAG a buscar: ");
		scanf("%19s", TAGsearch);
		fflush(stdin);
		while (actual) {
			if (strcmp(actual->TAG, TAGsearch) == 0) {
				printf("TAG %s encontrado en la posición %d.\n", TAGsearch, pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("TAG %s no se encontró en la lista.\n", TAGsearch);
		break;
	case 2:
		printf("Ingrese un Numero de PIN a buscar: ");
		scanf("%d", &NumeroPINsearch);
		fflush(stdin);
		while (actual) {
			if (actual->NumeroPIN == NumeroPINsearch) {
				printf("Numero de PIN %d encontrado en la posición %d.\n", NumeroPINsearch, pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("Numero de PIN %d no se encontró en la lista.\n", NumeroPINsearch);
		break;
	case 3:
		while (actual) {
			if (strcmp(actual->ESTADO, "INPUT") == 0) {
				printf("INPUT encontrado en la posición %d.\n", pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("INPUT no se encontró en la lista.\n");
		break;
	case 4:
		while (actual) {
			if (strcmp(actual->ESTADO, "OUTPUT") == 0) {
				printf("OUTPUT encontrado en la posición %d.\n", pos);
				encontrado = 1;
			}
			actual = actual->siguiente;
			pos++;
		}
		if (!encontrado) printf("OUTPUT no se encontró en la lista.\n");
		break;
	default:
		printf("Opción inválida.\n");
	}
}

// FFUNCION PARA CHEQUEAR PINES QUE YA SE OCUPARON
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

// ORDENAR LISTA POR NUMERO DE PIN
void OrdenarLista() {
	if (!inicio || !inicio->siguiente) {
		printf("La lista está vacía o tiene un solo elemento, no necesita ordenarse.\n");
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

// FUNCION DE SALIDA
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
//_____________________CARGA Y GUARDADO EN FIILES___________________________

// Guardar lista en archivo
void guardarEnArchivo() {
	if (!inicio) {
		printf("La lista está vacía, nada que guardar.\n");
		return;
	}
	
	char nombreArchivo[50];
	printf("Ingrese el nombre del archivo a guardar (ej: proyecto1.txt): ");
	fflush(stdin);           // limpiar buffer anterior
	fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
	
	// eliminar el salto de línea al final
	size_t len = strlen(nombreArchivo);
	if (len > 0 && nombreArchivo[len-1] == '\n') {
		nombreArchivo[len-1] = '\0';
	}
	FILE* f = fopen(nombreArchivo, "w");
	if (!f) {
		printf("Error al abrir archivo para escribir.\n");
		return;
	}
	
	NodoDoble* actual = inicio;
	while (actual) {
		fprintf(f, "|%-20s|        %-2d| %-6s|\n", actual->TAG, actual->NumeroPIN, actual->ESTADO);
				actual = actual->siguiente;
	}
	fclose(f);
	printf("Datos guardados en '%s'.\n", nombreArchivo);
}

// Cargar lista desde archivo
void cargarDesdeArchivo() {
	char nombreArchivo[50];
	
	printf("Archivos disponibles en la carpeta:\n");
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (strstr(dir->d_name, ".txt")) {
				printf(" - %s\n", dir->d_name);
			}
		}
		closedir(d);
	}
	
	printf("Ingrese el nombre del archivo a cargar: ");
	fflush(stdin);           // limpiar buffer anterior
	fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
	
	// eliminar el salto de línea al final
	size_t len = strlen(nombreArchivo);
	if (len > 0 && nombreArchivo[len-1] == '\n') {
		nombreArchivo[len-1] = '\0';
	}
	
	FILE* f = fopen(nombreArchivo, "r");
	if (!f) {
		printf("No se pudo abrir el archivo '%s'.\n", nombreArchivo);
		return;
	}
	
	// Limpiar lista actual antes de cargar
	NodoDoble* actual = inicio;
	while (actual) {
		NodoDoble* temp = actual;
		actual = actual->siguiente;
		free(temp);
	}
	inicio = fin = NULL;
	char linea[100];
	char TAG[20], ESTADO[7];
	int PIN;
	while (fgets(linea, sizeof(linea), f)) {
		// Leer desde la línea: todo hasta el último número antes del ESTADO
		// Suponiendo que el formato sea: TAG (puede tener espacios) PIN ESTADO
		int numCampos = sscanf(linea, "|%49[^|]| %d | %6s |", TAG, &PIN, ESTADO);
		
		if (numCampos == 3) {
			agregar(TAG, PIN, ESTADO);
		} else {
			printf("Error leyendo la línea: %s", linea);
		}
	}
	fclose(f);
	printf("Datos cargados desde '%s'.\n", nombreArchivo);
}

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
		printf("7. Mostrar lista inversa\n");
		printf("8. Guardar lista en archivo\n");
		printf("9. Cargar lista desde archivo\n");
		printf("0. Salir\n");
		printf("Seleccione una opción: ");
		scanf("%d", &opcion);
		fflush(stdin);		
		switch (opcion) {
		case 1: {
			char TAGadd[20];
			char ESTADOadd[7];
			
			printf("Ingrese un TAG a agregar: ");
			fflush(stdin);           // limpiar buffer anterior
			fgets(TAGadd, sizeof(TAGadd), stdin);
			
			// eliminar el salto de línea al final
			size_t len = strlen(TAGadd);
			if (len > 0 && TAGadd[len-1] == '\n') {
				TAGadd[len-1] = '\0';
			}
			// printf("DEBUG - TAG leído: '%s'\n", TAGadd);
			
			do {
				printf("Ingrese un numero de PIN para %s: ", TAGadd);
				while (scanf("%d", &NumeroPINadd) != 1) {
					printf("Por favor ingrese un número válido: ");
					fflush(stdin);
				}
				fflush(stdin);
			} while (!CheckPIN(NumeroPINadd));
			
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
						fflush(stdin);
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
		case 8:
			guardarEnArchivo();
			break;
		case 9:
			cargarDesdeArchivo();
			break;
		case 0:
			printf("Saliendo...\n");
			GoodBye();
			break;
		default:
			printf("Opción inválida.\n");
			fflush(stdin);
		}
		
	} while (opcion != 0);
}


int main() {
	menu();
	return 0;
}
