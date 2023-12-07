#include "Image.h"



Image::Image(filepath path) {
	sf::Image image;

	//std::cout << path.string() << '\n';

	image.loadFromFile(path.string());
	auto dimension = image.getSize();

	int vertCounter = 0;
	int rowCounter = 0;
	
	mWidth = dimension.x;
	mHeight = dimension.y;
	mData.resize(mWidth * mHeight);

	for (int row = 0; row < mHeight; ++row) {
		for (int col = 0; col < mWidth; ++col) {
			auto clr = image.getPixel(col, row);
			mData[row*mWidth + col] = clr.r/255.f;
		}
	}
}

void Image::Print() {
	for (int row = 0; row < mHeight; ++row) {
		for (int col = 0; col < mWidth; ++col) {
			std::cout << (GetPixel(row, col) > 0.23529f ? "0" : " "); // 0.23529 = 60/255
		}
		std::cout << "\n";
	}
}

float Image::GetPixel(int row, int col) {
	return mData[row*mHeight + col];
}

void Image::SetPixel(int row, int col, float val) {
	val = std::max(0.f, val);
	val = std::min(1.f, val);
	mData[row*mHeight + col] = val;
}

Eigen::VectorXd Image::GetVector() {
	return mData;
}







