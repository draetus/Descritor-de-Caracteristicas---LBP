#include <opencv2/opencv.hpp>
#include <LBP.h>

int main(int argc, char** argv)
{
    cv::Mat original_image = cv::imread(argv[1], 1);
    
    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("LBP Image", original_image);
    cv::waitKeyEx(0);

    cv::Mat LBP_image;
    LBP::run(original_image, LBP_image);

    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("LBP Image", LBP_image);
    cv::waitKeyEx(0);
 
}
