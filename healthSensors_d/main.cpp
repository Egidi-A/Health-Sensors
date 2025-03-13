#include "./VIEW/healthdashboard.h"

#include <QApplication>
#include <controller.h>
#include "MODELLO/modello.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Modello* m = new Modello();
    Controller* c = new Controller();

    healthDashboard* w = new healthDashboard(m);

    c->setModelView_controller(m,w);
    w->setController(c);

    w->show();
    return a.exec();
}
