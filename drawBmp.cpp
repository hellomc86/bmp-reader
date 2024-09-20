#include "drawClass.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: drawBmp.exe <path_to_bmp>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    BMPReader reader;

    if (reader.openBMP(fileName)) {
        reader.displayBMP();        
    }

    return 0;
}
