#include "Data.h"
#include "Parser.h"

void Data::Save() {
	Parser p;
	p.Wrap(this);
}

Data::Data() {
	Parser p;
	p.Parse(this);
}
