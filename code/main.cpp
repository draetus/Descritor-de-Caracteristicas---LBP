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
    desc.run(original_image, LBP_image, featVec);

/*
    for (int i=0; i<featVec.size(); i++)
    {
        for (int j=0; j<featVec[i].size(); j++)
        {
            std::cout << (int)featVec[i][j] << "\n";
        }
    }
*/
    std::cout << "NUMERO: " << (original_image.rows-17) * (original_image.cols-17) << "\n";

    for (int i=0; i<featVec.size(); i++)
    {
        std::cout << featVec[i].size() << "\n";
    }

    std::string strings[] = {"Hue", "Saturation", "Value", 
                             "Media 3x3", "Desvio Padrao 3x3", "Assimetria 3x3", "Curtose 3x3", "Energia 3x3",
                             "Media 5x5", "Desvio Padrao 5x5", "Assimetria 5x5", "Curtose 5x5", "Energia 5x5",
                             "Media 7x7", "Desvio Padrao 7x7", "Assimetria 7x7", "Curtose 7x7", "Energia 7x7",
                             "Media 9x9", "Desvio Padrao 9x9", "Assimetria 9x9", "Curtose 9x9", "Energia 9x9",};

    for (int i=0; i<featVec.size(); i++)
    {
        for (int j=0; j<featVec[i].size(); j++)
        {
            std::cout << strings[i] << ": " << (int)featVec[i][j] << "\n";
        }
    }
/*
    for (int j=0; j<featVec[0].size(); j++)
        {
            std::cout << "Hue: " << (int)featVec[0][j] << "\n";
        }
    for (int j=0; j<featVec[1].size(); j++)
        {
            std::cout << "Saturation: " << (int)featVec[1][j] << "\n";
        }
    for (int j=0; j<featVec[2].size(); j++)
        {
            std::cout << "Value: " << (int)featVec[2][j] << "\n";
        }
    for (int j=0; j<featVec[3].size(); j++)
        {
            std::cout << "Media 3x3: " << (int)featVec[3][j] << "\n";
        }
    for (int j=0; j<featVec[4].size(); j++)
        {
            std::cout << "Desvio Padrao 3x3: " << (int)featVec[4][j] << "\n";
        }
    for (int j=0; j<featVec[5].size(); j++)
        {
            std::cout << "Assimetria 3x3: " << (int)featVec[5][j] << "\n";
        }
    for (int j=0; j<featVec[6].size(); j++)
        {
            std::cout << "Curtose 3x3: " << (int)featVec[6][j] << "\n";
        }
    for (int j=0; j<featVec[7].size(); j++)
        {
            std::cout << "Energia 3x3: " << (int)featVec[4][j] << "\n";
        }
    for (int j=0; j<featVec[8].size(); j++)
        {
            std::cout << "Media 5x5: " << (int)featVec[5][j] << "\n";
        }
    for (int j=0; j<featVec[9].size(); j++)
        {
            std::cout << "Desvio Padrao 5x5: " << (int)featVec[6][j] << "\n";
        }
    for (int j=0; j<featVec[10].size(); j++)
        {
            std::cout << "Assimetria 5x5: " << (int)featVec[7][j] << "\n";
        }
    for (int j=0; j<featVec[11].size(); j++)
        {
            std::cout << "Curtose 5x5: " << (int)featVec[8][j] << "\n";
        }
    for (int j=0; j<featVec[12].size(); j++)
        {
            std::cout << "Energia 5x5: " << (int)featVec[9][j] << "\n";
        }
    for (int j=0; j<featVec[13].size(); j++)
        {
            std::cout << "Media 7x7: " << (int)featVec[10][j] << "\n";
        }
    for (int j=0; j<featVec[14].size(); j++)
        {
            std::cout << "Desvio Padrao 7x7: " << (int)featVec[11][j] << "\n";
        }
    for (int j=0; j<featVec[15].size(); j++)
        {
            std::cout << "Assimetria 7x7: " << (int)featVec[12][j] << "\n";
        }
    for (int j=0; j<featVec[16].size(); j++)
        {
            std::cout << "Curtose 7x7: " << (int)featVec[13][j] << "\n";
        }
    for (int j=0; j<featVec[17].size(); j++)
        {
            std::cout << "Energia 7x7: " << (int)featVec[14][j] << "\n";
        }
    for (int j=0; j<featVec[18].size(); j++)
        {
            std::cout << "Media 9x9: " << (int)featVec[15][j] << "\n";
        }
    for (int j=0; j<featVec[19].size(); j++)
        {
            std::cout << "Desvio Padrao 9x9: " << (int)featVec[16][j] << "\n";
        }
    for (int j=0; j<featVec[20].size(); j++)
        {
            std::cout << "Assimetria 9x9: " << (int)featVec[17][j] << "\n";
        }
    for (int j=0; j<featVec[21].size(); j++)
        {
            std::cout << "Curtose 9x9: " << (int)featVec[18][j] << "\n";
        }
    for (int j=0; j<featVec[22].size(); j++)
        {
            std::cout << "Energia 9x9: " << (int)featVec[19][j] << "\n";
        }
*/
}
