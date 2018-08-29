#include "ZQ_CNN_SSD.h"
#include <cblas.h>
#include <vector>
#include <iostream>
#include "opencv2\opencv.hpp"
using namespace ZQ;
using namespace std;
using namespace cv;



int main()
{
	int thread_num = 4;
	openblas_set_num_threads(thread_num);
	
	Mat img0 = cv::imread("data\\004545.jpg", 1);
	//Mat img0 = cv::imread("data\\face1.jpg", 1);
	if (img0.empty())
	{
		cout << "empty image\n";
		return EXIT_FAILURE;
	}
	
	ZQ_CNN_SSD detector;
	if (!detector.Init("model\\MobileNetSSD_deploy.zqparams", "model\\MobileNetSSD_deploy.nchwbin", "detection_out"))
	{
		printf("failed to init detector!\n");
		return false;
	}
	
	int out_iter = 10;
	int iters = 1;
	std::vector<ZQ_CNN_SSD::BBox> output;
	const float kScoreThreshold = 0.5f;
	for (int out_it = 0; out_it < out_iter; out_it++)
	{
		double t1 = omp_get_wtime();
		for (int it = 0; it < iters; it++)
		{
			if(!detector.Detect(output, img0.data, img0.cols, img0.rows, img0.step[0], kScoreThreshold, false))
			{
				cout << "failed to run\n";
				return EXIT_FAILURE;
			}
		}
		double t2 = omp_get_wtime();
		printf("[%d] times cost %.3f s, 1 iter cost %.3f ms\n", iters, t2 - t1, 1000 * (t2 - t1) / iters);
	}
	const char* kClassNames[] = { "__background__", "aeroplane", "bicycle", "bird", "boat",
		"bottle", "bus", "car", "cat", "chair",
		"cow", "diningtable", "dog", "horse",
		"motorbike", "person", "pottedplant",
		"sheep", "sofa", "train", "tvmonitor" };
	//const char* kClassNames[] = { "__background__", "eye", "nose", "mouth", "face" };
	
	// draw
	for (auto& bbox : output) 
	{
		cv::Rect rect(bbox.col1, bbox.row1, bbox.col2 - bbox.col1 + 1, bbox.row2 - bbox.row1 + 1);
		cv::rectangle(img0, rect, cv::Scalar(0, 0, 255), 2);
		char buff[300];
		sprintf_s(buff, 300, "%s: %.2f", kClassNames[bbox.label], bbox.score);
		cv::putText(img0, buff, cv::Point(bbox.col1, bbox.row1), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0));
	}

	cv::imwrite("./ssd-result.jpg", img0);
	cv::imshow("ZQCNN-SSD", img0);
	cv::waitKey(0);

	return EXIT_SUCCESS;
}
