#pragma once
#include "pch.h"

static const int imageHeight = 28;
static const int imageWidth = 28;

class Image {
	using filepath = std::filesystem::path;

public:
	Image(filepath);

	// Print out the image with ' ' and '0'
	void Print();

	// Convert image data into vector
	Eigen::VectorXd GetVector();

	// Get pixel at 2D coordinate of image
	float GetPixel(int row, int col);
	// Set pixel at 2D coordinate of image
	void SetPixel(int row, int col, float val);

private:
	Eigen::VectorXd mData;
	int mHeight;
	int mWidth;

};


















