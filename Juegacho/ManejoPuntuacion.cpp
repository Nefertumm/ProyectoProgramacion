#include "ManejoPuntuacion.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

ManejoPuntuacion::ManejoPuntuacion() 
{
	ifstream archiLeer("puntaje.dat", ios::binary|ios::ate);
	if (!archiLeer.is_open()) 
		return;
	cout << "Leyo el archivo" << endl;
	_puntuaciones.resize(archiLeer.tellg()/sizeof(Puntuacion));
	archiLeer.seekg(0);
	
	for(int i=0;i<int(_puntuaciones.size());i++) 
	{ 
		Puntuacion_Aux aux;
		archiLeer.read(reinterpret_cast<char*>(&aux), sizeof(Puntuacion_Aux));
		cout << "Entro al for" << endl;
		cout << aux._nombre << " AbriendoAux " << aux._puntos << endl;
		_puntuaciones[i] = pasar_a_puntuacion(aux);
		cout << _puntuaciones[i]._nombre << " Abriendo " << _puntuaciones[i]._puntos << endl;
	}
	archiLeer.close();
}

Puntuacion_Aux ManejoPuntuacion::pasar_a_auxiliar(Puntuacion p) 
{
	Puntuacion_Aux aux;
	aux._puntos = p._puntos;
	strcpy(aux._nombre, p._nombre.c_str());
	return aux;
}

Puntuacion ManejoPuntuacion::pasar_a_puntuacion(Puntuacion_Aux aux)
{
	Puntuacion  p;
	p._puntos = aux._puntos;
	p._nombre = aux._nombre;	
	return p;
}

void ManejoPuntuacion::registrarPuntuacion(Puntuacion p)
{
	_puntuaciones.push_back(p);
	sort(_puntuaciones.begin(), _puntuaciones.end());
	reverse(_puntuaciones.begin(), _puntuaciones.end());
	if (int(_puntuaciones.size()) > 5)
		_puntuaciones.resize(5);
	for(int i=0;i<int(_puntuaciones.size());i++) 
		cout << _puntuaciones[i]._nombre << " Guardando " << _puntuaciones[i]._puntos << endl;
	Guardar();
}

void ManejoPuntuacion::Guardar()
{
	ofstream archiGuardar("puntaje.dat", ios::binary|ios::trunc);
	for(int i=0;i<int(_puntuaciones.size());i++) 
	{ 
		Puntuacion_Aux aux;
		aux = pasar_a_auxiliar(_puntuaciones[i]);
		archiGuardar.write(reinterpret_cast<char*>(&aux), sizeof(Puntuacion_Aux));
	}
	archiGuardar.close();
}

ManejoPuntuacion::~ManejoPuntuacion() { }
