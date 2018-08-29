#ifndef _ZQ_CNN_MTCNN_H_
#define _ZQ_CNN_MTCNN_H_
#pragma once
#include "ZQ_CNN_Net.h"
#include "ZQ_CNN_BBoxUtils.h"
#include <omp.h>
namespace ZQ
{
	class ZQ_CNN_MTCNN
	{
	public:
		using string = std::string;
		ZQ_CNN_MTCNN()
		{
			min_size = 60;
			thresh[0] = 0.6;
			thresh[1] = 0.7;
			thresh[2] = 0.7;
			nms_thresh[0] = 0.6;
			nms_thresh[1] = 0.7;
			nms_thresh[2] = 0.7;
			width = 0;
			height = 0;
			factor = 0.709;
			show_debug_info = false;
		}
		~ZQ_CNN_MTCNN()
		{

		}

	private:
		ZQ_CNN_Net pnet, rnet, onet;
		float thresh[3], nms_thresh[3];
		int min_size;
		int width, height;
		float factor;
		std::vector<float> scales;
		std::vector<ZQ_CNN_Tensor4D_NHW_C_Align128bit> pnet_images;
		ZQ_CNN_Tensor4D_NHW_C_Align128bit input, rnet_image, onet_image;
		bool show_debug_info;
	public:
		void TurnOnShowDebugInfo() { show_debug_info = true; }
		void TurnOffShowDebugInfo() { show_debug_info = false; }
		bool Init(const string& pnet_param, const string& pnet_model, const string& rnet_param, const string& rnet_model,
			const string& onet_param, const string& onet_model)
		{
			return pnet.LoadFrom(pnet_param, pnet_model) && rnet.LoadFrom(rnet_param, rnet_model) && onet.LoadFrom(onet_param, onet_model);
		}

		void SetPara(int w, int h, int min_face_size = 60, float pthresh = 0.6, float rthresh = 0.7, float othresh = 0.7,
			float nms_pthresh = 0.6, float nms_rthresh = 0.7, float nms_othresh = 0.7, float scale_factor = 0.709)
		{
			min_size = __max(12, min_face_size);
			thresh[0] = __max(0.1, pthresh); thresh[1] = __max(0.1, rthresh); thresh[2] = __max(0.1, othresh);
			nms_thresh[0] = __max(0.1, nms_pthresh); nms_thresh[1] = __max(0.1, nms_rthresh); nms_thresh[2] = __max(0.1, nms_othresh);
			scale_factor = __max(0.5, __min(0.9, scale_factor));
			if (width != w || height != h || factor != scale_factor)
			{
				scales.clear();
				pnet_images.clear();

				width = w; height = h;
				float minside = __min(width, height);
				int MIN_DET_SIZE = 12;
				float m = (float)MIN_DET_SIZE / min_size;
				minside *= m;
				while (minside > MIN_DET_SIZE)
				{
					scales.push_back(m);
					minside *= factor;
					m *= factor;
				}
				minside = __min(width, height);
				int count = scales.size();
				for (int i = scales.size() - 1; i >= 0; i--)
				{
					if (scales[i] * minside < MIN_DET_SIZE)
						count--;
				}
				
				scales.resize(count);
				pnet_images.resize(count);
			}
		}

