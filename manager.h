#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include <QVector>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QJsonArray>
#include "goods.h"
#include "pull_dialog.h"
#include "push_dialog.h"

namespace Ui {
class manager;
}

class pull_dialog;
class push_dialog;

class manager : public QWidget
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = 0);
    ~manager();

    void put_them_in(QString, int);
    void put_them_out(QString, int);

private slots:
    void on_pullButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::manager *ui;
    QStandardItemModel *goods_model;
    QVector <goods> goods_list;
    pull_dialog *mpull_dialog;
    push_dialog *mpush_dialog;
    QJsonArray *json;
};

#endif // MANAGER_H
