#include <iostream>
#include <queue>
#include<string>
using namespace std;

class ArbolBinarioBusqueda {
private:
    struct NodoABB {
        int dato;
        string nombre;
        NodoABB* der;
        NodoABB* izq;
        NodoABB* padre;

        NodoABB(int valor,string nom) : dato(valor),nombre(nom), der(nullptr), izq(nullptr), padre(nullptr) {}
    };

    NodoABB* raiz; // Apuntador a la ra�z del �rbol

public:
    ArbolBinarioBusqueda() : raiz(nullptr) {}

   void insertarNodo(int dato, string nombre) {
    NodoABB* nuevo = new NodoABB(dato, nombre);
    NodoABB* aux = nullptr;

    if (raiz == nullptr) {
        raiz = nuevo;
    } else {
        aux = raiz;
        while (aux != nullptr) {
            // Si el nombre es menor o igual al dato del nodo actual, va al subárbol izquierdo
            if (nombre <= aux->nombre && aux->izq == nullptr) {
                nuevo->padre = aux;
                aux->izq = nuevo;
                aux = nullptr;
            }
            // Si el nombre es mayor al dato del nodo actual, va al subárbol derecho
            else if (nombre > aux->nombre && aux->der == nullptr) {
                nuevo->padre = aux;
                aux->der = nuevo;
                aux = nullptr;
            }
            // Si el nombre es menor o igual, sigue explorando el subárbol izquierdo
            else if (nombre <= aux->nombre) {
                aux = aux->izq;
            }
            // Si el nombre es mayor, sigue explorando el subárbol derecho
            else {
                aux = aux->der;
            }
        }
    }
}

    // Buscar un nodo
    int buscarNodo(string nombre) {
        NodoABB* aux = raiz;
        while (aux != nullptr) {
            if (nombre == aux->nombre) {
                return aux->dato;
            } else if (nombre < aux->nombre) {
                aux = aux->izq;
            } else {
                aux = aux->der;
            }
        }
        return -1;
    }

};

