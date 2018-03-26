#ifndef PUSH_DIALOG_H
#define PUSH_DIALOG_H

#include <QDialog>

#include "manager.h"

namespace Ui {
class push_dialog;
}
class manager;

class push_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit push_dialog(manager *parent = 0);
    ~push_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::push_dialog *ui;
    manager *mparent;
};

#endif // PUSH_DIALOG_H
