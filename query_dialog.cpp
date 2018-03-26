#include "query_dialog.h"
#include "ui_query_dialog.h"

query_dialog::query_dialog(manager *parent) :
    QDialog((QWidget *)parent),
    ui(new Ui::query_dialog)
{
    ui->setupUi(this);
    mparent = parent;
}

query_dialog::~query_dialog()
{
    delete ui;
}

void query_dialog::on_buttonBox_accepted()
{
    QString query_context = ui->query_textbox->toPlainText();
    if (query_context.isEmpty()) {
        mparent->update_table();
        return;
    }
    QStringList context_list = query_context.split('\n');
    mparent->selcet_table(context_list);
}
