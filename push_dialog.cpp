#include "push_dialog.h"
#include "ui_push_dialog.h"

push_dialog::push_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::push_dialog)
{
    ui->setupUi(this);
}

push_dialog::~push_dialog()
{
    delete ui;
}

void pull_dialog::on_buttonBox_accepted()
{
    QString pull_context = ui->pull_textbox->toPlainText();
    QStringList context_list = pull_context.split('\n');
    foreach(QString str, context_list) {
        QStringList item_list = str.split(' ');
        QString item_name = item_list[0];
        int item_num = QString::toInt(item_list[1]);
        parent->put_them_out(item_name, item_num);
    }
}
