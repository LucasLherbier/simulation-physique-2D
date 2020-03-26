#ifndef WINDOW_H
#define WINDOW_H

#include "helper.h"
#include "widget.h"
#include <QWidget>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    void mouseDoubleClickEvent(QMouseEvent *e);
private:
    Helper helper;
};

#endif
