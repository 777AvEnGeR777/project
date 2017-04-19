#pragma once
#include "Parser.h"
#include <iostream>
#include "tinyxml2.h"
#include "Data.h"



class Parser {
public:
	Parser();

	void Parse();
	void Wrap(Data *data);
};