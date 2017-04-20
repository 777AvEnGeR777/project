#include "Data.h"

std::map<std::string, Account> Data::accountList;
std::map<std::string,Card> Data::cardList;
std::string Data::masterHash;

void Data::Save() {
	Parser p;
	p.Wrap();
}

void Data::Init() {
	Parser p;
	p.Parse();
}
