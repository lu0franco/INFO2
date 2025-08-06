#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 20
using namespace std;
struct motor{
	char SerialNumber [21];
	char Vendor [6];
	char Model [10];
	int Voperation;
	float Iwork;
	char ONOFF[4];
} stock [MAX];
int motorCount = 0;
void LogData(motor* m);
void ShowData(motor* m , int i);
void SearchData(motor* m);
void ShowOnData(motor* m);
void IworkData(motor* m);
void GoodBye();
void tableformat();
void SaveToFileData(motor* m , int CantMotores);
void LoadFromFileData(motor* m , int CantMotores);

int main(int argc, char *argv[]) {

	int Menu;
	do {
	printf (" \n");
	printf ("_______________________________________________________________________________________________ \n");
	printf ("Bienvenido al menú de control de stock y estado de los motores, elija una opción para continuar \n");
	printf ("1) Añadir un motor a la lista \n");
	printf ("2) Mostrar lista de motores \n");
	printf ("3) Buscar un motor por número de serie \n");
	printf ("4) Mostrar motores encendidos \n");
	printf ("5) Calcular consumo de corriente de los motores en funcionamiento \n");
	printf ("6) Guardar lista actual \n");
	printf ("7) Cargar lista de archivo \n");
	printf ("8) Cerrar programa \n");
	printf ("\n SU OPCION: ---->   ");
	scanf ("%d",&Menu);
	fflush(stdin);
	
	switch(Menu){
	case 1:
		if (motorCount < MAX) {
			LogData(&stock[motorCount]);
			motorCount++;
		} else {
			printf("Stock lleno\n");
		}
		printf (" \n");
		printf("Datos cargados\n");
		break;
	case 2:
		printf("Tabla de datos de los motores:\n");
		tableformat();
		for (int j = 0; j < motorCount; j++) {
			ShowData(stock, j);
		}
		printf (" \n");
		printf("Datos mostrados correctamente \n");
		break;
	case 3:
		SearchData(stock);
		printf (" \n");
		printf("Búsqueda realizada \n");
		break;
	case 4:
		printf ("Los motores encendidos actualmente son:    \n");
		ShowOnData(stock);
		break;
	case 5:
		printf ("El consumo de los motores es:    \n");
		IworkData(stock);
		break;
	case 6:
		printf ("Ha seleccionado guardar lista    \n");
		SaveToFileData(stock ,motorCount);
		break;
	case 7:
		printf ("Ha seleccionado cargar lista     \n");
		LoadFromFileData(stock ,motorCount);
		break;
	case 8:
		printf ("Usted ha elegido cerrar el programa, hasta luego.\n");
		GoodBye();
		break;
	}
	}while (Menu != 8);
	
	return 0;
}

