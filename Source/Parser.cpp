#include "Parser.h"
#include "Account.h"
#include "Data.h"
#include "Card.h"
#include "Encryptor.h"
#include <iostream>
#include "tinyxml2.h"
#include <fstream>
#include <map>


using namespace tinyxml2;

Parser::Parser() {
	
}

void Parser::Parse(Data *data) {
	std::string s_data;

	XMLDocument doc;
	XMLError error = doc.LoadFile("data.xml");
	if (error != tinyxml2::XML_SUCCESS) return;


	XMLNode * pRoot = doc.FirstChild();
	XMLElement * masterHash = pRoot->FirstChildElement("master");
	XMLElement * raw_data = pRoot->FirstChildElement("data");
	
	(*data).masterHash = masterHash->GetText();
	s_data = raw_data->GetText();
	s_data = Encryptor::Decrypt(s_data);
	
	XMLDocument tmp;
	tmp.Parse(s_data.c_str());
	
	XMLNode  *accountsNode = tmp.FirstChildElement("accounts");
	XMLNode  *cardsNode = tmp.FirstChildElement("cards");

	std::string key;
	for (XMLNode* child = accountsNode->FirstChild(); child != NULL; child = child->NextSibling())
	{
		key = child->FirstChildElement("key")->GetText();
		
		(*data).accountList[key] = Account(
			key,
			child->FirstChildElement("login")->GetText(),
			child->FirstChildElement("password")->GetText(),
			child->FirstChildElement("comment")->GetText()
		);
	}

	for (XMLNode* child = cardsNode->FirstChild(); child != NULL; child = child->NextSibling())
	{
		key = child->FirstChildElement("key")->GetText();

		(*data).cardList[key] = Card(
			key,
			child->FirstChildElement("number")->GetText(),
			child->FirstChildElement("date")->GetText(),
			child->FirstChildElement("cvc")->GetText(),
			child->FirstChildElement("owner")->GetText(),
			child->FirstChildElement("pin")->GetText(),
			child->FirstChildElement("secret")->GetText(),
			child->FirstChildElement("phone")->GetText()
		);

	}
	
}

void Parser::Wrap(Data *data) {
	std::string userData = userDataToString(data);	
	userData = Encryptor::Encrypt(userData);
	
	XMLDocument doc;

	XMLNode *proot = doc.NewElement("root");
	XMLElement *master = doc.NewElement("master");
	XMLElement *xml_data = doc.NewElement("data");
	
	master->SetText((*data).masterHash.c_str());
	xml_data->SetText(userData.c_str());
	
	doc.InsertEndChild(proot);
	proot->InsertEndChild(master);
	proot->InsertEndChild(xml_data);

	doc.SaveFile("data.xml");

}

std::string Parser::userDataToString(Data *data){
	XMLDocument tmp;
	XMLElement * el;
	XMLNode *account;
	XMLNode *accounts = tmp.NewElement("accounts");
	tmp.InsertEndChild(accounts);
	for(std::map<std::string,Account>::iterator iter = (*data).accountList.begin(); 
		iter != (*data).accountList.end(); ++iter){
			account = tmp.NewElement("account");
			accounts->InsertEndChild(account);

			el = tmp.NewElement("key");
			el->SetText(iter->second.key.c_str());
			account->InsertEndChild(el);

			el = tmp.NewElement("login");
			el->SetText(iter->second.login.c_str());
			account->InsertEndChild(el);

			el = tmp.NewElement("password");
			el->SetText(iter->second.password.c_str());
			account->InsertEndChild(el);

			el = tmp.NewElement("comment");
			el->SetText(iter->second.comment.c_str());
			account->InsertEndChild(el);			
	}

	XMLNode *card;
	XMLNode *cards = tmp.NewElement("cards");
	tmp.InsertEndChild(cards);
	for(std::map<std::string,Card>::iterator iter = (*data).cardList.begin(); 
		iter != (*data).cardList.end(); ++iter){
			card = tmp.NewElement("card");
			cards->InsertEndChild(card);

			el = tmp.NewElement("key");
			el->SetText(iter->second.key.c_str());
			card->InsertEndChild(el);

			el = tmp.NewElement("number");
			el->SetText(iter->second.number.c_str());
			card->InsertEndChild(el);

			el = tmp.NewElement("date");
			el->SetText(iter->second.date.c_str());
			card->InsertEndChild(el);

			el = tmp.NewElement("cvc");
			el->SetText(iter->second.cvc.c_str());
			card->InsertEndChild(el);

			el = tmp.NewElement("pin");
			el->SetText(iter->second.pin.c_str());
			card->InsertEndChild(el);	

			el = tmp.NewElement("owner");
			el->SetText(iter->second.owner.c_str());
			card->InsertEndChild(el);

			el = tmp.NewElement("phone");
			el->SetText(iter->second.phone.c_str());
			card->InsertEndChild(el);	

			el = tmp.NewElement("secret");
			el->SetText(iter->second.secret.c_str());
			card->InsertEndChild(el);
	}
	//temp kostyl
	tmp.SaveFile("tmp.xml");

	std::ifstream file("tmp.xml");
	std::string temp;
	std::string data_string;
	while(std::getline(file, temp)) {
		data_string += temp + '\n';
	}
	std::remove("tmp.xml");
	return data_string;
}