#pragma once
#include "pch.h"


static const int imageHeight = 28;
static const int imageWidth = 28;

class JazzImage {
	using filepath = std::filesystem::path;

public:
	JazzImage(filepath);

	char* Begin();
	
	void RangeCallBack();

	bool GetPixel(int row, int col);
	void SetPixel(int row, int col, bool state);

private:
	char mData[imageHeight*imageWidth];
	int mHeight = imageHeight;
	int mWidth = imageWidth;

};


















