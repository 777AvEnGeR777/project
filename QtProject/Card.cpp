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
	key = xmlNode->FirstChildElement("key")->GetText();
	number = xmlNode->FirstChildElement("number")->GetText();
	date = xmlNode->FirstChildElement("date")->GetText();
	cvc = xmlNode->FirstChildElement("cvc")->GetText();
	owner = xmlNode->FirstChildElement("owner")->GetText();
	pin = xmlNode->FirstChildElement("pin")->GetText();
	secret = xmlNode->FirstChildElement("secret")->GetText();
	phone = xmlNode->FirstChildElement("phone")->GetText();
}

Card::Card(XMLNode* xmlNode) {
	Unwrap(xmlNode);
}