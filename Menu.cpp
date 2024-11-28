#include <iostream>
#include "Hash.cpp"
#include <limits>
#include <ios>

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nPresione ENTER para continuar...";
    cin.get();
}

// --- Menú de Usuario ---
void menu()
{
    int opcion;
    TablaHash tabla;
    ArbolBinarioBusqueda arbol;

    leerPelicula(tabla, arbol); // Cargar datos desde el archivo

    while (true)
    {
        limpiarPantalla();
        cout << "--- Menu ---\n";
        cout << "1. Buscar pelicula por ID\n";
        cout << "2. Buscar pelicula por titulo\n";
        cout << "3. Buscar por Indice de la tabla Hash: \n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                pelicula->imprimir();
            else
                cout << "Pelicula no encontrada.\n";

            esperarTecla();
        }
        case 2:
        {
            limpiarPantalla();
            // cin.ignore(); // Limpiar buffer de entrada
            string titulo;
            cout << "Ingrese el titulo de la pelicula: ";
            getline(cin, titulo);
            int p = arbol.buscarNodo(titulo);
            Pelicula *pelicula = tabla.buscar(p);

            if (pelicula)
                pelicula->imprimir();
            else
                cout << "Pelicula no encontrada.\n";

            esperarTecla(); // Pausa antes de limpiar
            break;
        }
        case 3:
        {
            int indice;
            cout << "Digite el indice de la pelicula: " << endl;
            cin >> indice;

            Pelicula *pelicula = tabla.buscar(indice);
            if (pelicula)
                pelicula->imprimir();
            else
                cout << "Pelicula no encontrada.\n";

            break;
        }
        case 4:
        {

            limpiarPantalla();
            cout << "Saliendo del programa...\n";
            return; // Salir del menú
            break;
        }
        default:
        {
            limpiarPantalla();
            cout << "Opcion no valida. Intente nuevamente.\n";
            esperarTecla(); // Pausa antes de limpiar
            break;
        }
        }
    }
}

#endif // __MENU
