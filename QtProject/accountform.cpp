#include "accountform.h"
#include "ui_accountform.h"

accountform::accountform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountform)
{

    ui->setupUi(this);

    ui->field_password->setEchoMode(QLineEdit::Password);



    connect(ui->button_save, SIGNAL(clicked(bool)), this, SLOT(save_account()));
    connect(ui->button_showpassword, SIGNAL(pressed()), this, SLOT(toggleShowPassword()));
    connect(ui->button_showpassword, SIGNAL(released()), this, SLOT(toggleHidePassword()));
    connect(ui->button_generate, SIGNAL(clicked(bool)), this, SLOT(generatePassword()));

}

accountform::~accountform()
{
    delete ui;
}

void accountform::generatePassword() {
    std::string password = PasswordGenerator::Instance().Generate(ui->spin_password_length->value(),
                                                                  ui->checkbox_letters->isChecked(),
                                                                  ui->checkbox_digits->isChecked(),
                                                                  ui->checkbox_specials->isChecked());
    ui->field_password->setText(QString(password.c_str()));
}

void accountform::toggleShowPassword(){
     ui->field_password->setEchoMode(QLineEdit::Normal);
}

void accountform::toggleHidePassword(){
    ui->field_password->setEchoMode(QLineEdit::Password);
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

    if(name.empty()){
        QMessageBox::warning(nullptr, "Empty account name", "\nAccount name cannot be empty!\n",
                             QMessageBox::Ok);
        return;
    }

    if(login.empty() && password.empty()){
        QMessageBox::warning(nullptr, "Empty record!",
                             "\nPlease, fill at least one field \"Login\" or \"Password\"!\n", QMessageBox::Ok);
        return;
    }

    if(Data::Instance().accountList.find(name) != Data::Instance().accountList.end()){
        if(QMessageBox::warning(nullptr, "Account name is already exist!",
                                "\nThis account name is already exist!\nDo you want to override it?\n",
                                QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
            Data::Instance().accountList.find(name)->second.login = login;
            Data::Instance().accountList.find(name)->second.password = password;
            Data::Instance().accountList.find(name)->second.comment = comment;
            Data::Instance().Save();
            close();
        }
        return;
    }

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
