#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "IWrappable.h"

class Account: IWrappable {
public:
	std::string key;
	std::string login;
	std::string password;
	std::string comment;
	void Wrap(tinyxml2::XMLDocument&, tinyxml2::XMLNode*);
	void Unwrap(tinyxml2::XMLNode*);
	Account(std::string _key, std::string _login, std::string _password, std::string _comment):
		key(_key), login(_login), password(_password), comment(_comment) {}
	Account(tinyxml2::XMLNode*);
};

#endif
