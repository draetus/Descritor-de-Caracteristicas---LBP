#include "Calc.hpp"

/*
 * Function that starts the sum with the higher left term
 */
int Calc::sumArea(const cv::Mat& image, int posX, int posY, int rangeX, int rangeY)
{
    int sum = 0;
    for (int i=posX-rangeX; i<posX+rangeX; i++)
    {
        for (int j=posY-rangeY; j<posY+rangeY; j++)
        {
            sum += image.at<int>(i,j);
        }
    }
    return sum;
}

/*
 * Function that calculates the average values vector of an image
 * Calculation based on a LBP image
 */
void Calc::average(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j)
{
    if (image.channels() > 3)
    return;

    int totalSum = 0;
    i = i/2;
    j = j/2;

    std::vector<float> averVec;

    for (int m=8; m<image.rows; i++)                   //Getting the center pixel row
    {
        for (int n=8; n<image.cols; j++)               //Getting the center pixel col
        {
            averVec.push_back( sumArea( image, m, n, i, j ) / (i*j) );
        }
    }

    featVec.push_back(&averVec);
}

void Calc::standard_deviation(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j)
{
}

void Calc::asymmetry(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j)
{
}

void Calc::curtose(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j)
{
}

void Calc::energy(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j)
{
}
