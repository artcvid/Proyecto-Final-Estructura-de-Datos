#include <iostream>
using namespace std;

#ifndef _LDL
#define _LDL

struct NodoLDL
{
    int dato;
    NodoLDL *sig;
    NodoLDL *ant;

    // Constructor
    NodoLDL(int d) : dato(d), sig(nullptr), ant(nullptr) {}
};

class ListaDoble
{
private:
    NodoLDL *inicio; // Puntero al primer nodo de la lista
    NodoLDL *fin;    // Puntero al último nodo de la lista
    int sizeList;

public:
    // Constructor
    ListaDoble() : inicio(nullptr), fin(nullptr), sizeList(0) {}

    bool estaVacia()
    {
        return inicio == nullptr;
    }

    int getSize()
    {
        return sizeList;
    }

    // Método para buscar un valor específico en la lista
    bool buscarDato(int valor)
    {
        NodoLDL *actual = inicio;
        while (actual != nullptr)
        {
            if (actual->dato == valor)
            {
                return true; // Valor encontrado
            }
            actual = actual->sig;
        }
        return false; // Valor no encontrado
    }

    void insertaInicio(int dato)
    {
        NodoLDL *aux = new NodoLDL(dato);
        if (estaVacia())
        {
            inicio = aux;
            fin = aux;
        }
        else
        {
            aux->sig = inicio;
            inicio->ant = aux;
            inicio = aux;
        }
        sizeList++;
    }

    // Método para insertar al final
    void insertaFinal(int dato)
    {
        NodoLDL *nuevo = new NodoLDL(dato);
        if (estaVacia())
        {
            inicio = fin = nuevo;
        }
        else
        {
            fin->sig = nuevo;
            nuevo->ant = fin;
            fin = nuevo;
        }
        sizeList++;
    }

    // Método para borrar un nodo con un valor específico
    bool borraDato(int valor)
    {
        NodoLDL *actual = inicio;

        // Buscar el nodo con el valor especificado
        while (actual != nullptr && actual->dato != valor)
        {
            actual = actual->sig;
        }

        // Si no se encuentra el valor
        if (!actual)
        {
            cout << "Valor " << valor << " no encontrado en la lista." << endl;
            return false;
        }

        // Si el nodo a eliminar es el único nodo en la lista
        if (actual == inicio && actual == fin)
        {
            inicio = fin = nullptr;
        }
        // Si el nodo a eliminar es el primer nodo
        else if (actual == inicio)
        {
            inicio = inicio->sig;
            inicio->ant = nullptr;
        }
        // Si el nodo a eliminar es el último nodo
        else if (actual == fin)
        {
            fin = fin->ant;
            fin->sig = nullptr;
        }
        // Si el nodo a eliminar está en una posición intermedia
        else
        {
            actual->ant->sig = actual->sig;
            actual->sig->ant = actual->ant;
        }

        delete actual; // Liberar la memoria del nodo eliminado
        sizeList--;    // Disminuir el tamaño de la lista
        return true;
    }

    // Metodo para mostrar la lista de izq a derecha
    void recorreDerecha()
    {
        NodoLDL *temp = inicio;
        while (temp != nullptr)
        {
            cout << temp->dato << " -> ";
            temp = temp->sig; // Moverse al siguiente nodo
        }
        cout << "nullptr" << endl;
    }

    // Metodo para mostrar la lista de derecha a izq
    void recorreIzquierda()
    {
        NodoLDL *temp = fin;
        while (temp != nullptr)
        {
            cout << temp->dato << " -> ";
            temp = temp->ant; // Moverse al siguiente nodo
        }
        cout << "nullptr" << endl;
    }

    // Método para insertar de manera ascendente
    void insertaOrdenado(int dato)
    {
        NodoLDL *nuevo = new NodoLDL(dato);

        // Si la lista esta vacia
        if (!inicio)
        {
            inicio = fin = nuevo;
        }
        // Si el nuevo dato es menor o igual que el primer dato de la lista
        else if (dato <= inicio->dato)
        {
            nuevo->sig = inicio;
            inicio->ant = nuevo;
            inicio = nuevo;
        }
        // Si el nuevo dato es mayor que el �ltimo dato de la lista
        else if (dato >= fin->dato)
        {
            fin->sig = nuevo;
            nuevo->ant = fin;
            fin = nuevo;
        }
        // Si el nuevo dato va en alg�n lugar intermedio
        else
        {
            NodoLDL *actual = inicio;
            // Encontrar la posicion correcta
            while (actual->sig && actual->sig->dato < dato)
            {
                actual = actual->sig;
            }

            // Insertar el nuevo nodo entre 'actual' y 'actual->sig'
            nuevo->sig = actual->sig;
            if (actual->sig)
            {
                actual->sig->ant = nuevo;
            }
            nuevo->ant = actual;
            actual->sig = nuevo;
        }

        // Aumentar
        sizeList++;
    }
};

#endif // _LDL
