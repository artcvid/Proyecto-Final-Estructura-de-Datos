#include <iostream>
#include "ListaDoble.cpp"
using namespace std;

#ifndef _HASHENCADENADO
#define _HASHENCADENADO

const int HASH_SIZE = 100;

class HashEncadenado {
private:
    ListaDoble* tabla[HASH_SIZE];

    int hashFuncion(int clave) {
        return clave % HASH_SIZE;
    }

public:
    HashEncadenado() {
        for (int i = 0; i < HASH_SIZE; i++) {
            tabla[i] = nullptr;
        }
    }

    void insertar(int valor) {
        int indice = hashFuncion(valor);
        if (tabla[indice] == nullptr) {
            tabla[indice] = new ListaDoble();
        }
        tabla[indice]->insertaFinal(valor);
    }

    bool buscar(int valor) {
        int indice = hashFuncion(valor);
        if (tabla[indice] == nullptr) {
            return false;
        }
        return tabla[indice]->buscarDato(valor);
    }

    bool borrar(int valor) {
        int indice = hashFuncion(valor);
        if (tabla[indice] == nullptr) {
            return false;
        }
        bool eliminado = tabla[indice]->borraDato(valor);
        if (tabla[indice]->estaVacia()) {
            delete tabla[indice];
            tabla[indice] = nullptr;
        }
        return eliminado;
    }

    void mostrarTabla() {
        for (int i = 0; i < HASH_SIZE; i++) {
            if (tabla[i] != nullptr) {
                cout << "Indice " << i << ": ";
                tabla[i]->recorreDerecha();
            }
        }
    }

};

#endif // _HASHENCADENADO

