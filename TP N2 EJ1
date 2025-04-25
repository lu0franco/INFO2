#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 20
using namespace std;
struct motor{
	char SerialNumber [20];
	char Vendor [3];
	char Model [7];
	int Voperation;
	float Iwork;
	char ONOFF[3];
} stock [MAX];
int motorCount = 0;
void LogData(motor* m);
void ShowData(motor* m , int i);
void SearchData(motor* m);
void ShowOnData(motor* m);
void IworkData(motor* m);
void GoodBye();
void tableformat();

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
	printf ("6) Cerrar programa \n");
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
		printf ("Usted ha elegido cerrar el programa, hasta luego.\n");
		GoodBye();
		break;
	}
	}while (Menu != 6);
	
	return 0;
}

void LogData(motor* m) {
	printf("Ingrese el Numero de serie: ");
	scanf("%20s",m->SerialNumber);
	fflush(stdin);
	printf("Ingrese la marca: ");
	scanf("%3s",m->Vendor);
	fflush(stdin);
	printf("Ingrese el modelo: ");
	scanf("%7s",m->Model);
	fflush(stdin);
	printf("Ingrese el voltaje de trabajo: ");
	int flagVoperation=0;
	do {
		printf("NOTA: solo se admiten valores ''220'' y ''380'' -->");
		scanf("%d",&flagVoperation);
			m->Voperation=flagVoperation;
			fflush(stdin);
	}while (flagVoperation!=220 && flagVoperation!=380);

	printf("Ingrese la corriente de trabajo: ");
	float flagIwork=0;
	do {
		printf("NOTA: solo se admiten valores positivos -->");
		scanf("%f",&flagIwork);
		m->Iwork=flagIwork;
		fflush(stdin);
	}while (flagIwork<0);
	printf("Ingrese estado del motor: ");
	char ONOFFtemp [3];
	int flagONOFF=0;
	do {
	printf("NOTA: solo se admiten valores ''ON'' y ''OFF''-->");
	scanf("%s",ONOFFtemp);
	
	if (strcmp(ONOFFtemp, "ON")==0 || strcmp(ONOFFtemp, "OFF")==0){
		flagONOFF=1;
	}
	}while (flagONOFF==0);
	strcpy(m->ONOFF,ONOFFtemp);
	fflush(stdin);
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
