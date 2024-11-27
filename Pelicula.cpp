#include <string>

using namespace std;

#ifndef _PELICULA
#define _PELICULA

struct Pelicula
{
    int id;
    string imdb_id;
    string original_title; 
    string overview;
    float vote_average;

    Pelicula(int _id, string _imdb, string _title, string _overview, float _vote)
        : id(_id), imdb_id(_imdb), original_title(_title), overview(_overview), vote_average(_vote) {}
};

#endif //_PELICULA