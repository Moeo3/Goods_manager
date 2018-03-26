#include "pull_dialog.h"
#include "ui_pull_dialog.h"

#include <QDebug>

pull_dialog::pull_dialog(manager *parent) :
    QDialog((QWidget *)parent),
    ui(new Ui::pull_dialog)
{
    ui->setupUi(this);
    mparent = parent;
}

pull_dialog::~pull_dialog()
{
    delete ui;
}

void pull_dialog::on_buttonBox_accepted()
{
    QString pull_context = ui->pull_textbox->toPlainText();
    QStringList context_list = pull_context.split('\n');
    foreach (QString str, context_list) {
        QStringList item_list = str.split(' ');
        QString item_name = item_list[0];
        int item_num = QString(item_list[1]).toInt();
        mparent->put_them_in(item_name, item_num);
    }
    mparent->update_table();
    this->close();
}
