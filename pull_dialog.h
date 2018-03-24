#ifndef PULL_DIALOG_H
#define PULL_DIALOG_H

#include <QDialog>

#include "manager.h"

namespace Ui {
class pull_dialog;
}

class pull_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit pull_dialog(QWidget *parent = 0);
    ~pull_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::pull_dialog *ui;
};

#endif // PULL_DIALOG_H
