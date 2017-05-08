#include "accountform.h"
#include "ui_accountform.h"

accountform::accountform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountform),
    show_password(false)
{

    ui->setupUi(this);

    if(!show_password){
        ui->field_password->setEchoMode(QLineEdit::Password);
        ui->button_showpassword->setText("Show password");
    }else{
        ui->field_password->setEchoMode(QLineEdit::Normal);
        ui->button_showpassword->setText("Hide password");
    }

    connect(ui->button_save, SIGNAL(clicked(bool)), this, SLOT(save_account()));
    connect(ui->button_showpassword, SIGNAL(clicked(bool)), this, SLOT(toggleShowPassword()));
}

accountform::~accountform()
{
    delete ui;
}

void accountform::toggleShowPassword(){
    if(!show_password){
        ui->field_password->setEchoMode(QLineEdit::Password);
        ui->button_showpassword->setText("Show password");
    }else{
        ui->field_password->setEchoMode(QLineEdit::Normal);
        ui->button_showpassword->setText("Hide password");
    }
    show_password = !show_password;
}

void accountform::set_account_name(std::string name){
    account_name = name;
    ui->field_accountName->setText(name.c_str());
    ui->field_accountName->setEnabled(false);
    ui->field_comment->setText(Data::Instance().accountList.find(name.c_str())->second.comment.c_str());
    ui->field_login->setText(Data::Instance().accountList.find(name.c_str())->second.login.c_str());
    ui->field_password->setText(Data::Instance().accountList.find(name.c_str())->second.password.c_str());
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
        Data::Instance().accountList.find(account_name)->second.login = login;
        Data::Instance().accountList.find(account_name)->second.password = password;
        Data::Instance().accountList.find(account_name)->second.comment = comment;
    }

    Data::Instance().Save();
    close();
}
