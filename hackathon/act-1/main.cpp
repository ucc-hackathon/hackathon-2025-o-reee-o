#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Libro {
private:
    int codigo;
    string titulo;
    string autor;
    int anio;
    string categoria;
    bool prestado;
    int vecesPrestado;

public:
    Libro(int _codigo, string _titulo, string _autor, int _anio, string _categoria)
        : codigo(_codigo), titulo(_titulo), autor(_autor), anio(_anio),
          categoria(_categoria), prestado(false), vecesPrestado(0) {}

    void mostrarLibro() const {
        cout << "==========\n";
        cout << "Codigo: " << codigo << "\n";
        cout << "Titulo: " << titulo << "\n";
        cout << "Autor: " << autor << "\n";
        cout << "Anio: " << anio << "\n";
        cout << "Categoria: " << categoria << "\n";
        cout << "Prestado: " << (prestado ? "Si" : "No") << "\n";
        cout << "Veces prestado: " << vecesPrestado << "\n";
    }

    bool estaPrestado() const { return prestado; }
    string getCategoria() const { return categoria; }
    string getAutor() const { return autor; }
    string getTitulo() const { return titulo; }
    int getVecesPrestado() const { return vecesPrestado; }

    bool prestar() {
        if (!prestado) {
            prestado = true;
            vecesPrestado += 1;
            cout << "Se ha prestado: " << titulo << "\n";
            return true;
        } else {
            cout << "El libro '" << titulo << "' ya esta prestado.\n";
            return false;
        }
    }

    void devolver() {
        if (prestado) {
            prestado = false;
            cout << "Libro devuelto correctamente: " << titulo << "\n";
        } else {
            cout << "El libro no estaba prestado: " << titulo << "\n";
        }
    }
};

class Usuario {
private:
    string nombre;
    long legajo;
    int librosPrestados;

public:
    Usuario(const string& _nombre, long _legajo)
        : nombre(_nombre), legajo(_legajo), librosPrestados(0) {}

    void mostrarUsuario() const {
        cout << "Nombre: " << nombre << "\n";
        cout << "Legajo: " << legajo << "\n";
        cout << "Libros pedidos: " << librosPrestados << "\n";
    }

    string getNombre() const { return nombre; }
    long getLegajo() const { return legajo; }
    int getLibrosPrestados() const { return librosPrestados; }
    void incrementarLibrosPrestados() { ++librosPrestados; }
};

class Alumno : public Usuario {
private:
    string carrera;

public:
    Alumno(const string& _nombre, long _legajo, const string& _carrera)
        : Usuario(_nombre, _legajo), carrera(_carrera) {}

    void mostrarAlumno() const {
        mostrarUsuario();
        cout << "Carrera: " << carrera << "\n";
    }
};

class Profesor : public Usuario {
private:
    string area;

public:
    Profesor(const string& _nombre, long _legajo, const string& _area)
        : Usuario(_nombre, _legajo), area(_area) {}

    void mostrarProfesor() const {
        mostrarUsuario();
        cout << "Area: " << area << "\n";
    }
};

void buscarPorAutor(const vector<Libro> &libros, const string &autor) {
    cout << "=== BUSCAR POR AUTOR: " << autor << " ===\n";
    bool encontro = false;
    for (const Libro &l : libros) {
        if (l.getAutor() == autor) {
            l.mostrarLibro();
            encontro = true;
        }
    }
    if (!encontro) cout << "No existe libro con el autor: " << autor << "\n";
}

void mostrarTopTres(const vector<Libro> &libros) {
    int top1 = -1, top2 = -1, top3 = -1;
    int c1 = -1, c2 = -1, c3 = -1;

    for (int i = 0; i < libros.size(); ++i) {
        int cnt = libros[i].getVecesPrestado();
        if (cnt > c1) {
            c3 = c2; top3 = top2;
            c2 = c1; top2 = top1;
            c1 = cnt; top1 = i;
        } else if (cnt > c2) {
            c3 = c2; top3 = top2;
            c2 = cnt; top2 = i;
        } else if (cnt > c3) {
            c3 = cnt; top3 = i;
        }
    }

    cout << "=== TOP 3 LIBROS MAS PRESTADOS ===\n";
    int mostrados = 0;
    if (top1 != -1 && c1 > 0) {
        cout << "1) " << libros[top1].getTitulo() << " - Veces prestado: " << c1 << "\n";
        ++mostrados;
    }
    if (top2 != -1 && c2 > 0) {
        cout << "2) " << libros[top2].getTitulo() << " - Veces prestado: " << c2 << "\n";
        ++mostrados;
    }
    if (top3 != -1 && c3 > 0) {
        cout << "3) " << libros[top3].getTitulo() << " - Veces prestado: " << c3 << "\n";
        ++mostrados;
    }
    if (mostrados == 0) cout << "No hay libros prestados todavía.\n";
}

