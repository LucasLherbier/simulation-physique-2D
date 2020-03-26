#include "window.h"
#include <QApplication>
#include <QSurfaceFormat>
#include "particulesystem.h"
#include "surface.h"
#include <QDebug>

vector<Particule*> part;
vector<surface*> surf;
vector<Particule*> part2;
vector<vector <Particule*>> ensemble_solides ;



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

/*----------------------------------------------------------------------------------------
Creation des solides initiales
----------------------------------------------------------------------------------------*/
    create_solide({50.0, 120.0},{0.0, 60.0}, 12) ;
    create_solide({325.0, 50.0},{-50.0, 0.0},  12) ;
    create_solide({130.0, 285.0},{0.0, 25.0},  12) ;


/*----------------------------------------------------------------------------------------
Creation des surfaces
----------------------------------------------------------------------------------------*/
    surface *s1 = new surface(100,300,0,-1) ;
    surface *s2 = new surface(0,200,1,-1);
    surface *s3 = new surface(400,200,-1,-1) ;
    surf.push_back(s2) ;
    surf.push_back(s1) ;
    surf.push_back(s3) ;


    Window window;
    window.show();
    return app.exec();
}
