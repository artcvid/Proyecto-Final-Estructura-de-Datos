#include <iostream>
#include "Hash.cpp"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    TablaHash tabla;
    ArbolBinarioBusqueda arbol;
    leerpelis(tabla, arbol);
    menu(tabla, arbol);

    return 0;
}