void LogData(motor* m) {
	char buffer[100];
	
	printf("Ingrese el Numero de serie: ");
	fgets(buffer, sizeof(buffer), stdin);
	sscanf(buffer, "%21[^\n]", m->SerialNumber);  // Máximo 19 caracteres
	
	// Marca (Vendor)
	printf("Ingrese la marca: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = 0;  // Eliminar '\n'
	strncpy(m->Vendor, buffer, sizeof(m->Vendor) - 1);
	m->Vendor[sizeof(m->Vendor) - 1] = '\0';
	
	// Modelo
	printf("Ingrese el modelo: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = 0;  // Eliminar '\n'
	strncpy(m->Model, buffer, sizeof(m->Model) - 1);
	m->Model[sizeof(m->Model) - 1] = '\0';
	
	// Voltaje: solo 220 o 380
	do {
		printf("Ingrese el voltaje de trabajo, NOTA: solo se admiten valores '220' y '380' --> ");
		fgets(buffer, sizeof(buffer), stdin);
		if (sscanf(buffer, "%d", &m->Voperation) != 1) {
			printf("Entrada inválida. Intente de nuevo.\n");
			continue;
		}
	} while (m->Voperation != 220 && m->Voperation != 380);
	
	// Corriente: positivo
	float flagIwork;
	
	do {
		printf("Ingrese la corriente de trabajo, NOTA: solo se admiten valores positivos --> ");
		fgets(buffer, sizeof(buffer), stdin);
		
		// Intentar convertir a float y validar que sea positivo
		if (sscanf(buffer, "%f", &flagIwork) == 1 && flagIwork >= 0) {
			m->Iwork = flagIwork;
			break;
		} else {
			printf("Entrada inválida. Intente de nuevo.\n");
		}
		
	} while (1);
	
	// Estado ON/OFF
	do {
		printf("Ingrese estado, NOTA: solo se admiten valores 'ON' y 'OFF' --> ");
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%3s", m->ONOFF);  // Solo dos letras + '\0'
	} while (strcmp(m->ONOFF, "ON") != 0 && strcmp(m->ONOFF, "OFF") != 0);
}

void ShowData(motor* m , int i) {
	printf("| %-19s | %-7s | %-7s | %-20d | %-22.2f | %-6s |\n", m[i].SerialNumber, m[i].Vendor, m[i].Model, m[i].Voperation, m[i].Iwork, m[i].ONOFF);
}

void SearchData(motor* m) {
	char SerialNumberSearch[20];
	fflush(stdin);
	printf("Ingrese número de serie a buscar: ");
	scanf("%s", SerialNumberSearch);
	for (int i = 0; i < motorCount; i++) {
		if (strcmp(m[i].SerialNumber, SerialNumberSearch) == 0) {
			tableformat();
			ShowData(m, i);
			return;
		}
	}
	printf("No se han encontrado coincidencias.\n");
}

void ShowOnData(motor* m) {
	int i=-1;
	do{
		i++;
		if ( strcmp(m[i].ONOFF, "ON") == 0 )
		{
			tableformat();
			ShowData(m, i);
		}
	} while (i < motorCount);
	printf("No hay motores encendidos \n");
	return;
}

void IworkData(motor* m) {
	int i=-1;
	float IworkTotal=0;
	do{
		i++;
		if ( strcmp(m[i].ONOFF, "ON") == 0 )
		{
		IworkTotal=IworkTotal+m[i].Iwork;
		}
	} while (i < motorCount);
	if (IworkTotal !=0){
		printf( "%-22.2f\n", IworkTotal);
	}else{
	printf("No hay motores encendidos \n");
	}
	return;
}
	
void tableformat(){
	printf("|  Numero de serie    | Marca   | Modelo  | Voltaje de trabajo   | Corriente de trabajo   | Estado |\n");
	printf("____________________________________________________________________________________________________\n");
return;
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
void SaveToFileData(motor* m , int CantMotores) {
	int i=-1;
	char nameFile[15]="SavedList";
	strcat(nameFile, ".bin");
	FILE  *Filebin;
	
	/*Uso de fprintf*/
	Filebin = fopen(nameFile,"wb");
	if (Filebin != NULL) {
		fwrite(&CantMotores, sizeof(int), 1, Filebin); // Guardar cantidad primero
		fwrite(m, sizeof(motor), CantMotores, Filebin);
		fclose(Filebin);
		printf("Se ha terminado de escribir %s \n", nameFile);
	} else printf("Problemas al abrir el archivo.");

	
	return;
	}
void LoadFromFileData(motor* m , int CantMotoresParam) {
	char nameFile[20] = "SavedList.bin";
	FILE *Filebin = fopen(nameFile, "rb");
	if (Filebin != NULL) {
		int cantidad;
		fread(&cantidad, sizeof(int), 1, Filebin); // Leemos la cantidad real
		if (cantidad > MAX) {
			printf("Archivo contiene más motores de los que permite el programa.\n");
			fclose(Filebin);
			return;
		}
		size_t leidos = fread(m, sizeof(motor), cantidad, Filebin);
		motorCount = cantidad;  // ¡¡¡ACTUALIZAMOS motorCount!!!
		fclose(Filebin);
		printf("Se han leído %d motores desde %s\n", motorCount, nameFile);
	} else {
		printf("Problemas al abrir el archivo para leer.\n");
	}
}

