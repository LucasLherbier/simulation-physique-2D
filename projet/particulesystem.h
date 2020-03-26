#ifndef PARTICULESYSTEM_H
#define PARTICULESYSTEM_H

#include <QObject>
#include <QWidget>
#include <vector>

using namespace std ;

//Déclaration de la structure particule
struct Particule{
        vector<double> position{0.,0.};
        vector<double> velocity{0.,0.} ;
        double mass = 0 ;
};

//Déclaration de la structure solide
struct Solide {
    Particule *p1 ;
    Particule *p2 ;
    Particule *p3 ;
    Particule *p4 ;
};



/*----------------------------------------------------------------------------------------
Déclaration des fonctions
----------------------------------------------------------------------------------------*/

double norme(Particule *P1, Particule *P2) ;

//Fonctions de construction des structures PARTICULES et SOLIDES
Particule *create_particule(vector<double> position, vector<double>  velocity, double mass);

void create_solide (vector <double> p, vector <double> v, int l);


//Fonctions de mises à jours des coordonées
Particule *update_position(Particule* P1, int interval, Particule* P2) ;

Particule *update_velocity(Particule* P1, int interval, vector<double> force) ;

Particule *rectify(Particule* p1, int temps, Particule* p2) ;


//Fonctions de calculs des contraintes
double C_extraparticule(Particule *p1, Particule *p2, int r) ;

Particule *resolve_particule(Particule *p1, Particule *p2, int r) ;

void C_solide (vector <Particule*> solide, double r) ;


//Déclaration des variables globales
extern vector<Particule*> part;
extern vector<Particule*> part2;
extern vector<vector <Particule*>> ensemble_solides ;


#endif // PARTICULESYSTEM_H
