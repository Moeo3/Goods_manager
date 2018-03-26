#ifndef QUERY_DIALOG_H
#define QUERY_DIALOG_H

#include <QDialog>

#include "manager.h"

namespace Ui {
class query_dialog;
}
class manager;

class query_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit query_dialog(manager *parent = 0);
    ~query_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::query_dialog *ui;
    manager *mparent;
};

#endif // QUERY_DIALOG_H
