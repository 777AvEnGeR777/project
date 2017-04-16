#include <string>
#include "cryptolib.h"
#include "cryptopp565\sha.h"
#include "cryptopp565\aes.h"
#include "cryptopp565\base64.h"
#include "cryptopp565\modes.h"

class Encryptor {
public:
	static std::string Encrypt(std::string str);
	static std::string Decrypt(std::string str);
	static std::string Hash(std::string str);
private:
	static byte secretKey[CryptoPP::AES::MAX_KEYLENGTH];
	static byte iv[CryptoPP::AES::IV_LENGTH];
	static void DerieveKey(std::string password);
};