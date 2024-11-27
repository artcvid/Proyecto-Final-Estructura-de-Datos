#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#define Archivo "movies_metadata.csv"
using namespace std;

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
    ifstream archivo(Archivo);

    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    string linea;

    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        vector<string> campos = dividirLineaCSV(linea, ',');
        stringstream stream(linea);

        // Verificar que hay suficientes campos para evitar accesos inválidos
        if (campos.size() < 24)
        {
            cerr << "Error: línea con formato incorrecto." << endl;
            continue;
        }

        // Extraer los campos deseados
        string id = campos[5];
        string imdb_id = campos[6];
        string original_title = campos[8];
        string overview = campos[9];
        string vote_average = campos[22];

        // Imprimir los datos extraídos
        cout << "ID: " << id << endl;
        cout << "IMDb ID: " << imdb_id << endl;
        cout << "Título: " << original_title << endl;
        cout << "Descripción: " << overview << endl;
        cout << "Calificación promedio: " << vote_average << endl;
        cout << "-------------------------" << endl;
    }
    

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