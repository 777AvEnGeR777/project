#ifndef PARSER_H
#define PARSER_H

#include "tynixml\tinyxml2.h"
#include "Data.h"
#include "Encryptor.h"

class Parser {
public:
	Parser();

    void ParseData();
    void ParseMaster();
	void Wrap();
private:
	std::string userDataToString();
};

#endif
