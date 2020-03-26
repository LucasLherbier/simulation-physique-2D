#include "particulesystem.h"
#include <vector>
#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <QDebug>
#include <iostream>
#include <math.h>



double norme(Particule *P1, Particule *P2) {
    double distance_x = (P1->position[0]-P2->position[0]) * (P1->position[0]-P2->position[0]) ;
    double distance_y = (P1->position[1]-P2->position[1]) * (P1->position[1]-P2->position[1]) ;
    return sqrt(distance_x + distance_y) ;
}



/*----------------------------------------------------------------------------------------
Création des fonctions permettant la construction des structures PARTICULES et SOLIDES
----------------------------------------------------------------------------------------*/

//Construction d'un point
Particule * create_particule(double p_x, double p_y, double v_x, double v_y, double mass){
    Particule *P = new Particule() ;
    Particule *p = new Particule() ;
    P->position = {p_x, p_y} ;
    P->velocity = {v_x, v_y} ;
    P->mass = mass ;
    *p = *P ;
    part.push_back(P) ;
    part2.push_back(p) ;
    return p ;
}

//Construction d'un solide
void create_solide (vector <double> p,vector <double> v, int l){
    //l est la distance entre les deux centres des particules adjacentes
    Particule *p1 = create_particule(p[0], p[1], v[0], v[1], 1) ;
    Particule *p2 = create_particule(p[0]+l, p[1], v[0], v[1], 1) ;
    Particule *p3 = create_particule(p[0], p[1]+l, v[0], v[1], 1) ;
    Particule *p4 = create_particule(p[0]+l, p[1]+l, v[0], v[1], 1) ;
    ensemble_solides.push_back({p1,p2,p3,p4}) ;
}




/*----------------------------------------------------------------------------------------
Création des fonctions de MISES A JOURS des paramètres
----------------------------------------------------------------------------------------*/

//Mise à jour de la vitesse d'une particule soumise à une force
Particule *update_velocity(Particule* P1, int interval, vector<double> force){
    //Mise à jour de la vitesse suivant un interval de temps et une force
    P1->velocity[1]+= force[1]*interval/(1000*P1->mass);
    P1->velocity[0]+= force[0]*interval/(1000*P1->mass);
    return P1 ;
}

//Mise à jour des paramètres d'une particule via une copie, dans le cas où on ne tient pas compte des contraintes
Particule *update_position(Particule* P1, int interval, Particule* P2){
    //La particule P2 fait office du point P1 virtuellement à l'instant d'après, si on ne tient pas compte des contraintes
    P2->position[1]= P1->position[1] + P1->velocity[1]*interval/1000;
    P2->position[0]= P1->position[0] + P1->velocity[0]*interval/1000;
    return P2 ;
}

//Mise à jour des paramètres d'une particule à la suite des des contraintes
Particule *rectify(Particule* p1, int interval, Particule* p2) {
    //Remise à jour de la vitesse et de la positon en fonction des contraintes
    p1->velocity[0] = (p2->position[0]-p1->position[0])*1000/interval ;
    p1->velocity[1] = (p2->position[1]-p1->position[1])*1000/interval ;
    p1->position[0] = p2->position[0] ;
    p1->position[1] = p2->position[1] ;
    return p1 ;
}




/*----------------------------------------------------------------------------------------
Création des fonctions calculant les contraintes
----------------------------------------------------------------------------------------*/

//Calcul des contraintes entre deux particules de deux solides différents
double C_extraparticule(Particule *p1, Particule *p2, int r){
    //r est le rayon des particules
    double distance = norme(p1, p2) - 2*r  ;
    return distance ;
}


//Mise à jour des coordonnées de deux particules, appartenant à deux solides différents, en cas de choc
Particule *resolve_particule(Particule *p1, Particule *p2, int r){
    //r est le rayon des particules
    double res = C_extraparticule(p1, p2, r) ;
    if (res <0 ) {
        double distance = norme(p1, p2) ;
        double inverse_masses = 1/p1->mass+1/p2->mass ;
        p1->position[0] += - res*(p1->position[0]- p2->position[0])/(inverse_masses*p1->mass*distance);
        p1->position[1] += - res*(p1->position[1]- p2->position[1])/(inverse_masses*p1->mass*distance);
        p2->position[0] += res*(p1->position[0]- p2->position[0])/(inverse_masses*p2->mass*distance);
        p2->position[1] += res*(p1->position[1]- p2->position[1])/(inverse_masses*p2->mass*distance);
    }
    return p1 ;
}


//Calcul des contraintes entre les particules d'un même solide
void C_solide (vector <Particule*> solide, double r){
    double L = r ;
    //stiff permet de jouer sur l'élasticité du solide
    double stiff = 1 ;
    for (unsigned int j=0; j<3 ; j++ ){
        for (unsigned int i=j+1 ; i<4; i++ ) {
            //Mise à jour de la longueur L pour la particule opposée symétriquement
            if (i+j==3) {
                L = sqrt(2.0)*L ;
            }
            //Vérfie la distance entre les particules j et i
            double res = norme(solide[j], solide[i]) - L  ;
            if (res!=0.0 ) {
                //Mise à jour des coordonnées
                double distance = norme(solide[j], solide[i]) ;
                double inverse_masses = 1/solide[j]->mass + 1/solide[i]->mass ;
                solide[j]->position[1] += - stiff*res*(solide[j]->position[1]- solide[i]->position[1])/(inverse_masses*solide[j]->mass*distance);
                solide[j]->position[0] += - stiff*res*(solide[j]->position[0]- solide[i]->position[0])/(inverse_masses*solide[j]->mass*distance);
                solide[i]->position[1] += stiff*res*(solide[j]->position[1]- solide[i]->position[1])/(inverse_masses*solide[i]->mass*distance);
                solide[i]->position[0] += stiff*res*(solide[j]->position[0]- solide[i]->position[0])/(inverse_masses*solide[i]->mass*distance);
            L = r ;
            }
        }
    }
}
