#include "manager.h"
#include "ui_manager.h"

#include <QJsonDocument>
#include <QFile>
#include <QDebug>

manager::manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
    goods_model = new QStandardItemModel();
    json = new QJsonArray();
    //Data Model
    goods_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Name")));
    goods_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Quantity")));
    //use setModel() method binding data model and QTableView together
    ui->tableView->setModel(goods_model);

    /***********Set table option***********/
    // show the line heads by default, if you think it is not beautiful enough, we can hide them.
    ui->tableView->verticalHeader()->hide();
    // Choose is choosing the whole line.
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // set the units of the table to be read-only.
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFile file("list.json");
    try {
        file.open(QIODevice::ReadOnly);
        QByteArray BA = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(BA);
        *json = jsonDoc.array();
    } catch (const char *str) {
        qDebug() << str;
    }
    for (QJsonArray::Iterator iter = json->begin(); iter != json->end(); ++ iter) {
        goods tmp; tmp.read(iter->toObject());
        goods_list.push_back(tmp);
    }
}

manager::~manager()
{
    for (QVector <goods>::Iterator iter = goods_list.begin(); iter != goods_list.end(); ++ iter) {
        QJsonObject tmp; iter->write(tmp);
        json->push_back(tmp);
    }
    QJsonDocument jsonDoc(*json);
    QByteArray BA = jsonDoc.toJson();
    QFile file("list.json");
    try {
        file.open(QIODevice::WriteOnly);
        file.write(BA);
        file.close();
    } catch (const char *str) {
        qDebug() << str;
    }
    delete ui;
}

void manager::on_pullButton_clicked()
{
    mpull_dialog = new pull_dialog(this);
    mpull_dialog->show();
}

void manager::on_pushButton_clicked()
{
    mpush_dialog = new push_dialog(this);
    mpush_dialog->show();
}

void manager::put_them_in(QString name, int num)
{
    for (auto good : goods_list) {
        if (name == good.name()) {
            good.set_quantity(good.quantity() + num);
            return;
        }
    }
    goods_list.push_back(goods(name, num));
}

void manager::put_them_out(QString name, int num)
{
    for (auto good : goods_list) {
        if (name == good.name()) {
            if (good.quantity() - num < 0) {
                QMessageBox::warning(
                    this, "Are you silly?", QString("We do not have such many ") +
                    name + QString("!!!!!!"), QMessageBox::Yes
                );
            } else good.set_quantity(good.quantity() - num);
            return;
        }
    }
    QMessageBox::warning(
        this, "Are you silly?", QString("We do not have any ") +
        name + QString("!!!!!!"), QMessageBox::Yes
    );
}
