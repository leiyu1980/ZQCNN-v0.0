#include <mmintrin.h> //MMX  
#include <xmmintrin.h> //SSE(include mmintrin.h)  
#include <emmintrin.h> //SSE2(include xmmintrin.h)  
#include <pmmintrin.h> //SSE3(include emmintrin.h)  
#include <tmmintrin.h>//SSSE3(include pmmintrin.h)  
#include <smmintrin.h>//SSE4.1(include tmmintrin.h)  
#include <nmmintrin.h>//SSE4.2(include smmintrin.h)  
#include <wmmintrin.h>//AES(include nmmintrin.h)  
#include <immintrin.h>//AVX(include wmmintrin.h)  
#include <intrin.h>//(include immintrin.h)  
#include <stdio.h>
#include <stdlib.h>

#if defined(__cplusplus) || defined(c_plusplus) 
extern "C" {
#endif

#define zq_cnn_relu_32f_align zq_cnn_relu_32f_align128bit
#define zq_cnn_relu_32f_align_omp zq_cnn_relu_32f_align128bit_omp
#define zq_mm_load_ps _mm_load_ps
#define zq_mm_store_ps _mm_store_ps
#define zq_mm_setzero_ps _mm_setzero_ps
#define zq_mm_max_ps _mm_max_ps
#define zq_mm_type __m128
#define zq_mm_align_size 4
#define zq_mm_align_size_mul_2 8
#define zq_mm_align_size_mul_3 12
#define zq_mm_align_size_mul_4 16
#define zq_mm_align_size_mul_5 20
#define zq_mm_align_size_mul_6 24
#define zq_mm_align_size_mul_7 28
#define zq_mm_align_size_mul_8 32
#define zq_mm_align_size_mul_16 64
#define zq_mm_align_size_mul_32 128

#include "zq_cnn_relu_32f_align_c_raw.h"

#undef zq_cnn_relu_32f_align
#undef zq_cnn_relu_32f_align_omp
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_setzero_ps
#undef zq_mm_max_ps
#undef zq_mm_type
#undef zq_mm_align_size
#undef zq_mm_align_size_mul_2
#undef zq_mm_align_size_mul_3
#undef zq_mm_align_size_mul_4
#undef zq_mm_align_size_mul_5
#undef zq_mm_align_size_mul_6
#undef zq_mm_align_size_mul_7
#undef zq_mm_align_size_mul_8
#undef zq_mm_align_size_mul_16
#undef zq_mm_align_size_mul_32

#define zq_cnn_relu_32f_align zq_cnn_relu_32f_align256bit
#define zq_cnn_relu_32f_align_omp zq_cnn_relu_32f_align256bit_omp
#define zq_mm_load_ps _mm256_load_ps
#define zq_mm_store_ps _mm256_store_ps
#define zq_mm_setzero_ps _mm256_setzero_ps
#define zq_mm_max_ps _mm256_max_ps
#define zq_mm_type __m256
#define zq_mm_align_size 8
#define zq_mm_align_size_mul_2 16
#define zq_mm_align_size_mul_3 24
#define zq_mm_align_size_mul_4 32
#define zq_mm_align_size_mul_5 40
#define zq_mm_align_size_mul_6 48
#define zq_mm_align_size_mul_7 56
#define zq_mm_align_size_mul_8 64
#define zq_mm_align_size_mul_16 128
#define zq_mm_align_size_mul_32 256

#include "zq_cnn_relu_32f_align_c_raw.h"

#undef zq_cnn_relu_32f_align
#undef zq_cnn_relu_32f_align_omp
#undef zq_mm_load_ps
#undef zq_mm_store_ps
#undef zq_mm_setzero_ps
#undef zq_mm_max_ps
#undef zq_mm_type
#undef zq_mm_align_size
#undef zq_mm_align_size_mul_2
#undef zq_mm_align_size_mul_3
#undef zq_mm_align_size_mul_4
#undef zq_mm_align_size_mul_5
#undef zq_mm_align_size_mul_6
#undef zq_mm_align_size_mul_7
#undef zq_mm_align_size_mul_8
#undef zq_mm_align_size_mul_16
#undef zq_mm_align_size_mul_32


	void zq_cnn_relu_32f_align0(
		float* in_tensor4D_data,	// in & out
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep
	)
	{
		float data_v;
		int n, h, w, c;
		float* slice_ptr, *row_ptr, *pix_ptr, *c_ptr;

		for (n = 0, slice_ptr = in_tensor4D_data; n < in_N; n++, slice_ptr += in_sliceStep)
		{
			for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
			{
				for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
				{
					for (c = 0, c_ptr = pix_ptr; c < in_C; c++, c_ptr++)
					{
						data_v = *c_ptr;
						
						*c_ptr = __max(0,data_v);
					}
				}
			}
		}

	}

	void zq_cnn_relu_32f_align0_omp(
		float* in_tensor4D_data,	// in & out
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep,
		int thread_count
	)
	{
		int c;
		int chunk_size = (in_C + thread_count - 1) / thread_count;
		for (c = 0; c < in_C; c++)
		{
			int n, h, w;
			float data_v;
			float* slice_ptr, *row_ptr, *pix_ptr;

			for (n = 0, slice_ptr = in_tensor4D_data + c; n < in_N; n++, slice_ptr += in_sliceStep)
			{
				for (h = 0, row_ptr = slice_ptr; h < in_H; h++, row_ptr += in_widthStep)
				{
					for (w = 0, pix_ptr = row_ptr; w < in_W; w++, pix_ptr += in_pixelStep)
					{
						data_v = *pix_ptr;
						*pix_ptr = __max(0, data_v);
					}
				}
			}
		}
	}


#if defined(__cplusplus) || defined(c_plusplus) 
}
#endif