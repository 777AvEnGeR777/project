#include "stateaccount.h"
#include <QMessageLogger>


StateAccount::StateAccount()
{

}

void StateAccount::create(){
    accountform *account_form = new accountform;
    account_form->exec();
}

void StateAccount::build(){

}

void StateAccount::edit(QString key){
    accountform *account_form = new accountform;
    account_form->set_account_name(key.toUtf8().constData());
    account_form->exec();
}

void StateAccount::save(){

}

void StateAccount::del(QString key){
    Data::Instance().accountList.erase(Data::Instance().accountList.find(key.toStdString()));
    Data::Instance().Save();
}
