#include "Data.h"

void Data::Save() {
	Parser p;
	p.Wrap();
}

void Data::GetData() {
    Parser p;
    p.ParseData();
}

void Data::GetMaster() {
    Parser p;
    p.ParseMaster();
}

Data &Data::Instance() {
    static Data instance;
    return instance;
}
