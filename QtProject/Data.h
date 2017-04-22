#pragma once
#include <map>
#include "Account.h"
#include "Card.h"
#include "Parser.h"

class Data {
public:
	static Data* Instance();
    std::map<std::string, Account> accountList;
	std::map<std::string,Card> cardList;
	std::string masterHash;
	void Save();
private:
	static Data *instance;
};
