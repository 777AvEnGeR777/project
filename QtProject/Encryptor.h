#include <string>
#include "cryptopp565/cryptlib.h"
#include "cryptopp565/sha.h"
#include "cryptopp565/aes.h"
#include "cryptopp565/base64.h"
#include "cryptopp565/modes.h"
#include "cryptopp565/pwdbased.h"

class Encryptor {
public:
	static Encryptor* Instance();
	std::string Encrypt(std::string str);
	std::string Decrypt(std::string str);
	std::string Hash(std::string str);
	void DerieveKey(std::string password);
private:
	static Encryptor* instance;
	static byte secretKey[CryptoPP::AES::MAX_KEYLENGTH];
	static const byte iv[CryptoPP::AES::BLOCKSIZE];
};
