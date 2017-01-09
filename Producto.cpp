#include "Producto.h"
#include <string>


int Producto::obtenerId() 
{
	return _id;
}

float Producto::obtenerPrecio()
{
	return _precio;
}

char* Producto::obtenerNombre()
{
	return _nombre;
}

int Producto::obtenerCantidad()
{
	return _cantidad;
}
