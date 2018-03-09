#include <opencv2/opencv.hpp>
#include <vector>

class Descriptor
{
private:
	std::vector<float> average_Vec, standard_deviation_Vec, asymmetry_Vec, curtose_Vec, energy_Vec;
	std::vector<int> Sum;

	template <typename _Tp>
	void sumArea(const cv::Mat& lbp_image, int posX, int posY, int rangeX, int rangeY);

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
	void run(const cv::Mat& image, std::vector<std::vector<float> >& featVec, int i, int j);
	void clear();
};
