#ifndef COMMON_HELPER_H
#define COMMON_HELPER_H

#include <QFile>
#include <QApplication>

class common_helper
{
public:
    common_helper() {}
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

#endif // COMMON_HELPER_H
