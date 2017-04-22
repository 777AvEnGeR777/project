#include "Parser.h"
#define FILE_NAME "data.xml"
using namespace tinyxml2;

Parser::Parser() {

}

void Parser::ParseMaster() {
    XMLDocument doc;
    XMLError error = doc.LoadFile(FILE_NAME);
    if (error != tinyxml2::XML_SUCCESS) return;

    XMLNode * pRoot = doc.FirstChild();
    XMLElement * masterHash = pRoot->FirstChildElement("master");
    Data::Instance().masterHash = masterHash->GetText();
}

void Parser::ParseData() {
	std::string s_data;

	XMLDocument doc;
	XMLError error = doc.LoadFile(FILE_NAME);
	if (error != tinyxml2::XML_SUCCESS) return;

	XMLNode * pRoot = doc.FirstChild();
	XMLElement * raw_data = pRoot->FirstChildElement("data");
	
	s_data = raw_data->GetText();
    s_data = Encryptor::Instance().Decrypt(s_data);
	
	XMLDocument tmp;
	tmp.Parse(s_data.c_str());
	
	XMLNode  *accountsNode = tmp.FirstChildElement("accounts");
	XMLNode  *cardsNode = tmp.FirstChildElement("cards");

	for (XMLNode* child = accountsNode->FirstChild(); child != NULL; child = child->NextSibling())
	{
		Account account(child);
        Data::Instance().accountList.insert(std::pair<std::string, Account>(account.key, account));
	}

	for (XMLNode* child = cardsNode->FirstChild(); child != NULL; child = child->NextSibling())
	{
		Card card(child);
        Data::Instance().cardList.insert(std::pair<std::string, Card>(card.key, card));
	}
}

void Parser::Wrap() {
	std::string userData = userDataToString();	
    userData = Encryptor::Instance().Encrypt(userData);
	
	XMLDocument doc;

	XMLNode *proot = doc.NewElement("root");
	XMLElement *master = doc.NewElement("master");
	XMLElement *xml_data = doc.NewElement("data");
	
    master->SetText(Data::Instance().masterHash.c_str());
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
    for(auto iter = Data::Instance().accountList.begin();
        iter != Data::Instance().accountList.end(); ++iter){
			iter->second.Wrap(tmp, accounts);		
	}

    XMLNode *cards = tmp.NewElement("cards");
	tmp.InsertEndChild(cards);
    for(auto iter = Data::Instance().cardList.begin();
        iter != Data::Instance().cardList.end(); ++iter){
			iter->second.Wrap(tmp, cards);
	}

	XMLPrinter printer;
	tmp.Print(&printer);
	std::string data_string(printer.CStr());

	return data_string;
}
