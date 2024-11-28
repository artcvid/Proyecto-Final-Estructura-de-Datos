#include <string>
#include <iostream>

using namespace std;

#ifndef _PELICULA
#define _PELICULA

class Pelicula
{
private:
    // TODO: Pasar los valores a privado
public:
    int id;
    string imdb_id;
    string original_title;
    string overview;
    float vote_average;
    Pelicula(int _id, string _imdb, string _title, string _overview, float _vote) : id(_id), imdb_id(_imdb), original_title(_title), overview(_overview), vote_average(_vote) {};
    ~Pelicula() {};
    void imprimir();
};

void Pelicula::imprimir()
{
    cout << "Titulo: " << original_title << "\n";
    cout << "Calificacion: " << vote_average << "\n";
    cout << "Enlace IMDb: https://www.imdb.com/title/" << imdb_id << "/\n";
    cout << "Overview: " << overview << endl;
}

#endif //_PELICULA