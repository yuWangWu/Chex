#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

double pi = 3.14159265;

struct Vector2D {
    double x = 0, y= 0;
};

struct Baldosa {
    Vector2D centro;
    Vector2D e0, e1, e2, e3, e4, e5;
};

Baldosa calcLados(Vector2D centro, float lado);
Vector2D calcCentroDerAbajo(Vector2D original, float lado);
Vector2D calcCentroDerArriba(Vector2D original, float lado);
Vector2D calcCentroArriba(Vector2D original, float lado);
void imprimeBaldosa(Baldosa baldosa);

int main() {
    float lado = 10;
    float altura = sqrt(pow(lado, 2) - pow(lado / 2, 2));

    std::vector<std::vector<Baldosa>> tablero(11, std::vector<Baldosa> (11));

    // Suponemos que el origen de coordenadas esta 
    // en el centro de la baldosa 5, 5.
    // Esto hara que programar las animaciones 
    // sea mas facil en un futuro (o eso espero)

    tablero[0][0].centro = {10 * altura * cos(210 * (pi / 180)), 10 * altura * sin(210 * (pi / 180))};

    for (auto x:{1, 2, 3, 4, 5}) {
        tablero[x][0].centro = calcCentroDerAbajo(tablero[x-1][0].centro, altura);
    }
    for (auto x:{6, 7, 8, 9, 10}) {
        tablero[x][0].centro = calcCentroDerArriba(tablero[x-1][0].centro, altura);
    }
    
    for (auto x:{0, 1, 2, 3, 4, 5}) {
        for (int i = 1; i <= (5 + x); i++) {
            tablero[x][i].centro = calcCentroArriba(tablero[x][i-1].centro, altura);
        }
    }
    for (auto x:{6, 7, 8, 9, 10}) {
        for (int i = 1; i <= (15 - x); i++) {
            tablero[x][i].centro = calcCentroArriba(tablero[x][i-1].centro, altura);
        }
    }

    for (auto x:{0, 1, 2, 3, 4, 5}) {
        for (int i = 0; i <= (5 + x); i++) {
            tablero[x][i] = calcLados(tablero[x][i].centro, lado);
        }
    }
    for (auto x:{6, 7, 8, 9, 10}) {
        for (int i = 0; i <= (15 - x); i++) {
            tablero[x][i] = calcLados(tablero[x][i].centro, lado);
        }
    }

    std::ofstream aristas("datosBaldosas.txt");

    for (auto x:{0, 1, 2, 3, 4, 5}) {
        for (int i = 0; i <= (5 + x); i++) {
            aristas << tablero[x][i].centro.x << " " << tablero[x][i].centro.y << " ";
            aristas << tablero[x][i].e0.x << " " << tablero[x][i].e0.y << " ";
            aristas << tablero[x][i].e1.x << " " << tablero[x][i].e1.y << " ";
            aristas << tablero[x][i].e2.x << " " << tablero[x][i].e2.y << " ";
            aristas << tablero[x][i].e3.x << " " << tablero[x][i].e3.y << " ";
            aristas << tablero[x][i].e4.x << " " << tablero[x][i].e4.y << " ";
            aristas << tablero[x][i].e5.x << " " << tablero[x][i].e5.y << "\n";
        }
    }
    for (auto x:{6, 7, 8, 9, 10}) {
        for (int i = 0; i <= (15 - x); i++) {
            aristas << tablero[x][i].centro.x << " " << tablero[x][i].centro.y << " ";
            aristas << tablero[x][i].e0.x << " " << tablero[x][i].e0.y << " ";
            aristas << tablero[x][i].e1.x << " " << tablero[x][i].e1.y << " ";
            aristas << tablero[x][i].e2.x << " " << tablero[x][i].e2.y << " ";
            aristas << tablero[x][i].e3.x << " " << tablero[x][i].e3.y << " ";
            aristas << tablero[x][i].e4.x << " " << tablero[x][i].e4.y << " ";
            aristas << tablero[x][i].e5.x << " " << tablero[x][i].e5.y << "\n";
        }
    }

    aristas.close();

    return 0;
}

Baldosa calcLados(Vector2D centro, float lado) {
    Baldosa resultado;
    resultado.centro = centro;

    resultado.e0 = {centro.x - lado, centro.y};
    resultado.e1 = {centro.x + lado * cos(120 * (pi / 180)), centro.y + lado * sin(120 * (pi / 180))};
    resultado.e2 = {centro.x + lado * cos(60 * (pi / 180)), centro.y + lado * sin(60 * (pi / 180))};
    resultado.e3 = {centro.x + lado, centro.y};
    resultado.e4 = {centro.x + lado * cos(300 * (pi / 180)), centro.y + lado * sin(300 * (pi / 180))};
    resultado.e5 = {centro.x + lado * cos(240 * (pi / 180)), centro.y + lado * sin(240 * (pi / 180))};

    return resultado;
}

Vector2D calcCentroArriba(Vector2D original, float altura) {
    Vector2D calculado;

    calculado = {original.x, original.y + (altura * 2)};
    return calculado;
}

Vector2D calcCentroDerAbajo(Vector2D original, float altura) {
    Vector2D calculado;

    calculado = {original.x + 2 * altura * cos(330 * (pi / 180)), original.y + 2 * altura * sin(330 * (pi / 180))};
    return calculado;
}

Vector2D calcCentroDerArriba(Vector2D original, float altura) {
    Vector2D calculado;

    calculado = {original.x + 2 * altura * cos(30 * (pi / 180)), original.y + 2 * altura * sin(30 * (pi / 180))};
    return calculado;
}

void imprimeBaldosa(Baldosa baldosa) {
    std::cout << "--- BEGIN ---\n";

    std::cout << "Centro: \t" << baldosa.centro.x << ", " << baldosa.centro.y << "\n";
    std::cout << "e0: \t\t" << baldosa.e0.x << ", " << baldosa.e0.y << "\n";
    std::cout << "e1: \t\t" << baldosa.e1.x << ", " << baldosa.e1.y << "\n";
    std::cout << "e2: \t\t" << baldosa.e2.x << ", " << baldosa.e2.y << "\n";
    std::cout << "e3: \t\t" << baldosa.e3.x << ", " << baldosa.e3.y << "\n";
    std::cout << "e4: \t\t" << baldosa.e4.x << ", " << baldosa.e4.y << "\n";
    std::cout << "e5: \t\t" << baldosa.e5.x << ", " << baldosa.e5.y << "\n";

    std::cout << "--- END ---" << std::endl;
}
