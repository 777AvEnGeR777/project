#include "accountform.h"
#include "ui_accountform.h"

accountform::accountform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountform)
{
    ui->setupUi(this);
    connect(ui->button_save, SIGNAL(clicked(bool)), this, SLOT(save_account()));
}

accountform::~accountform()
{
    delete ui;
}

void accountform::set_account_name(std::string name){
    account_name = name;
}

void accountform::save_account(){
    std::string name = ui->field_accountName->text().toStdString();
    std::string login = ui->field_login->text().toStdString();
    std::string password = ui->field_password->text().toStdString();
    std::string comment = ui->field_comment->toPlainText().toStdString();

    Account account (name, login, password, comment);

    if(account_name == ""){
        Data::Instance().accountList.insert(std::make_pair(name, account));
    }else{
        Data::Instance().accountList.insert(std::make_pair(account_name, account));
    }
    Data::Instance().Save();
    close();
}
