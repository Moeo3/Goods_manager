#include "push_dialog.h"
#include "ui_push_dialog.h"

push_dialog::push_dialog(manager *parent) :
    QDialog((QWidget *)parent),
    ui(new Ui::push_dialog)
{
    ui->setupUi(this);
    mparent = parent;
}

push_dialog::~push_dialog()
{
    delete ui;
}

void push_dialog::on_buttonBox_accepted()
{
    QString push_context = ui->push_textbox->toPlainText();
    QStringList context_list = push_context.split('\n');
    foreach (QString str, context_list) {
        QStringList item_list = str.split(' ');
        QString item_name = item_list[0];
        int item_num = QString(item_list[1]).toInt();
        mparent->put_them_out(item_name, item_num);
    }
    mparent->update_table();
}
