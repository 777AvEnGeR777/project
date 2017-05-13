#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <string>
#include <algorithm>
class PasswordGenerator
{
public:
    static PasswordGenerator& Instance();
    std::string Generate(int passwordLength, bool includeChars, bool includeDigits, bool includeSpecial);
private:
    PasswordGenerator() {}
    PasswordGenerator(const PasswordGenerator&);
    PasswordGenerator& operator=(PasswordGenerator&);
};

#endif // PASSWORDGENERATOR_H
