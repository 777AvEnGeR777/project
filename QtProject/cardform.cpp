#include "cardform.h"
#include "ui_cardform.h"

cardform::cardform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cardform)
{
    ui->setupUi(this);

    connect(ui->button_cardSave, SIGNAL(clicked(bool)), this, SLOT(save_card()));
    connect(ui->button_show_secret,SIGNAL(clicked(bool)), this, SLOT(changeSecretVisibility()));
    connect(ui->button_show_pin, SIGNAL(clicked(bool)), this, SLOT(changePinVisibility()));
}

cardform::~cardform()
{
    delete ui;
}

void cardform::set_card_name(std::string name){
    account_name = name;
    ui->field_cardName->setText(name.c_str());
    ui->field_cardName->setEnabled(false);
    ui->field_cardCVC->setText(Data::Instance().cardList.find(name.c_str())->second.cvc.c_str());
    ui->field_cardDate->setText(Data::Instance().cardList.find(name.c_str())->second.date.c_str());
    ui->field_cardNumber->setText(Data::Instance().cardList.find(name.c_str())->second.number.c_str());
    ui->field_cardOwner->setText(Data::Instance().cardList.find(name.c_str())->second.owner.c_str());
    ui->field_cardPhone->setText(Data::Instance().cardList.find(name.c_str())->second.phone.c_str());
    ui->field_cardSecret->setText(Data::Instance().cardList.find(name.c_str())->second.secret.c_str());
    ui->field_cardPin->setText(Data::Instance().cardList.find(name.c_str())->second.pin.c_str());
}

void cardform::save_card(){
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
        return;
    }

    if(number.empty()){
        QMessageBox::warning(nullptr, "Empty card number!", "\nPlease, fill the \"Card number\" field!\n",
                             QMessageBox::Ok);
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

void cardform::changeSecretVisibility()
{
    if(ui->button_show_secret->isChecked())
        FieldManager::Instance().showField(ui->field_cardSecret);
    else
        FieldManager::Instance().hideField(ui->field_cardSecret);
}

void cardform::changePinVisibility()
{
    if(ui->button_show_pin->isChecked())
        FieldManager::Instance().showField(ui->field_cardPin);
    else
        FieldManager::Instance().hideField(ui->field_cardPin);
}

