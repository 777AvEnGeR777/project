#pragma once
#include <string>

class IWrappable {
public:
	virtual std::string Wrap() = 0;
	virtual void Unwrap(std::string xmlString) = 0;
};
