#ifndef _ZQ_CNN_FORWARD_SSE_UTILS_H_
#define _ZQ_CNN_FORWARD_SSE_UTILS_H_
#pragma once
#include "ZQ_CNN_Defines.h"
#include "ZQ_CNN_Tensor4D.h"
#include "ZQ_CNN_BBoxUtils.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <omp.h>

namespace ZQ
{
	class ZQ_CNN_Forward_SSEUtils
	{
	public:
		static bool ConvolutionWithBias(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& filters, const ZQ_CNN_Tensor4D& bias,
			int strideH, int strideW, int dilation_H, int dilation_W, int padH, int padW, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			//num_threads = 4;
			double t1 = omp_get_wtime();
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int filter_N = filters.GetN();
			int filter_H = filters.GetH();
			int filter_W = filters.GetW();
			int filter_C = filters.GetC();
			int out_N = output.GetN();
			int out_H = output.GetH();
			int out_W = output.GetW();
			int out_C = output.GetC();
			float bias_C = bias.GetC();
			int need_H = (in_H - (filter_H - 1)*dilation_H - 1 + (padH << 1)) / strideH + 1;
			int need_W = (in_W - (filter_W - 1)*dilation_W - 1 + (padW << 1)) / strideW + 1;
			if (in_N <= 0 || in_H <= 0 || in_W <= 0 || in_C == 0
				|| need_H < 0  || need_W < 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return true;
			}
			if (filter_C != in_C || filter_N != bias_C)
				return false;

			int need_N = in_N;
			
			int need_C = filter_N;
			if (out_N != need_N || out_H != need_H || out_W != need_W || out_C != need_C)
			{
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);
			}

			if (padH != 0 || padW != 0)
			{
				if (!input.Padding(padW, padH, 0))
					return false;
			}

			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int filter_sliceStep = filters.GetSliceStep();
			int filter_widthStep = filters.GetWidthStep();
			int filter_pixStep = filters.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			float* in_firstPixelData = input.GetFirstPixelPtr() - padH*in_widthStep - padW*in_pixStep;
			const float* filter_firstPixelData = filters.GetFirstPixelPtr();
			float* out_firstPixelData = output.GetFirstPixelPtr();
			const float* bias_firstPixelData = bias.GetFirstPixelPtr();

