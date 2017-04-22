#include "Data.h"

Data* Data::instance = nullptr;

void Data::Save() {
	Parser p;
	p.Wrap();
}

void Data::GetData() {
    Parser p;
    p.ParseData();
}

Data* Data::Instance() {
    if(instance == nullptr) {
		instance = new Data();
		Parser p;
        p.ParseMaster();
	}
	return instance;
}
