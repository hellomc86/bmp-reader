#include "drawClass.h"

BMPReader::BMPReader() : pixelData(nullptr), width(0), height(0), bitCount(0) {}

bool BMPReader::openBMP(const std::string& fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open BMP file." << std::endl;
		return false;
	}

	// Чтение заголовков BMP файла
	file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));
	file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BITMAPINFOHEADER));

	// Проверка формата файла
	if (fileHeader.bfType != 0x4D42 || (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32)) {
		std::cerr << "Error: Unsupported BMP format. Only 24-bit or 32-bit BMP files are supported." << std::endl;
		file.close();
		return false;
	}

	width = infoHeader.biWidth;

	height = std::abs(infoHeader.biHeight);
	bitCount = infoHeader.biBitCount;
		
	// Вычисление размера данных пикселей
	int dataSize = fileHeader.bfSize - fileHeader.bfOffBits;
	
	// Выделение памяти для данных пикселей
	pixelData = new unsigned char[dataSize];

	// Переход к началу данных пикселей
	file.seekg(fileHeader.bfOffBits, std::ios::beg);
	file.read(reinterpret_cast<char*>(pixelData), dataSize);

	file.close();
	return true;
}

void BMPReader::displayBMP() {
	if (!pixelData) {
		std::cerr << "Error: No pixel data to display." << std::endl;
		return;
	}
	// В формате BMP есть дополнение (padding), если ширина изображения не является кратной 4.
	// Из-за этого изображение может отображаться некорректно.
	// Поэтому мы вычисляем индекс ширины (widthIndex).
	int widthIndex = ((width + 31) / 32) * 32;
	// Проход по пикселям и отображение черного и белого цветов
	for (int y = height - 1; y >= 0; --y) { // В BMP координаты начинаются снизу
		for (int x = 0; x < width; ++x) {
			int pixelIndex = ((x + y * widthIndex) * (bitCount / 8));
			unsigned char blue = pixelData[pixelIndex];
			unsigned char green = pixelData[pixelIndex + 1];
			unsigned char red = pixelData[pixelIndex + 2];

			if (red == 255 && green == 255 && blue == 255) {
				std::cout << " ";  // Белый цвет
			}
			else if (red == 0 && green == 0 && blue == 0) {
				std::cout << "#";  // Черный цвет
			}
			else {
				std::cout << "?";  // Неподдерживаемый цвет
			}
		}
		std::cout << std::endl;
	}
}

void BMPReader::closeBMP() {
	if (pixelData) {
		delete[] pixelData;
		pixelData = nullptr;
	}
}

BMPReader::~BMPReader() {
	closeBMP();  // Освобождение ресурсов при завершении объекта
}
