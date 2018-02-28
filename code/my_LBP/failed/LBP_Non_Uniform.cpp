#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

int main(int argc, char** argv)
{
    if ( argc != 2 )
    {
        std::cout << "Usage: ./LBP_Non_Uniform <Image_Path>\n";
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

    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("LBP Image", original_image);
    cv::waitKeyEx(0);
  
    for (int i=1; i<gray_image.rows-1; i++)
    {
        for (int j=1; j<gray_image.cols-1; j++)
        {
            int pixelValue = 0;
            int center = original_image.at<uchar>(i,j);

            pixelValue |= (gray_image.at<uchar>(i-1,j-1) > center) << 7;
            pixelValue |= (gray_image.at<uchar>(i-1,j) > center) << 6;
            pixelValue |= (gray_image.at<uchar>(i-1,j+1) > center) << 5;
            pixelValue |= (gray_image.at<uchar>(i,j+1) > center) << 4;
            pixelValue |= (gray_image.at<uchar>(i+1,j+1) > center) << 3;
            pixelValue |= (gray_image.at<uchar>(i+1,j) > center) << 2;
            pixelValue |= (gray_image.at<uchar>(i+1,j-1) > center) << 1;
            pixelValue |= (gray_image.at<uchar>(i,j-1) > center) << 0;

            /*pixelValue += (gray_image.at<uchar>(i-1,j-1) < gray_image.at<uchar>(i,j)) ? 128 : 0;
            pixelValue += (gray_image.at<uchar>(i-1,j) < gray_image.at<uchar>(i,j)) ? 64 : 0;
            pixelValue += (gray_image.at<uchar>(i-1,j+1) < gray_image.at<uchar>(i,j)) ? 32 : 0;
            pixelValue += (gray_image.at<uchar>(i,j+1) < gray_image.at<uchar>(i,j)) ? 16 : 0;
            pixelValue += (gray_image.at<uchar>(i+1,j+1) < gray_image.at<uchar>(i,j)) ? 8 : 0;
            pixelValue += (gray_image.at<uchar>(i+1,j) < gray_image.at<uchar>(i,j)) ? 4 : 0;
            pixelValue += (gray_image.at<uchar>(i+1,j-1) < gray_image.at<uchar>(i,j)) ? 2 : 0;
            pixelValue += (gray_image.at<uchar>(i,j-1) < gray_image.at<uchar>(i,j)) ? 1 : 0;*/

            

            
            LBP_image.at<uchar>(i-1,j-1) = pixelValue;
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


    for (int i=0; i<256 ; i++)
    {
        std::cout << "Case " << i << ": " << apparitions[i] << std::endl;
    }

    LBP_image.release();

    return 0;
}
