#include "Descriptor.hpp"
#include <iostream>

Descriptor::Descriptor(){}

Descriptor::~Descriptor(){}

/**
 * Clears the vectors
 */
void Descriptor::clear() {
    this->average_Vec.clear();
    this->standard_deviation_Vec.clear(); this->asymmetry_Vec.clear();
    this->curtose_Vec.clear();
    this->energy_Vec.clear();
}

/*
 * Function that starts the sum with the higher left term
 */
template <typename _Tp>
int Descriptor::Sum(const cv::Mat& lbp_image, int posX, int posY, int rangeX, int rangeY, int pot)
{
    int minor_sum = 0;
    int count=0;
    for (int i=posX-rangeX; i<=posX+rangeX; i++)
    {
        for (int j=posY-rangeY; j<=posY+rangeY; j++)
        {
            minor_sum += std::pow((int)lbp_image.at<_Tp>(i,j), pot);       //Navigates through all pixels in the area and sum them
        }
    }
    return minor_sum;
}


template <typename _Tp>
float Descriptor::SumMinusAverage(const cv::Mat& lbp_image, int posX, int posY, int rangeX, int rangeY, int pot)
{
    float minor_sum = 0;
    int k = (posX-8)*(lbp_image.cols-16) + posY-8;
    for (int i=posX-rangeX; i<=posX+rangeX; i++)
    {
        for (int j=posY-rangeY; j<=posY+rangeY; j++)
        {
            minor_sum += std::pow( (float)lbp_image.at<_Tp>(i,j) -
                    this->average_Vec[k], pot);
        }
    }
    return minor_sum;
}



/*
 * Function that calculates the average values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::average(const cv::Mat& lbp_image, int i, int j)
{
    int sum;
    int count=0;

    for (int m=8; m<lbp_image.rows-8; m++)                   //Getting the center pixel row
    {
        for (int n=8; n<lbp_image.cols-8; n++)               //Getting the center pixel col
        {
            sum = Sum<_Tp>(lbp_image, m, n, i/2, j/2);
            this->average_Vec.push_back(sum / (i*j));
        }
    }

}

/*
 * Function that calculates the standard deviation values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::standard_deviation(const cv::Mat& lbp_image, int i, int j)
{
    float aux;

    for (int m=8; m<lbp_image.rows-8; m++)
    {
        for (int n=8; n<lbp_image.cols-8; n++)
        {
            aux = this->SumMinusAverage<_Tp>(lbp_image, m, n, i/2, j/2, 2);
            aux = std::sqrt(aux/(i*j));
            this->standard_deviation_Vec.push_back(aux);
        }
    }
}

/*
 * Function that calculates the asymmetry values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::asymmetry(const cv::Mat& lbp_image, int i, int j)
{
    long k;
    double aux;

    for (int m=8; m<lbp_image.rows-8; m++)
    {
        for (int n=8; n<lbp_image.cols-8; n++)
        {
            k = (m-8)*(lbp_image.cols-16) + n-8;
            aux = this->SumMinusAverage<_Tp>(lbp_image, m, n, i/2, j/2, 3);
            if (i * j * std::pow(this->standard_deviation_Vec[k], 3) == 0)
            {
                aux = 0;
            }
            else
            {
                aux = aux / (i * j * std::pow(this->standard_deviation_Vec[k], 3));
            }
            this->asymmetry_Vec.push_back(aux);
        }
    }
}

/*
 * Function that calculates the curtose values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::curtose(const cv::Mat& lbp_image, int i, int j)
{
    int k;
    float aux;

    for (int m=8; m<lbp_image.rows-8; m++)
    {
        for (int n=8; n<lbp_image.cols-8; n++)
        {
            k = (m-8)*(lbp_image.cols-16) + n-8;
            aux = this->SumMinusAverage<_Tp>(lbp_image, m, n, i/2, j/2, 4);
            if (i * j * std::pow(this->standard_deviation_Vec[k], 4) == 0)
            {
                aux = 0;
            }
            else
            {
                aux = aux / (i * j * std::pow(this->standard_deviation_Vec[k], 4));
            }
            this->curtose_Vec.push_back(aux);
        }
    }
}

/*
 * Function that calculates the energy values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::energy(const cv::Mat& lbp_image, int i, int j)
{
    int k=0;
    float sum;

    for (int m=8; m<lbp_image.rows-8; m++)
    {
        for (int n=8; n<lbp_image.cols-8; n++)
        {
            sum = Sum<_Tp>(lbp_image, m, n, i/2, j/2, 2);
            this->energy_Vec.push_back(sum/(i*j));
        }
    }
}

/**
 * Main Function that runs the descriptor and fills the feature vector
 * It runs and then clean the Classes vector to ensure that it doesn't
 * interfere in the next runs
 */
