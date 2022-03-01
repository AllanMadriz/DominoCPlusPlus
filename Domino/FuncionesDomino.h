#pragma once
#include <string>
#include <stdlib.h>		//Llamamos las librerias necesarias
#include <time.h>
#include "EstructurasDomino.h" //incluimos las Estructura del Domino
//Metodo para revisar que el dato pasado sea un numero
bool revisaSiEsNumero(string elNumero) {
	//Crea una variable booleana en true
	bool revision = true;
	//En caso de encontrar una letra se convierte en false
	for (int i = 0; i < elNumero.length(); i++)
	{
		if (!isdigit(elNumero[i])) {
			revision = false;
		}
	}
	//Retorna esa variable
	return revision;
}
//Metodo para crear el Domino
void crearDomino(vector<Domino> &vectDomino) {
	//Creamos las variables a manejar en el programa
	int cont = 0, numIzq = 0, inicio = 0, limit = 7, numDere = 0;
	//Se crea un for hasta que sea menor al 28 que seran el total de fichas
	for (int i = 0; i < 28; i++)
	{
		//Cada ficha tendra su inicio con el numIzq y el numDere
		vectDomino[i].izquierda = numIzq;
		vectDomino[i].derecha = numDere;
		numDere++; //Por iteracion se aumenta el numeroDere
		cont++; //Por iteracion se aumenta el cont
		if (cont == limit) { //Si cont es igual a limit
			cont = 0;	//Cont pasa a ser 0
			limit--; //Limit se reduce en 1 (El inicio de limit es 7)
			inicio++; //Se aumenta inicio
			numIzq = inicio; //NumIzq se convierte en inicio
			numDere = inicio; //NumDere se convierte en inicio
		}
	}
}
//Metodo para repartir fichas
void repartirFichas(vector<Domino> &vectDomino, vector<Jugador>& jugador, int pos) {

	int numRandom;	//Variable a trabajar el numero random
	srand(time(NULL)); 
	//Creamos un for
	for (int i = 0; i < 7; i++)
	{	//Se genera el random
		numRandom = rand() % vectDomino.size();
		jugador[pos].manoJugador.push_back(vectDomino[numRandom]); //Se inserta en la mano del jugador
		vectDomino.erase(vectDomino.begin() + numRandom); //Se elimina esa posicion del vector de domino
	}
}
//Metodo para crear jugadores
void crearJugadores(vector<Jugador> &vectJugador, vector<Domino> &vectDomino) {
	//Se crea la variable nombre
	string nombre = "";
	cin.ignore(); //Se limpia el residuo que pudo quedar de anteriores inputs
	//Se crea un bucle que pasa por cada jugador
	for (int i = 0; i < 4; i++)
	{	//Se les solicita el nombre que tendra cada uno
		system("cls");
		cout << "\n\n\tNombre para el jugador " << i + 1 << ":\n\t";
		getline(cin, nombre);
		vectJugador[i].nombreJugador = nombre; //Se le asigna el nombre al elemento de la estructura
		repartirFichas(vectDomino, vectJugador, i); //Se le reparten las fichas con las que jugara
	}

}
//Metodo para sortear turnos
void sortearTurnos(int &pos1, int& pos2, int& pos3, int& pos4) {

	vector<int> posicion = { 0,1,2,3 }; //Se colocan las posiciones que tendran 
	int i; //Se crea lo que sera el numero random
	srand(time(NULL));
	
	i = rand() % posicion.size(); //Se general numero random 
	pos1 = posicion[i]; //Se le da el digito que se encuentre en esa posicion del vector
	posicion.erase(posicion.begin() + i); //Se borra ese digito

	i = rand() % posicion.size();
	pos2 = posicion[i];
	posicion.erase(posicion.begin() + i);

	i = rand() % posicion.size();
	pos3 = posicion[i];
	posicion.erase(posicion.begin() + i);

	pos4 = posicion[0]; //Como solo queda un digito es el que se le asigna
}
//Metodo para mostrar mano
void mostrarMano(vector<Jugador> &vectJugador, int pos) {
	//Mostramos que jugador esta actualmente presente
	cout << "\n\tMano Jugador: " << vectJugador[pos].nombreJugador << "\n\n\t";
	for (int i = 0; i < vectJugador[pos].manoJugador.size(); i++) //Se crea un for para recorre todas las fichas
	{	//Imprimimos la ficha completa en cada for
		cout << i + 1 << ".[" << vectJugador[pos].manoJugador[i].izquierda << "|" 
			 << vectJugador[pos].manoJugador[i].derecha << "]  ";
	}
	cout << endl;
}
//Metodo para mostrar tablero
void mostrarTablero(vector<Domino> vectDomino) {
	//Creamos las variables necesarias
	int cont = 0, filas = 0;
	//Se crea un for del tamanio del tablero
	for (int i = 0; i < vectDomino.size(); i++)
	{	//Se muestra la ficha completa, tanto izquierda como derecha
		cout << "[" << vectDomino[i].izquierda << "|" << vectDomino[i].derecha << "] ";
		cont++; //Se aumentara el contador
		if (filas < 3) { //Si filas es menor a 3 
			if (cont == 7) { // Si el contador no ha llegado a 7, se manejan las filas de a 7 para mayor orden
				cout << endl;
				for (int i = 0; i < 6; i++)	//Se crea un for para imprimir espacios una cantidad de veces
				{
					cout << "      ";
				}
				cout << "   " << char(24) << "\n"; //Imprimimos una flecha hacia arriba
				cout << " "; 
				cout << char(218); //Imprimimos una figura para conectar la flecha anterior
				for (int i = 0; i < 6; i++)	//Imprimimos una linea una cantidad de veces
				{
					cout << "------";
				}
				cout << "-" << char(217);	//Imprimimos una figura para conectar la flecha anterior
				cout << "\n " << char(25) << "\n"; //Imprimimos una flecha hacia arriba
				cont = 0;	//Cont se convierte en 0
				filas++; //Se aumenta las filas
			}
		}
	}

	cout << "\n\n";
}
//Metodo para comprobar si el jugador tiene movimientos validos 
bool comprobarMovimientos(vector<Jugador> vectJugador, int pos, vector<Domino> vectTablero) {
	//Creamos dos variables para manejar 
	int tamanioMano = vectJugador[pos].manoJugador.size(), cont = 0;
	int tamanioTablero = vectTablero.size() - 1;
	bool movimiento = false; //Creamos un booleano para saber si tiene movimientos

	do {
		if (vectJugador[pos].manoJugador[cont].izquierda == vectTablero[tamanioTablero].derecha) {	//Si el lado izquierdo es igual
			movimiento = true;	//Moviento se vuelve en true
			cont = tamanioMano; //Cont nos saca del bucle
		}
		else if (vectJugador[pos].manoJugador[cont].derecha == vectTablero[tamanioTablero].derecha) { //Si el lado derecho es igual
			movimiento = true; //El movimiento se vuelve en true
			cont = tamanioMano; //cont nos saca del bucle
		}
		else if (vectJugador[pos].manoJugador[cont].izquierda == vectTablero[0].izquierda) {
			movimiento = true; //El movimiento se vuelve en true
			cont = tamanioMano; //cont nos saca del bucle
		}
		else if (vectJugador[pos].manoJugador[cont].derecha == vectTablero[0].izquierda) {
			movimiento = true; //El movimiento se vuelve en true
			cont = tamanioMano; //cont nos saca del bucle
		}
		cont++; //Si no se cumple ninguna cont aumenta 
	} while (cont < tamanioMano); //Salimos cuando cont es del tamanio de la mano

	return movimiento; //Devolvemos el boolean
}
//Metodo para averiguar el tamanio de la mano
int tamanioMano(vector<Jugador> vectJugador, int pos) {
	//Retornamos el tamanio de la mano del jugador 
	return vectJugador[pos].manoJugador.size();

}
//Metodo para colocar las fichas del jugador
void colocarFichas(vector<Jugador> &vectJugador, int pos, int &pasoTurno, vector<Domino> &vectTablero){
	//Creamos las variables necesarias para trabajar en metodo
	int cambio = 0, op = 0, correcto = 0;
	string opString; 
	//Si es la primera ficha a colocar
	if (vectTablero.size() == 0) {
		do {
			do {
				system("cls");
				mostrarTablero(vectTablero);	//Mostramos tablero
				mostrarMano(vectJugador, pos);	//Mostramos Mano
				cout << "\n\n\tSeleccione la ficha que desea colocar: ";
				cin >> opString;	//Solicitamos la ficha que desea el jugador
			} while (!revisaSiEsNumero(opString)); //Se repite hasta que sea un numero correcto y no pasen letras
			op = stoi(opString); //Se le asigna ese string a un int para un manejo mas facil
		} while (op < 1 || op > vectJugador[pos].manoJugador.size());	//Lo anterior se repite hasta que las opciones esten en el rango de fichas
		op = op - 1; //Se le restara 1 porque el usuario ve el dato con un numero extra, ejem: opcion 1 --> posicion 0 del vector
		vectTablero.push_back(vectJugador[pos].manoJugador[op]); //Esa opcion se le coloca al tablero
		vectJugador[pos].manoJugador.erase(vectJugador[pos].manoJugador.begin() + op); //Esa opcion se elimina de la mano del jugador
	}
	else if (comprobarMovimientos(vectJugador, pos, vectTablero)) { //Comprobamos que el jugador tenga algun movimiento valido
		do {
			do {
				do {
					system("cls");	
					mostrarTablero(vectTablero); //Mostramos tablero
					mostrarMano(vectJugador, pos); //Mostramos mano
					cout << "\n\tSeleccione la ficha que desea colocar:  ";
					cin >> opString; //Solicitamos la ficha que desea el jugador
				} while (!revisaSiEsNumero(opString)); //Se repite hasta que sea un numero correcto y no pasen letras
				op = stoi(opString);  //Se le asigna ese string a un int para un manejo mas facil
			} while (op < 1 || op > vectJugador[pos].manoJugador.size());  //Lo anterior se repite hasta que las opciones esten en el rango de fichas
			correcto = 0; //La variable correcto se coloca en 0
			op = op - 1; //Se le disminuye a op 1

			if (vectJugador[pos].manoJugador[op].izquierda == vectTablero[vectTablero.size() - 1].derecha) { //si la izquierda coincide
				vectTablero.push_back(vectJugador[pos].manoJugador[op]); //se coloca la ficha en el tablero
				vectJugador[pos].manoJugador.erase(vectJugador[pos].manoJugador.begin() + op); //Se elimina de la mano del jugador
				correcto = 1; //Correcto se coloca en 1
			}
			else if (vectJugador[pos].manoJugador[op].derecha == vectTablero[vectTablero.size() - 1].derecha) { //Si la derecha coincide
				cambio = vectJugador[pos].manoJugador[op].derecha; //Se guarda el valor de la dercha en la variable cambio
				vectJugador[pos].manoJugador[op].derecha = vectJugador[pos].manoJugador[op].izquierda; //La derecha ahora tendra el valor de la izquierda
				vectJugador[pos].manoJugador[op].izquierda = cambio; //Y ahora la izquierda sera el valor de cambio (derecha)
				vectTablero.push_back(vectJugador[pos].manoJugador[op]); //Se agrega al tablero
				vectJugador[pos].manoJugador.erase(vectJugador[pos].manoJugador.begin() + op); //Se elimina de la mano del jugador
				correcto = 1; //Correcto se coloca en 1
			}
			else if (vectJugador[pos].manoJugador[op].derecha == vectTablero[0].izquierda) {
				vectTablero.insert(vectTablero.begin() ,vectJugador[pos].manoJugador[op]); //se coloca la ficha en el tablero
				vectJugador[pos].manoJugador.erase(vectJugador[pos].manoJugador.begin() + op); //Se elimina de la mano del jugador
				correcto = 1; //Correcto se coloca en 1
			}
			else if (vectJugador[pos].manoJugador[op].izquierda == vectTablero[0].izquierda) {
				cambio = vectJugador[pos].manoJugador[op].derecha; //Se guarda el valor de la dercha en la variable cambio
				vectJugador[pos].manoJugador[op].derecha = vectJugador[pos].manoJugador[op].izquierda; //La derecha ahora tendra el valor de la izquierda
				vectJugador[pos].manoJugador[op].izquierda = cambio; //Y ahora la izquierda sera el valor de cambio (derecha)
				vectTablero.insert(vectTablero.begin(), vectJugador[pos].manoJugador[op]); //Se agrega al tablero
				vectJugador[pos].manoJugador.erase(vectJugador[pos].manoJugador.begin() + op); //Se elimina de la mano del jugador
				correcto = 1; //Correcto se coloca en 1
			}
			else {
				cout << "\n\tEsa ficha no esta permitida!\n\t"; //Informamos que esa ficha no encaja 
				system("pause");
			}
		} while (correcto == 0); //Se repite mientras correcto sea 0
	}
	else {
		mostrarTablero(vectTablero); 
		mostrarMano(vectJugador, pos);
		cout << "\n\tNo tiene ningun movimiento valido!\n\n\t"; //Informamos que no tiene ningun movimiento
		pasoTurno++; //Pasa turno
		system("pause"); 
	}

	if (tamanioMano(vectJugador, pos) == 0) { //Si la mano es 0 significa que gano
		pasoTurno = 4; //Se le asigna 4 de valor
	}

}
//Metodo para averiguar la suma de las fichas en la mano
int sumaMano(vector<Jugador> vectJugador, int pos) {
	//Creamos la varible a utilizar
	int sumaMano = 0;
	//Se crea un for por el tamanio de la mano del jugador
	for (int i = 0; i < vectJugador[pos].manoJugador.size(); i++)
	{	//Se van sumando la izquierda y la derecha
		sumaMano = sumaMano + vectJugador[pos].manoJugador[i].derecha + vectJugador[pos].manoJugador[i].izquierda;
	}
	//Retornamos la suma de la mano
	return sumaMano;
}
//Metodo para mostrar el menu del que hara uso el jugador
int menuJugador() {

	int op;
	system("cls");
	cout << "\n\n\t1 - Colocar ficha"
		 << "\n\t2 - Pasar Turno\n";
	cin >> op;

	return op;
}
//Metodo para deducir al ganador, segun su suma de mano
void ganador(vector<Jugador> vectJugador) {
	//Se crea un objeto jugador que sera igual al primero del vector jugador
	Jugador jugador = vectJugador[0];
	int aux = sumaMano(vectJugador, 0); //Un int aux que tendra la suma mano del primer jugador
	//Se crea un for que pasa por cada jugador
	for (int i = 1; i < vectJugador.size(); i++)
	{	//Calculamos sumas, cambiamos al objeto y aux en caso de que sean menores
		if (aux > sumaMano(vectJugador, i)) {
			jugador = vectJugador[i];
			aux = sumaMano(vectJugador, i);
		}
	}

	system("cls");
	cout << "\n\n\tEl Ganador del Juego es: " << jugador.nombreJugador << "\n\n\t"; //Mostramos al ganador, el que tenga menos suma de las fichas en mano
	system("pause");
}
//Metodo para hacer el funcionamiento de los cases
void funcionCases(int &pasoTurno, int &turno, int pos, vector<Jugador> &vectJugador, vector<Domino> &vectTablero) {

	system("cls");
	colocarFichas(vectJugador, pos, pasoTurno, vectTablero); //Se llaman al metodo colocar fichas
	system("cls");
	mostrarTablero(vectTablero); //Mostramos el tablero
	mostrarMano(vectJugador, pos); //Mostramos la mano
	cout << "\n\t";
	system("pause");
	turno++; //Se pasa al siguiente turno

}
