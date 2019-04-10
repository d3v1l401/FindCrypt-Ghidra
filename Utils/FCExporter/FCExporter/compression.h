#pragma once
#ifndef _COMPR_H_
#define _COMPR_H_
#include <vector>
using namespace std;
#include <gzip.h>
using namespace CryptoPP;

class Compression {
private:


public:

	static void Compress(unsigned char* _input, size_t _inSize, vector<byte>& _out);
};

#endif