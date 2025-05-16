/*Ejemplo fputc_fputs.cpp

Solicitar nombre de archivo al usuario.

Solicitar texto al usuario para guardarlo en el archivo.
*/
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
	char nameFile[15];
	char FileContent [100];
	printf("Elija un nombre de archivo (será .txt independientemente del nombre)\n");
	scanf ( "%s" ,nameFile);
	strcat(nameFile, ".txt");
	printf("Escriba la cadena a almacenar en el archivo %s \n", nameFile );
	scanf ( "%s" ,FileContent);
	FILE  *Filetext;
	
	/*Uso de fputc*/
	int i = 0;
	/*Uso de fputs*/
	Filetext = fopen(nameFile,"w");
	if (Filetext != NULL) {
		fputs(FileContent, Filetext);
		printf("Se ha terminado de escribir Filetext.txt \n");
	} else printf("Problemas al abrir el archivo.");
	fclose(Filetext);
	
	return 0;
}

/* ATENCION, FALTA AMPLIAR A LOS OTROS CASOSEjemplo fgetc_fgets.cpp

Solicitar nombre de archivo al usuario.

Solicitar palabra al usuario y buscarla en el texto leído desde el archivo.

Ejemplo entrada_formateada.cpp

Guardar con fprintf, 2 datos enteros solicitados al usuario, y cerrar archivo.

Posteriormente abrir archivo, leer los datos, y realizar la suma de los mismos, mostrando en pantalla el resultado.
  Actividad:

Ampliar la funcionalidad de actividad anterior, día 07-05, para guardar en el archivo una cantidad variable de números, provistos por el usuario. Realizar la suma con el mismo tipo de secuencia descripto en el punto anterior (1.guardar datos, 2.cerrar archivo, 3. abrir archivo, 4. leer/sumar datos).

*** Quienes no alcanzaron a completar la actividad del 07-05 pueden hacerlo en esta entrega.
*/

