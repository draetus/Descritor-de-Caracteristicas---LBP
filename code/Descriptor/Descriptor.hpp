#include <opencv2/opencv.hpp>
#include <vector>
#include <math.h>

class Descriptor
{
private:
	std::vector<float> average_Vec, standard_deviation_Vec, asymmetry_Vec, curtose_Vec, energy_Vec;

	template <typename _Tp>
	int Sum(const cv::Mat& lbp_image, int posX, int posY, int rangeX, int rangeY, int pot=1);

	template <typename _Tp>
	float SumMinusAverage(const cv::Mat& lbp_image, int posX, int posY, int rangeX, int rangeY, int pot=1);

	template <typename _Tp>
	void average(const cv::Mat& lbp_image, int i, int j);

	template <typename _Tp>
	void standard_deviation(const cv::Mat& lbp_image, int i, int j);

	template <typename _Tp>
	void asymmetry(const cv::Mat& lbp_image, int i, int j);

	template <typename _Tp>
	void curtose(const cv::Mat& lbp_image, int i, int j);

	template <typename _Tp>
	void energy(const cv::Mat& lbp_image, int i, int j);
public:
	Descriptor();
	~Descriptor();
	void run(const cv::Mat& image, std::vector<std::vector<float> >& featVec);
	void clear();
};
