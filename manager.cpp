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
    QJsonArray json;
    try {
        file.open(QIODevice::ReadOnly);
        QByteArray BA = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(BA);
        json = jsonDoc.array();
    } catch (const char *str) {
        qDebug() << str;
    }
    qDebug() << "我们居然打开了file";
    for (QJsonArray::Iterator iter = json.begin(); iter != json.end(); ++ iter) {
        goods tmp; tmp.read(iter->toObject());
        goods_list.push_back(tmp);
    }
    qDebug() << "不知道哪里来的" << json;
    qDebug() << "good数量" << json.size();
    update_table();
}

manager::~manager()
{
    QJsonArray json;
    for (QVector <goods>::Iterator iter = goods_list.begin(); iter != goods_list.end(); ++ iter) {
        if (iter->quantity() <= 0) continue;
        QJsonObject tmp; iter->write(tmp);
        json.push_back(tmp);
    }
    QJsonDocument jsonDoc(json);
    QByteArray BA = jsonDoc.toJson();
    QFile file("list.json");
    try {
        file.open(QIODevice::WriteOnly);
        qDebug() << "写入" << BA;
        file.write(BA);
        file.close();
    } catch (const char *str) {
        qDebug() << str;
    }
    delete ui;
}

void manager::on_pullButton_clicked()
{
    qDebug() << "点击了pull";
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
    for (QVector <goods>::Iterator iter = goods_list.begin(); iter != goods_list.end(); ++ iter) {
        if (name == iter->name()) {
            iter->set_quantity(iter->quantity() + num);
            return;
        }
    }
    goods_list.push_back(goods(name, num));
}

void manager::put_them_out(QString name, int num)
{
    for (QVector <goods>::Iterator iter = goods_list.begin(); iter != goods_list.end(); ++ iter)  {
        if (name == iter->name()) {
            if (iter->quantity() - num < 0) {
                QMessageBox::warning(
                    this, "Are you silly?", QString("We do not have such many ") +
                    name + QString("!!!!!!"), QMessageBox::Yes
                );
            } else iter->set_quantity(iter->quantity() - num);
            return;
        }
    }
    QMessageBox::warning(
        this, "Are you silly?", QString("We do not have any ") +
        name + QString("!!!!!!"), QMessageBox::Yes
    );
}

void manager::update_table() {
    goods_model->removeRows(0, goods_model->rowCount());
    int count = 0;
    for (QVector <goods>::Iterator iter = goods_list.begin(); iter != goods_list.end(); ++ iter) {
        if (iter->quantity() <= 0) continue;
        goods_model->setItem(count, 0, new QStandardItem(iter->name()));
        goods_model->setItem(count, 1, new QStandardItem(QString::number(iter->quantity(), 10)));
        ++ count;
    }
}

void manager::selcet_table(QStringList str) {
    goods_model->removeRows(0, goods_model->rowCount());
    int count = 0;
    for (QVector <goods>::Iterator iter = goods_list.begin(); iter != goods_list.end(); ++ iter) {
        if (iter->quantity() <= 0) continue;
        if (str.contains(iter->name()) == 0) continue;
        goods_model->setItem(count, 0, new QStandardItem(iter->name()));
        goods_model->setItem(count, 1, new QStandardItem(QString::number(iter->quantity(), 10)));
        ++ count;
    }
}

void manager::on_queryButton_clicked()
{
    mquery_dialog = new query_dialog(this);
    mquery_dialog->show();
}
