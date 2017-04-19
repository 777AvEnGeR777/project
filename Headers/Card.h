#pragma once
#include "IWrappable.h"

class Card: IWrappable {
public:
	std::string key;
	std::string number;
	std::string date;
	std::string cvc;
	std::string owner;
	std::string pin;
	std::string secret;
	std::string phone;
	std::string Wrap();
	void Unwrap(std::string xmlString);
	Card(std::string _key, std::string _number, std::string _date, std::string _cvc, std::string _owner,
		std::string _pin, std::string _secret, std::string _phone): key(_key), number(_number),
		date(_date), cvc(_cvc), owner(_owner), pin(_pin), secret(_secret), phone(_phone) {}
	Card(std::string xmlString);
};