			int align_mode = __min((int)input.GetAlignType(), __min((int)filters.GetAlignType(), (int)output.GetAlignType()));
			if (in_C == 1)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_0);
			else if (in_C <= 4)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_128bit);
			else if (in_C <= 8)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_256bit);
			//output.Reset();
			if (num_threads <= 1)
			{
				_convolution_nopadding(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW, dilation_H, dilation_W,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep);
				_addbias(__min(bias.GetAlignType(), output.GetAlignType()), out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep,
					bias_firstPixelData);
			}
			else
			{
				_convolution_nopadding_omp(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW, dilation_H, dilation_W,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep, num_threads);
				_addbias_omp(__min(bias.GetAlignType(), output.GetAlignType()), out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep,
					bias_firstPixelData, num_threads);
			}
			
			
			double t2 = omp_get_wtime();
			//printf("utils:conv: %.3f ms\n", (t2 - t1) * 1000);
			return true;
		}

		static bool Convolution(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& filters, int strideH, int strideW, int dilation_H, int dilation_W, int padH, int padW,
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int filter_N = filters.GetN();
			int filter_H = filters.GetH();
			int filter_W = filters.GetW();
			int filter_C = filters.GetC();
			int out_N = output.GetN();
			int out_H = output.GetH();
			int out_W = output.GetW();
			int out_C = output.GetC();
			int need_H = (in_H - (filter_H - 1)*dilation_H - 1 + (padH << 1)) / strideH + 1;
			int need_W = (in_W - (filter_W - 1)*dilation_W - 1 + (padW << 1)) / strideW + 1;
			if (in_N <= 0 || in_H <= 0 || in_W <= 0 || in_C == 0
				|| need_H < 0 || need_W < 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return true;
			}
			if (filter_C != in_C)
				return false;

			int need_N = in_N;
			int need_C = filter_N;
			if (out_N != need_N || out_H != need_H || out_W != need_W || out_C != need_C)
			{
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);
			}

			if (padH != 0 || padW != 0)
			{
				if (!input.Padding(padW, padH, 0))
					return false;
			}
			
			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int filter_sliceStep = filters.GetSliceStep();
			int filter_widthStep = filters.GetWidthStep();
			int filter_pixStep = filters.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			float* in_firstPixelData = input.GetFirstPixelPtr() - padH*in_widthStep - padW*in_pixStep;
			const float* filter_firstPixelData = filters.GetFirstPixelPtr();
			float* out_firstPixelData = output.GetFirstPixelPtr();

			int align_mode = __min((int)input.GetAlignType(), __min((int)filters.GetAlignType(), (int)output.GetAlignType()));
			if (in_C == 1)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_0);
			else if (in_C <= 4)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_128bit);
			else if (in_C <= 8)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_256bit);

			//output.Reset();
			if (num_threads <= 1)
			{
				_convolution_nopadding(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW, dilation_H, dilation_W,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep);
			}
			else
			{
				_convolution_nopadding_omp(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW, dilation_H, dilation_W,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep, num_threads);
			}
			
			return true;
		}

		static bool DepthwiseConvolutionWithBias(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& filters, const ZQ_CNN_Tensor4D& bias,
			int strideH, int strideW, int padH, int padW, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			//num_threads = 4;
			double t1 = omp_get_wtime();
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int filter_N = filters.GetN();
			int filter_H = filters.GetH();
			int filter_W = filters.GetW();
			int filter_C = filters.GetC();
			int out_N = output.GetN();
			int out_H = output.GetH();
			int out_W = output.GetW();
			int out_C = output.GetC();
			float bias_C = bias.GetC();
			if (in_N <= 0 || in_H <= 0 || in_W <= 0 || in_C == 0
				|| (in_H - filter_H + (padH << 1)) < 0 || (in_W - filter_W + (padW << 1)) < 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return true;
			}
			if (filter_C != in_C || filter_N != 1)
				return false;

			int need_N = in_N;
			int need_H = (in_H - filter_H + (padH << 1)) / strideH + 1;
			int need_W = (in_W - filter_W + (padW << 1)) / strideW + 1;
			int need_C = in_C;
			if (out_N != need_N || out_H != need_H || out_W != need_W || out_C != need_C)
			{
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);
			}

			if (padH != 0 || padW != 0)
			{
				if (!input.Padding(padW, padH, 0))
					return false;
			}

			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int filter_sliceStep = filters.GetSliceStep();
			int filter_widthStep = filters.GetWidthStep();
			int filter_pixStep = filters.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			float* in_firstPixelData = input.GetFirstPixelPtr() - padH*in_widthStep - padW*in_pixStep;
			const float* filter_firstPixelData = filters.GetFirstPixelPtr();
			float* out_firstPixelData = output.GetFirstPixelPtr();
			const float* bias_firstPixelData = bias.GetFirstPixelPtr();

			int align_mode = __min((int)input.GetAlignType(), __min((int)filters.GetAlignType(), (int)output.GetAlignType()));
			if (in_C == 1)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_0);
			else if (in_C <= 4)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_128bit);
			else if (in_C <= 8)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_256bit);
			//output.Reset();
			if (num_threads <= 1)
			{
				_depthwise_convolution_nopadding(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep);
				_addbias(__min(bias.GetAlignType(), output.GetAlignType()), out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep,
					bias_firstPixelData);
			}
			else
			{
				_depthwise_convolution_nopadding_omp(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep, num_threads);
				_addbias_omp(__min(bias.GetAlignType(), output.GetAlignType()), out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep,
					bias_firstPixelData, num_threads);
			}
			
			double t2 = omp_get_wtime();
			//printf("utils:conv: %.3f ms\n", (t2 - t1) * 1000);
			return true;
		}

		static bool DepthwiseConvolution(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& filters, int strideH, int strideW, int padH, int padW, 
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			//num_threads = 1;
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int filter_N = filters.GetN();
			int filter_H = filters.GetH();
			int filter_W = filters.GetW();
			int filter_C = filters.GetC();
			int out_N = output.GetN();
			int out_H = output.GetH();
			int out_W = output.GetW();
			int out_C = output.GetC();
			if (in_N <= 0 || in_H <= 0 || in_W <= 0 || in_C == 0
				|| (in_H - filter_H + (padH << 1)) < 0 || (in_W - filter_W + (padW << 1)) < 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return true;
			}
			if (filter_C != in_C || filter_N != 1)
				return false;

			int need_N = in_N;
			int need_H = (in_H - filter_H + (padH << 1)) / strideH + 1;
			int need_W = (in_W - filter_W + (padW << 1)) / strideW + 1;
			int need_C = in_C;
			if (out_N != need_N || out_H != need_H || out_W != need_W || out_C != need_C)
			{
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);
			}

			if (padH != 0 || padW != 0)
			{
				if (!input.Padding(padW, padH, 0))
					return false;
			}

			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int filter_sliceStep = filters.GetSliceStep();
			int filter_widthStep = filters.GetWidthStep();
			int filter_pixStep = filters.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			float* in_firstPixelData = input.GetFirstPixelPtr() - padH*in_widthStep - padW*in_pixStep;
			const float* filter_firstPixelData = filters.GetFirstPixelPtr();
			float* out_firstPixelData = output.GetFirstPixelPtr();

			int align_mode = __min((int)input.GetAlignType(), __min((int)filters.GetAlignType(), (int)output.GetAlignType()));
			if (in_C == 1)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_0);
			else if (in_C <= 4)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_128bit);
			else if (in_C <= 8)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_256bit);

			//output.Reset();
			if (num_threads <= 1)
			{
				_depthwise_convolution_nopadding(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep);
			}
			else
			{
				_depthwise_convolution_nopadding_omp(align_mode, in_firstPixelData, in_N, in_H + (padH << 1), in_W + (padW << 1), in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_H, filter_W, filter_C, filter_pixStep, filter_widthStep, filter_sliceStep, strideH, strideW,
					out_firstPixelData, need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep, num_threads);
			}

			return true;
		}

		static bool InnerProductWithBias(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& filters, const ZQ_CNN_Tensor4D& bias, 
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			double t1 = omp_get_wtime();
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int filter_N = filters.GetN();
			int filter_H = filters.GetH();
			int filter_W = filters.GetW();
			int filter_C = filters.GetC();
			int out_N = output.GetN();
			int out_H = output.GetH();
			int out_W = output.GetW();
			int out_C = output.GetC();
			float bias_C = bias.GetC();
			if (in_N <= 0 || in_H <= 0 || in_W <= 0 || in_C == 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return true;
			}
			if (filter_H != in_H || filter_W != in_W || filter_C != in_C || filter_N != bias_C)
				return false;

			int need_N = in_N;
			int need_H = 1;
			int need_W = 1;
			int need_C = filter_N;
			if (out_N != need_N || out_H != need_H || out_W != need_W || out_C != need_C)
			{
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);
			}

			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int filter_sliceStep = filters.GetSliceStep();
			int filter_widthStep = filters.GetWidthStep();
			int filter_pixStep = filters.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			float* in_firstPixelData = input.GetFirstPixelPtr();
			const float* filter_firstPixelData = filters.GetFirstPixelPtr();
			float* out_firstPixelData = output.GetFirstPixelPtr();
			const float* bias_firstPixelData = bias.GetFirstPixelPtr();

			int align_mode = __min((int)input.GetAlignType(), __min((int)filters.GetAlignType(), (int)output.GetAlignType()));
			if (in_C == 1)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_0);
			else if (in_C <= 4)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_128bit);
			else if (in_C <= 8)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_256bit);
			if (num_threads <= 1)
			{
				_inner_product(align_mode, in_firstPixelData, in_N, in_H, in_W, in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_pixStep, filter_widthStep, filter_sliceStep,
					out_firstPixelData, need_N, out_sliceStep, num_threads);
				_addbias(output.GetAlignType(), output.GetFirstPixelPtr(), need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep,
					bias_firstPixelData);
			}
			else
			{
				_inner_product(align_mode, in_firstPixelData, in_N, in_H, in_W, in_C, in_pixStep, in_widthStep, in_sliceStep,
					filter_firstPixelData, filter_N, filter_pixStep, filter_widthStep, filter_sliceStep,
					out_firstPixelData, need_N, out_sliceStep, num_threads);
				_addbias_omp(output.GetAlignType(), output.GetFirstPixelPtr(), need_N, need_H, need_W, need_C, out_pixStep, out_widthStep, out_sliceStep,
					bias_firstPixelData, num_threads);
			}
			double t2 = omp_get_wtime();
			//printf("utils:inner: %.3f ms\n", (t2 - t1)*1000);
			return true;
		}

		static bool InnerProduct(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& filters, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int filter_N = filters.GetN();
			int filter_H = filters.GetH();
			int filter_W = filters.GetW();
			int filter_C = filters.GetC();
			int out_N = output.GetN();
			int out_H = output.GetH();
			int out_W = output.GetW();
			int out_C = output.GetC();
			if (in_N <= 0 || in_H <= 0 || in_W <= 0 || in_C == 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return true;
			}
			if (filter_H != in_H || filter_W != in_W || filter_C != in_C)
				return false;

			int need_N = in_N;
			int need_H = 1;
			int need_W = 1;
			int need_C = filter_N;
			if (out_N != need_N || out_H != need_H || out_W != need_W || out_C != need_C)
			{
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);
			}

			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int filter_sliceStep = filters.GetSliceStep();
			int filter_widthStep = filters.GetWidthStep();
			int filter_pixStep = filters.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			float* in_firstPixelData = input.GetFirstPixelPtr();
			const float* filter_firstPixelData = filters.GetFirstPixelPtr();
			float* out_firstPixelData = output.GetFirstPixelPtr();
			
			int align_mode = __min((int)input.GetAlignType(), __min((int)filters.GetAlignType(), (int)output.GetAlignType()));
			if (in_C == 1)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_0);
			else if (in_C <= 4)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_128bit);
			else if (in_C <= 8)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_256bit);
			_inner_product(align_mode, in_firstPixelData, in_N, in_H, in_W, in_C, in_pixStep, in_widthStep, in_sliceStep,
				filter_firstPixelData, filter_N, filter_pixStep, filter_widthStep, filter_sliceStep,
				out_firstPixelData, need_N, out_sliceStep, num_threads);

			return true;
		}

		static void MaxPooling(const ZQ_CNN_Tensor4D &input, ZQ_CNN_Tensor4D &output, int kernel_H, int kernel_W, 
			int stride_H, int stride_W, bool global_pool, int num_threads = 1)
		{
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int need_W, need_H;
			int need_N = in_N;
			int need_C = in_C;
			if (global_pool)
			{
				need_H = 1;
				need_W = 1;
				kernel_H = in_H;
				kernel_W = in_W;
				stride_H = 1;
				stride_W = 1;
			}
			else
			{
				need_W = ceil((float)(in_W - kernel_W) / stride_W + 1);
				need_H = ceil((float)(in_H - kernel_H) / stride_H + 1);
			}
			
			if (need_W <= 0 || need_H <= 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return ;
			}

			bool suredivided = (in_H - kernel_H) % stride_H == 0 && (in_W - kernel_W) % stride_W == 0;
			if (output.GetN() != need_N || output.GetH() != need_H || output.GetW() != need_W || output.GetC() != need_C)
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);

			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();

			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			if(num_threads <= 1)
				_maxpooling(align_mode, in_data, in_N, in_H, in_W, in_C, in_pixStep, in_widthStep, in_sliceStep, kernel_H, kernel_W, stride_H, stride_W, 
					out_data, need_H, need_W, out_pixStep, out_widthStep, out_sliceStep);
			else
				_maxpooling_omp(align_mode, in_data, in_N, in_H, in_W, in_C, in_pixStep, in_widthStep, in_sliceStep, kernel_H, kernel_W, stride_H, stride_W,
					out_data, need_H, need_W, out_pixStep, out_widthStep, out_sliceStep, num_threads);
			
		}

		static void AVGPooling(const ZQ_CNN_Tensor4D &input, ZQ_CNN_Tensor4D &output, int kernel_H, int kernel_W,
			int stride_H, int stride_W, bool global_pool, int num_threads = 1)
		{
			int in_N = input.GetN();
			int in_H = input.GetH();
			int in_W = input.GetW();
			int in_C = input.GetC();
			int need_W, need_H;
			int need_N = in_N;
			int need_C = in_C;
			if (global_pool)
			{
				need_H = 1;
				need_W = 1;
				kernel_H = in_H;
				kernel_W = in_W;
				stride_H = 1;
				stride_W = 1;
			}
			else
			{
				need_W = ceil((float)(in_W - kernel_W) / stride_W + 1);
				need_H = ceil((float)(in_H - kernel_H) / stride_H + 1);
			}

			if (need_W <= 0 || need_H <= 0)
			{
				output.ChangeSize(0, 0, 0, 0, 0, 0);
				return;
			}

			bool suredivided = (in_H - kernel_H) % stride_H == 0 && (in_W - kernel_W) % stride_W == 0;
			if (output.GetN() != need_N || output.GetH() != need_H || output.GetW() != need_W || output.GetC() != need_C)
				output.ChangeSize(need_N, need_H, need_W, need_C, 0, 0);

			int in_sliceStep = input.GetSliceStep();
			int in_widthStep = input.GetWidthStep();
			int in_pixStep = input.GetPixelStep();
			int out_sliceStep = output.GetSliceStep();
			int out_widthStep = output.GetWidthStep();
			int out_pixStep = output.GetPixelStep();
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();

			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			if (num_threads <= 1)
				_avgpooling(align_mode, in_data, in_N, in_H, in_W, in_C, in_pixStep, in_widthStep, in_sliceStep, kernel_H, kernel_W, stride_H, stride_W,
					out_data, need_H, need_W, out_pixStep, out_widthStep, out_sliceStep);
			else
				_avgpooling_omp(align_mode, in_data, in_N, in_H, in_W, in_C, in_pixStep, in_widthStep, in_sliceStep, kernel_H, kernel_W, stride_H, stride_W,
					out_data, need_H, need_W, out_pixStep, out_widthStep, out_sliceStep, num_threads);

		}

		static bool PReLU(ZQ_CNN_Tensor4D &input, const ZQ_CNN_Tensor4D& slope, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			if (slope.GetC() != C)
				return false;
			float* data = input.GetFirstPixelPtr();
			const float* slope_Data = slope.GetFirstPixelPtr();
			int pixelStep = input.GetPixelStep();
			int widthStep = input.GetWidthStep();
			int sliceStep = input.GetSliceStep();

			int align_mode = __min(input.GetAlignType(), slope.GetAlignType());
			if(num_threads <= 1)
				_prelu(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, slope_Data);
			else
				_prelu_omp(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, slope_Data, num_threads);
			return true;
		}

		static void ReLU(ZQ_CNN_Tensor4D &input, int num_threads = 1)
		{
			//num_threads = 2;
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return ;
			float* data = input.GetFirstPixelPtr();
			int pixelStep = input.GetPixelStep();
			int widthStep = input.GetWidthStep();
			int sliceStep = input.GetSliceStep();

			int align_mode = input.GetAlignType();
			if(num_threads <= 1)
				_relu(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep);
			else
				_relu_omp(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep,num_threads);
		}

		static void Dropout(ZQ_CNN_Tensor4D &input, float dropout_ratio, int num_threads = 1)
		{
			if (dropout_ratio == 0.0f)
			{
				return;
			}
			else
			{
				int N = input.GetN();
				int H = input.GetH();
				int W = input.GetW();
				int C = input.GetC();
				if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
					return ;
				int sliceStep = input.GetSliceStep();
				int widthStep = input.GetWidthStep();
				int pixStep = input.GetPixelStep();
				float* data = input.GetFirstPixelPtr();

				int align_mode = input.GetAlignType();
				_dropout(align_mode, data, N, H, W, C, pixStep, widthStep, sliceStep, dropout_ratio, num_threads);
			}
		}

		static bool Softmax(ZQ_CNN_Tensor4D &input, int axis, int num_threads = 1)
		{
			if (axis < 0 || axis >= 4)
				return false;
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			float* data = input.GetFirstPixelPtr();
			int sliceStep = input.GetSliceStep();
			int widthStep = input.GetWidthStep();
			int pixStep = input.GetPixelStep();

			int align_mode = input.GetAlignType();
			/*if (C <= 8)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_0);
			else if (C <= 16)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_128bit);
			else if (C <= 32)
				align_mode = __min(align_mode, ZQ_CNN_Tensor4D::ALIGN_256bit);
			*/
			_softmax(align_mode, axis, data, N, H, W, C, pixStep, widthStep, sliceStep, num_threads);
			return true;
		}

		static bool BatchNormScaleBias(ZQ_CNN_Tensor4D &input, const ZQ_CNN_Tensor4D& mean, const ZQ_CNN_Tensor4D& var, const ZQ_CNN_Tensor4D& slope, 
			const ZQ_CNN_Tensor4D& bias, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			if (mean.GetC() != C || var.GetC() != C || slope.GetC() != C || bias.GetC() != C)
				return false;
			float* data = input.GetFirstPixelPtr();
			const float* mean_data = mean.GetFirstPixelPtr();
			const float* var_data = var.GetFirstPixelPtr();
			const float* slope_data = slope.GetFirstPixelPtr();
			const float* bias_data = bias.GetFirstPixelPtr();
			int pixelStep = input.GetPixelStep();
			int widthStep = input.GetWidthStep();
			int sliceStep = input.GetSliceStep();

			int align_mode = __min(input.GetAlignType(), __min(mean.GetAlignType(), __min(var.GetAlignType(), __min(slope.GetAlignType(), bias.GetAlignType()))));
			if(num_threads <= 1)
				_batchnorm_scalebias(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, mean_data, var_data, 
					slope_data, bias_data);
			else
				_batchnorm_scalebias_omp(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, mean_data, var_data,
					slope_data, bias_data, num_threads);
			return true;
		}

		static bool BatchNorm(ZQ_CNN_Tensor4D &input, const ZQ_CNN_Tensor4D& mean, const ZQ_CNN_Tensor4D& var, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			if (mean.GetC() != C || var.GetC() != C)
				return false;
			float* data = input.GetFirstPixelPtr();
			const float* mean_data = mean.GetFirstPixelPtr();
			const float* var_data = var.GetFirstPixelPtr();
			int pixelStep = input.GetPixelStep();
			int widthStep = input.GetWidthStep();
			int sliceStep = input.GetSliceStep();

			int align_mode = __min(input.GetAlignType(), __min(mean.GetAlignType(), var.GetAlignType()));
			if(num_threads <= 1)
				_batchnorm(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, mean_data, var_data);
			else
				_batchnorm_omp(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, mean_data, var_data, num_threads);
			return true;
		}


		/*
		a = bias - slope * mean / sqrt(var)
		b = slope / sqrt(var)
		value = b * value + a
		*/
		static bool BatchNormScaleBias_Compute_b_a(ZQ_CNN_Tensor4D& b, ZQ_CNN_Tensor4D& a, const ZQ_CNN_Tensor4D& mean, const ZQ_CNN_Tensor4D& var, const ZQ_CNN_Tensor4D& scale, const ZQ_CNN_Tensor4D& bias)
		{
			int C = b.GetC();
			if (C == 0)
				return false;
			
			
			if (a .GetC() != C || mean.GetC() != C || var.GetC() != C || scale.GetC() != C || bias.GetC() != C)
				return false;
			float* b_data = b.GetFirstPixelPtr();
			float* a_data = a.GetFirstPixelPtr();
			const float* mean_data = mean.GetFirstPixelPtr();
			const float* var_data = var.GetFirstPixelPtr();
			const float* scale_data = scale.GetFirstPixelPtr();
			const float* bias_data = bias.GetFirstPixelPtr();
			for (int c = 0; c < C; c++)
			{
				b_data[c] = scale_data[c] / __max(sqrt(__max(var_data[c],0)),1e-32);
				a_data[c] = bias_data[c] - mean_data[c] * b_data[c];
			}
			return true;
		}

		/*
		a = - slope * mean / sqrt(var)
		b = slope / sqrt(var)
		value = b * value + a
		*/
		static bool BatchNormScale_Compute_b_a(ZQ_CNN_Tensor4D& b, ZQ_CNN_Tensor4D& a, const ZQ_CNN_Tensor4D& mean, const ZQ_CNN_Tensor4D& var, const ZQ_CNN_Tensor4D& scale)
		{
			int C = b.GetC();
			if (C == 0)
				return false;


			if (a.GetC() != C || mean.GetC() != C || var.GetC() != C || scale.GetC() != C)
				return false;
			float* b_data = b.GetFirstPixelPtr();
			float* a_data = a.GetFirstPixelPtr();
			const float* mean_data = mean.GetFirstPixelPtr();
			const float* var_data = var.GetFirstPixelPtr();
			const float* scale_data = scale.GetFirstPixelPtr();
			for (int c = 0; c < C; c++)
			{
				b_data[c] = scale_data[c] / sqrt(var_data[c]);
				a_data[c] =  - mean_data[c] * b_data[c];
			}
			return true;
		}

		/*
		a = - slope * mean / sqrt(var)
		b = slope / sqrt(var)
		value = b * value + a
		*/
		static bool BatchNorm_Compute_b_a(ZQ_CNN_Tensor4D& b, ZQ_CNN_Tensor4D& a, const ZQ_CNN_Tensor4D& mean, const ZQ_CNN_Tensor4D& var)
		{
			int C = b.GetC();
			if (C == 0)
				return false;


			if (a.GetC() != C || mean.GetC() != C || var.GetC() != C)
				return false;
			float* b_data = b.GetFirstPixelPtr();
			float* a_data = a.GetFirstPixelPtr();
			const float* mean_data = mean.GetFirstPixelPtr();
			const float* var_data = var.GetFirstPixelPtr();
			for (int c = 0; c < C; c++)
			{
				b_data[c] = 1.0f / sqrt(var_data[c]);
				a_data[c] = -mean_data[c] * b_data[c];
			}
			return true;
		}

		/*
		a = bias - slope * mean / sqrt(var)
		b = slope / sqrt(var)
		value = b * value + a
		***OR***
		a = -mean/sqrt(var)
		b = 1/sqrt(var)
		value = b * value + a
		*/
		static bool BatchNorm_b_a(ZQ_CNN_Tensor4D &input, const ZQ_CNN_Tensor4D& b, const ZQ_CNN_Tensor4D& a, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			if (b.GetC() != C || a.GetC() != C)
				return false;
			float* data = input.GetFirstPixelPtr();
			const float* b_data = b.GetFirstPixelPtr();
			const float* a_data = a.GetFirstPixelPtr();
			int pixelStep = input.GetPixelStep();
			int widthStep = input.GetWidthStep();
			int sliceStep = input.GetSliceStep();

			int align_mode = __min(input.GetAlignType(), __min(b.GetAlignType(),a.GetAlignType()));
			if(num_threads <= 1)
				_batchnorm_b_a(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, b_data, a_data);
			else
				_batchnorm_b_a_omp(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, b_data, a_data, num_threads);
			return true;
		}

		static bool ScaleWithBias(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& scale, const ZQ_CNN_Tensor4D& bias, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			if (scale.GetC() != C || scale.GetC() != C)
				return false;
			float* data = input.GetFirstPixelPtr();
			const float* scale_data = scale.GetFirstPixelPtr();
			const float* bias_data = bias.GetFirstPixelPtr();
			int pixelStep = input.GetPixelStep();
			int widthStep = input.GetWidthStep();
			int sliceStep = input.GetSliceStep();

			int align_mode = __min(input.GetAlignType(), __min(scale.GetAlignType(), bias.GetAlignType()));
			if(num_threads <= 1)
				_scalebias(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, scale_data, bias_data);
			else
				_scalebias_omp(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, scale_data, bias_data, num_threads);
			return true;
		}

		static bool Scale(ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& scale, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			if (scale.GetC() != C)
				return false;
			float* data = input.GetFirstPixelPtr();
			const float* scale_data = scale.GetFirstPixelPtr();
			int pixelStep = input.GetPixelStep();
			int widthStep = input.GetWidthStep();
			int sliceStep = input.GetSliceStep();

			int align_mode = __min(input.GetAlignType(), scale.GetAlignType());
			if(num_threads <= 1)
				_scalebias(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, scale_data, NULL);
			else
				_scalebias_omp(align_mode, data, N, H, W, C, pixelStep, widthStep, sliceStep, scale_data, NULL, num_threads);
			return true;
		}

		static bool Eltwise_Sum(const std::vector<const ZQ_CNN_Tensor4D*>& input, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int in_num = input.size();
			if (in_num < 2)
				return false;
			for (int i = 0; i < in_num; i++)
			{
				if (input[i] == 0) return false;
			}
			int N = input[0]->GetN();
			int H = input[0]->GetH();
			int W = input[0]->GetW();
			int C = input[0]->GetC();
			for (int i = 1; i < in_num; i++)
			{
				if (N != input[i]->GetN() || H != input[i]->GetH() || W != input[i]->GetW() || C != input[i]->GetC())
					return false;
			}
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			std::vector<const float*> in_tensor_data(in_num);
			std::vector<int> in_pixStep(in_num), in_widthStep(in_num), in_sliceStep(in_num);
			float* out_data = output.GetFirstPixelPtr();
			for (int i = 0; i < in_num; i++)
			{
				in_tensor_data[i] = input[i]->GetFirstPixelPtr();
				in_pixStep[i] = input[i]->GetPixelStep();
				in_widthStep[i] = input[i]->GetWidthStep();
				in_sliceStep[i] = input[i]->GetSliceStep();
			}
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = output.GetAlignType();
			for (int i = 0; i < in_num; i++)
				align_mode = __min(align_mode, input[i]->GetAlignType());
			if(num_threads <= 1)
				_eltwise_sum(align_mode, in_num, &in_tensor_data[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep,
					out_sliceStep);
			else
				_eltwise_sum_omp(align_mode, in_num, &in_tensor_data[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep, 
					out_sliceStep, num_threads);
			return true;
		}

		static bool Eltwise_SumWithWeight(const std::vector<const ZQ_CNN_Tensor4D*>& input, const std::vector<float>& weight, 
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int in_num = input.size();
			if (in_num < 2 || in_num != weight.size())
				return false;
			for (int i = 0; i < in_num; i++)
			{
				if (input[i] == 0) return false;
			}
			int N = input[0]->GetN();
			int H = input[0]->GetH();
			int W = input[0]->GetW();
			int C = input[0]->GetC();
			for (int i = 1; i < in_num; i++)
			{
				if (N != input[i]->GetN() || H != input[i]->GetH() || W != input[i]->GetW() || C != input[i]->GetC())
					return false;
			}
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			std::vector<const float*> in_tensor_data(in_num);
			std::vector<int> in_pixStep(in_num), in_widthStep(in_num), in_sliceStep(in_num);
			float* out_data = output.GetFirstPixelPtr();
			for (int i = 0; i < in_num; i++)
			{
				in_tensor_data[i] = input[i]->GetFirstPixelPtr();
				in_pixStep[i] = input[i]->GetPixelStep();
				in_widthStep[i] = input[i]->GetWidthStep();
				in_sliceStep[i] = input[i]->GetSliceStep();
			}
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = output.GetAlignType();
			for (int i = 0; i < in_num; i++)
				align_mode = __min(align_mode, input[i]->GetAlignType());
			if(num_threads <= 1)
				_eltwise_sum_with_weight(align_mode, in_num, &in_tensor_data[0], &weight[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep,
					out_sliceStep);
			else
				_eltwise_sum_with_weight_omp(align_mode, in_num, &in_tensor_data[0], &weight[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep, 
					out_sliceStep, num_threads);
			return true;
		}

		static bool Eltwise_Mul(const std::vector<const ZQ_CNN_Tensor4D*>& input, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int in_num = input.size();
			if (in_num < 2)
				return false;
			for (int i = 0; i < in_num; i++)
			{
				if (input[i] == 0) return false;
			}
			int N = input[0]->GetN();
			int H = input[0]->GetH();
			int W = input[0]->GetW();
			int C = input[0]->GetC();
			for (int i = 1; i < in_num; i++)
			{
				if (N != input[i]->GetN() || H != input[i]->GetH() || W != input[i]->GetW() || C != input[i]->GetC())
					return false;
			}
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			std::vector<const float*> in_tensor_data(in_num);
			std::vector<int> in_pixStep(in_num), in_widthStep(in_num), in_sliceStep(in_num);
			float* out_data = output.GetFirstPixelPtr();
			for (int i = 0; i < in_num; i++)
			{
				in_tensor_data[i] = input[i]->GetFirstPixelPtr();
				in_pixStep[i] = input[i]->GetPixelStep();
				in_widthStep[i] = input[i]->GetWidthStep();
				in_sliceStep[i] = input[i]->GetSliceStep();
			}
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = output.GetAlignType();
			for (int i = 0; i < in_num; i++)
				align_mode = __min(align_mode, input[i]->GetAlignType());
			if(num_threads <= 1)
				_eltwise_mul(align_mode, in_num, &in_tensor_data[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep,
					out_sliceStep);
			else
				_eltwise_mul_omp(align_mode, in_num, &in_tensor_data[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep, 
					out_sliceStep, num_threads);
			return true;
		}

		static bool Eltwise_Max(const std::vector<const ZQ_CNN_Tensor4D*>& input, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int in_num = input.size();
			if (in_num < 2)
				return false;
			for (int i = 0; i < in_num; i++)
			{
				if (input[i] == 0) return false;
			}
			int N = input[0]->GetN();
			int H = input[0]->GetH();
			int W = input[0]->GetW();
			int C = input[0]->GetC();
			for (int i = 1; i < in_num; i++)
			{
				if (N != input[i]->GetN() || H != input[i]->GetH() || W != input[i]->GetW() || C != input[i]->GetC())
					return false;
			}
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			std::vector<const float*> in_tensor_data(in_num);
			std::vector<int> in_pixStep(in_num), in_widthStep(in_num), in_sliceStep(in_num);
			float* out_data = output.GetFirstPixelPtr();
			for (int i = 0; i < in_num; i++)
			{
				in_tensor_data[i] = input[i]->GetFirstPixelPtr();
				in_pixStep[i] = input[i]->GetPixelStep();
				in_widthStep[i] = input[i]->GetWidthStep();
				in_sliceStep[i] = input[i]->GetSliceStep();
			}
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = output.GetAlignType();
			for (int i = 0; i < in_num; i++)
				align_mode = __min(align_mode, input[i]->GetAlignType());
			if(num_threads <= 1)
				_eltwise_max(align_mode, in_num, &in_tensor_data[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep, 
					out_sliceStep);
			else
				_eltwise_max_omp(align_mode, in_num, &in_tensor_data[0], N, H, W, C, &in_pixStep[0], &in_widthStep[0], &in_sliceStep[0], out_data, out_pixStep, out_widthStep,
					out_sliceStep, num_threads);
			return true;
		}

		
		static bool ScalarOperation_Add(const ZQ_CNN_Tensor4D& input, float scalar, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			_scalaroperation_add(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep, 
				out_data, out_pixStep, out_widthStep, out_sliceStep);
			return true;
		}

		static bool ScalarOperation_Add(ZQ_CNN_Tensor4D& input, float scalar, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int align_mode = input.GetAlignType();
			float* in_data = input.GetFirstPixelPtr();
			_scalaroperation_add(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep);
			return true;
		}
		
		static bool ScalarOperation_Mul(const ZQ_CNN_Tensor4D& input, float scalar, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			_scalaroperation_mul(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep,
				out_data, out_pixStep, out_widthStep, out_sliceStep);
			return true;
		}

		static bool ScalarOperation_Mul(ZQ_CNN_Tensor4D& input, float scalar, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int align_mode = input.GetAlignType();
			float* in_data = input.GetFirstPixelPtr();
			_scalaroperation_mul(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep);
			return true;
		}

		static bool ScalarOperation_Max(const ZQ_CNN_Tensor4D& input, float scalar, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			_scalaroperation_max(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep,
				out_data, out_pixStep, out_widthStep, out_sliceStep);
			return true;
		}

		static bool ScalarOperation_Max(ZQ_CNN_Tensor4D& input, float scalar, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int align_mode = input.GetAlignType();
			float* in_data = input.GetFirstPixelPtr();
			_scalaroperation_max(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep);
			return true;
		}

		static bool ScalarOperation_Min(const ZQ_CNN_Tensor4D& input, float scalar, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			_scalaroperation_min(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep,
				out_data, out_pixStep, out_widthStep, out_sliceStep);
			return true;
		}

		static bool ScalarOperation_Min(ZQ_CNN_Tensor4D& input, float scalar, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int align_mode = input.GetAlignType();
			float* in_data = input.GetFirstPixelPtr();
			_scalaroperation_min(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep);
			return true;
		}

		static bool ScalarOperation_Pow(const ZQ_CNN_Tensor4D& input, float scalar, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			_scalaroperation_pow(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep,
				out_data, out_pixStep, out_widthStep, out_sliceStep);
			return true;
		}

		static bool ScalarOperation_Pow(ZQ_CNN_Tensor4D& input, float scalar, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int align_mode = input.GetAlignType();
			float* in_data = input.GetFirstPixelPtr();
			_scalaroperation_pow(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep);
			return true;
		}

		static bool ScalarOperation_Rdiv(const ZQ_CNN_Tensor4D& input, float scalar, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			_scalaroperation_rdiv(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep,
				out_data, out_pixStep, out_widthStep, out_sliceStep);
			return true;
		}

		static bool ScalarOperation_Rdiv(ZQ_CNN_Tensor4D& input, float scalar, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int align_mode = input.GetAlignType();
			float* in_data = input.GetFirstPixelPtr();
			_scalaroperation_rdiv(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep);
			return true;
		}

		static bool ScalarOperation_Rminus(const ZQ_CNN_Tensor4D& input, float scalar, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
				output.ChangeSize(N, H, W, C, 0, 0);
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep(), out_widthStep = output.GetWidthStep(), out_sliceStep = output.GetSliceStep();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			_scalaroperation_rminus(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep,
				out_data, out_pixStep, out_widthStep, out_sliceStep);
			return true;
		}

		static bool ScalarOperation_Rminus(ZQ_CNN_Tensor4D& input, float scalar, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			int in_pixStep = input.GetPixelStep(), in_widthStep = input.GetWidthStep(), in_sliceStep = input.GetSliceStep();
			int align_mode = input.GetAlignType();
			float* in_data = input.GetFirstPixelPtr();
			_scalaroperation_rminus(align_mode, scalar, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep);
			return true;
		}

		static bool LRN_across_channels(const ZQ_CNN_Tensor4D& input, int local_size, float alpha, float beta, float k, 
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			if (local_size % 2 != 1)
				return false;
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			if (output.GetN() != N || output.GetH() != H || output.GetW() != W || output.GetC() != C)
			{
				output.ChangeSize(N, H, W, C, 0, 0);
			}

			int in_pixStep = input.GetPixelStep();
			int in_widthStep = input.GetWidthStep();
			int in_sliceStep = input.GetSliceStep();
			int out_pixStep = output.GetPixelStep();
			int out_widthStep = output.GetWidthStep();
			int out_sliceStep = output.GetSliceStep();
			const float* in_data = input.GetFirstPixelPtr();
			float* out_data = output.GetFirstPixelPtr();
			int align_mode = __min(input.GetAlignType(), output.GetAlignType());
			_lrn_across_channels(align_mode, local_size, alpha, beta, k, in_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep, out_data, out_pixStep, out_widthStep, 
				out_sliceStep, num_threads);
			return true;
		}

		static bool Normalize(ZQ_CNN_Tensor4D& input, ZQ_CNN_Tensor4D& scale, bool across_spatial, bool channel_shared, const float eps=1e-10, int num_threads = 1)
		{
			int N = input.GetN();
			int H = input.GetH();
			int W = input.GetW();
			int C = input.GetC();
			if (N <= 0 || H <= 0 || W <= 0 || C <= 0)
				return true;
			
			int in_pixStep = input.GetPixelStep();
			int in_widthStep = input.GetWidthStep();
			int in_sliceStep = input.GetSliceStep();
			float* in_data = input.GetFirstPixelPtr();
			const float* scale_data = scale.GetFirstPixelPtr();
			int align_mode = __min(input.GetAlignType(), scale.GetAlignType());
			_normalize(align_mode, across_spatial, channel_shared, in_data, scale_data, N, H, W, C, in_pixStep, in_widthStep, in_sliceStep,eps, num_threads);
			return true;
		}

		static bool Permute(const ZQ_CNN_Tensor4D& input, const int order[4], ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			return input.Permute_NCHW(output, order, num_threads);
		}

		static bool Flatten(const ZQ_CNN_Tensor4D& input, int axis, int end_axis, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			return input.Flatten_NCHW(output, axis, end_axis, num_threads);
		}

		static bool Reshape(const ZQ_CNN_Tensor4D& input, const std::vector<int>& shape, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			return input.Reshape_NCHW(output, shape, num_threads);
		}

		static bool PriorBox(const ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& data,
			const std::vector<float>& min_sizes, const std::vector<float>& max_sizes,
			const std::vector<float>& aspect_ratios, const std::vector<float>& variance,
			bool flip, int num_priors, bool clip, int img_w, int img_h,	float step_w, float step_h, float offset,
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			return _prior_box(input, data, min_sizes, max_sizes, aspect_ratios, variance, flip, num_priors, clip, img_w, img_h, step_w, step_h, offset, 
				output, num_threads);
		}

		static bool PriorBoxText(const ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& data,
			const std::vector<float>& min_sizes, const std::vector<float>& max_sizes,
			const std::vector<float>& aspect_ratios, const std::vector<float>& variance,
			bool flip, int num_priors, bool clip, int img_w, int img_h, float step_w, float step_h, float offset,
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			return _prior_box_text(input, data, min_sizes, max_sizes, aspect_ratios, variance, flip, num_priors, clip, img_w, img_h, step_w, step_h, offset,
				output, num_threads);
		}

		static bool Concat_NCHW_get_size(const std::vector<ZQ_CNN_Tensor4D*>& inputs, int axis, int& out_N, int& out_C, int& out_H, int& out_W)
		{
			return _concat_NCHW_get_size(inputs, axis, out_N, out_C, out_H, out_W);
		}

		static bool Concat_NCHW(const std::vector<ZQ_CNN_Tensor4D*>& inputs, int axis, ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			return _concat_NCHW(inputs, axis, output, num_threads);
		}

		static bool DetectionOuput(const ZQ_CNN_Tensor4D& loc, const ZQ_CNN_Tensor4D& conf,
			const ZQ_CNN_Tensor4D& prior, int num_priors, int num_loc_classes, int num_classes, bool share_location,
			int background_label_id, ZQ_CNN_BBoxUtils::PriorBoxCodeType code_type, bool variance_encoded_in_target,
			float nms_thresh, float nms_eta, int nms_top_k, float confidence_thresh, int keep_top_k, 
			ZQ_CNN_Tensor4D& output, int num_threads = 1)
		{
			return _detection_output(loc, conf, prior, num_priors, num_loc_classes, num_classes, share_location,
				background_label_id, code_type, variance_encoded_in_target, nms_thresh, nms_eta, nms_top_k, 
				confidence_thresh, keep_top_k, output, num_threads);
		}

	private:
		static void _convolution_nopadding(int align_mode, const float* in_data, int in_N, int in_H, int in_W,
			int in_C, int in_pixStep, int in_widthStep, int in_sliceStep,const float* filter_data, int filter_N, int filter_H, int filter_W, int filter_C, 
			int filter_pixStep, int filter_widthStep, int filter_sliceStep,	int strideH, int strideW, int dilation_H, int dilation_W,
			float* out_data, int out_N, int out_H, int out_W, int out_C, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _convolution_nopadding_omp(int align_mode, const float* in_data, int in_N, int in_H, int in_W,
			int in_C, int in_pixStep, int in_widthStep, int in_sliceStep, const float* filter_data, int filter_N, int filter_H, int filter_W, int filter_C, 
			int filter_pixStep, int filter_widthStep, int filter_sliceStep, int strideH, int strideW, int dilation_H, int dilation_W, 
			float* out_data, int out_N, int out_H, int out_W, int out_C, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _depthwise_convolution_nopadding(int align_mode, const float* in_data, int in_N, int in_H, int in_W,
			int in_C, int in_pixStep, int in_widthStep, int in_sliceStep,
			const float* filter_data, int filter_N, int filter_H, int filter_W, int filter_C, int filter_pixStep, int filter_widthStep, int filter_sliceStep,
			int strideH, int strideW, float* out_data, int out_N, int out_H, int out_W, int out_C, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _depthwise_convolution_nopadding_omp(int align_mode, const float* in_data, int in_N, int in_H, int in_W,
			int in_C, int in_pixStep, int in_widthStep, int in_sliceStep,
			const float* filter_data, int filter_N, int filter_H, int filter_W, int filter_C, int filter_pixStep, int filter_widthStep, int filter_sliceStep,
			int strideH, int strideW, float* out_data, int out_N, int out_H, int out_W, int out_C, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _inner_product(int align_mode, const float* in_data, int in_N, int in_H, int in_W, int in_C, int in_pixStep, int in_widthStep, int in_sliceStep,
			const float* filter_data, int filter_N, int filter_pixStep, int filter_widthStep, int filter_sliceStep,
			float* out_data, int out_N, int out_sliceStep, int num_threads);

		static void _addbias(int align_mode, float* data, int N, int H, int W, int C, int pixelStep, int widthStep, int sliceStep, 
			const float* bias_Data);

		static void _addbias_omp(int align_mode, float* data, int N, int H, int W, int C, int pixelStep, int widthStep, int sliceStep,
			const float* bias_Data, int num_threads);

		static void _softmax(int align_mode, int axis, float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, 
			int num_threads);

		static void _dropout(int align_mode, float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, 
			float ratio, int num_threads);

		static void _prelu(int align_mode, float* data, int N, int H, int W, int C, int pixelStep, int widthStep, int sliceStep, 
			const float* slope_Data);

		static void _prelu_omp(int align_mode, float* data, int N, int H, int W, int C, int pixelStep, int widthStep, int sliceStep,
			const float* slope_Data, int num_threads);

		static void _relu(int align_mode, float* data, int N, int H, int W, int C, int pixelStep, int widthStep, int sliceStep);

		static void _relu_omp(int align_mode, float* data, int N, int H, int W, int C, int pixelStep, int widthStep, int sliceStep,
			int num_threads);

		static void _maxpooling(int align_mode, const float* in_data, int N, int in_H, int in_W, int C, int in_pixStep, int in_widthStep, int in_sliceStep,
			int kernel_H, int kernel_W, int stride_H, int stride_W,	float* out_data, int out_H, int out_W, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _maxpooling_omp(int align_mode, const float* in_data, int N, int in_H, int in_W, int C, int in_pixStep, int in_widthStep, int in_sliceStep,
			int kernel_H, int kernel_W, int stride_H, int stride_W, float* out_data, int out_H, int out_W, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _avgpooling(int align_mode, const float* in_data, int N, int in_H, int in_W, int C, int in_pixStep, int in_widthStep, int in_sliceStep,
			int kernel_H, int kernel_W, int stride_H, int stride_W, float* out_data, int out_H, int out_W, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _avgpooling_omp(int align_mode, const float* in_data, int N, int in_H, int in_W, int C, int in_pixStep, int in_widthStep, int in_sliceStep,
			int kernel_H, int kernel_W, int stride_H, int stride_W, float* out_data, int out_H, int out_W, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _batchnorm(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, const float* mean, const float* var);

		static void _batchnorm_omp(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, const float* mean, const float* var,
			int num_threads);

		static void _batchnorm_scalebias(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			const float* mean, const float* var, const float* slope, const float* bias);

		static void _batchnorm_scalebias_omp(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			const float* mean, const float* var, const float* slope, const float* bias, int num_threads);

		/*
		a = bias - slope * mean / sqrt(var)
		b = slope / sqrt(var)
		value = b * value + a
		***OR***
		a = -mean/sqrt(var)
		b = 1/sqrt(var)
		value = b * value + a
		*/
		static void _batchnorm_b_a(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, const float* b, const float* a);

		/*
		a = bias - slope * mean / sqrt(var)
		b = slope / sqrt(var)
		value = b * value + a
		***OR***
		a = -mean/sqrt(var)
		b = 1/sqrt(var)
		value = b * value + a
		*/
		static void _batchnorm_b_a_omp(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, const float* b, const float* a,
			int num_threads);

		static void _scalebias(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, const float* scale, const float* bias);

		static void _scalebias_omp(int align_mode, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep, const float* scale, const float* bias,
			int num_threads);

		static void _eltwise_sum(int align_mode, int in_tensor_num, const float** in_data, int N, int H, int W, int C, const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _eltwise_sum_omp(int align_mode, int in_tensor_num, const float** in_data, int N, int H, int W, int C, const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _eltwise_sum_with_weight(int align_mode, int in_tensor_num, const float** in_data, const float* weight, int N, int H, int W, int C,
			const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _eltwise_sum_with_weight_omp(int align_mode, int in_tensor_num, const float** in_data, const float* weight, int N, int H, int W, int C,
			const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _eltwise_mul(int align_mode, int in_tensor_num, const float** in_data, int N, int H, int W, int C, const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _eltwise_mul_omp(int align_mode, int in_tensor_num, const float** in_data, int N, int H, int W, int C, const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _eltwise_max(int align_mode, int in_tensor_num, const float** in_data, int N, int H, int W, int C, const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _eltwise_max_omp(int align_mode, int in_tensor_num, const float** in_data, int N, int H, int W, int C, const int* pixStep, const int* widthStep, const int* sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _scalaroperation_add(int align_mode, float scalar, const float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _scalaroperation_add(int align_mode, float scalar, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep);

		static void _scalaroperation_mul(int align_mode, float scalar, const float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _scalaroperation_mul(int align_mode, float scalar, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep);

		static void _scalaroperation_max(int align_mode, float scalar, const float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _scalaroperation_max(int align_mode, float scalar, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep);

		static void _scalaroperation_min(int align_mode, float scalar, const float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _scalaroperation_min(int align_mode, float scalar, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep);

		static void _scalaroperation_pow(int align_mode, float scalar, const float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _scalaroperation_pow(int align_mode, float scalar, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep);

		static void _scalaroperation_rdiv(int align_mode, float scalar, const float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _scalaroperation_rdiv(int align_mode, float scalar, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep);

		static void _scalaroperation_rminus(int align_mode, float scalar, const float* in_data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep,
			float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep);

		static void _scalaroperation_rminus(int align_mode, float scalar, float* data, int N, int H, int W, int C, int pixStep, int widthStep, int sliceStep);

		static void _lrn_across_channels(int align_mode, int local_size, float alpha, float beta, float k, const float* in_data, int N, int H, int W, int C,
			int in_pixStep, int in_widthStep, int in_sliceStep, float* out_data, int out_pixStep, int out_widthStep, int out_sliceStep, int num_threads);

		static void _normalize(int align_mode, bool across_spatial, bool channel_shared, float* in_data, const float* scale, int N, int H, int W, int C, 
			int in_pixStep, int in_widthStep, int in_sliceStep, const float eps, int num_threads);

		static bool _prior_box(const ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& data,
			const std::vector<float>& min_sizes, const std::vector<float>& max_sizes,
			const std::vector<float>& aspect_ratios, const std::vector<float>& variance,
			bool flip, int num_priors, bool clip, int img_w, int img_h, float step_w, float step_h, float offset,
			ZQ_CNN_Tensor4D& output, int num_threads);

		static bool _prior_box_text(const ZQ_CNN_Tensor4D& input, const ZQ_CNN_Tensor4D& data,
			const std::vector<float>& min_sizes, const std::vector<float>& max_sizes,
			const std::vector<float>& aspect_ratios, const std::vector<float>& variance,
			bool flip, int num_priors, bool clip, int img_w, int img_h, float step_w, float step_h, float offset,
			ZQ_CNN_Tensor4D& output, int num_threads);

		static bool _concat_NCHW_get_size(const std::vector<ZQ_CNN_Tensor4D*>& inputs, int axis, int& out_N, int& out_C, int& out_H, int& out_W);

		static bool _concat_NCHW(const std::vector<ZQ_CNN_Tensor4D*>& inputs, int axis, ZQ_CNN_Tensor4D& output, int num_threads);

		static bool _detection_output(const ZQ_CNN_Tensor4D& loc, const ZQ_CNN_Tensor4D& conf,
			const ZQ_CNN_Tensor4D& prior, int num_priors, int num_loc_classes, int num_classes, bool share_location,
			int background_label_id, ZQ_CNN_BBoxUtils::PriorBoxCodeType code_type, bool variance_encoded_in_target,
			float nms_thresh, float nms_eta, int nms_top_k, float confidence_thresh, int keep_top_k, ZQ_CNN_Tensor4D& output, int num_threads);
	};

}

#endif
