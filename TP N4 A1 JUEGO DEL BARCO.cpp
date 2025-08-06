#include <stdio.h>
#include <string.h>
#include <stdlib.h> // para srand() y random()
#include <time.h>      // para time()

typedef struct{
	char TABLERO[5][5];
	int Balas;
}GameState;

int main(int argc, char *argv[]) {
	GameState partida;
	char TABLE [5][5];
	int CANNONBALLSCOUNTER = 10;
	int puntero_x;
	int puntero_y;
	char nameFile[15]= "SavedGame.bin";
	void StartGame(char TABLE[5][5]);
	void ShowGame(char TABLE[5][5]);
	void ShootAction(char TABLE[5][5],int *CANNONBALLSCOUNTER , int *puntero_x , int *puntero_y);
	void GetShootData ();
	void SaveData (char TABLE[5][5],int *CANNONBALLSCOUNTER, char nameFile[15], GameState* game);
	void LoadData (char TABLE[5][5],int *CANNONBALLSCOUNTER, char nameFile[15], GameState* game);
	void GoodBye();
	int Menu;
	do{
		printf("\n\n");
		printf("Menú del juego\n");
		printf ("____________________________\n");
		printf("1) Inicia el juego.\n");
		printf("2) Muestra el tablero. \n");
		printf("3) Dispara al barco.\n");
		printf("4) Guardar esta partida.\n");
		printf("5) Cargar una partida existente.\n");
		printf("6) Salir. \n");
		scanf("%d",&Menu);
		fflush(stdin);
		
		
		switch(Menu){
		case 1:
			printf("Se ha inicializado el tablero de juego \n");
			StartGame (TABLE);
			break;
		case 2:
			printf("Tablero actual  tiros restantes: %d \n", CANNONBALLSCOUNTER);
			ShowGame (TABLE);
			break;
		case 3:
			printf("Elija dónde disparar \n");
			ShootAction (TABLE, &CANNONBALLSCOUNTER, &puntero_x ,&puntero_y);
			break;
		case 4:
			printf ("Ha seleccioando guardar partida \n");
			SaveData(TABLE, &CANNONBALLSCOUNTER, nameFile, &partida);
			break;
		case 5:
			printf ("Ha seleccioando cargar partida \n");
			LoadData(TABLE, &CANNONBALLSCOUNTER, nameFile, &partida);
			break;
		case 6:
			printf ("Partida abandonada \n");
			GoodBye();
			break;
		}
		
	}while(Menu !=6);

	return 0;
}

void StartGame (char TABLE[5][5]){
	int i;
	int j;
	int x;
	int y;
	for (i=0; i<=4; i++){
		for (j=0; j<=4; j++){
			TABLE[i][j]= char(126);
		}
	}
	srand(time(0));
	x = rand()% 5;
	y = rand()% 5;
//	printf("%d , %d \n" , x,y);
	TABLE[x][y]= 'B';
	return;
}

void ShowGame (char TABLE[5][5]){
	int i;
	int j;
	for (i=0; i<=4; i++){
		for (j=0; j<=4; j++){
			if (TABLE [i][j] !='A'){
				if (j==4){printf("%c \n" , '~');}
				else{printf("%c " , '~');}
				
			}else {
				if (j==4){printf("%c \n" , 'A');}
				else{printf("%c " , 'A');}
			}
//			 if (j==4){printf("%c \n" , TABLE[i][j]);} //MUESTRA TODA LA INFO
//			else {printf("%c " , TABLE[i][j]);}
			
		}
	}
	return;
}
void ShowGameWin (char TABLE[5][5]){
		int i;
		int j;
		for (i=0; i<=4; i++){
			for (j=0; j<=4; j++){
				if (j==4){printf("%c \n" ,TABLE [i][j]);;}
				else{printf("%c " ,TABLE [i][j]);}
				
					//			 if (j==4){printf("%c \n" , TABLE[i][j]);} //MUESTRA TODA LA INFO
					//			else {printf("%c " , TABLE[i][j]);}
					
			}
		}
		return;
	}
int GetShootData (){
	int number;
	while (number < 0 || number >4){
		if (scanf("%d",&number) == 1) {
			if (number < 0 || number >4) {printf("Número Inválido.\n");} else {printf("Número Válido.\n");}
		} else {
			printf("El valor ingresado no es un número, ingrese un número válido:  ");
			fflush(stdin);
		}
	}
	fflush(stdin);
	return number;
}
void ShootAction (char TABLE[5][5] , int *CANNONBALLSCOUNTER , int *puntero_x, int *puntero_y){
	int check=0;
	if (*CANNONBALLSCOUNTER !=0){
	do {
	printf("Defina Valor de X para el Disparo (debe ser un numero entre 0 y 4):  ");
	*puntero_x=GetShootData();
	printf("Defina Valor de Y para el Disparo (debe ser un numero entre 0 y 4):  ");
	*puntero_y=GetShootData();
	if (TABLE[*puntero_y][*puntero_x] == 'A') {
		printf("Ya se disparó a estas coordenadas en una jugada anterior \n");
		check=1;
	}else {check=0;}
	} while (check==1);
	if (TABLE[*puntero_y][*puntero_x] == 'B') {
		printf("GANASTE, FIN DEL JUEGO. A CONTINUACION SE MUESTRA TU TABLERO \n");
		TABLE[*puntero_y][*puntero_x] = 'X';
		ShowGameWin (TABLE);
	}else {printf("sos un malo \n");
	TABLE[*puntero_y][*puntero_x] = 'A';
	int tiros =*CANNONBALLSCOUNTER;
	tiros--;
	*CANNONBALLSCOUNTER=tiros;
	printf("Quedan %d disparos \n" , tiros);
	}
	}
	else {printf ("Se acabaron los disparos,¿desea comenzar otra partida? Elija la opción 1 en el menu del juego \n");
	}
	return;
}

void SaveData (char TABLE[5][5], int *CANNONBALLSCOUNTER, char nameFile[15], GameState* game){
	int i;
	int j;	
	/*copiar todo a un struct para guardarlo mas facil*/
	for (i=0; i<=4; i++){
		for (j=0; j<=4; j++){
			game->TABLERO[i][j]=TABLE[i][j];
		}
	}
	game->Balas=*CANNONBALLSCOUNTER;
	
	/*pasarlo al archivo en binario*/
	FILE  *Filebin;
	Filebin = fopen(nameFile,"wb");
	if (Filebin != NULL) {
		fwrite(game, sizeof(GameState), 1, Filebin);
		fclose(Filebin);
		printf("Se ha terminado de escribir %s \n", nameFile);
	} else printf("Problemas al abrir el archivo.");
	// Limpiar struct luego de guardar
	memset(game, 0, sizeof(GameState));
	return;
}
	
void LoadData (char TABLE[5][5], int *CANNONBALLSCOUNTER, char nameFile[15], GameState* game){
	
	/*leer del archivo en binario*/
	FILE  *Filebin;
	Filebin = fopen(nameFile,"rb");
	if (Filebin != NULL) {
		size_t gameleido=fread(game, sizeof(GameState), 1, Filebin);
		fclose(Filebin);
		printf("Se han leído %zu elementos desde %s\n", gameleido, nameFile);
		int i;
		int j;	
		int h;
		for (h = 0; h < gameleido; h++) {
			/*copiar del struct al programa*/
			for (i=0; i<=4; i++){
				for (j=0; j<=4; j++){
					TABLE[i][j]=game->TABLERO[i][j];
				}
			}
			*CANNONBALLSCOUNTER=game->Balas;
		}
	} else printf("Problemas al abrir el archivo.");
	

	

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
