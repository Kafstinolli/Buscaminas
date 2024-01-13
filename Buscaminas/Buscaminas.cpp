#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

int columnasJuego;
int filasJuego;
int minasJuego;
int banderasRestantesJuego;
bool activarTruco;

int juegosGanados;
int juegosPerdidos;
int juegosCancelados;
vector<vector<string>>contenidoEstadisticas;

string estadisticas[3][2];

char tableroVisible[20][20];
char tableroInvisible[20][20];

void calcularMinasAlrededor();
int verificarPartida();
void limpiarTablero();
void dificultadPartida(int dificultad);
void ponerMinas();
void ponerNumerosFila(int fila);
void mostrarCelda(int fila, int columna);

int numeroAleatoreo();

int main() {


}

void calcularMinasAlrededor() {

	int contadorMinas;
	
	for (int fila = 0; fila < filasJuego; fila++) {
		for (int columna = 0; columna < columnasJuego; columna++) {
			if (tableroInvisible[fila][columna] = 'M') {
				contadorMinas = 0;

				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						if (i == 0 && j == 0)
							continue;

						int verificarFila = fila + i;
						int verificarColumna = columna + j;

						if (verificarFila < 0 || verificarFila >= filasJuego || verificarColumna < 0 || verificarColumna >= columnasJuego)
							continue;
						if (tableroInvisible[verificarFila][verificarColumna] == 'M')
							contadorMinas++;

					}
				}
				tableroInvisible[fila][columna] = contadorMinas + 48;

			}

		}
	}
}

int verificarPartida() {

	for (int fila = 0; fila < filasJuego; fila++) {
		for (int columna = 0; columna < columnasJuego; columna++) {
			if (tableroVisible[fila][columna] == 'X')
				return 0;
		}
	}
	for (int fila = 0; fila < filasJuego; fila++) {
		for (int columna = 0; columna < columnasJuego; columna++) {
			if ((tableroVisible[fila][columna] != tableroInvisible[fila][columna]) && tableroInvisible[fila][columna] != 'M')
				return 1;
		}
	}
	return 2;
}

void limpiarTablero() {

	for (int fila = 0; fila < 20; fila++) {
		for (int columna = 0; columna < 20; columna++) {
			tableroVisible[fila][columna] = '.';
			tableroInvisible[fila][columna] = '.';
		}
	}
}

void dificultadPartida(int dificultad){
	
	switch (dificultad)
	{
	case 1:
		columnasJuego = 10;
		filasJuego = 8;
		minasJuego = 10;
		break;

	case 2:
		columnasJuego = 18;
		filasJuego = 14;
		minasJuego = 40;
		break;

	case 3:
		columnasJuego = 20;
		filasJuego = 20;
		minasJuego = 99;
		break;
	
	default:
		break;
	}
	banderasRestantesJuego = minasJuego;
}

void ponerMinas(){

	int contadorMinas = 0;
	int coordenadasColumnas;
	int coordenadasFilas;

	while (contadorMinas < minasJuego){}
	{
		coordenadasColumnas = numeroAleatoreo() % columnasJuego;
		coordenadasFilas = numeroAleatoreo() % filasJuego;
		if(tableroInvisible[coordenadasFilas][coordenadasColumnas] == '.'){
			tableroInvisible[coordenadasFilas][coordenadasColumnas] = 'M';
			contadorMinas++;
		}
	}	
}

void ponerNumerosFila(int fila){

	if(fila % 10 == 9){
		cout << ((fila + 1) / 10) % 1;
	}
	else{
		cout << '  ';
	}
	cout << (fila + 1) % 10 << " | ";
}

int numeroAleatoreo(){

	return rand();
}

void mostrarCelda(int fila, int columna){

	tableroVisible[fila][columna] = tableroInvisible[fila][columna];
	if(tableroVisible[fila][columna] == '0')
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				if(i == 0 && j == 0)
				continue;

				int abrirFIla = fila + i;
				int abrirColumna = columna + j;
				if(abrirFIla < 0 || abrirFIla >= filasJuego || abrirColumna < 0 || abrirColumna>= columnasJuego)
					continue;
				if(tableroVisible[abrirFIla][abrirColumna] == '.')
					mostrarCelda(abrirFIla, abrirColumna);
			}
		}
}