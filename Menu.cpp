#include <iostream>
#include "Hash.cpp"

using namespace std;

#ifndef __MENU
#define __MENU

// --- Función para limpiar la pantalla ---
void limpiarPantalla()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/MacOS
#endif
}

// --- Función para esperar una tecla ---
void esperarTecla()
{
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(); // Limpiar buffer previo
    cin.get();    // Esperar entrada del usuario
}

// --- Menú de Usuario ---
void menu()
{
    int opcion;
    TablaHash tabla;
    ArbolBinarioBusqueda arbol;

    leerpelis(tabla, arbol); // Cargar datos desde el archivo

    while (true)
    {
        limpiarPantalla(); // Limpia la pantalla antes de mostrar el menú
        cout << "\n--- Menu ---\n";
        cout << "1. Buscar pelicula por ID\n";
        cout << "2. Buscar pelicula por titulo\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            limpiarPantalla();
            cout << "Ingrese el ID de la pelicula: ";
            int id;
            cin >> id;

            Pelicula *pelicula = tabla.buscar(id);
            if (pelicula)
            {
                cout << "Titulo: " << pelicula->original_title << "\n";
                cout << "Calificacion: " << pelicula->vote_average << "\n";
                cout << "Enlace IMDb: https://www.imdb.com/title/" << pelicula->imdb_id << "/\n";
            }
            else
            {
                cout << "Pelicula no encontrada.\n";
            }
            esperarTecla(); // Pausa antes de limpiar
            break;
        }

        case 2:
        {
            limpiarPantalla();
            cin.ignore(); // Limpiar buffer de entrada
            string titulo;
            cout << "Ingrese el titulo de la pelicula: ";
            getline(cin, titulo);

            int p = arbol.buscarNodo(titulo);
            Pelicula *m = tabla.buscar(p);
            if (m)
            {
                cout << "Titulo: " << m->original_title << "\n";
                cout << "Calificacion: " << m->vote_average << "\n";
                cout << "Enlace IMDb: https://www.imdb.com/title/" << m->imdb_id << "/\n";
            }
            else
            {
                cout << "Pelicula no encontrada.\n";
            }
            esperarTecla(); // Pausa antes de limpiar
            break;
        }

        case 3:
            limpiarPantalla();
            cout << "Saliendo del programa...\n";
            return; // Salir del menú

        default:
            limpiarPantalla();
            cout << "Opcion no valida. Intente nuevamente.\n";
            esperarTecla(); // Pausa antes de limpiar
            break;
        }
    }
}

#endif // __MENU
