#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <sstream>

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

string estadistica[3][2];

char tableroVisible[20][20];
char tableroInvisible[20][20];

void calcularMinasAlrededor();
void limpiarTablero();
void dificultadPartida(int dificultad);
void ponerMinas();
void ponerNumerosFila(int fila);
void mostrarCelda(int fila, int columna);
void ponerBandera(int fila, int columna);
void estadisticas();
void mostrarTableros();
void abrirCelda(int fila, int columna);
void ponerTablero();
void pintarColumnasArriba();
void pintarColumnasDecenas();
void pintarColumnasUnidades();
void finalizarJuego();
void ingresarCoordenadas(int inicio, int fin);
void crearEstadisticas();
void iniciarTablero();
void tableroDificultad(int nivel);
void menuDificultad();
void menuInicio();
void menuJuego();
void menuPrincipal();
void mostrarEstadisticas();
void iniciarJuego();
void jugar();

int verificarCoordenada(char verificador);
int verificarEntrada();
int validarOpcionMenu(string menu);
int verificarPartida();
int numeroAleatoreo();

int main() {

	int opcionMenu;
	int iniciar = 1;

	crearEstadisticas();

	srand(time(NULL));

	while(iniciar){
		int opcionMenu;
		system("clear");
		do{
			menuPrincipal();
			opcionMenu = validarOpcionMenu("Menu");
		}while(opcionMenu < 0);
		switch(opcionMenu){

			case 1: 
				iniciarJuego();
				jugar();
				break;

			case 2:
				mostrarEstadisticas();
				break;

			case 3:
				finalizarJuego();
				iniciar = 0;	
		}
	}
	return 0;
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

void iniciarJuego(){

	int opcionMenu;
	do{
		menuDificultad();
		opcionMenu = validarOpcionMenu("Dificultad");
	}while(opcionMenu < 0);
	tableroDificultad(opcionMenu);
	iniciarTablero();
}

void jugar(){

	int opcionMenu;
	int juego = 1;
	while(juego == 1){
		system("clear");
		do{
			menuJuego();
			opcionMenu = validarOpcionMenu("opcion jugar");
		}while(opcionMenu < 0);
		if(opcionMenu == 3){
			juego = 3;
			continue;
		}
		menuJuego();
		cout << "digite la coordenada en X (0 para cancelar).\n";
		int coordenadaColumna = verificarCoordenada('c');
		int coordenadaFila;
		if(coordenadaColumna != -1)
		{
			cout << "Digite la coordenada en Y (0 para cancelar).\n";
			coordenadaFila = verificarCoordenada('r');
		}
		if(coordenadaColumna != -1 && coordenadaFila != -1){
			switch(opcionMenu){

				case 1: abrirCelda(coordenadaFila, coordenadaColumna);
				break;
				case 2: ponerBandera(coordenadaFila, coordenadaColumna);
				break;
			}
		}
		juego = verificarPartida();
	}
	mostrarTableros();
	system("clear");

	switch (juego)
	{
	case 1: 
		cout << "perdiste el juego. \n";
		juegosPerdidos++;
		break;

	case 2: 
		cout << "Ganaste el juego. \n";
		juegosGanados++;
		break;

	case 3:
		cout << "juego cancelado. \n";
		juegosCancelados++;
		break;
	}

	estadisticas();

	cout << "digite cualquier numero par avolver al menu principal.\n" << endl;
	menuInicio();
	ponerTablero();
	int entrada;
	do{
		cin >> entrada;
	}while(verificarEntrada());
}

int validarOpcionMenu(string menu){

	int opcionMenu;
	cin >> opcionMenu;
	if(opcionMenu == 1234){
		activarTruco = !activarTruco;
		system("clear");
		cout << "valor del truco: " << activarTruco << endl;
		return -1;
	}
	system("clear");
	if(!verificarEntrada()){
		if(menu == "Menu"){
			if(opcionMenu < 1 || opcionMenu > 3){
				cout << "Opcion invalida";
				ingresarCoordenadas(1,3);
				return -1;
			}
		}
		if(menu == "Dificultad"){
			if(opcionMenu < 1 || opcionMenu > 3){
				cout << "Opcion invalida";
				ingresarCoordenadas(1,3);
				return -1;
			}
		}
		if(menu == "opcion del juego"){
			if(opcionMenu < 1 || opcionMenu > 3){
				cout << "Opcion invalida ";
				ingresarCoordenadas(1,3);
				return -1;
			}
		}
		return opcionMenu;
	}
	return -1;
}

int verificarCoordenada(char verificador){

		int coordenada;
		do{
			cin >> coordenada;
			if(coordenada == 1234){
				activarTruco = !activarTruco;
				cout << "valor del truco: " << activarTruco << endl;
				coordenada = -1;
			}
			else if(!verificarEntrada()){
				if(verificador == 'r' && (coordenada > filasJuego ||coordenada < 0)){
					ingresarCoordenadas(1, filasJuego);
					coordenada = -1;
				}
				if(verificador == 'c' && (coordenada > columnasJuego || coordenada < 0)){
					ingresarCoordenadas(1, columnasJuego);
					coordenada = -1;
				}
			}
			else
				coordenada = -1;
		}while(coordenada < 0);
		return coordenada -1;
}

void crearEstadisticas(){

	vector<string> fila;
	string linea, palabra; 

	fstream file("estadistica", ios::in);
	if(file.is_open())
	{
		while (getline(file, linea))
		{
			fila.clear();

			stringstream str(linea);

			while(getline(str, palabra, ','))
				fila.push_back(palabra);
			contenidoEstadisticas.push_back(fila);	
		}
	}
	else
	{
		ofstream myfile("estadistica");
		if(myfile.is_open())
		{
			myfile << "Ganadas,0\n";
			myfile << "Perdidas,0\n";
			myfile << "Canceladas,0\n";
			myfile.close();
			crearEstadisticas();
		}
		else cout << "Error al crear el archivo";
	}

	juegosGanados = stoi(contenidoEstadisticas[0][1]);
	juegosPerdidos = stoi(contenidoEstadisticas[1][1]);
	juegosCancelados = stoi(contenidoEstadisticas[2][1]);
}

void iniciarTablero(){

	limpiarTablero();
	ponerMinas();
	calcularMinasAlrededor();
}

void tableroDificultad(int nivel){

	switch (nivel)
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
	}

	banderasRestantesJuego = minasJuego;
}

