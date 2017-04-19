#pragma once
#include <string>
#include "cryptopp565\cryptlib.h"
#include "cryptopp565\sha.h"
#include "cryptopp565\aes.h"
#include "cryptopp565\base64.h"
#include "cryptopp565\modes.h"
#include "cryptopp565\pwdbased.h"

class Encryptor {
public:
	static std::string Encrypt(std::string str);
	static std::string Decrypt(std::string str);
	static std::string Hash(std::string str);
	static void DerieveKey(std::string password);
private:
	static byte secretKey[CryptoPP::AES::MAX_KEYLENGTH];
	static const byte iv[CryptoPP::AES::BLOCKSIZE];
};