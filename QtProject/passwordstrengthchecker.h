#ifndef PASSWORDSTRENGTHCHECKER_H
#define PASSWORDSTRENGTHCHECKER_H
#include <string>
#include <cmath>
#include "enums.h"

class PasswordStrengthChecker
{
public:
    static PasswordStrengthChecker* Instance();
    PasswordStrength CheckPasswordStrength(const std::string &password);
private:
    static PasswordStrengthChecker* instance;
    int CalculateCharset(const std::string& password);
    PasswordStrength CalculateStrength(int charset, const std::string &password);
};

#endif // PASSWORDSTRENGTHCHECKER_H
