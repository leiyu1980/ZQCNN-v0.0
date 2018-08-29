#ifndef _ZQ_CNN_BATCH_NORM_SCALE_32F_ALIGN_C_H_
#define _ZQ_CNN_BATCH_NORM_SCALE_32F_ALIGN_C_H_

#if defined(__cplusplus) || defined(c_plusplus) 
extern "C" {
#endif

	/*
	 a = bias - scale * mean / sqrt(var)
	 b = scale / sqrt(var)
	 value = b * value + a
	*/
	void zq_cnn_batchnormscale_32f_mean_var_scale_bias_align0(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		const float* scale_data,
		const float* bias_data
	);

	/*
	a = bias - scale * mean / sqrt(var)
	b = scale / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnormscale_32f_mean_var_scale_bias_align0_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		const float* scale_data,
		const float* bias_data,
		int thread_count
	);

	/*
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_mean_var_align0(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data
	);

	/*
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_mean_var_align0_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		int thread_count
	);

	/*
	value = scale*value+bias
	*/
	void zq_cnn_scale_32f_align0(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* scale_data,
		const float* bias_data	// bias can be NULL
	);

	/*
	value = scale*value+bias
	*/
	void zq_cnn_scale_32f_align0_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* scale_data,
		const float* bias_data,	// bias can be NULL
		int thread_count
	);

	/*
	a = bias - slope * mean / sqrt(var)
	b = slope / sqrt(var)
	value = b * value + a
	OR
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_b_a_align0(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* b_data,
		const float* a_data
	);

	/*
	a = bias - slope * mean / sqrt(var)
	b = slope / sqrt(var)
	value = b * value + a
	OR
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_b_a_align0_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* b_data,
		const float* a_data,
		int thread_count
	);


	/*
	a = bias - scale * mean / sqrt(var)
	b = scale / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnormscale_32f_mean_var_scale_bias_align128bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		const float* scale_data,
		const float* bias_data
	);

	/*
	a = bias - scale * mean / sqrt(var)
	b = scale / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnormscale_32f_mean_var_scale_bias_align128bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		const float* scale_data,
		const float* bias_data,
		int thread_count
	);

	/*
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_mean_var_align128bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data
	);

	/*
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_mean_var_align128bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		int thread_count
	);

	/*
	value = scale*value+bias
	*/
	void zq_cnn_scale_32f_align128bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* scale_data,
		const float* bias_data	// bias can be NULL
	);

	/*
	value = scale*value+bias
	*/
	void zq_cnn_scale_32f_align128bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* scale_data,
		const float* bias_data,	// bias can be NULL
		int thread_count
	);

	/*
	a = bias - slope * mean / sqrt(var)
	b = slope / sqrt(var)
	value = b * value + a
	OR
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_b_a_align128bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* b_data,
		const float* a_data
	);

	/*
	a = bias - slope * mean / sqrt(var)
	b = slope / sqrt(var)
	value = b * value + a
	OR
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_b_a_align128bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* b_data,
		const float* a_data,
		int thread_count
	);


	/*
	a = bias - scale * mean / sqrt(var)
	b = scale / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnormscale_32f_mean_var_scale_bias_align256bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		const float* scale_data,
		const float* bias_data
	);

	/*
	a = bias - scale * mean / sqrt(var)
	b = scale / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnormscale_32f_mean_var_scale_bias_align256bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		const float* scale_data,
		const float* bias_data,
		int thread_count
	);

	/*
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_mean_var_align256bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data
	);

	/*
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_mean_var_align256bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* mean_data,
		const float* var_data,
		int thread_count
	);

	/*
	value = scale*value+bias
	*/
	void zq_cnn_scale_32f_align256bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* scale_data,
		const float* bias_data	// bias can be NULL
	);

	/*
	value = scale*value+bias
	*/
	void zq_cnn_scale_32f_align256bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* scale_data,
		const float* bias_data,	// bias can be NULL
		int thread_count
	);

	/*
	a = bias - slope * mean / sqrt(var)
	b = slope / sqrt(var)
	value = b * value + a
	OR
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_b_a_align256bit(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* b_data,
		const float* a_data
	);

	/*
	a = bias - slope * mean / sqrt(var)
	b = slope / sqrt(var)
	value = b * value + a
	OR
	a = - mean / sqrt(var)
	b = 1 / sqrt(var)
	value = b * value + a
	*/
	void zq_cnn_batchnorm_32f_b_a_align256bit_omp(
		float* in_data,
		int in_N,
		int in_H,
		int in_W,
		int in_C,
		int in_pixStep,
		int in_widthStep,
		int in_sliceStep,
		const float* b_data,
		const float* a_data,
		int thread_count
	);
	

#if defined(__cplusplus) || defined(c_plusplus) 
}
#endif


#endif
