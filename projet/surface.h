#ifndef SURFACE_H
#define SURFACE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <vector>
#include "particulesystem.h"

using namespace  std ;
void draw_bloc(QPainter *painter,vector <vector<int>> p);
Particule * resolve_bloc(Particule *p, int r, vector <vector<double>> b) ;

class surface
{
public:
    vector<double> point ;
    vector<double> n ;
    surface(double p_x, double p_y, double n_x, double n_y);
    double C_plan(vector<double> pi,int r) ;
    Particule *resolve(Particule* p, int r) ;
    void display(QPainter *painter, surface *surf);
};

//Déclaration des variables globales
extern vector<surface*> surf;

#endif // SURFACE_H
