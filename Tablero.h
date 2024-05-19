#pragma once
#include "Baldosa.h"
#include "Esfera.h"

#include <vector>

class Tablero {
public:
	std::vector<std::vector<Baldosa>> tablero{
		{std::vector<Baldosa>(6)},
		{std::vector<Baldosa>(7)},
		{std::vector<Baldosa>(8)},
		{std::vector<Baldosa>(9)},
		{std::vector<Baldosa>(10)},
		{std::vector<Baldosa>(11)},
		{std::vector<Baldosa>(10)},
		{std::vector<Baldosa>(9)},
		{std::vector<Baldosa>(8)},
		{std::vector<Baldosa>(7)},
		{std::vector<Baldosa>(6)}
	};

public:
	Tablero();
	void dibujar() const;
};