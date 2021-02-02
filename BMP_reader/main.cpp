#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class BMPimage {

public:

	BMPimage(string fileName) {
		_file.open(fileName, fstream::in | fstream::binary);		

		_readBitmapFileHeader();
		_readDIBheader();
	}

	~BMPimage() {
		_file.close();
	}
		
	int getImageSize() {
		cout << "The image size is: " << this->_fileSize << " by " << this->_bitmapHeight << endl;
		return this->_bitmapWidth * this->_bitmapHeight;
	}

private:
	static const int _bitmapFileHeaderSize = 14;
	static const int _dibHeaderSize = 12;

	fstream _file;

	char _bitmapFileHeader[_bitmapFileHeaderSize];
	int _fileSize;
	int _fileOffsetToPixelArray;

	char _dibHeader[_dibHeaderSize];
	int _headerSize;
	int _bitmapWidth;
	int _bitmapHeight;
	int _channelNumber;
	int _bitsPerPixel;

	void _readBitmapFileHeader() {
		for (int i = 0; i < _bitmapFileHeaderSize; i++) {
			_file.get(_bitmapFileHeader[i]);
		}

		_fileSize = (int)_bitmapFileHeader[2];
		_fileOffsetToPixelArray = (int)_bitmapFileHeader[10];
	}

	void _readDIBheader() {
		for (int i = 0; i < _dibHeaderSize; i++) {
			_file >> _dibHeader[i];
		}
		
		_headerSize = (int)_dibHeader[0];
		_bitmapWidth = (short)_dibHeader[2];
		_bitmapHeight = (short)_dibHeader[4];
		_channelNumber = (short)_dibHeader[6];
		_bitsPerPixel = (short)_dibHeader[8];

		int bytesLeft = _headerSize - _dibHeaderSize;

		for (int i = 0; i < bytesLeft; i++) {
			int byteBuffer;
			_file >> byteBuffer;
		}
	}
};

int main(void) {

	string filename;

	//cout << "Please enter the image's file name: ";
	//cin >> filename;

	BMPimage image("Beach.bmp");

	image.getImageSize();

	return 0;
}