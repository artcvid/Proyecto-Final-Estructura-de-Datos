
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#define Archivo "movies_metadata.csv"
using namespace std;

// --- Estructura Pelicula ---
struct Pelicula
{
    int id;
    string imdb_id;
    string original_title;
    string overview;
    float vote_average;

    Pelicula(int _id, string _imdb, string _title, string _overview, float _vote)
        : id(_id), imdb_id(_imdb), original_title(_title), overview(_overview), vote_average(_vote) {}
};
// --- Tabla Hash con Doble Hashing ---
class TablaHash
{
private:
    static const int TABLE_SIZE = 100000;
    Pelicula *tabla[TABLE_SIZE];
    bool ocupada[TABLE_SIZE] = {false}; // Rastrea posiciones ocupadas

    int hash1(int id) const { return id % TABLE_SIZE; }
    int hash2(int id) const { return 1 + (id % (TABLE_SIZE - 1)); }

public:
    TablaHash()
    {
        fill(tabla, tabla + TABLE_SIZE, nullptr);
    }

    void insertar(int id, const Pelicula &pelicula)
    {
        int indice = hash1(id);
        int step = hash2(id);

        while (ocupada[indice])
        {
            indice = (indice + step) % TABLE_SIZE;
        }

        tabla[indice] = new Pelicula(pelicula);
        ocupada[indice] = true;
    }

    Pelicula *buscar(int id) const
    {
        int indice = hash1(id);
        int step = hash2(id);

        while (ocupada[indice])
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

int leerpelis()
{
    TablaHash tabla;
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
            cerr << "Error: línea con formato incorrecto." << endl;
            i++;
            continue;
        }
        else if (campos[0] != "False")
        {
            cerr << "Error: línea con formato incorrecto." << endl;
            i++;
            continue;
        }

        else
        {
            // Extraer los campos deseados
            string idi = campos[5];       // Columna 6: id
            int id = stoi(idi);                 i++;
            string imdb_id = campos[6];             // Columna 7: imdb_id
            string original_title = campos[8];      // Columna 10: original_title
            string overview = campos[9];            // Columna 11: overview
            string vote_average = campos[22];       // Columna 23: vote_average
            float vote_averag = stof(vote_average); // Cambiado a float para vote_average

            // Insertar los datos en el arreglo de estructuras.
            Pelicula pelicula(id, imdb_id, original_title, overview, vote_averag);
            tabla.insertar(id, pelicula);
        }
    }

    Pelicula *peli = tabla.buscar(461257);
    cout << peli->original_title << endl;

    archivo.close();
    return 0;
}

int main()
{
    cout << "Hola mundo, emi es una buena persona" << endl;
    cout << "Hola mundo, Emi es un pendejo" << endl;
    leerpelis();

    return 0;
}

#endif // HASHTABLE_H
