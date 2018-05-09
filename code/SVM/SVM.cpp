#include "SVM.hpp"

SVM::SVM(std::vector<std::vector<float> > &featVec)
{
    svm = cv::ml::SVM::create();
    svm->setKernel(cv::ml::SVM::RBF);      //CvSVM::RBF, CvSVM::LINEAR
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setDegree(0);                     // for poly
    svm->setGamma(20);                     // for poly/rbf/sigmoid
    svm->setCoef0(0);                      // for poly/sigmoid

    svm->setC(7);                          // for CV_SVM_C_SVC, CV_SVM_EPS_SVR and CV_SVM_NU_SVR
    svm->setNu(0.0);                       // for CV_SVM_NU_SVC, CV_SVM_ONE_CLASS, and CV_SVM_NU_SVR
    svm->setP(0.0);                        // for CV_SVM_EPS_SVR

    //svm->setClassWeights(NULL);            // for CV_SVM_C_SVC
    svm->setClassWeights(cv::Mat());         // for CV_SVM_C_SVC

    //svm->setTermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 1000, 1e-6);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 1000, 1e-6));

    /*
    this->trainingData = trainingData;
    this->trainingClasses = trainingClasses;
    this->testData = testData;
    this->testClasses = testClasses;
    */
}

cv::Mat& SVM::labelData(int rows, int cols, const std::vector<std::vector<float> > &featVec, int equation)
{
    cv::Mat labels(featVec[0].size(), 1, CV_32FC1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            featVec[0][i*cols + j];
            featVec[1][i*cols + j];
            featVec[2][i*cols + j];
            featVec[3][i*cols + j];
            featVec[4][i*cols + j];
            featVec[5][i*cols + j];
            featVec[6][i*cols + j];
        }
    }
}

int SVM::f(float x, float y, int equation)
{
}

void SVM::svm_run()
{
}

void SVM::run()
{
}
