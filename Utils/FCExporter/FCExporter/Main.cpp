#include "consts.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include "compression.h"
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
		unsigned char* memp = reinterpret_cast<unsigned char*>(val);
		std::reverse(memp, memp + sizeof(T));
	}

public:

	bool isOpen() {
		return this->_isOpen;
	}

	DbManager(std::string _fPath) :
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

	bool AddEntry(unsigned char* _buff, size_t _size, size_t _el_size, std::string _name, uint8_t toCompress = 0) {
		if (_buff != nullptr && _size > 0) {

			std::string _b64d;
			_b64d.resize(_size);
			memcpy(&_b64d[0], _buff, _size);

			int _nameLength = _name.length();
			SWAP(_nameLength);
			WRITE(_nameLength, sizeof(int));
			WRITE(_name[0], _name.length());			
			WRITE(toCompress, sizeof(uint8_t));
			SWAP(_el_size);
			WRITE(_el_size, sizeof(int));
			if (toCompress) {

				if (_b64d.data() == nullptr || _size <= 0)
					throw std::runtime_error("Input data and/or size is null");

				vector<byte> _outBuff;
				Compression::Compress((unsigned char*)_b64d.data(), _b64d.length(), _outBuff);

				if (_outBuff.data() == nullptr)
					throw std::runtime_error("Returned compressed buffer null despite should not");

				// Remember the SWAP?
				size_t _cpy = _outBuff.size();

				SWAP(_cpy);
				WRITE(_cpy, sizeof(int));
				WRITE(_outBuff.data()[0], _outBuff.size());

				_b64d.clear();
				_outBuff.clear();
			} else {

				int _buffLength = _b64d.length();
				SWAP(_buffLength);
				WRITE(_buffLength, sizeof(int));
				WRITE(_b64d[0], _b64d.length());
				_b64d.clear();
			}
			this->_writtenItems++;
			// Sometimes I need to check the raw buffer to be sure it's working.
			this->_stream.flush(); 

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

	DbManager* db = new DbManager("database.d3v");
	if (db->isOpen()) {
		cout << "[+] ARCHIVE CREATED - MAGIC (0xD3010401)" << std::endl;
		////////////////////////////
		// SPARSE SERIALIZE		  //
		////////////////////////////
		cout << " |---- SPARSE CONSTANTS\n |" << std::endl;
		for (auto i = 0; i < 5; i++) {
			uint8_t shouldCompress = sparse_consts[i].size > 20 ? 0x01 : 0x00;

			if (!db->AddEntry((unsigned char*)sparse_consts[i].array, sparse_consts[i].size, sparse_consts[i].size_elem, sparse_consts[i].name, shouldCompress))
				cout << " |--[" << i << "] \"" << sparse_consts[i].name << "\" failed to add due to corrupted cast." << std::endl;
			else
				cout << " |--[" << i << "] Added \"" << sparse_consts[i].name << "\" (" << sparse_consts[i].size << ")" << std::endl;
		}
		

		////////////////////////////
		// NON SPARSE SERIALIZE   //
		////////////////////////////
		cout << " |---- NON-SPARSE CONSTANTS\n |" << std::endl;
		for (auto i = 0; i < 119; i++) {
			uint8_t shouldCompress = sparse_consts[i].size > 20 ? 0x01 : 0x00;

			if (!db->AddEntry((unsigned char*)non_sparse_consts[i].array, non_sparse_consts[i].size, non_sparse_consts[i].size_elem, non_sparse_consts[i].name, shouldCompress))
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
