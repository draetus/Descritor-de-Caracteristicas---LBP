#include <opencv2/opencv.hpp>

class SVM
{
private:
	cv::Mat trainingData, trainingClasses;
	cv::Mat testData, testClasses;
	cv::Ptr<cv::ml::SVM> svm;
	std::vector<std::vector<float> > featVec;

	cv::Mat& labelData(int rows, int cols, const std::vector<std::vector<float> > &featVec, int equation);

	int f(float x, float y, int equation);

	void svm_run();
	
public:
	void run();
	SVM(std::vector<std::vector<float> > &featVec);
};
