#include "Data.h"

Data* Data::instance = NULL;

void Data::Save() {
	Parser p;
	p.Wrap();
}

Data* Data::Instance() {
	if(instance == NULL) {
		instance = new Data();
		Parser p;
		p.Parse();
	}
	return instance;
}
