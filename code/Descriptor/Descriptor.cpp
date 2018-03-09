#include "Descriptor.hpp"

Descriptor::Descriptor(){}

Descriptor::~Descriptor(){}

/**
 * Clears the vectors
 */
void Descriptor::clear() {
    this->average_Vec.clear();
    this->standard_deviation_Vec.clear();
    this->asymmetry_Vec.clear();
    this->curtose_Vec.clear();
    this->energy_Vec.clear();
}

/*
 * Function that starts the sum with the higher left term
 */
template <typename _Tp>
void Descriptor::sumArea(const cv::Mat& lbp_image, int posX, int posY, int rangeX, int rangeY)
{
    int minor_sum = 0;
    int k=0;
    for (int i=posX-rangeX; i<=posX+rangeX; i++)
    {
        for (int j=posY-rangeY; j<=posY+rangeY; j++)
        {
            minor_sum += (int)lbp_image.at<_Tp>(i,j);       //Navigates through all pixels in the area and sum them
            k++;
        }
    }
    Sum.push_back(minor_sum);
}


/*
 * Function that calculates the average values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::average(const cv::Mat& lbp_image, int i, int j)
{
    int k = 0;

    for (int m=8; m<lbp_image.rows-8; m++)                   //Getting the center pixel row
    {
        for (int n=8; n<lbp_image.cols-8; n++)               //Getting the center pixel col
        {
            sumArea<_Tp>(lbp_image, m, n, i/2, j/2);
            this->average_Vec.push_back(Sum[k] / (i*j));
            k++;
            //this->average_Vec.push_back( sumArea( lbp_image, m, n, i, j ) / (i*j) );
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
}

/*
 * Function that calculates the asymmetry values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::asymmetry(const cv::Mat& lbp_image, int i, int j)
{
}

/*
 * Function that calculates the curtose values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void Descriptor::curtose(const cv::Mat& lbp_image, int i, int j)
{
}

/*
 * Function that calculates the energy values vector of an image
 * Calculation based on a LBP image
 */
template <typename _Tp>
void energy(const cv::Mat& lbp_image, int i, int j)
{
}

/**
 * Main Function that runs the descriptor and fills the feature vector
 * It runs and then clean the Classes vector to ensure that it doesn't
 * interfere in the next runs
 */
void Descriptor::run(const cv::Mat& image, std::vector<std::vector<float> >& featVec, int i, int j)
{
    if (image.channels() > 1)        //Checking if the image is valid (LBP Image)
        return;

    switch (image.type())            //identifying the image type
    {
        case CV_8SC1:
            this->average<char>(image, i, j);
            break;

        case CV_8UC1:
            this->average<unsigned char>(image, i, j);
            break;
            
        case CV_16SC1:
            this->average<short>(image, i, j);
            break;
                
        case CV_16UC1:
            this->average<unsigned short>(image, i, j);
            break;

        case CV_32SC1:
            this->average<int>(image, i, j);
            break;

        case CV_32FC1:
            this->average<float>(image, i, j);
            break;

        case CV_64FC1:
            this->average<double>(image, i, j);
            break;
    }
    featVec.push_back(this->average_Vec);
    this->clear();
}
