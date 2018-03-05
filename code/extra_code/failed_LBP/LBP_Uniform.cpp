#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        std::cout << "Usage: ./LBP_Uniform <Image_Path>\n";
        return -1;
    }

    cv::Mat original_image;
    original_image = cv::imread(argv[1], 1);

    cv::Mat LBP_image(original_image.rows, original_image.cols, CV_8UC1, cv::Scalar(0));
    cv::Mat gray_image;


    if (!original_image.data)
    {
        std::cout << "No image found...";
        return -1;
    }
    
    cv::cvtColor(original_image, gray_image, cv::COLOR_BGR2GRAY);
    LBP_image = gray_image.clone();

    bool pixelValue[8], atual;
    int transicoes = 0;

    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("LBP Image", original_image);
    cv::waitKeyEx(0);
   
    for (int i=1; i<original_image.cols; i++)
    {
        for (int j=1; j<original_image.rows; j++)
        {
            pixelValue[0] = (gray_image.at<uchar>(i-1,j-1) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
            pixelValue[1] = (gray_image.at<uchar>(i-1,j) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
            pixelValue[2] = (gray_image.at<uchar>(i-1,j+1) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
            pixelValue[3] = (gray_image.at<uchar>(i,j+1) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
            pixelValue[4] = (gray_image.at<uchar>(i+1,j+1) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
            pixelValue[5] = (gray_image.at<uchar>(i+1,j) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
            pixelValue[6] = (gray_image.at<uchar>(i+1,j-1) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
            pixelValue[7] = (gray_image.at<uchar>(i,j-1) <= gray_image.at<uchar>(i,j)) ? 1 : 0;
    
            atual = pixelValue[0];
 
            for (int k=1; k<8; k++)
            {
                if (pixelValue[k] != atual)
                {
                    transicoes++;
                    atual = pixelValue[k];
                }
            }
 
            if (transicoes <3)
            {
                LBP_image.at<uchar>(i,j) = 0;
                for (int k=0; k<8; k++)
                {
                    LBP_image.at<uchar>(i,j) += (pixelValue[k]) ? std::pow(2, k) : 0;
                }
            }
            else
            {
                LBP_image.at<uchar>(i,j) = 5;
            }

            for (int k=0; k<8; k++)
            {
                pixelValue[k] = 0;
            }
            transicoes = 0;
        }
        cv::imshow("LBP Image", LBP_image);
        cv::waitKeyEx(1);
    }
    
    cv::imshow("LBP Image", LBP_image);
    cv::waitKeyEx(0);

    original_image.release();
    gray_image.release();

    int apparitions[256] = {0};

    for (int i=1; i<LBP_image.rows; i++)
    {
        for (int j=1; j<LBP_image.cols; j++)
        {
            for (int k=0; k<256; k++)
            {
                if (LBP_image.at<uchar>(i,j) == k)
                {
                    apparitions[k]++;
                }
            }
        }
    }

    for (int i=0; i<256; i++)
    {
        if (apparitions[i] != 0)
        std::cout << "Case " << i << ": " << apparitions[i] << std::endl;
    }

    LBP_image.release();

    return 0;
}
