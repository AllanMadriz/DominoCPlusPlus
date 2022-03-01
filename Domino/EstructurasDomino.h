#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Domino
{
	int izquierda;
	int derecha;

};

struct Jugador
{
	string nombreJugador;
	vector<Domino> manoJugador;
};