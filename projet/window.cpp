#include "widget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include "particulesystem.h"
#include <QDebug>

Window::Window()
{
    setWindowTitle(tr("Simulation physique 2D"));
    Widget *native = new Widget(&helper, this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, native, &Widget::animate);
    //50 est le pas de calcul, c'est aussi la valeur de la variable interval du fichier helper.cpp
    timer->start(50);
}

void Window::mouseDoubleClickEvent(QMouseEvent *e)
{
    if ( e->button() == Qt::LeftButton )
    {
        QPointF x = e->localPos() ;
        create_solide({x.x(), x.y()},{0.0, 0.0}, 12) ;
    }
}
