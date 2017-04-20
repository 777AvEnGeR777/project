#pragma once
#include "tynixml\tinyxml2.h"
#include "Data.h"
#include "Encryptor.h"

class Parser {
public:
	Parser();

	void Parse();
	void Wrap();
private:
	std::string userDataToString();
};