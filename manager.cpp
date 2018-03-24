#include "manager.h"
#include "ui_manager.h"

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
}

manager::~manager()
{
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
        if (name == good->name()) {
            good->set_quantity(good->quantity() + num);
            return;
        }
    }
    goods_list.push_back(goods(name, num));
}

void manager::put_them_out(QString name, int num)
{
    for (auto good : goods_list) {
        if (name == good->name()) {
            if (good->quantity() - num < 0) {
                QMessageBox::Critical(
                    0, "Are you silly?", QString("We do not have such many ") +
                    name + QString("!!!!!!"), QMessageBox::Yes
                );
            } else good->set_quantity(good->quantity() - num);
            return;
        }
    }
    QMessageBox::Critical(
        0, "Are you silly?", QString("We do not have any ") +
        name + QString("!!!!!!"), QMessageBox::Yes
    );
}
