#include <map>
#include "Account.h"
#include "Card.h"

class Data {
public:
	static std::map<std::string, Account> accountList;
	static std::map<std::string,Card> cardList;
	static std::string masterHash;
	void Save();
	Data();
};
