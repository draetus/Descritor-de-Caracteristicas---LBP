#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>


template <typename _Tp>
void LBP_(const cv::Mat& src, cv::Mat& dst)
{
    dst = cv::Mat::zeros(src.rows - 1, src.cols - 1, CV_8UC1);
    for (int i = 1; i < src.rows ; i++)
    {
        for (int j = 1; j < src.cols ; j++)
        {
            _Tp center = src.at<_Tp>(i,j);
            unsigned char code = 0;
            code |= (src.at<_Tp>(i - 1, j - 1) > center) << 7;
            code |= (src.at<_Tp>(i - 1, j) > center) << 6;
            code |= (src.at<_Tp>(i - 1, j + 1) > center) << 5;
            code |= (src.at<_Tp>(i, j + 1) > center) << 4;
            code |= (src.at<_Tp>(i + 1, j + 1) > center) << 3;
            code |= (src.at<_Tp>(i + 1, j) > center) << 2;
            code |= (src.at<_Tp>(i + 1, j - 1) > center) << 1;
            code |= (src.at<_Tp>(i, j - 1) > center) << 0;
            dst.at<unsigned char>(i - 1, j - 1) = code;
        }
    }
}


void run(const cv::Mat &img_input, cv::Mat &img_output)
{
    if (img_input.empty())
        return;

    int height = img_input.size().height;
    int width = img_input.size().width;
    int channels = img_input.channels();

    cv::Mat img_gray;
    if (channels > 1)
        cv::cvtColor(img_input, img_gray, CV_BGR2GRAY);
    else
        img_input.copyTo(img_gray);

    switch (img_gray.type())
    {
        case CV_8SC1:
            LBP_<char>(img_gray, img_output);
            break;

        case CV_8UC1:
            LBP_<unsigned char>(img_gray, img_output);
            break;
            
        case CV_16SC1:
            LBP_<short>(img_gray, img_output);
            break;
                
        case CV_16UC1:
            LBP_<unsigned short>(img_gray, img_output);
            break;

        case CV_32SC1:
            LBP_<int>(img_gray, img_output);
            break;

        case CV_32FC1:
            LBP_<float>(img_gray, img_output);
            break;

        case CV_64FC1:
            LBP_<double>(img_gray, img_output);
            break;

    }
}

int main(int argc, char** argv)
{
    cv::Mat original_image = cv::imread(argv[1], 1);
    
    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("LBP Image", original_image);
    cv::waitKeyEx(0);

    cv::Mat LBP_image;
    run(original_image, LBP_image);

    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("LBP Image", LBP_image);
    cv::waitKeyEx(0);
 
}