		bool Find(const unsigned char* bgr_img, int _width, int _height, int _widthStep, std::vector<ZQ_CNN_BBox>& results, int num_threads = 1)
		{
			double t1 = omp_get_wtime();
			if (width != _width || height != _height)
				return false;
			std::vector<unsigned char> buffer(width* height * 3);
			for (int h = 0; h < height; h++)
			{
				const unsigned char* bgr_row = bgr_img + h*_widthStep;
				unsigned char* cur_row = &buffer[0] + h*width * 3;
				for (int w = 0; w < width; w++)
				{
					cur_row[w * 3 + 0] = bgr_row[w * 3 + 2];
					cur_row[w * 3 + 1] = bgr_row[w * 3 + 1];
					cur_row[w * 3 + 2] = bgr_row[w * 3 + 0];
				}
			}
			if (!input.ConvertFromBGR(&buffer[0], width, height, width*3))
				return false;
			double t2 = omp_get_wtime();
			if(show_debug_info)
				printf("convert cost: %.3f ms\n", 1000 * (t2 - t1));

			ZQ_CNN_OrderScore order;
			pnet.TurnOffShowDebugInfo();
			std::vector<std::vector<ZQ_CNN_BBox>> bounding_boxes(scales.size());
			std::vector<std::vector<ZQ_CNN_OrderScore>> bounding_scores(scales.size());
			for (int i = 0; i < scales.size(); i++)
			{
				int changedH = (int)ceil(height*scales[i]);
				int changedW = (int)ceil(width*scales[i]);
				if (changedH < 2 || changedW < 2)
					continue;
				input.ResizeBilinear(pnet_images[i], changedW, changedH, 0, 0);
				double t11 = omp_get_wtime();
				//for(int j = 0;j < 1000;j++)
				pnet.Forward(pnet_images[i],num_threads);
				double t12 = omp_get_wtime();
				if (show_debug_info)
					printf("Pnet [%d]: resolution [%dx%d], cost:%.3f ms\n", i, changedW, changedH, 1000 * (t12 - t11));
				double t13 = omp_get_wtime();
				//
				const ZQ_CNN_Tensor4D* score = pnet.GetBlobByName("prob1");
				const ZQ_CNN_Tensor4D* location = pnet.GetBlobByName("conv4-2");
				//for pooling 
				int stride = 2;
				int cellsize = 12;
				int count = 0;
				//score p
				int scoreH = score->GetH();
				int scoreW = score->GetW();
				int scorePixStep = score->GetPixelStep();
				int locationPixStep = location->GetPixelStep();
				const float *p = score->GetFirstPixelPtr() + 1;
				const float *plocal = location->GetFirstPixelPtr();
				ZQ_CNN_BBox bbox;
				ZQ_CNN_OrderScore order;
				for (int row = 0; row < scoreH; row++)
				{
					for (int col = 0; col < scoreW; col++)
					{
						if (*p > thresh[0])
						{
							bbox.score = *p;
							order.score = *p;
							order.oriOrder = count;
							bbox.row1 = round((stride*row + 1) / scales[i]);
							bbox.col1 = round((stride*col + 1) / scales[i]);
							bbox.row2 = round((stride*row + 1 + cellsize) / scales[i]);
							bbox.col2 = round((stride*col + 1 + cellsize) / scales[i]);
							bbox.exist = true;
							bbox.area = (bbox.row2 - bbox.row1)*(bbox.col2 - bbox.col1);
							for (int channel = 0; channel < 4; channel++)
								bbox.regreCoord[channel] = *(plocal + channel);
							bounding_boxes[i].push_back(bbox);
							bounding_scores[i].push_back(order);
							count++;
						}
						p += scorePixStep;
						plocal += locationPixStep;
					}
				}
				ZQ_CNN_BBoxUtils::_nms(bounding_boxes[i], bounding_scores[i], 0.5f/*nms_threshold[0]*/, "Union");
				double t14 = omp_get_wtime();
				if (show_debug_info)
					printf("nms cost: %.3f ms\n", 1000 * (t14 - t13));
				
			}
			
			std::vector<ZQ_CNN_BBox> firstBbox;
			std::vector<ZQ_CNN_OrderScore> firstOrderScore;
			int count = 0;
			for (int i = 0; i < scales.size(); i++)
			{
				std::vector<ZQ_CNN_BBox>::iterator it = bounding_boxes[i].begin();
				for (; it != bounding_boxes[i].end(); it++)
				{
					if ((*it).exist)
					{
						firstBbox.push_back(*it);
						order.score = (*it).score;
						order.oriOrder = count;
						firstOrderScore.push_back(order);
						count++;
					}
				}
			}


			//the first stage's nms
			if (count < 1) return false;
			double t15 = omp_get_wtime();
			ZQ_CNN_BBoxUtils::_nms(firstBbox, firstOrderScore, nms_thresh[0], "Union");
			ZQ_CNN_BBoxUtils::_refine_and_square_bbox(firstBbox, width, height);
			double t16 = omp_get_wtime();
			if (show_debug_info)
				printf("nms cost: %.3f ms\n", 1000 * (t16 - t15));
			if (show_debug_info)
				printf("first stage candidate count: %d\n", count);
			double t3 = omp_get_wtime();
			if (show_debug_info)
				printf("stage 1: cost %.3f ms\n", 1000 * (t3 - t2));


			/////////////////
			//second stage
			rnet.TurnOffShowDebugInfo();
			count = 0;
			std::vector<ZQ_CNN_BBox>::iterator it = firstBbox.begin();
			std::vector<ZQ_CNN_BBox> secondBbox;
			std::vector<ZQ_CNN_OrderScore> secondScore;
			std::vector<int> src_off_x, src_off_y, src_rect_w, src_rect_h;
			int r_count = 0;
			for (; it != firstBbox.end(); it++)
			{
				if ((*it).exist)
				{
					int off_x = it->col1;
					int off_y = it->row1;
					int rect_w = it->col2 - off_x;
					int rect_h = it->row2 - off_y;
					if (off_x < 0 || off_x + rect_w > width || off_y < 0 || off_y + rect_h > height || rect_w <= 2 || rect_h <= 2)
					{
						(*it).exist = false;
						continue;
					}
					else
					{
						src_off_x.push_back(off_x);
						src_off_y.push_back(off_y);
						src_rect_w.push_back(rect_w);
						src_rect_h.push_back(rect_h);
						r_count++;
						secondBbox.push_back(*it);
					}
				}
			}


			if (!input.ResizeBilinearRect(rnet_image, 24, 24, 0, 0, src_off_x, src_off_y, src_rect_w, src_rect_h))
			{
				return false;
			}
			double t21 = omp_get_wtime();
			rnet.Forward(rnet_image,num_threads);
			double t22 = omp_get_wtime();
			const ZQ_CNN_Tensor4D* score = rnet.GetBlobByName("prob1");
			const ZQ_CNN_Tensor4D* location = rnet.GetBlobByName("conv5-2");
			const float* score_ptr = score->GetFirstPixelPtr();
			const float* location_ptr = location->GetFirstPixelPtr();
			int score_sliceStep = score->GetSliceStep();
			int location_sliceStep = location->GetSliceStep();
			for(int i = 0; i < r_count;i++)
			{
				if (score_ptr[i*score_sliceStep+1] > thresh[1])
				{
					for (int j = 0; j < 4; j++)
						secondBbox[i].regreCoord[j] = location_ptr[i*location_sliceStep+j];
					secondBbox[i].area = src_rect_w[i] * src_rect_h[i];
					secondBbox[i].score = score_ptr[i*score_sliceStep + 1];
					order.score = secondBbox[i].score;
					order.oriOrder = count++;
					secondScore.push_back(order);
				}
				else
				{
					secondBbox[i].exist = false;
				}
			}
			
			if (count < 1)
				return false;

			
			for (int i = secondBbox.size()-1; i >= 0; i--)
			{
				if (!secondBbox[i].exist)
					secondBbox.erase(secondBbox.begin() + i);
			}
			ZQ_CNN_BBoxUtils::_nms(secondBbox, secondScore, nms_thresh[1], "Union");
			ZQ_CNN_BBoxUtils::_refine_and_square_bbox(secondBbox, width, height);

			double t4 = omp_get_wtime();
			if (show_debug_info)
				printf("run Rnet [%d] times (%.3f ms), candidate after nms: %d \n", r_count, 1000*(t22-t21), count);
			if (show_debug_info)
				printf("stage 2: cost %.3f ms\n", 1000 * (t4 - t3));

			//////

			//third stage 
			onet.TurnOffShowDebugInfo();
			count = 0;
			it = secondBbox.begin();
			std::vector<ZQ_CNN_BBox> thirdBbox;
			std::vector<ZQ_CNN_OrderScore> thirdScore;
			double t9 = omp_get_wtime();
			double part1 = 0, part2 = 0;
			int o_count = 0;
			src_off_x.clear(); src_off_y.clear(); src_rect_w.clear(); src_rect_h.clear();
			for (; it != secondBbox.end(); it++)
			{
				if ((*it).exist)
				{
					int off_x = it->col1;
					int off_y = it->row1;
					int rect_w = it->col2 - off_x;
					int rect_h = it->row2 - off_y;
					if (off_x < 0 || off_x + rect_w > width || off_y < 0 || off_y + rect_h > height || rect_w <= 2 || rect_h <= 2)
					{
						(*it).exist = false;
						continue;
					}
					else
					{
						src_off_x.push_back(off_x);
						src_off_y.push_back(off_y);
						src_rect_w.push_back(rect_w);
						src_rect_h.push_back(rect_h);
						o_count++;
						thirdBbox.push_back(*it);
					}
				}
			}


			if (!input.ResizeBilinearRect(onet_image, 48, 48, 0, 0, src_off_x, src_off_y, src_rect_w, src_rect_h))
			{
				return false;
			}

			double t31 = omp_get_wtime();
			onet.Forward(onet_image,num_threads);
			double t32 = omp_get_wtime();
			score = onet.GetBlobByName("prob1");
			location = onet.GetBlobByName("conv6-2");
			const ZQ_CNN_Tensor4D* keyPoint = onet.GetBlobByName("conv6-3");
			score_ptr = score->GetFirstPixelPtr();
			location_ptr = location->GetFirstPixelPtr();
			const float* keyPoint_ptr = keyPoint->GetFirstPixelPtr();
			score_sliceStep = score->GetSliceStep();
			location_sliceStep = location->GetSliceStep();
			int keyPoint_sliceStep = keyPoint->GetSliceStep();
			for (int i = 0; i < o_count; i++)
			{
				if (score_ptr[i*score_sliceStep + 1] > thresh[2])
				{
					for (int j = 0; j < 4; j++)
						thirdBbox[i].regreCoord[j] = location_ptr[i*location_sliceStep + j];
					for (int num = 0; num < 5; num++)
					{
						thirdBbox[i].ppoint[num] = thirdBbox[i].col1 + (thirdBbox[i].col2 - thirdBbox[i].col1)*keyPoint_ptr[i*keyPoint_sliceStep + num];
						thirdBbox[i].ppoint[num+5] = thirdBbox[i].row1 + (thirdBbox[i].row2 - thirdBbox[i].row1)*keyPoint_ptr[i*keyPoint_sliceStep + num + 5];
					}
					thirdBbox[i].area = src_rect_w[i] * src_rect_h[i];
					thirdBbox[i].score = score_ptr[i*score_sliceStep + 1];
					order.score = thirdBbox[i].score;
					order.oriOrder = count++;
					thirdScore.push_back(order);
				}
				else
				{
					thirdBbox[i].exist = false;
				}
			}

			
			if (count < 1)
				return false;
			
			for (int i = thirdBbox.size() - 1; i >= 0; i--)
			{
				if (!thirdBbox[i].exist)
					thirdBbox.erase(thirdBbox.begin() + i);
			}
			ZQ_CNN_BBoxUtils::_refine_and_square_bbox(thirdBbox, width, height);
			ZQ_CNN_BBoxUtils::_nms(thirdBbox, thirdScore, nms_thresh[2], "Min");
			double t5 = omp_get_wtime();
			if (show_debug_info)
				printf("run Onet [%d] times (%.3f ms), candidate after nms: %d \n", o_count,1000*(t32-t31), count);
			if (show_debug_info)
				printf("stage 3: cost %.3f ms\n", 1000 * (t5 - t4));
			results = thirdBbox;
			if (show_debug_info)
				printf("final found num : %d, cost: %.3f ms\n", (int)(results.size()), 1000*(t5-t1));
			return true;
		}
	};
}
#endif