void Descriptor::run(const cv::Mat& original_image, const cv::Mat& image, std::vector<std::vector<double> >& featVec)
{
    if (image.channels() > 1)        //Checking if the image is valid (LBP Image)
        return;

    int i,j;

    cv::Mat HSV_image;
    cv::cvtColor(original_image, HSV_image, CV_BGR2HSV);

    std::vector<double> h,s,v;                  //Adding the HSV values in the feature vector

    for (int m=8; m<image.rows-8; m++)
    {
        for (int n=8; n<image.cols-8; n++)
        {
            h.push_back((double)HSV_image.at<cv::Vec3b>(m,n)[0]);
            s.push_back((double)HSV_image.at<cv::Vec3b>(m,n)[1]);
            v.push_back((double)HSV_image.at<cv::Vec3b>(m,n)[2]);
        }
    }
    featVec.push_back(h);
    featVec.push_back(s);
    featVec.push_back(v);

    for (i=3; i<10; i+=2)
    {
        j=i;
        switch (image.type())            //identifying the image type
        {
            case CV_8SC1:
                this->average<char>(image, i, j);
                this->standard_deviation<char>(image, i, j);
                this->asymmetry<char>(image, i, j);
                this->curtose<char>(image, i, j);
                this->energy<char>(image, i, j);

                break;

            case CV_8UC1:
                this->average<unsigned char>(image, i, j);
                this->standard_deviation<unsigned char>(image, i, j);
                this->asymmetry<unsigned char>(image, i, j);
                this->curtose<unsigned char>(image, i, j);
                this->energy<unsigned char>(image, i, j);

                break;
                
            case CV_16SC1:
                this->average<short>(image, i, j);
                this->standard_deviation<short>(image, i, j);
                this->asymmetry<short>(image, i, j);
                this->curtose<short>(image, i, j);
                this->energy<short>(image, i, j);

                break;
                    
            case CV_16UC1:
                this->average<unsigned short>(image, i, j);
                this->standard_deviation<unsigned short>(image, i, j);
                this->asymmetry<unsigned short>(image, i, j);
                this->curtose<unsigned short>(image, i, j);
                this->energy<unsigned short>(image, i, j);

                break;

            case CV_32SC1:
                this->average<int>(image, i, j);
                this->standard_deviation<int>(image, i, j);
                this->asymmetry<int>(image, i, j);
                this->curtose<int>(image, i, j);
                this->energy<int>(image, i, j);

                break;

            case CV_32FC1:
                this->average<float>(image, i, j);
                this->standard_deviation<float>(image, i, j);
                this->asymmetry<float>(image, i, j);
                this->curtose<float>(image, i, j);
                this->energy<float>(image, i, j);

                break;

            case CV_64FC1:
                this->average<double>(image, i, j);
                this->standard_deviation<double>(image, i, j);
                this->asymmetry<double>(image, i, j);
                this->curtose<double>(image, i, j);
                this->energy<double>(image, i, j);

                break;
        }
        featVec.push_back(this->average_Vec);
        featVec.push_back(this->standard_deviation_Vec);
        featVec.push_back(this->asymmetry_Vec);
        featVec.push_back(this->curtose_Vec);
        featVec.push_back(this->energy_Vec);
        this->clear();
    }
}
