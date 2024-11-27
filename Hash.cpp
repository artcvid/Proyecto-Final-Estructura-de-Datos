
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Arbol.cpp"
#include "Pelicula.cpp"
#define Archivo "movies_metadata.csv"
using namespace std;

const int TABLE_SIZE = 100000;

// --- Tabla Hash con Doble Hashing ---
class TablaHash
{
private:
    Pelicula *tabla[TABLE_SIZE];
    // bool ocupada[TABLE_SIZE] = {false}; // Rastrea posiciones ocupadas

    int hash1(int key) const { return key % TABLE_SIZE; }
    int hash2(int key) const { return 7 - (key % 7); }

public:
    // Inicializador
    TablaHash()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            tabla[i] = nullptr;
        }
    }

    void insertar(int key, const Pelicula &pelicula)
    {
        int probe = hash1(key);
        int step = hash2(key);

        while (tabla[probe] != nullptr)
        {
            probe = (probe + step) % TABLE_SIZE;
        }

        tabla[probe] = new Pelicula(pelicula);
        // ocupada[probe] = true;
    }

    Pelicula *buscar(int id) const
    {
        int indice = hash1(id);
        int step = hash2(id);

        while (1)
        {
            if (tabla[indice] && tabla[indice]->id == id)
            {
                return tabla[indice];
            }
            indice = (indice + step) % TABLE_SIZE;
        }
        return nullptr;
    }
};

// Función para dividir una línea de CSV considerando comillas dobles
vector<string> dividirLineaCSV(const string &linea, char delimitador)
{
    vector<string> campos;
    string campo;
    bool entreComillas = false;

    for (char c : linea)
    {
        if (c == '"')
        {
            entreComillas = !entreComillas; // Cambiar estado de las comillas
        }
        else if (c == delimitador && !entreComillas)
        {
            campos.push_back(campo);
            campo.clear();
        }
        else
        {
            campo += c;
        }
    }

    // Agregar el último campo
    campos.push_back(campo);

    return campos;
}

int leerpelis(TablaHash &tabla, ArbolBinarioBusqueda &arbol)
{
    //    TablaHash tabla;
    ifstream archivo(Archivo);

    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    string linea;

    getline(archivo, linea);
    int i = 1;
    while (getline(archivo, linea))
    {
        vector<string> campos = dividirLineaCSV(linea, ',');
        stringstream stream(linea);

        // Verificar que hay suficientes campos para evitar accesos inválidos
        if (campos.size() < 24)
        {
            //    cerr << "Error: línea con formato incorrecto." << endl;
            i++;
            continue;
        }
        else if (campos[0] != "False")
        {
            // cerr << "Error: línea con formato incorrecto." << endl;
            i++;
            continue;
        }

        else
        {
            // Extraer los campos deseados
            string idi = campos[5]; // Columna 6: id
            int id = stoi(idi);
            i++;
            string imdb_id = campos[6];        // Columna 7: imdb_id
            string original_title = campos[8]; // Columna 10: original_title
            string overview = campos[9];       // Columna 11: overview
            string vote_average = campos[22];  // Columna 23: vote_average
            float vote_averag = stof(vote_average);

            // Insertar los datos en el arreglo de estructuras.
            Pelicula pelicula(id, imdb_id, original_title, overview, vote_averag);
            tabla.insertar(id, pelicula);
            arbol.insertarNodo(id, original_title);
        }
    }
    archivo.close();
    return 0;
}

#endif // HASHTABLE_H
