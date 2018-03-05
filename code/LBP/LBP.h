#include <iostream>
#include <opencv2/opencv.hpp>

class LBP
{

private:
    template <typename _Tp>
    void static LBP_(const cv::Mat& src, cv::Mat& dst);

public:
    LBP();
    ~LBP();

    void static run(const cv::Mat &img_input, cv::Mat &img_output);
    void static run_and_show(const cv::Mat &img_input, cv::Mat &img_output);
};
