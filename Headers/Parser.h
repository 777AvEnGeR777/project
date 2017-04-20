#pragma once
#include "Parser.h"
#include <iostream>
#include "tinyxml2.h"
#include "Data.h"



class Parser {
public:
	Parser();

	void Parse(Data *data);
	void Wrap(Data *data);
private:
	std::string userDataToString(Data *data);
};