#include <iostream>
#include <fstream>
#include <windows.h>

class BMPReader {
private:
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    unsigned char* pixelData;

    int width;
    int height;
    int bitCount;

public:
    BMPReader();
    ~BMPReader();

    bool openBMP(const std::string& fileName);

    void displayBMP();

    void closeBMP();
    
};
