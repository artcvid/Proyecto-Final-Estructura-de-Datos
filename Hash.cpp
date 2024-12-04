#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Pelicula.cpp"
#define Archivo "movies_metadata.csv"
using namespace std;

const int TABLE_SIZE = 100000;

// --- Tabla Hash con Doble Hashing ---
class TablaHash {
private:
    Pelicula* tabla[TABLE_SIZE];
    int hash1(int key) const { return key % TABLE_SIZE; }
    int hash2(int key) const { return 7 - (key % 7); }

public:
    vector<Pelicula*> obtenerPeliculas() const {
        vector<Pelicula*> peliculas;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (tabla[i] != nullptr) {
                peliculas.push_back(tabla[i]);
            }
        }
        return peliculas;
    }

    // Inicializador
    TablaHash() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            tabla[i] = nullptr;
        }
    }

    void insertar(int key, const Pelicula& pelicula) {
        int probe = hash1(key);
        int step = hash2(key);

        while (tabla[probe] != nullptr) {
            probe = (probe + step) % TABLE_SIZE;
        }

        tabla[probe] = new Pelicula(pelicula);
    }

    Pelicula* buscar(int id) const {
        int indice = hash1(id);
        int step = hash2(id);

        while (true) {
            if (tabla[indice] && tabla[indice]->id == id) {
                return tabla[indice];
            }
            indice = (indice + step) % TABLE_SIZE;
            if (tabla[indice] == nullptr) break; // Termina si encuentra posición vacía
        }
        return nullptr;
    }


};

// Función para dividir una línea de CSV considerando comillas dobles
vector<string> dividirLineaCSV(const string& linea, char delimitador) {
    vector<string> campos;
    string campo;
    bool entreComillas = false;

    for (char c : linea) {
        if (c == '"') {
            entreComillas = !entreComillas;
        } else if (c == delimitador && !entreComillas) {
            campos.push_back(campo);
            campo.clear();
        } else {
            campo += c;
        }
    }
    campos.push_back(campo);
    return campos;
}

// Función para leer películas desde archivo y cargarlas en la tabla hash
int leerPelicula(TablaHash& tabla) {
    ifstream archivo(Archivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }
    int i = 1;
    string linea, concat;
    getline(archivo, linea); // Saltar encabezado
    concat = linea;

    while (getline(archivo, linea)) {
        vector<string> campos;
        if (linea[0] != 'F' || (linea[0] == ' ' && concat.size() > 2)) {
            concat.append(linea);
            campos = dividirLineaCSV(concat, ',');
        } else {
            concat = linea;
            campos = dividirLineaCSV(concat, ',');
        }

        if (campos.size() < 24 || campos[0] != "False") continue;

        // Extraer los campos deseados
        int id = stoi(campos[5]); // Columna 6: id
        string imdb_id = campos[6]; // Columna 7: imdb_id
        string original_title = campos[8]; // Columna 10: original_title
        string overview = campos[9]; // Columna 11: overview
        float vote_average = stof(campos[22]); // Columna 23: vote_average

        // Insertar película en la tabla hash
        Pelicula pelicula(id, imdb_id, original_title, overview, vote_average);
        tabla.insertar(id, pelicula);
    }

    archivo.close();
    return 0;
}

#endif // HASHTABLE_H
