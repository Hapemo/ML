#include "JazzImage.h"



JazzImage::JazzImage(filepath path) {
	sf::Image image;

	std::cout << path.string() << '\n';

	image.loadFromFile(path.string());
	auto dimension = image.getSize();

	int vertCounter = 0;
	int rowCounter = 0;
	
	for (int row = 0; row < dimension.x; ++row) {
		for (int col = 0; col < dimension.y; ++col) {

			auto clr = image.getPixel(col, row);
			if (clr.r < 60) std::cout << " ";
			else std::cout << "0";
		}
		std::cout << '\n';
	}



}


bool JazzImage::GetPixel(int row, int col) {
	int position = row*mWidth + col;
	return false;
}

void JazzImage::SetPixel(int row, int col, bool state) {

}









