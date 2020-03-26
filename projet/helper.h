#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

#include "particulesystem.h"

class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
};

#endif
