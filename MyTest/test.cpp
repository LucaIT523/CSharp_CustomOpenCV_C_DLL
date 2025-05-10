#include "pch.h"
#include "test.h"
#include <string>

cv::Mat* g_RtnMat = 0x00;

cv::Mat ConvertToCvMat(char* imageData, int width, int height, int channels)
{
	if (channels == 3) {
		cv::Mat mat(height, width, CV_MAKETYPE(CV_8UC3, channels));
		memcpy(mat.data, imageData, width * height * channels);
		return mat;

	}
	else if (channels == 1)
	{
		cv::Mat mat(height, width, CV_MAKETYPE(CV_8UC1, channels));
		memcpy(mat.data, imageData, width * height);
		return mat;
	}
}


uchar*
PreProcessImage(char* imageData, int width, int height, int channels, uint* resizedWidth, uint* resizedHeight, ST_MyRect	rect, int iScaleFactor, int iErodeValue, int iDilateValue, int iSmoothValue, int iThreshType, int iThreshMinValue, int iThreshMaxValue, signed int IsWhiteOnBlack)
{
	int				w_nRtn = -1;

	//.
	PreProcessImage_close();
	//.
	if (imageData == NULL) {
		return NULL;
	}
	if (width <= 0 || height <= 0) {
		return NULL;
	}

	//. change c# MAT to c++ MAT
	Mat in_img = ConvertToCvMat((char*)imageData, width, height, channels);

	//. Convert MyRect information to cv::Rect
	cv::Rect	w_rect(rect.m_X, rect.m_Y, rect.m_Width, rect.m_Height);

	//. 
	std::cout << "Rect : " << w_rect.height << ",  " << w_rect.width << ",  " << w_rect.x << ",  " << w_rect.y << std::endl;
	std::cout << "iScaleFactor : " << iScaleFactor << std::endl;
	std::cout << "iErodeValue : " << iErodeValue << std::endl;
	std::cout << "iDilateValue : " << iDilateValue << std::endl;
	std::cout << "iSmoothValue : " << iSmoothValue << std::endl;
	std::cout << "iThreshType : " << iThreshType << std::endl;
	std::cout << "iThreshMinValue : " << iThreshMinValue << std::endl;
	std::cout << "iThreshMaxValue : " << iThreshMaxValue << std::endl;

	bool	w_IsWhiteOnBlack = (bool)IsWhiteOnBlack;
	if (w_IsWhiteOnBlack == true) {
		std::cout << "IsWhiteOnBlack is true " << std::endl;
	}
	else {
		std::cout << "IsWhiteOnBlack is false " << std::endl;
	}

	//.resize:
	Mat resized_img;
	int resized_width = 300;
	int resized_height = 200;
	resize(in_img, resized_img, Size(resized_width, resized_height), INTER_LINEAR);
	*resizedWidth = resized_width;
	*resizedHeight = resized_height;

	//. convert to gray scal
	cv::Mat gray_img;
	cv::cvtColor(resized_img, gray_img, cv::COLOR_BGR2GRAY);

	//. threshold
	//cv::Mat threshold_img;
	//threshold(gray_img, threshold_img, iThreshMinValue, iThreshMaxValue, iThreshType);

	//. 
	cv::merge(std::vector<cv::Mat>{gray_img, gray_img, gray_img}, gray_img);
	g_RtnMat = new Mat(gray_img);
	return g_RtnMat->data;
}

void PreProcessImage_close()
{
	if (g_RtnMat != 0x00) {
		delete g_RtnMat;
		g_RtnMat = 0x00;
	}
	return;
}

//
//cv::Mat*
//PreProcessImage(char* imageData, int width, int height, int channels, uint* resizedWidth, uint* resizedHeight, Rect	rect, int iScaleFactor, int iErodeValue, int iDilateValue, int iSmoothValue, int iThreshType, int iThreshMinValue, int iThreshMaxValue, signed int IsWhiteOnBlack)
//{
//	int				w_nRtn = -1;
//
//	if (imageData == NULL) {
//		return NULL;
//	}
//	if (width <= 0 || height <= 0) {
//		return NULL;
//	}
//
//	//. change c# MAT to c++ MAT
//	Mat in_img = ConvertToCvMat((char*)imageData, width, height, channels);
//
//	//. 
//	std::cout << "Rect : " << rect.height << ",  " << rect.width << ",  " << rect.x << ",  " << rect.y << std::endl;
//	std::cout << "iScaleFactor : " << iScaleFactor << std::endl;
//	std::cout << "iErodeValue : " << iErodeValue << std::endl;
//	std::cout << "iDilateValue : " << iDilateValue << std::endl;
//	std::cout << "iSmoothValue : " << iSmoothValue << std::endl;
//	std::cout << "iThreshType : " << iThreshType << std::endl;
//	std::cout << "iThreshMinValue : " << iThreshMinValue << std::endl;
//	std::cout << "iThreshMaxValue : " << iThreshMaxValue << std::endl;
//
//	bool	w_IsWhiteOnBlack = (bool)IsWhiteOnBlack;
//	if (w_IsWhiteOnBlack == true) {
//		std::cout << "IsWhiteOnBlack is true " << std::endl;
//	}
//	else {
//		std::cout << "IsWhiteOnBlack is false " << std::endl;
//	}
//
//	//.resize:
//	Mat resized_img;
//	int resized_width = 300;
//	int resized_height = 200;
//	resize(in_img, resized_img, Size(resized_width, resized_height), INTER_LINEAR);
//	*resizedWidth = resized_width;
//	*resizedHeight = resized_height;
//
//	//. convert to gray scal
//	cv::Mat gray_img;
//	cv::cvtColor(resized_img, gray_img, cv::COLOR_BGR2GRAY);
//
//	//. threshold
//	cv::Mat threshold_img;
//	threshold(gray_img, threshold_img, iThreshMinValue, iThreshMaxValue, iThreshType);
//
//	return new Mat(threshold_img);
//
//}
