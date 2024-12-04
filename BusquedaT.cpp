#include <iostream>
#include <vector>
#include <algorithm>
#include "Pelicula.cpp"
#include "Hash.cpp"

using namespace std;

struct TituloID
{
    int id;
    string titulo;
};

// Función para copiar datos desde la tabla hash y almacenarlos en un arreglo dinámico
TituloID *cargarPeliculasDesdeHash(TablaHash &tabla, int &cantidad)
{
    vector<Pelicula *> peliculas = tabla.obtenerPeliculas();
    cantidad = peliculas.size();

    TituloID *arreglo = new TituloID[cantidad];
    for (int i = 0; i < cantidad; ++i)
    {
        arreglo[i].id = peliculas[i]->id;
        arreglo[i].titulo = peliculas[i]->original_title; // Ajusta el nombre del campo
    }
    return arreglo;
}

// Implementación del algoritmo QuickSort para ordenar por título
void quickSort(TituloID *arreglo, int izquierda, int derecha)
{
    if (izquierda >= derecha)
        return;
    int pivote = izquierda + (derecha - izquierda) / 2;
    string pivoteTitulo = arreglo[pivote].titulo;

    int i = izquierda, j = derecha;
    while (i <= j)
    {
        while (arreglo[i].titulo < pivoteTitulo)
            i++;
        while (arreglo[j].titulo > pivoteTitulo)
            j--;
        if (i <= j)
        {
            swap(arreglo[i], arreglo[j]);
            i++;
            j--;
        }
    }
    quickSort(arreglo, izquierda, j);
    quickSort(arreglo, i, derecha);
}

// Búsqueda binaria por título
TituloID *busquedaBinaria(TituloID *arreglo, int cantidad, const string &titulo)
{
    int izquierda = 0, derecha = cantidad - 1;
    while (izquierda <= derecha)
    {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (arreglo[medio].titulo == titulo)
        {
            return &arreglo[medio];
        }
        else if (arreglo[medio].titulo < titulo)
        {
            izquierda = medio + 1;
        }
        else
        {
            derecha = medio - 1;
        }
    }
    return nullptr;
}