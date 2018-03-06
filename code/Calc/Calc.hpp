#include <opencv2/opencv.hpp>
#include <vector>

class Calc
{
private:
	static int sumArea(const cv::Mat& image, int posX, int posY, int rangeX, int rangeY);
public:
	static void average(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j);
	static void standard_deviation(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j);
	static void asymmetry(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j);
	static void curtose(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j);
	static void energy(const cv::Mat& image, std::vector<std::vector<float> *>& featVec, int i, int j);
};
