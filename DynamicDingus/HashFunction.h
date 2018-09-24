#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H
#include <functional>
namespace HashFunction {
	typedef std::function< unsigned int(const char*, unsigned int)> HashFunc;
	// implementation of a basic addition hash
	unsigned int badHash(const char* data, unsigned int length);
	// ADD YOUR FUNCTIONS HERE
	unsigned int BKDRHash(unsigned char* data, unsigned int size);
	unsigned int ELFHash(unsigned char* data, unsigned int size);
	std::string owoHash(unsigned char* data, unsigned int size);
	// a helper to access a default hash function
	//todo I don't think this works as Is but I call the hash type manually so no issue
	static std::string (*default)(unsigned char* data, unsigned size) = owoHash;
}
#endif // HASHFUNCTION_H
