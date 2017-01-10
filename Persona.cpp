#include "Persona.h"
#include <string>


std::string Persona::obtenerNombre ( ) 
{
	return _nombre;
}

std::string Persona::obtenerApellido ( ) 
{
	return _apellido;
}

uint64 Persona::obtenerDni ( ) 
{
	return _dni;
}

uint Persona::obtenerTelefono ( ) 
{
	return _telefono;
}

