#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include "particulesystem.h"

class Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent);
    std::vector<Particule*>part;

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Helper *helper;
    int elapsed;
};

#endif
