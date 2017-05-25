#include "statecard.h"

StateCard::StateCard()
{

}
void StateCard::create(){

}

void StateCard::edit(QString key){
    card *card_form = new cardform;
    card_form->set_card_name(key);

    card_form->exec();
}

void StateCard::build(){

}

void StateCard::del(){

}

void StateCard::save(){

}
