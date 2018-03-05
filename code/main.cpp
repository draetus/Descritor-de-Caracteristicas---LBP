#include <opencv2/opencv.hpp>
#include "LBP/LBP.h"

int main(int argc, char** argv)
{
    cv::Mat original_image = cv::imread(argv[1], 1);
    cv::Mat LBP_image;
    LBP::run_and_show(original_image, LBP_image);
}
