#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto
{
	public:
		Producto(int id, int cantidad, float precio, char* nombre) : _id(id), _cantidad(cantidad), _precio(precio), _nombre(nombre) { }
		
		int obtenerId();
		float obtenerPrecio();
		char* obtenerNombre();
		int obtenerCantidad();
		
		
		
	protected:
		int _id, _cantidad;
		float _precio;
		char* _nombre;
};

#endif