void abrirCelda(int fila, int columna){

	if(tableroInvisible[fila][columna] == 'M'){
		tableroVisible[fila][columna] = 'x';
		return;
	}
	if(tableroVisible[fila][columna] != 'F')
		mostrarCelda(fila, columna);
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

void ponerTablero(){
	 pintarColumnasArriba();
	 for(int fila = 0; fila < filasJuego; fila++){
		ponerNumerosFila(fila);
		for(int columna = 0; columna < columnasJuego; columna++){
		cout << tableroVisible[fila][columna] << ' ';
		}
		if(activarTruco){
			cout << "     ";
			ponerNumerosFila(fila);
			for(int columna = 0; columna < columnasJuego; columna++){
				cout << tableroInvisible[fila][columna] << ' ';
			}
		}
		cout << "\n";
	 }
}

void pintarColumnasArriba(){

	cout << "     ";
	string separarLinea;
	for(int c = 0; c <(columnasJuego * 2) - 1; c++){
		separarLinea += "-";
	}
	pintarColumnasDecenas();
	if(activarTruco){
		cout << "          ";
		pintarColumnasDecenas();
	}
	cout << "\n";

	cout << "      ";
	pintarColumnasUnidades();
	if(activarTruco){
		cout << "        ";
		pintarColumnasUnidades;
	}
	cout << "\n     " + separarLinea;
	if(activarTruco){
		cout << "            " + separarLinea;
	}
	cout << "\n";
}

void pintarColumnasDecenas(){

	for(int i = 0; i < columnasJuego; i++){
		if(i % 10 == 9){
			cout << ((i + 1) / 10) % 10 << ' ';
		}
		else{
			cout << "  ";
		}
	}
}

void pintarColumnasUnidades(){

	for(int i = 0; i < columnasJuego; i++){
		cout << (i + 1) % 10 << ' ';
	}
}

void menuDificultad(){

	menuInicio();
	cout << endl;
	cout << "seleccione la dificultad del juego:\n";
	cout << "1. Facil \n";
	cout << "2. Medio \n";
	cout << "3. Dificil \n";
}

void menuJuego(){

	menuInicio();
	cout << "Banderas restantes:  " << banderasRestantesJuego;
	cout << "\n*******************************\n\n";
	ponerTablero();
	cout << "\n1. Abrir Celda.\n";
	cout << "2. Poner o quitar bandera.\n";
	cout << "3. Cancelar Juego.\n";

}

void finalizarJuego(){

	cout << "a finalizado el juego. \n";
}

void menuInicio(){

	cout << "*************buscaminas************" << endl;
	
}

void ingresarCoordenadas(int inicio, int fin){

	cout << "ingrese un numero entre " << inicio << " and " << fin << ".\n\n";
}

void menuPrincipal(){

	menuInicio();
	cout << endl;
	cout << "1. Iniciar Juego\n";
	cout << "2. Ver Estadisticas\n";
	cout << "3. Finalizar Aplicacion\n";
}

void mostrarEstadisticas(){

	cout << "digite cualquiere numero paar regresar al menu principal.\n" << endl; 
	menuInicio();
	cout << endl;
	cout << contenidoEstadisticas[0][0] << ": " << juegosGanados << endl; 
	cout << contenidoEstadisticas[1][0] << ": " << juegosPerdidos << endl;
	cout << contenidoEstadisticas[2][0] << ": " << juegosCancelados << endl << endl;

	int entrada;
	do{
		cin >> entrada;
	}while(verificarEntrada());
}

void ponerNumerosFila(int fila){

	if(fila % 10 == 9){
		cout << ((fila + 1) / 10) % 1;
	}
	else{
		cout << ' ';
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

void ponerBandera(int fila, int columna){

	if(tableroVisible[fila][columna] == '.'){
		if(tableroVisible[fila][columna] == 'F'){
			tableroVisible[fila][columna] = '.';
			banderasRestantesJuego++;
		}
		else{
			tableroVisible[fila][columna] = 'F';
			banderasRestantesJuego--;
		}
	}
}

void estadisticas(){

	ofstream myfile ("estadistica");
	if(myfile.is_open())
	{
		myfile << "Ganadas," << juegosGanados << "\n";
		myfile << "Perdidas," << juegosPerdidos << "\n";
		myfile << "Canceladas," << juegosCancelados << "\n";
		myfile.close();
	}
	else cout << "No se puede actualizar estadisticas. \n\n";
}

int verificarEntrada(){

	if(cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Solo puedes ingresar numeros.";
		return -1;
	}
	return 0;
}

void mostrarTableros(){

	for(int fila = 0; fila < filasJuego; fila++){
		for(int columna = 0; columna < columnasJuego; columna++){
			if(tableroVisible[fila][columna] != 'F' && tableroVisible[fila][columna] != 'X')
				tableroVisible[fila][columna] = tableroInvisible[fila][columna];
			if(tableroVisible[fila][columna] == 'F' && tableroInvisible[fila][columna] != 'M')
				tableroVisible[fila][columna] = 'W';	
		}
	}
}