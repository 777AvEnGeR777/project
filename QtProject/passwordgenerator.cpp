#include "passwordgenerator.h"

PasswordGenerator& PasswordGenerator::Instance()
{
    static PasswordGenerator instance;
    return instance;
}

std::string PasswordGenerator::Generate(int passwordLength, bool includeChars, bool includeDigits,
                                        bool includeSpecial)
{
    // TODO
    return "";
}
