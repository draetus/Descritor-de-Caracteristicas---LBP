#include <opencv2/opencv.hpp>
#include <iostream>
#include "LBP/LBP.hpp"
#include "Descriptor/Descriptor.hpp"

int main(int argc, char** argv)
{
    cv::Mat original_image = cv::imread(argv[1], 1);
    cv::Mat LBP_image, HSV_image;

    LBP::run_and_show(original_image, LBP_image);
    cv::cvtColor(original_image, HSV_image, CV_BGR2HSV);

    std::vector<std::vector<float> > featVec;

    Descriptor desc;
    desc.run(LBP_image, featVec, 3, 3);

    for (int i=0; i<featVec[0].size(); i++)
    {
        std::cout << (int)featVec[3][i] << " " ;
    }
}
