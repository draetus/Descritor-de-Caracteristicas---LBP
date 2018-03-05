#include <iostream>
#include <LBP.h>
#include <olbp/OLBP.h>

using namespace lbplibrary;

void test_OLBP(std::string input)
{
    cv::Mat original_image;
    original_image = cv::imread(input, 1);

    if (!original_image.data)
    {
        std::cout << "No image found...";
        return;
    }

    cv::namedWindow("LBP Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("LBP Image", original_image);
    cv::waitKeyEx(0);

    cv::Mat lbp_image;
    OLBP* lbp = new OLBP();
    lbp->run(original_image, lbp_image);

    cv::imshow("LBP Image", lbp_image);
    cv::waitKeyEx(0);
    delete lbp;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Wrong use" << std::endl;
        return -1;
    }
    test_OLBP(argv[1]);
    return 0;
}