bool prestarLibroA(Usuario &u, Libro &l) {
    if (l.prestar()) {
        u.incrementarLibrosPrestados();
        return true;
    }
    return false;
}

void mostrarUsuarioConMasPrestamos(const vector<Usuario*> &usuarios) {
    if (usuarios.empty()) {
        cout << "No hay usuarios.\n";
        return;
    }
    const Usuario* mejor = usuarios[0];
    for (size_t i = 1; i < usuarios.size(); ++i) {
        if (usuarios[i]->getLibrosPrestados() > mejor->getLibrosPrestados())
            mejor = usuarios[i];
    }
    cout << "Usuario con mas libros pedidos:\n";
    cout << mejor->getNombre() << " - Libros pedidos: " << mejor->getLibrosPrestados() << "\n";
}

int main() {
    Alumno alumno1("Santino", 12345, "Informatica");
    Alumno alumno2("Luciana", 22334, "Matematica");
    Profesor prof1("Carlos Perez", 56789, "Ingenieria");
    Profesor prof2("Ana Ruiz", 66778, "Fisica");

    vector<Libro> libros = {
        Libro(1001, "C++ Avanzado",          "Stroustrup",   2015, "Programacion"),
        Libro(1002, "Matematicas 1",         "Perez",        2010, "Matematicas"),
        Libro(1003, "Fisica General",        "Lopez",        2018, "Fisica"),
        Libro(1004, "Algoritmos y Estruct.", "Gonzalez",     2012, "Programacion"),
        Libro(1005, "Calculo I",             "Ramirez",      2009, "Matematicas"),
        Libro(1006, "Quimica Basica",        "Martinez",     2011, "Quimica"),
        Libro(1007, "Introduccion a Redes",  "Vega",         2016, "Informática"),
        Libro(1008, "Bases de Datos",        "Silva",        2014, "Informática"),
        Libro(1009, "Estadistica",           "Fernandez",    2013, "Matematicas"),
        Libro(1010, "Filosofia Moderna",     "Ruiz",         2005, "Humanidades"),
        Libro(1011, "Sistemas Operativos",   "Torres",       2017, "Informática"),
        Libro(1012, "Electrotecnia",         "Castro",       2008, "Ingenieria"),
        Libro(1013, "Metodologia Cientifica","Alvarez",      2019, "Ciencia"),
        Libro(1014, "Analisis de Señales",   "Diaz",         2010, "Ingenieria"),
        Libro(1015, "Historia Universal",    "Molina",       2006, "Historia"),
        Libro(1016, "Historia Universal 2",  "Molina",       2006, "Historia")
    };

    prestarLibroA(alumno1, libros[0]);
    prestarLibroA(alumno1, libros[2]);
    prestarLibroA(alumno1, libros[4]);

    prestarLibroA(prof1, libros[1]);
    prestarLibroA(prof1, libros[10]);
    prestarLibroA(prof1, libros[11]);
    prestarLibroA(prof1, libros[3]);

    prestarLibroA(alumno2, libros[7]);
    prestarLibroA(alumno2, libros[8]);

    prestarLibroA(prof2, libros[15]);

    vector<Usuario*> usuarios = { &alumno1, &alumno2, &prof1, &prof2 };

    cout << "\nEstado actual de usuarios:\n";
    alumno1.mostrarAlumno();
    cout << "\n";
    alumno2.mostrarAlumno();
    cout << "\n";
    prof1.mostrarProfesor();
    cout << "\n";
    prof2.mostrarProfesor();
    cout << "\n";

    mostrarUsuarioConMasPrestamos(usuarios);
    cout << "\n";

    mostrarTopTres(libros);

    buscarPorAutor(libros, "Molina");

    return 0;
}
