#include "statecard.h"

StateCard::StateCard()
{

}
void StateCard::create(){
    cardform *card_form = new cardform;
    card_form->exec();
}

void StateCard::edit(QString key){
    cardform *card_form = new cardform;
    card_form->set_card_name(key.toStdString());
    card_form->exec();
}

void StateCard::build(){

}

void StateCard::del(QString key){
    Data::Instance().cardList.erase(Data::Instance().cardList.find(key.toStdString()));
    Data::Instance().Save();
}

void StateCard::save(){

}
