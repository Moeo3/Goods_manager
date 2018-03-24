#ifndef PUSH_DIALOG_H
#define PUSH_DIALOG_H

#include <QDialog>

namespace Ui {
class push_dialog;
}

class push_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit push_dialog(QWidget *parent = 0);
    ~push_dialog();

private:
    Ui::push_dialog *ui;
};

#endif // PUSH_DIALOG_H
