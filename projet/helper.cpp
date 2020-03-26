#include "helper.h"
#include <particulesystem.h>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <vector>
#include <surface.h>
#include <iostream>
#include <math.h>

using namespace  std ;

Helper::Helper()
{
    background = QBrush(QColor(3, 34, 76));
    circleBrush = QBrush(Qt::green);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
}


void Helper::paint(QPainter *painter, QPaintEvent *event)
{
    /*----------------------------------------------------------------------------------------
    Choix des paramètres
    ----------------------------------------------------------------------------------------*/

    int dt = 50 ;
    int r = 10 ;
    vector<double> force {0,+100};

    //Caractéristiques de l'affichage
    painter->fillRect(event->rect(), background);
    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    //Affichage des surfaces
    for(surface* &s:surf){
        s->display(painter, s) ;
    }

    //Calculs des vitesses des points
    for(Particule* &p:part){
        p = update_velocity(p,dt,force);
    }

    //Calculs des positions et vitesses des points, sur un vecteur copie, soumis qu'à la force
    for(unsigned int i = 0 ; i<part.size() ; i++ ){
        part2[i] = update_position(part[i],dt, part2[i]);
    }

    //Mise à jour des positions et vitesses des points sur le vecteur copie à cause des contraintes
    for (int i = 0 ; i<5; i++ ) {
        //Contraintes liées aux surfaces
        for(surface* &s:surf){
            for(Particule* &p:part2){
                  p = s->resolve(p,r);
            }
        }
        //Contraintes liées au bloc rectangulaire
        vector <vector<double>> B = {{70,70},{150,70},{150,100},{70,100}};
        for(Particule* &p:part2){
              p = resolve_bloc(p,r,B);
        }

        //Contraintes internes au solide
        for (vector<Particule*> solide:ensemble_solides){
            C_solide(solide, 12) ;
        }

        //Contraintes liées aux choc de particules
        for (unsigned int j = 0 ; j<part2.size()-4; j++){
            for (unsigned int k = (j/4+1)*4  ; k<part2.size(); k++) {
                 part2[j] = resolve_particule(part2[j], part2[k], r) ;
            }
        }

    }

    //Mise à jour des positions et vitesses des points via le vecteur copie
    for(unsigned int i = 0 ; i<part.size() ; i++ ){
        part[i] = rectify(part[i], dt, part2[i]);
    }

    painter->setBrush(Qt::red);
    painter->setPen(QPen(Qt::white,1));
    for(Particule* &p:part){
        painter->drawEllipse(QPoint(static_cast<int> (p->position[0]),static_cast<int> (p->position[1])),r,r) ;
    }

    //Affichage du bloc rectangulaire
    draw_bloc(painter,{{70,70},{150,70},{150,100},{70,100},}) ;
    painter->restore();
    painter->setFont(textFont);

}
