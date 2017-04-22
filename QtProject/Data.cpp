#include "Data.h"

Data* Data::instance = nullptr;

void Data::Save() {
	Parser p;
	p.Wrap();
}

Data* Data::Instance() {
    if(instance == nullptr) {
		instance = new Data();
		Parser p;
		p.Parse();
	}
	return instance;
}
