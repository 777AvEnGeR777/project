#include "Card.h"
using namespace tinyxml2;

void Card::Wrap(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode* cards) {
	XMLNode *card;
	XMLElement * el;
	card = doc.NewElement("card");
	cards->InsertEndChild(card);

	el = doc.NewElement("key");
	el->SetText(key.c_str());
	card->InsertEndChild(el);

	el = doc.NewElement("number");
	el->SetText(number.c_str());
	card->InsertEndChild(el);

	el = doc.NewElement("date");
	el->SetText(date.c_str());
	card->InsertEndChild(el);

	el = doc.NewElement("cvc");
	el->SetText(cvc.c_str());
	card->InsertEndChild(el);

	el = doc.NewElement("owner");
	el->SetText(owner.c_str());
	card->InsertEndChild(el);

	el = doc.NewElement("pin");
	el->SetText(pin.c_str());
	card->InsertEndChild(el);	

	el = doc.NewElement("phone");
	el->SetText(phone.c_str());
	card->InsertEndChild(el);	

	el = doc.NewElement("secret");
	el->SetText(secret.c_str());
	card->InsertEndChild(el);
}

void Card::Unwrap(XMLNode* xmlNode) {
    XMLElement* element = xmlNode->FirstChildElement("key");
    if(element->GetText() != nullptr)
        key = element->GetText();
    element = xmlNode->FirstChildElement("number");
    if(element->GetText() != nullptr)
        number = element->GetText();
    element = xmlNode->FirstChildElement("date");
    if(element->GetText() != nullptr)
        date = element->GetText();
    element = xmlNode->FirstChildElement("cvc");
    if(element->GetText() != nullptr)
        cvc = element->GetText();
    element = xmlNode->FirstChildElement("owner");
    if(element->GetText() != nullptr)
        owner = element->GetText();
    element = xmlNode->FirstChildElement("pin");
    if(element->GetText() != nullptr)
        pin = element->GetText();
    element = xmlNode->FirstChildElement("secret");
    if(element->GetText() != nullptr)
        secret = element->GetText();
    element = xmlNode->FirstChildElement("phone");
    if(element->GetText() != nullptr)
        phone = element->GetText();
}

Card::Card(XMLNode* xmlNode) {
	Unwrap(xmlNode);
}
