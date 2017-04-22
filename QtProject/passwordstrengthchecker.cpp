#include "passwordstrengthchecker.h"

PasswordStrengthChecker &PasswordStrengthChecker::Instance()
{
    static PasswordStrengthChecker instance;
    return instance;
}

int PasswordStrengthChecker::CalculateCharset(const std::string &password)
{
    const std::string alpha = "abcdefghijklmnopqrstuvwxyz";
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string upper_punct = "~`!@#$%^&*()-_+=";
    const std::string digits = "1234567890";

    int totalChars = 0x7f - 0x20;
    int alphaChars = alpha.length();
    int upperChars = upper.length();
    int upper_punctChars = upper_punct.length();
    int digitChars = digits.length();
    int otherChars = totalChars - (alphaChars + upperChars + upper_punctChars + digitChars);

    bool fAlpha = false;
    bool fUpper = false;
    bool fUpperPunct = false;
    bool fDigit = false;
    bool fOther = false;
    int charset = 0;

    for(unsigned int i = 0; i < password.length(); i++) {
        char character = password[i];

        if(!fAlpha && alpha.find(character) != std::string::npos) {
            fAlpha = true;
            charset += alphaChars;
        }
        else if(!fUpper && upper.find(character) != std::string::npos) {
            fUpper = true;
            charset += upperChars;
        }
        else if(!fDigit && digits.find(character) != std::string::npos) {
            fDigit = true;
            charset += digitChars;
        }
        else if(!fUpperPunct && upper_punct.find(character) != std::string::npos) {
            fUpperPunct = true;
            charset += upper_punctChars;
        }
        else if(!fOther) {
            fOther = true;
            charset += otherChars;
        }
        else
            break;
    }
    return charset;
}

PasswordStrength PasswordStrengthChecker::CalculateStrength(int charset, const std::string& password)
{
    double bits = std::log(charset) * (password.length() / std::log(2));
    bits = std::floor(bits);

    if(bits >= 128) {
        return BEST;
    }
    else if(bits >= 64) {
        return STRONG;
    }
    else if(bits >= 52) {
        return MEDIUM;
    }
    else {
        return WEAK;
    }
}

PasswordStrength PasswordStrengthChecker::CheckPasswordStrength(const std::string& password)
{
    if(password.empty())
    {
        return NO_PASSWORD;
    }

    int charset = CalculateCharset(password);

    return CalculateStrength(charset, password);
}
