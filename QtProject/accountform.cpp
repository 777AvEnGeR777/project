#include "accountform.h"
#include "ui_accountform.h"

accountform::accountform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountform)
{

    ui->setupUi(this);

    ui->field_password->setEchoMode(QLineEdit::Password);

    ui->cardForm->hide();

    connect(ui->button_save, SIGNAL(clicked(bool)), this, SLOT(save_account()));
    connect(ui->button_showpassword, SIGNAL(pressed()), this, SLOT(toggleShowPassword()));
    connect(ui->button_showpassword, SIGNAL(released()), this, SLOT(toggleHidePassword()));
    connect(ui->button_generate, SIGNAL(clicked(bool)), this, SLOT(generatePassword()));

    connect(ui->button_cardSave, SIGNAL(clicked(bool)), this, SLOT(save_card()));
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

void accountform::set_form_type(std::string set_type){
    if(set_type == "card"){
        ui->accountForm->hide();
        ui->cardForm->show();
        type=set_type;
    }
}

void accountform::set_account_name(std::string name){
    account_name = name;
    if(type == "card"){
        ui->field_cardName->setText(name.c_str());
        ui->field_cardName->setEnabled(false);
        ui->field_cardCVC->setText(Data::Instance().cardList.find(name.c_str())->second.cvc.c_str());
        ui->field_cardDate->setText(Data::Instance().cardList.find(name.c_str())->second.date.c_str());
        ui->field_cardNumber->setText(Data::Instance().cardList.find(name.c_str())->second.number.c_str());
        ui->field_cardOwner->setText(Data::Instance().cardList.find(name.c_str())->second.owner.c_str());
        ui->field_cardPhone->setText(Data::Instance().cardList.find(name.c_str())->second.phone.c_str());
        ui->field_cardSecret->setText(Data::Instance().cardList.find(name.c_str())->second.secret.c_str());
        ui->field_cardPin->setText(Data::Instance().cardList.find(name.c_str())->second.pin.c_str());
    }else{
        ui->field_accountName->setText(name.c_str());
        ui->field_accountName->setEnabled(false);
        ui->field_comment->setText(Data::Instance().accountList.find(name.c_str())->second.comment.c_str());
        ui->field_login->setText(Data::Instance().accountList.find(name.c_str())->second.login.c_str());
        ui->field_password->setText(Data::Instance().accountList.find(name.c_str())->second.password.c_str());
    }
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

    if(login.empty() && password.empty()){
        QMessageBox::warning(nullptr, "Empty record!",
                             "\nPlease, fill at least one field \"Login\" or \"Password\"!\n", QMessageBox::Ok);
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

void accountform::save_card(){
    std::string name = ui->field_cardName->text().toStdString();
    std::string number = ui->field_cardNumber->text().toStdString();
    std::string date = ui->field_cardDate->text().toStdString();
    std::string cvc = ui->field_cardCVC->text().toStdString();
    std::string owner = ui->field_cardOwner->text().toStdString();
    std::string pin = ui->field_cardPin->text().toStdString();
    std::string secret = ui->field_cardSecret->text().toStdString();
    std::string phone = ui->field_cardPhone->text().toStdString();

    Card card(name, number, date, cvc, owner, pin, secret, phone);

    if(name.empty()){
        QMessageBox::warning(nullptr, "Empty card name", "\nCard name cannot be empty!\n",
                             QMessageBox::Ok);
        Data::Instance().cardList.find(name)->second.number = number;
        Data::Instance().cardList.find(name)->second.date = date;
        Data::Instance().cardList.find(name)->second.cvc = cvc;
        Data::Instance().cardList.find(name)->second.owner = owner;
        Data::Instance().cardList.find(name)->second.pin = pin;
        Data::Instance().cardList.find(name)->second.secret = secret;
        Data::Instance().cardList.find(name)->second.phone = phone;
        Data::Instance().Save();
        return;
    }

    if(Data::Instance().cardList.find(name) != Data::Instance().cardList.end()){
        if(QMessageBox::warning(nullptr, "Card name is already exist!",
                                "\nThis card name is already exist!\nDo you want to override it?\n",
                                QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
            Data::Instance().cardList.find(account_name)->second.number = number;
            Data::Instance().cardList.find(account_name)->second.date = date;
            Data::Instance().cardList.find(account_name)->second.cvc = cvc;
            Data::Instance().cardList.find(account_name)->second.owner = owner;
            Data::Instance().cardList.find(account_name)->second.pin = pin;
            Data::Instance().cardList.find(account_name)->second.secret = secret;
            Data::Instance().cardList.find(account_name)->second.phone = phone;
            Data::Instance().Save();
            close();
        }
        return;
    }

    if(account_name == ""){
        Data::Instance().cardList.insert(std::make_pair(name, card));
    }else{
        Data::Instance().cardList.find(account_name)->second.number = number;
        Data::Instance().cardList.find(account_name)->second.date = date;
        Data::Instance().cardList.find(account_name)->second.cvc = cvc;
        Data::Instance().cardList.find(account_name)->second.owner = owner;
        Data::Instance().cardList.find(account_name)->second.pin = pin;
        Data::Instance().cardList.find(account_name)->second.secret = secret;
        Data::Instance().cardList.find(account_name)->second.phone = phone;
    }

    Data::Instance().Save();
    close();
}
