#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Equipo {
private:
    string nombre;
    int puntos;
    int golesAFavor;
    int golesEnContra;

public:
    Equipo(string n) {
        nombre = n;
        puntos = 0;
        golesAFavor = 0;
        golesEnContra = 0;
    }
    string getNombre() const { return nombre; }
    int getPuntos() const { return puntos; }
    int getDiferenciaGoles() const { return golesAFavor - golesEnContra; }
    void agregarPuntos(int p) { puntos += p; }
    void agregarGoles(int aFavor, int enContra) {
        golesAFavor += aFavor;
        golesEnContra += enContra;
    }
};

class Partido {
private:
    Equipo equipo1;
    Equipo equipo2;
    int golesEquipo1;
    int golesEquipo2;

public:
    Partido(Equipo e1, Equipo e2, int g1, int g2)
        : equipo1(e1), equipo2(e2), golesEquipo1(g1), golesEquipo2(g2) {}
    Equipo getEquipo1() const { return equipo1; }
    Equipo getEquipo2() const { return equipo2; }
    int getGolesEquipo1() const { return golesEquipo1; }
    int getGolesEquipo2() const { return golesEquipo2; }
    int getTotalGoles() const { return golesEquipo1 + golesEquipo2; }
};

int main() {
    Equipo equipos[] = {
        Equipo("UNRC"), Equipo("UCC"), Equipo("UTN"),
        Equipo("UNC"),  Equipo("UBP"), Equipo("UES21")
    };

    Partido partidos[] = {
        Partido(equipos[0], equipos[4], 0, 0), Partido(equipos[1], equipos[0], 3, 0),
        Partido(equipos[2], equipos[4], 2, 2), Partido(equipos[3], equipos[5], 3, 1),
        Partido(equipos[4], equipos[5], 2, 1), Partido(equipos[1], equipos[2], 4, 1),
        Partido(equipos[3], equipos[0], 2, 2), Partido(equipos[1], equipos[4], 0, 2),
        Partido(equipos[3], equipos[2], 0, 1), Partido(equipos[2], equipos[0], 0, 1),
        Partido(equipos[1], equipos[3], 2, 1), Partido(equipos[1], equipos[5], 2, 2),
        Partido(equipos[3], equipos[4], 1, 3), Partido(equipos[2], equipos[5], 1, 0),
        Partido(equipos[0], equipos[5], 2, 3)
    };

    int nPartidos = sizeof(partidos) / sizeof(partidos[0]);
    int nEquipos = sizeof(equipos) / sizeof(equipos[0]);

    cout << "## Partidos Ordenados por Cantidad de Goles" << endl;
    cout << "------------------------------------------" << endl;

    //goles dif
    bool intercambio;
    do {
        intercambio = false;
        for (int i = 0; i < nPartidos - 1; i++) {
            if (partidos[i].getTotalGoles() < partidos[i + 1].getTotalGoles()) {
                Partido temp = partidos[i];
                partidos[i] = partidos[i + 1];
                partidos[i + 1] = temp;
                intercambio = true;
            }
        }
    } while (intercambio);

    for (int i = 0; i < nPartidos; i++) {
        cout << partidos[i].getEquipo1().getNombre() << " [" << partidos[i].getGolesEquipo1() << " - " << partidos[i].getGolesEquipo2() << "] "
             << partidos[i].getEquipo2().getNombre() << "  (Total: " << partidos[i].getTotalGoles() << " goles)" << endl;
    }
    cout << "\n" << endl;

    cout << "## Tabla de Posiciones Final" << endl;
    cout << "---------------------------" << endl;

    //puntos tabla
    for (int i = 0; i < nPartidos; i++) {
        for (int j = 0; j < nEquipos; j++) {

            if (equipos[j].getNombre() == partidos[i].getEquipo1().getNombre()) {
                equipos[j].agregarGoles(partidos[i].getGolesEquipo1(), partidos[i].getGolesEquipo2());
                if (partidos[i].getGolesEquipo1() > partidos[i].getGolesEquipo2()) equipos[j].agregarPuntos(3);
                else if (partidos[i].getGolesEquipo1() == partidos[i].getGolesEquipo2()) equipos[j].agregarPuntos(1);
            }

            if (equipos[j].getNombre() == partidos[i].getEquipo2().getNombre()) {
                equipos[j].agregarGoles(partidos[i].getGolesEquipo2(), partidos[i].getGolesEquipo1());
                if (partidos[i].getGolesEquipo2() > partidos[i].getGolesEquipo1()) equipos[j].agregarPuntos(3);
                else if (partidos[i].getGolesEquipo1() == partidos[i].getGolesEquipo2()) equipos[j].agregarPuntos(1);
            }
        }
    }

    do {
        intercambio = false;
        for (int i = 0; i < nEquipos - 1; i++) {
            bool hayQueCambiar = false;
            if (equipos[i].getPuntos() < equipos[i+1].getPuntos() ||
               (equipos[i].getPuntos() == equipos[i+1].getPuntos() && equipos[i].getDiferenciaGoles() < equipos[i+1].getDiferenciaGoles())) {
                hayQueCambiar = true;
            }
            if (hayQueCambiar) {
                Equipo temp = equipos[i];
                equipos[i] = equipos[i+1];
                equipos[i+1] = temp;
                intercambio = true;
            }
        }
    } while (intercambio);

    cout << " 1er Puesto: " << equipos[0].getNombre() << " con " << equipos[0].getPuntos() << " puntos." << endl;
    cout << " 2do Puesto: " << equipos[1].getNombre() << " con " << equipos[1].getPuntos() << " puntos." << endl;
    cout << " 3er Puesto: " << equipos[2].getNombre() << " con " << equipos[2].getPuntos() << " puntos." << endl;

    return 0;
}