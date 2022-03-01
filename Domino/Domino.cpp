#include "FuncionesDomino.h"  //Incluimos a la hoja funciones en el proyecto actual
							  //ahi contamos con todo el desarrollo del trabajo

int main()
{
	//Se pasa a crear las variables necesarias, seguido de los vectores tambien
	string opcion;
	int turno, pasoTurno = 0;
	int pos1, pos2, pos3, pos4;
	vector<Domino> vectDomino(28);
	vector<Jugador> vectJugador(4);
	vector<Domino> vectTablero(0);
	//Se mostrar un chico menu para iniciar el juego
	do {
		
		do
		{
			system("cls");
			cout << "\n\n\t1 - Nuevo Juego"
				<< "\n\t2 - Salir del Programa\n\n\t";
			cin >> opcion;
		} while (!revisaSiEsNumero(opcion)); //Revisamos que no este intentado pasar una letra, unicamente numeros

		switch (stoi(opcion))
		{
		case 1:
			//Al iniciar el juego se llaman los metodos preparativos del juego
			turno = 0;
			vectTablero.resize(0); //Por cuestiones de desbordes volvemos a cambiar el size del vector en caso de que fuera modificado
			crearDomino(vectDomino); //Creamos el domino
			crearJugadores(vectJugador, vectDomino); //Creamos a los jugadores y su fichas
			sortearTurnos(pos1, pos2, pos3, pos4); //Sorteamos el orden en que jugaran los jugadores 
			system("cls");

			do {
				switch (turno) //Segun el case se llama al metodo funcionCases, donde se encuentran todas las funciones necesarias
				{
				case 0:
					pasoTurno = 0; //Volvemos a poner en 0 a pasoTurno, para reiniciar el conteo
					funcionCases(pasoTurno, turno, pos1, vectJugador, vectTablero);
					break;

				case 1:
					funcionCases(pasoTurno, turno, pos2, vectJugador, vectTablero);
					break;

				case 2:
					funcionCases(pasoTurno, turno, pos3, vectJugador, vectTablero);
					break;

				case 3:
					funcionCases(pasoTurno, turno, pos4, vectJugador, vectTablero);
					turno = 0;
					break;
				}
			} while (pasoTurno != 4); //Finaliza al cambiar la variable pasoTurno por 4

			ganador(vectJugador); //Metodo para deducir al ganador
			break;
		case 2:
			system("cls");
			cout << "\n\n\tFinalizando Programa...\n\n\t"; //Informamos que se esta cerrando el programa
			system("pause");
			break;

		default:
			system("cls");
			cout << "\n\n\tDigite una Opcion Valida...\n\n\t"; //Informamos que debe elegir una opcion correcta
			system("pause");
			break;
		}

	} while (stoi(opcion) != 2);

	return 0;
}
