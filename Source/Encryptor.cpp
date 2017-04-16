#include "Encryptor.h"

// Temp hardcoded variables, test only
byte aes_key[32] = {0};
byte iv_temp[16] = {0};

std::string Encryptor::Encrypt(std::string str) {
	// TODO
	std::string cipher;
	CryptoPP::StringSink* sink = new CryptoPP::StringSink(cipher);
	CryptoPP::Base64Encoder* base64_enc = new CryptoPP::Base64Encoder(sink);
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption aes(aes_key, sizeof(aes_key), iv_temp);
	CryptoPP::StreamTransformationFilter* aes_enc = new CryptoPP::StreamTransformationFilter(aes, base64_enc);
	CryptoPP::StringSource source(str, true, aes_enc);
	return cipher;
}

std::string Encryptor::Decrypt(std::string str) {
	// TODO
	std::string plainText;
	CryptoPP::StringSink* sink = new CryptoPP::StringSink(plainText);
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption aes(aes_key, sizeof(aes_key), iv_temp);
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
	// TODO
}
