#ifndef _ZQ_CNN_RELU_32F_ALIGN_C_H_
#define _ZQ_CNN_RELU_32F_ALIGN_C_H_

#if defined(__cplusplus) || defined(c_plusplus) 
extern "C" {
#endif



	void zq_cnn_relu_32f_align0(
		float* in_tensor4D_data,	// in & out
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep
	);

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
	);

	/*
	y = max(0,x)
	*/
	void zq_cnn_relu_32f_align128bit(
		float* in_tensor4D_data,	// in & out
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep
	);

	/*
	y = max(0,x)
	*/
	void zq_cnn_relu_32f_align128bit_omp(
		float* in_tensor4D_data,	// in & out
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep,
		int thread_count
	);

	/*
	y = max(0,x)
	*/
	void zq_cnn_relu_32f_align256bit(
		float* in_tensor4D_data,	// in & out
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep
	);

	/*
	y = max(0,x)
	*/
	void zq_cnn_relu_32f_align256bit_omp(
		float* in_tensor4D_data,	// in & out
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixelStep,
		int in_widthStep,
		int in_sliceStep,
		int thread_count
	);


#if defined(__cplusplus) || defined(c_plusplus) //��ƽ̨���巽��
}
#endif
#endif