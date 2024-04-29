#include "add_user.h"
#include "ui_add_user.h"

Add_User::Add_User(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_User)
{
    ui->setupUi(this);
}

Add_User::~Add_User()
{
    delete ui;
}


void Add_User::on_Add_Button_clicked()
{
    QString name=ui->User_Entry->toPlainText();
    emit namesignal(name);
}

