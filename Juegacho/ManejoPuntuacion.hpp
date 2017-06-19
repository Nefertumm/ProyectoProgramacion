#ifndef MANEJOPUNTUACION_HPP
#define MANEJOPUNTUACION_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Puntuacion
{
	std::string _nombre;
	int _puntos;
};

inline bool operator<(const Puntuacion &p1, const Puntuacion &p2)
{
	return p1._puntos < p2._puntos;
}

struct Puntuacion_Aux
{
	char _nombre[15];
	int _puntos;
};

class ManejoPuntuacion 
{
protected:
	vector<Puntuacion> _puntuaciones;
public:
	ManejoPuntuacion();
	~ManejoPuntuacion();
	
	Puntuacion_Aux pasar_a_auxiliar(Puntuacion p);
	Puntuacion pasar_a_puntuacion(Puntuacion_Aux aux);
	void registrarPuntuacion(Puntuacion p);
	void Guardar();
	
	int cantPuntajes() { return _puntuaciones.size(); }
	Puntuacion verPuntaje(int i) { return _puntuaciones[i]; }
};

#endif

