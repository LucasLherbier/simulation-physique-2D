#include "surface.h"
#include <QPainter>
#include <QPoint>
#include <cmath>
#include <iostream>
#include <math.h>



/*----------------------------------------------------------------------------------------
Création d'une classe surface
----------------------------------------------------------------------------------------*/

//Créate de la classe
surface::surface(double p_x, double p_y, double n_x, double n_y)
{
    this->point = {p_x,p_y};
    this->n = {n_x,n_y};
    double norme = sqrt(n[0]*n[0]+n[1]*n[1]) ;
    if(static_cast<int> (norme)!= 1){
        n[0] /= norme;
        n[1] /= norme;
    }
}



//Calcul de la contraintes entre une particules et une surface
double surface::C_plan(vector<double> pi, int r){
    //Renvoie la valeur de C(pi) pour un point pi, de rayon r, et une surface
    pi[0] = pi[0] - point[0] ;
    pi[1] = pi[1] - point[1] ;
    double res = pi[0]*n[0] + pi[1]*n[1] - r ;
    return res ;
}


//Mise à jour de la position liée à la contrainte surface, suivant la valeur de C(pi)
Particule* surface::resolve(Particule *p, int r){
    double res = C_plan(p->position, r) ;
    if (res <0 ) {
        double lambda = -res * p->mass;
        p->position[1] += lambda * n[1] / p->mass;
        p->position[0] += lambda * n[0] / p->mass;
    }
    return p ;
}





/*----------------------------------------------------------------------------------------
Affichage de la surface
----------------------------------------------------------------------------------------*/

void surface::display(QPainter *painter, surface *s){
    //L est la taille de la fenêtre
    int L = 400 ;
    //Calcul des coordonées des deux points de la surface appartenant aux extrémités de la fenêtre
    int x1 = 0 ;
    double y1 = s->n[0]*s->point[0]/s->n[1]+s->point[1];
    int x2 = L ;
    double y2 = s->n[0]*(s->point[0]-L)/s->n[1]+ s->point[1];

    //Choix des couleurs de fond et de contour
    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green,0));

    //Tracé d'un triangle ou d'un rectangle suivant le type de surface
    //Selon la surface, le 3e point du triangle est l'un des deux extrémités en y = L de la fenêtre
    if (s->n[0]<0) {
            QPolygon poly ;
            poly <<QPoint(x1, static_cast<int> (y1)) << QPoint(x2, static_cast<int> (y2)) <<QPoint(400,400.0) ;
            painter->drawPolygon(poly);
        }
    if (s->n[0]>0) {
            QPolygon poly ;
            poly <<QPoint(x1, static_cast<int> (y1)) << QPoint(x2, static_cast<int> (y2)) <<QPoint(0.0,400.0) ;
            painter->drawPolygon(poly);
        }
    if (static_cast<int> (s->n[0])==0){
        QPolygon poly ;
        poly <<QPoint(x1, static_cast<int> (y1)) << QPoint(x2, static_cast<int> (y2)) <<QPoint(400.0,400.0) <<QPoint(0.0,400.0) ;
        painter->drawPolygon(poly);
    }
}


/*----------------------------------------------------------------------------------------
Création et contraintes liées au bloc rectangulaire
----------------------------------------------------------------------------------------*/

//Affichage du bloc composé de 4 points, les 4 angles du rectangle
void draw_bloc(QPainter *painter,vector <vector<int>> p){
    QPolygon poly ;
    poly <<QPoint(p[0][0], p[0][1]) << QPoint(p[1][0], p[1][1]) <<QPoint(p[2][0], p[2][1]) <<QPoint(p[3][0], p[3][1])  ;
    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green,0));
    painter->drawPolygon(poly);
}

//Calcul des contraintes et mises à jours des positions liées au bloc rectangulaire
//Le vecteur B contient les 4 points du bloc
Particule * resolve_bloc(Particule *p, int r, vector <vector<double>> B) {
    double res = - 100000 ;
    double a,b,c ;
    unsigned int d = 0 ;
    //Vecteur des normales liées aux 4 points
    vector <vector<double>> n = {{0.0, -1.0},{1.0, 0.0},{0.0, 1.0},{-1.0, 0.0}};
    for (unsigned int i = 0; i<4; i++) {
        a = p->position[0] - B[i][0] ;
        b = p->position[1] - B[i][1] ;
        c = a*n[i][0] + b*n[i][1] - r ;
        //Calcul du maximum des contraintes
        if (c>res){
            res = c ;
            d = i ;
        }
    }
    //Mise à jours des positions
    if (res <0 ) {
        double lambda = -res * p->mass;
        p->position[1] += lambda * n[d][1] / p->mass;
        p->position[0] += lambda * n[d][0] / p->mass;
    }
    return p ;
}




