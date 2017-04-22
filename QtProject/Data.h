#pragma once
#include <map>
#include "Account.h"
#include "Card.h"
#include "Parser.h"

class Parser;

class Data {
public:
    static Data& Instance();
    std::map<std::string, Account> accountList;
	std::map<std::string,Card> cardList;
	std::string masterHash;
	void Save();
    void GetData();
    void GetMaster();
private:
    Data() {}
    Data(const Data&);
    Data& operator=(Data&);
    Parser* parser;

};
