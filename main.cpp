#include "manager.h"
#include "common_helper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    common_helper::setStyle(":/style.qss");
    manager w;
    w.show();

    return a.exec();
}
