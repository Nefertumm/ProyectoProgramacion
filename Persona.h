#include <string>

class Persona
{
	public:
		Persona(std::string, std::apellido, uint64 dni, uint tel) : _nombre(nombre), _apellido(apellido), _dni(dni), _telefono(telefono) { }
		
		std::string obtenerNombre();
		std::string obtenerApellido();
		uint64 obtenerDni();
		uint obtenerTelefono();
		
	protected:
		std::string _nombre, _apellido;
		uint64 _dni;
		uint _telefono;
};
