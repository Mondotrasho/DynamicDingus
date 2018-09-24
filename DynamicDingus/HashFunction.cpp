#include "HashFunction.h"
namespace HashFunction {
	// implementation of a basic addition hash
	//http://datagenetics.com/blog/july12014/index.html notes
	unsigned int badHash(const char* data, unsigned int length) {
		unsigned int hash = 0;

		for (unsigned int i = 0; i < length; ++i)
			hash += data[i];
		return hash;
	}

	unsigned int BKDRHash(unsigned char* data, unsigned int size) {
		unsigned int hash = 0;
		for (unsigned int i = 0; i < size; ++i) {
			hash = (hash * 1313) + data[i];
		}
		return (hash & 0x7FFFFFFF);
	}

	unsigned int ELFHash(unsigned char* data, unsigned int size) {
		unsigned int hash = 0, x = 0;
		for (unsigned int i = 0; i < size; ++i) {
			hash = (hash << 4) + data[i];
			if ((x = hash & 0xF0000000L) != 0) {
				hash ^= (x >> 24);
				hash &= ~x;
			}
		}
		return (hash & 0x7FFFFFFF);
	}

	//my hash converts byte array to owo with equal case as !
	//todo MAAAYBE make == w or O issue I can see is it would increase collisions I imagine but its not the best hashing function collision wise anyway
	std::string owoHash(unsigned char* data, unsigned size)
	{
		char owo[3] = { 'O','W','!' };

		std::string hash;
		for (unsigned int i = 0; i < size; ++i) {
			if (data[i] > owo[i % 3])
			{
				hash += 'O';
			}
			if (data[i] < owo[i % 3])
			{
				hash += 'W';
			}
			if (data[i] == owo[i % 3])
			{
				hash += '!';
			}
		}
		return hash;
	}
}
