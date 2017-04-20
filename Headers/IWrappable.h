#pragma once
#include <string>
#include "tynixml\tinyxml2.h"

class IWrappable {
public:
	virtual void Wrap(tinyxml2::XMLDocument&, tinyxml2::XMLNode*) = 0;
	virtual void Unwrap(tinyxml2::XMLNode*) = 0;
};