#pragma once

#include <comdef.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct ST_MyRect
{
	int		m_Height;
	int		m_Width;
	int		m_X;
	int		m_Y;
};


extern "C" {

	//. if success, return outImage.
	//. if error, return NULL
	__declspec(dllexport) uchar* PreProcessImage(char* imageData, int width, int height, int channels, uint* resizedWidth, uint* resizedHeight, ST_MyRect	rect, int iScaleFactor, int iErodeValue, int iDilateValue, int iSmoothValue, int iThreshType, int iThreshMinValue, int iThreshMaxValue, signed int IsWhiteOnBlack);

	__declspec(dllexport) void PreProcessImage_close();
}