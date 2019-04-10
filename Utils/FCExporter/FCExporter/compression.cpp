#include "compression.h"
#pragma comment(lib, "cryptlib.lib")

void Compression::Compress(unsigned char* _input, size_t _inSize, vector<byte>& _out) {
	if (_inSize > 0 && _input != nullptr) {

		CryptoPP::Gzip _compressor;
		_compressor.Put((byte*)_input, _inSize);
		_compressor.MessageEnd();

		auto avail = _compressor.MaxRetrievable();
		if (avail) {
			_out.resize(avail);

			_compressor.Get(&_out[0], _out.size());
		}
		
	}
}
