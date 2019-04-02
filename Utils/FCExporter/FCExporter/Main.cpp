#include "consts.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

#define TEST_BEFORE_ADD
#define MAGIC		0xD3010401

class DbManager {
private:
#define WRITE(b, s) { this->_stream.write(reinterpret_cast<char*>(&b), s); }
#define SWAP(x)		{ this->Swap(&x); }
	fstream		_stream;
	bool		_isOpen = false;
	uint16_t	_writtenItems = 0;

	// https://stackoverflow.com/users/95286/dingo
	template <typename T>
	inline void Swap(T* val) {
		unsigned char *memp = reinterpret_cast<unsigned char*>(val);
		std::reverse(memp, memp + sizeof(T));
	}

public:

	bool isOpen() {
		return this->_isOpen;
	}

	DbManager(std::string _fPath):
		_stream(_fPath, ios::out | ios::binary) {

		if (_stream.is_open()) {
			this->_isOpen = true;

			auto _magicBoi = MAGIC;

			SWAP(_magicBoi);
			WRITE(_magicBoi, sizeof(int));

			SWAP(this->_writtenItems);
			WRITE(this->_writtenItems, sizeof(uint16_t));
		}
	}

	~DbManager() {
		if (this->isOpen()) {
			this->_stream.flush();

			// Updates content counter.
			this->_stream.seekg(sizeof(int) + 0, ios::beg);
			SWAP(this->_writtenItems);
			WRITE(this->_writtenItems, sizeof(uint16_t));
			this->_stream.close();
		}
	}

	bool AddEntry(unsigned char* _buff, size_t _size, std::string _name, uint8_t toCompress = 0) {
		if (_buff != nullptr && _size > 0) {
			//auto _b64d = base64_encode(_buff, _size);

			std::string _b64d;
			_b64d.resize(_size);
			memcpy(&_b64d[0], _buff, _size);

#undef TEST_BEFORE_ADD
#ifdef TEST_BEFORE_ADD
			auto _rebuffed = base64_decode(_b64d);
			if (memcmp(_buff, _rebuffed.c_str(), _size) != 0)
				return false;
			
			_rebuffed.clear();
#endif

			auto _nameLength = _name.length();
			SWAP(_nameLength);
			WRITE(_nameLength, sizeof(int));
			WRITE(_name[0], _name.length());

			WRITE(toCompress, sizeof(uint8_t));

			if (toCompress) {
				/*
				auto _compressed = Gzip::compress(_b64d);
				_b64d.clear();

				auto _buffLength = _compressed.length();
				this->_stream.write(reinterpret_cast<char*>(&_buffLength), sizeof(int));
				this->_stream.write(reinterpret_cast<char*>(&_compressed[0]), _compressed.length());
				_compressed.clear();
				*/
				goto BYPASS;
			} else {

			BYPASS:
				auto _buffLength = _b64d.length();
				SWAP(_buffLength);
				WRITE(_buffLength, sizeof(int));
				WRITE(_b64d[0], _b64d.length());
				_b64d.clear();
			}
			this->_writtenItems++;

			return true;
		}

		return false;
	}

	uint16_t itemCount() {
		return this->_writtenItems;
	}

	void Flush() {
		this->_stream.flush();
	}
#undef WRITE
#undef SWAP
};

int main(int argc, char* argv[]) {

	DbManager* db = new DbManager("FConsts.d3v");
	if (db->isOpen()) {
		cout << "[+] ARCHIVE CREATED - MAGIC (0xD3010401)" << std::endl;
		////////////////////////////
		// SPARSE SERIALIZE		  //
		////////////////////////////
		cout << " |---- SPARSE CONSTANTS\n |" << std::endl;
		for (auto i = 0; i < 5; i++) 
			if (!db->AddEntry((unsigned char*)sparse_consts[i].array, sparse_consts[i].size, sparse_consts[i].name))
				cout << " |--[" << i << "] \"" << sparse_consts[i].name << "\" failed to add due to corrupted cast." << std::endl;
			else
				cout << " |--[" << i << "] Added \"" << sparse_consts[i].name << "\" (" << sparse_consts[i].size << ")" << std::endl;
		

		////////////////////////////
		// NON SPARSE SERIALIZE   //
		////////////////////////////
		cout << " |---- NON-SPARSE CONSTANTS\n |" << std::endl;
		for (auto i = 0; i < 78; i++) {
			if (!db->AddEntry((unsigned char*)non_sparse_consts[i].array, non_sparse_consts[i].size, non_sparse_consts[i].name))
				cout << " |--[" << i << "] \"" << non_sparse_consts[i].name << "\" failed to add due to corrupted cast." << std::endl;
			else
				cout << " |--[" << i << "] Added \"" << non_sparse_consts[i].name << "\" (" << non_sparse_consts[i].size << ")" << std::endl;
		}
		cout << "[-] DONE [" << db->itemCount() << "] ITEMS ADDED.\n";

		db->~DbManager();
		db = nullptr;
	}

	getchar();
	return 0;
}