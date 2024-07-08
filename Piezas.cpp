#include "Piezas.h"

#include "stb_stl_loader.h"

// Funciones comunes 
Pieza::Pieza(Vector2Dfloat _pos, bool _equipo) {
	posMundo = _pos;
	if (_equipo) {
		equipo = BLANCO;
		color = { 200, 200, 200 };
	}
	else {
		equipo = NEGRO;
		color = { 135, 62, 35 };

	}
}

void Pieza::cargarModelo(const char* modelo) {
	if (!loadSTL(modelo, vertices, normales, posMundo))
		throw std::exception("No se ha podido abrir uno de los modelos!");
}

void Pieza::dibuja() {
	glBegin(GL_TRIANGLES);
	glColor3ub(color.r, color.g, color.b);
	for (int i = 0; i < vertices.size(); i++) {
		glNormal3f(normales[i].x, normales[i].y, normales[i].z);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
}

void Pieza::mover() {
	Vector2Dfloat diff = posMundo - posMundoAnterior;
	if (!sincronia) {
		for (Vector3Dfloat& _vect : vertices) {
			_vect.x = _vect.x + diff.x;
			_vect.y = _vect.y + diff.y;
		}
		sincronia = true;
	}
}

// Inicializaciones
bVacio::bVacio(Vector2Dfloat _pos, bool _equipo) : Pieza(_pos, _equipo) {
	tipo = VACIO;
}

Peon::Peon(Vector2Dfloat _pos, bool _equipo) : Pieza(_pos, _equipo) {
	tipo = PEON;
	const char* modelo;
	if (_equipo)
		modelo = "gameData/modelos/NE555.stl";
	else
		modelo = "gameData/modelos/NE555.stl";
	cargarModelo(modelo);
}

Torre::Torre(Vector2Dfloat _pos, bool _equipo) : Pieza(_pos, _equipo) {
	tipo = TORRE;
	const char* modelo;
	if (_equipo)
		modelo = "gameData/modelos/CAPACITOR.stl";
	else
		modelo = "gameData/modelos/CAPACITOR.stl";
	cargarModelo(modelo);
}

Alfil::Alfil(Vector2Dfloat _pos, bool _equipo) : Pieza(_pos, _equipo) {
	tipo = ALFIL;
	const char* modelo;
	if (_equipo)
		modelo = "gameData/modelos/LED.stl";
	else
		modelo = "gameData/modelos/LED.stl";
	cargarModelo(modelo);
}

Caballo::Caballo(Vector2Dfloat _pos, bool _equipo, bool equipo) : Pieza(_pos, _equipo) {
	tipo = CABALLO;
	const char* modelo;
	if (equipo) 
		modelo = "gameData/modelos/POTENCIOMETROblanco.stl";
	else
		modelo = "gameData/modelos/POTENCIOMETROnegro.stl";
	cargarModelo(modelo);
}

Reina::Reina(Vector2Dfloat _pos, bool _equipo) : Pieza(_pos, _equipo) {
	tipo = REINA;
	const char* modelo;
	if (_equipo)
		modelo = "gameData/modelos/ATMEGA328Pblanco.stl";
	else
		modelo = "gameData/modelos/ATMEGA328Pnegro.stl";
	cargarModelo(modelo);
}

Rey::Rey(Vector2Dfloat _pos, bool _equipo) : Pieza(_pos, _equipo) {
	tipo = REY;
	const char* modelo;
	if (_equipo)
		modelo = "gameData/modelos/TRANSISTORblanco.stl";
	else
		modelo = "gameData/modelos/TRANSISTORnegro.stl";
	cargarModelo(modelo);
}
