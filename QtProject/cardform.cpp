#include "cardform.h"
#include "ui_cardform.h"

cardform::cardform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cardform)
{
    ui->setupUi(this);
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
    ui->field_cardPin->setText(Data::Instance().cardList.find(name.c_str())->second.pin.c_str())
}
