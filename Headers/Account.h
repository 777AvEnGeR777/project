#pragma once
#include "IWrappable.h"

class Account: IWrappable {
public:
	std::string key;
	std::string login;
	std::string password;
	std::string comment;
	std::string Wrap();
	void Unwrap(std::string xmlString);
	Account(std::string _key, std::string _login, std::string _password, std::string _comment):
		key(_key), login(_login), password(_password), comment(_comment) {}
	Account(std::string xmlString);
	Account():key(""), login(""), password(""), comment(""){};
};