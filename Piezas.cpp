#include "Piezas.h"
#include "stb_stl_loader.h"
#include "freeglut.h"

// Funciones comunes 
Pieza::Pieza(Vector2Dint _pos, Color _color) {
	posTablero = _pos;
	color = _color;
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
Peon::Peon(Vector2Dint _pos, Color _color) : Pieza(_pos, _color) {
	const char* modelo = "gameData/Peon.stl";
	cargarModelo(modelo);
}

Torre::Torre(Vector2Dint _pos, Color _color) : Pieza(_pos, _color) {
	const char* modelo = "gameData/Torre.stl";
	cargarModelo(modelo);
}

Alfil::Alfil(Vector2Dint _pos, Color _color) : Pieza(_pos, _color) {
	const char* modelo = "gameData/Alfil.stl";
	cargarModelo(modelo);
}

Caballo::Caballo(Vector2Dint _pos, Color _color, bool equipo) : Pieza(_pos, _color) {
	if (equipo) {
		const char* modelo = "gameData/Caballo.stl";
		cargarModelo(modelo);
	}
	else {
		const char* modelo = "gameData/CaballoContrario.stl";
		cargarModelo(modelo);
	}
}

Reina::Reina(Vector2Dint _pos, Color _color) : Pieza(_pos, _color) {
	const char* modelo = "gameData/Reina.stl";
	cargarModelo(modelo);
}

Rey::Rey(Vector2Dint _pos, Color _color) : Pieza(_pos, _color) {
	const char* modelo = "gameData/Rey.stl";
	cargarModelo(modelo);
}

// Busca caminos 
