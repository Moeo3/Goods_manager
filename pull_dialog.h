#ifndef PULL_DIALOG_H
#define PULL_DIALOG_H

#include <QDialog>

#include "manager.h"

namespace Ui {
class pull_dialog;
}
class manager;

class pull_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit pull_dialog(manager *parent = 0);
    ~pull_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::pull_dialog *ui;
    manager *mparent;
};

#endif // PULL_DIALOG_H
