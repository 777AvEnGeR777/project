#include "Parser.h"
#define FILE_NAME "data.xml"
using namespace tinyxml2;

Parser::Parser() {

}

void Parser::Parse() {
	std::string s_data;

	XMLDocument doc;
	XMLError error = doc.LoadFile(FILE_NAME);
	if (error != tinyxml2::XML_SUCCESS) return;


	XMLNode * pRoot = doc.FirstChild();
	XMLElement * masterHash = pRoot->FirstChildElement("master");
	XMLElement * raw_data = pRoot->FirstChildElement("data");
	
	Data::masterHash = masterHash->GetText();
	s_data = raw_data->GetText();
	s_data = Encryptor::Decrypt(s_data);
	
	XMLDocument tmp;
	tmp.Parse(s_data.c_str());
	
	XMLNode  *accountsNode = tmp.FirstChildElement("accounts");
	XMLNode  *cardsNode = tmp.FirstChildElement("cards");

	std::string key;
	for (XMLNode* child = accountsNode->FirstChild(); child != NULL; child = child->NextSibling())
	{
		Account account(child);
		Data::accountList.insert(std::pair<std::string, Account>(account.key, account));
	}

	for (XMLNode* child = cardsNode->FirstChild(); child != NULL; child = child->NextSibling())
	{
		Card card(child);
		Data::cardList.insert(std::pair<std::string, Card>(card.key, card));
	}
}

void Parser::Wrap() {
	std::string userData = userDataToString();	
	userData = Encryptor::Encrypt(userData);
	
	XMLDocument doc;

	XMLNode *proot = doc.NewElement("root");
	XMLElement *master = doc.NewElement("master");
	XMLElement *xml_data = doc.NewElement("data");
	
	master->SetText(Data::masterHash.c_str());
	xml_data->SetText(userData.c_str());
	
	doc.InsertEndChild(proot);
	proot->InsertEndChild(master);
	proot->InsertEndChild(xml_data);

	doc.SaveFile(FILE_NAME);


}

std::string Parser::userDataToString(){
	XMLDocument tmp;
	XMLNode *accounts = tmp.NewElement("accounts");
	tmp.InsertEndChild(accounts);
	for(std::map<std::string,Account>::iterator iter = Data::accountList.begin(); 
		iter != Data::accountList.end(); ++iter){
			iter->second.Wrap(tmp, accounts);		
	}

	XMLNode *cards = tmp.NewElement("cards");
	tmp.InsertEndChild(cards);
	for(std::map<std::string,Card>::iterator iter = Data::cardList.begin(); 
		iter != Data::cardList.end(); ++iter){
			iter->second.Wrap(tmp, cards);
	}

	XMLPrinter printer;
	tmp.Print(&printer);
	std::string data_string(printer.CStr());

	return data_string;
}