#include "Encryptor.h"

byte Encryptor::secretKey[CryptoPP::AES::MAX_KEYLENGTH] = {0};
const byte Encryptor::iv[CryptoPP::AES::BLOCKSIZE] = { 17, 169, 134, 74, 155, 98, 110, 24,
	237, 60, 198, 177, 86, 74, 193, 8 };

std::string Encryptor::Encrypt(std::string str) {
	std::string cipher;
	CryptoPP::StringSink* sink = new CryptoPP::StringSink(cipher);
	CryptoPP::Base64Encoder* base64_enc = new CryptoPP::Base64Encoder(sink);
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption aes(secretKey, sizeof(secretKey), iv);
	CryptoPP::StreamTransformationFilter* aes_enc = new CryptoPP::StreamTransformationFilter(aes, base64_enc);
	CryptoPP::StringSource source(str, true, aes_enc);
	return cipher;
}

std::string Encryptor::Decrypt(std::string str) {
	std::string plainText;
	CryptoPP::StringSink* sink = new CryptoPP::StringSink(plainText);
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption aes(secretKey, sizeof(secretKey), iv);
	CryptoPP::StreamTransformationFilter* aes_dec = new CryptoPP::StreamTransformationFilter(aes, sink);
	CryptoPP::Base64Decoder* base64_dec = new CryptoPP::Base64Decoder(aes_dec);
	CryptoPP::StringSource decryptor(str, true, base64_dec);
	return plainText;
}

std::string Encryptor::Hash(std::string str) {
	CryptoPP::SHA512 hash;
	byte digest[CryptoPP::SHA512::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)str.c_str(), str.length());

	CryptoPP::Base64Encoder encoder;
	std::string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();
	
	return output;
}

void Encryptor::DerieveKey(std::string password) {
	byte salt[] = "6pEZCNFKh3";
	size_t saltLen = strlen((const char*)salt);

	CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA1> pbkdf2;
	pbkdf2.DeriveKey(secretKey, sizeof(secretKey), 0, (const byte*)password.data(), password.length(),
		salt, saltLen, 1);
}
