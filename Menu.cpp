#include <iostream>
#include "Hash.cpp"     
#include "BusquedaT.cpp" 
#include <limits>

using namespace std;

#ifndef __MENU
#define __MENU

// --- Función para limpiar la pantalla ---
void limpiarPantalla() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/MacOS
#endif
}

// --- Función para esperar una tecla ---
void esperarTecla() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nPresione ENTER para continuar...";
    cin.get();
}

// --- Menú de Usuario ---
void menu() {
    int opcion;
    TablaHash tabla;

    leerPelicula(tabla); // Cargar datos desde el archivo

    int cantidad;
    TituloID* peliculas = cargarPeliculasDesdeHash(tabla, cantidad);
    quickSort(peliculas, 0, cantidad - 1); // Ordenar por título

    while (true) {
        limpiarPantalla();
        cout << "--- Menu ---\n";
        cout << "1. Buscar pelicula por ID\n";
        cout << "2. Buscar pelicula por titulo\n";
        cout << "3. Buscar por Indice de la tabla Hash: \n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
        case 1: {
            limpiarPantalla();
            cout << "Ingrese el ID de la pelicula: ";
            int id;
            cin >> id;

            Pelicula* pelicula = tabla.buscar(id);
            if (pelicula)
                pelicula->imprimir();
            else
                cout << "Pelicula no encontrada.\n";

            esperarTecla();
            break;
        }
        case 2:
            {
            limpiarPantalla();
                cout << "Ingrese el titulo de la pelicula: ";
                string titulo;
                getline(cin, titulo);
                TituloID* resultado = busquedaBinaria(peliculas, cantidad, titulo);  
                if (resultado) {
                      Pelicula* pelicula = tabla.buscar(resultado->id);
                          if (pelicula) {
                         pelicula->imprimir();  
                         } else {
                 cout << "Pelicula no encontrada en la base de datos.\n";
                      }
              } else {
        cout << "Pelicula no encontrada por título.\n";
    }
    esperarTecla();  
    break;
}

            case 3: {
            int indice;
            cout << "Digite el indice de la pelicula: " << endl;
            cin >> indice;

            Pelicula* pelicula = tabla.buscar(indice);
            if (pelicula)
                pelicula->imprimir();
            else
                cout << "Pelicula no encontrada.\n";

            esperarTecla();
            break;
        }

        case 4: {
            delete[] peliculas; // Liberar memoria dinámica
            limpiarPantalla();
            cout << "Saliendo del programa...\n";
            return; // Salir del menú
        }
        default: {
            limpiarPantalla();
            cout << "Opcion no valida. Intente nuevamente.\n";
            esperarTecla(); // Pausa antes de limpiar
            break;
        }
        }
    }
}

#endif // __MENU
