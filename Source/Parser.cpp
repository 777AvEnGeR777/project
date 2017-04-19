#include "Parser.h"
#include <iostream>
#include "tinyxml2.h"
#include "Data.h"
#include <iostream>

using namespace tinyxml2;

Parser::Parser() {
	
}

void Parser::Parse() {

}

void Parser::Wrap(Data *data) {

    XMLDocument doc;
   
	XMLNode * pRoot = doc.NewElement("Root");
	doc.InsertFirstChild(pRoot);
	
    //XMLElement* titleElement = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" );

    
	XMLElement * pElement = doc.NewElement("IntValue");
	pElement->SetText(1110);

	

	pRoot->InsertEndChild(pElement);
	
	XMLPrinter printer;
    pRoot->Accept( &printer );
	
	std::cout << printer.CStr();



	int a;
	std::cin >> a;
	
	//std::cout << (*data).accountList["f"].key;
}