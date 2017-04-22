#include "Data.h"

void Data::Save() {
    parser->Wrap();
}

void Data::GetData() {
    parser->ParseData();
}

void Data::GetMaster() {
    parser->ParseMaster();
}

Data &Data::Instance() {
    static Data instance;
    return instance;
}
