#include "Account.h"
using namespace tinyxml2;

void Account::Wrap(tinyxml2::XMLDocument& doc, tinyxml2::XMLNode* accounts) {
	XMLElement *el;
	XMLNode *account;

	account = doc.NewElement("account");
	accounts->InsertEndChild(account);

	el = doc.NewElement("key");
	el->SetText(key.c_str());
	account->InsertEndChild(el);

	el = doc.NewElement("login");
	el->SetText(login.c_str());
	account->InsertEndChild(el);

	el = doc.NewElement("password");
	el->SetText(password.c_str());
	account->InsertEndChild(el);

	el = doc.NewElement("comment");
	el->SetText(comment.c_str());
	account->InsertEndChild(el);	
}

void Account::Unwrap(XMLNode* xmlNode) {
    XMLElement* element = xmlNode->FirstChildElement("key");
    if(element->GetText() != nullptr)
        key = element->GetText();
    element = xmlNode->FirstChildElement("login");
    if(element->GetText() != nullptr)
        login = element->GetText();
    element = xmlNode->FirstChildElement("password");
    if(element->GetText() != nullptr)
        password = element->GetText();
    element = xmlNode->FirstChildElement("comment");
    if(element->GetText() != nullptr)
        comment = element->GetText();
}

Account::Account(XMLNode* xmlNode) {
	Unwrap(xmlNode);
}
