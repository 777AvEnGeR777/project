#include "passwordgenerator.h"

using std::string;

PasswordGenerator& PasswordGenerator::Instance()
{
    static PasswordGenerator instance;
    return instance;
}

std::string PasswordGenerator::Generate(int passwordLength, bool includeChars, bool includeDigits,
                                        bool includeSpecial)
{
    if(passwordLength < 4)
        passwordLength = 4;

    string password = "";
    const string specials = "!@#$%^&*()_+=?{}~";
    int numOfDigits = includeDigits ? 1 : 0;
    int numOfSmallChars = includeChars ? 1 : 0;
    int numOfBigChars = numOfSmallChars;
    int numOfSpecial = includeSpecial ? 1 : 0;
    int totalNum = numOfDigits + numOfBigChars + numOfSmallChars + numOfSpecial;
    int tempValue = 0;

    if(includeChars && totalNum != passwordLength) {
        tempValue = rand() % (passwordLength - totalNum + 1);
        numOfSmallChars += tempValue;
        totalNum += tempValue;
        if(totalNum != passwordLength) {
            if(!includeDigits && !includeSpecial)
                numOfBigChars += passwordLength - totalNum;
            else {
                tempValue = rand() % (passwordLength - totalNum + 1);
                numOfBigChars += tempValue;
                totalNum += tempValue;
            }
        }
    }

    if(includeDigits && totalNum != passwordLength) {
        if(!includeSpecial)
            numOfDigits += passwordLength - totalNum;
        else {
            tempValue = rand() % (passwordLength - totalNum);
            numOfDigits += tempValue;
            totalNum += tempValue;
        }
    }

    if(includeSpecial && totalNum != passwordLength)
        numOfSpecial += passwordLength - totalNum;

    for(int i = 0; i < numOfDigits; i++)
        password += rand() % 10 + '0';

    for(int i = 0; i < numOfBigChars; i++)
        password += rand() % 26 + 'A';

    for(int i = 0; i < numOfSmallChars; i++)
        password += rand() % 26 + 'a';

    for(int i = 0; i < numOfSpecial; i++)
        password += specials[rand() % specials.length()];

    std::random_shuffle(password.begin(), password.end());

    return password;
}
