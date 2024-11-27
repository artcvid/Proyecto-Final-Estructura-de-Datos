#include <iostream>
#include "Hash.cpp"

using namespace std;

#ifndef __MENU
#define __MENU

// --- Menú de Usuario ---
void menu()
{
    int opcion;
    TablaHash tabla;
    ArbolBinarioBusqueda arbol;

    leerpelis(tabla, arbol);

    while (1)
    {
        cout << "\n--- Menú ---\n";
        cout << "1. Buscar película por ID\n";
        cout << "2. Buscar película por título\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            cout << "Ingrese el ID de la película: ";
            int id;
            cin >> id;

            Pelicula *pelicula = tabla.buscar(id);
            if (pelicula)
            {
                cout << "Título: " << pelicula->original_title << "\n";
                cout << "Calificación: " << pelicula->vote_average << "\n";
                cout << "Enlace IMDb: https://www.imdb.com/title/" << pelicula->imdb_id << "/\n";
            }
            else
            {
                cout << "Película no encontrada.\n";
            }
            break;
        }

        case 2:
        {
            cin.ignore();
            string titulo;
            cout << "Ingrese el título de la película: ";
            getline(cin, titulo);
            int p = arbol.buscarNodo(titulo);
            Pelicula *m = tabla.buscar(p);
            if (m)
            {
                cout << "Título: " << m->original_title << "\n";
                cout << "Calificación: " << m->vote_average << "\n";
                cout << "Enlace IMDb: https://www.imdb.com/title/" << m->imdb_id << "/\n";
            }
            else
            {
                cout << "Película no encontrada.\n";
            }
            break;
        }

        default:
            break;
        }
    };
}

#endif // __MENU