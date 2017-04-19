#pragma once
#include <map>
#include "Account.h"
#include "Card.h"

class Data {
public:
	std::map<std::string, Account> accountList;
	std::map<std::string,Card> cardList;
	std::string masterHash;
	void Save();
	Data();
};
