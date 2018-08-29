void zq_cnn_eltwise_sum_32f_align(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	int n, h, w, c, tensor_id;
	const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
	const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
	float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;
	if (C%zq_mm_align_size_mul_32 == 0)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C; c += zq_mm_align_size_mul_32)
					{
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr; c < C; c += zq_mm_align_size_mul_32)
						{
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						}
					}
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_16 == 0)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C; c += zq_mm_align_size_mul_16)
					{
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr; c < C; c += zq_mm_align_size_mul_16)
						{
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						}
					}
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_8 == 0)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C; c += zq_mm_align_size_mul_8)
					{
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;	c < C;	c += zq_mm_align_size_mul_8)
						{
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						}
					}
				}
			}
		}
	}
	else
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
					{
						zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;
							c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
						{
							zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
						}
					}
				}
			}
		}
	}
	
}

void zq_cnn_eltwise_sum_32f_align_omp(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep,
	int thread_count
)
{
	int n, h, w, tensor_id;
	int NHW = N*H*W;
	int chunk_size = (NHW + thread_count - 1) / thread_count;
	int* out_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in1_offsets = (int*)malloc(sizeof(int)*NHW);
	int idx = 0;
	for (n = 0; n < N; n++)
	{
		for (h = 0; h < H; h++)
		{
			for (w = 0; w < W; w++)
			{
				out_offsets[idx] = n*out_sliceStep + h*out_widthStep + w*out_pixelStep;
				in_offsets[idx] = n*in_sliceStep[0] + h*in_widthStep[0] + w*in_pixelStep[0];
				in1_offsets[idx] = n*in_sliceStep[1] + h*in_widthStep[1] + w*in_pixelStep[1];
				idx++;
			}
		}
	}

	if (C%zq_mm_align_size_mul_32 == 0)
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C; c += zq_mm_align_size_mul_32)
			{
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr; c < C; c += zq_mm_align_size_mul_32)
				{
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_16 == 0)
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C; c += zq_mm_align_size_mul_16)
			{
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr; c < C; c += zq_mm_align_size_mul_16)
				{
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_8 == 0)
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C; c += zq_mm_align_size_mul_8)
			{
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr; c < C; c += zq_mm_align_size_mul_8)
				{
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				}
			}
		}
	}
	else
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C;
				c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
			{
				zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
					c < C;
					c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
				{
					zq_mm_store_ps(out_c_ptr, zq_mm_add_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
				}
			}
		}
	}
	free(in_offsets);
	free(in1_offsets);
	free(out_offsets);
}

void zq_cnn_eltwise_sum_with_weight_32f_align(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	const float* weight,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	int n, h, w, c, tensor_id;
	const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
	const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
	float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;

	if (C%zq_mm_align_size_mul_32 == 0)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;	c += zq_mm_align_size_mul_32)
					{
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;	c += zq_mm_align_size_mul_32)
						{
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						}
					}
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_16 == 0)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;	c += zq_mm_align_size_mul_16)
					{
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;	c += zq_mm_align_size_mul_16)
						{
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						}
					}
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_8 == 0)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;	c += zq_mm_align_size_mul_8)
					{
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
						in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;	c += zq_mm_align_size_mul_8)
						{
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
							in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
						}
					}
				}
			}
		}
	}
	else
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
					{
						zq_mm_store_ps(out_c_ptr,
							zq_mm_add_ps(
								zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
								zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
							)
						);
					}
				}
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
				n < N;
				n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
			{
				for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
					h < H;
					h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
				{
					for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
						w < W;
						w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
					{
						for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
							c < C;
							c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
						{
							zq_mm_store_ps(out_c_ptr,
								zq_mm_add_ps(
									zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
									zq_mm_load_ps(out_c_ptr)
								)
							);
						}
					}
				}
			}
		}
	}
	
}

void zq_cnn_eltwise_sum_with_weight_32f_align_omp(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	const float* weight,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep,
	int thread_count
)
{
	int n, h, w, tensor_id;
	int NHW = N*H*W;
	int chunk_size = (NHW + thread_count - 1) / thread_count;
	int* out_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in1_offsets = (int*)malloc(sizeof(int)*NHW);
	int idx = 0;
	for (n = 0; n < N; n++)
	{
		for (h = 0; h < H; h++)
		{
			for (w = 0; w < W; w++)
			{
				out_offsets[idx] = n*out_sliceStep + h*out_widthStep + w*out_pixelStep;
				in_offsets[idx] = n*in_sliceStep[0] + h*in_widthStep[0] + w*in_pixelStep[0];
				in1_offsets[idx] = n*in_sliceStep[1] + h*in_widthStep[1] + w*in_pixelStep[1];
				idx++;
			}
		}
	}

	if (C%zq_mm_align_size_mul_32 == 0)
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C;	c += zq_mm_align_size_mul_32)
			{
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
					c < C;	c += zq_mm_align_size_mul_32)
				{
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_16 == 0)
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C;	c += zq_mm_align_size_mul_16)
			{
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
					c < C;	c += zq_mm_align_size_mul_16)
				{
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				}
			}
		}
	}
	else if (C%zq_mm_align_size_mul_8 == 0)
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C;	c += zq_mm_align_size_mul_8)
			{
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
				in_c_ptr += zq_mm_align_size; in1_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
					c < C;	c += zq_mm_align_size_mul_8)
				{
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
					in_c_ptr += zq_mm_align_size; out_c_ptr += zq_mm_align_size;
				}
			}
		}
	}
	else
	{
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
			const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr, *in1_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C;
				c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
			{
				zq_mm_store_ps(out_c_ptr,
					zq_mm_add_ps(
						zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[0])),
						zq_mm_mul_ps(zq_mm_load_ps(in1_c_ptr), zq_mm_set1_ps(weight[1]))
					)
				);
			}
		}
		for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
		{
			idx = 0;
			for (n = 0; n < N; n++)
			{
				for (h = 0; h < H; h++)
				{
					for (w = 0; w < W; w++)
					{
						in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
						idx++;
					}
				}
			}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
			for (idx = 0; idx < NHW; idx++)
			{
				const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
				float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
				const float* in_c_ptr;
				float* out_c_ptr;
				int c;
				for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
					c < C;
					c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
				{
					zq_mm_store_ps(out_c_ptr,
						zq_mm_add_ps(
							zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_set1_ps(weight[tensor_id])),
							zq_mm_load_ps(out_c_ptr)
						)
					);
				}
			}
		}
	}
	free(in_offsets);
	free(in1_offsets);
	free(out_offsets);
}

void zq_cnn_eltwise_mul_32f_align(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	int n, h, w, c, tensor_id;
	const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
	const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
	float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;
	for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
		n < N;
		n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
	{
		for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
			h < H;
			h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
		{
			for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
				w < W;
				w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
			{
				for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
					c < C;
					c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
				{
					zq_mm_store_ps(out_c_ptr, zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				}
			}
		}
	}
	for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
					{
						zq_mm_store_ps(out_c_ptr, zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					}
				}
			}
		}
	}
}

void zq_cnn_eltwise_mul_32f_align_omp(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep,
	int thread_count
)
{
	int n, h, w, tensor_id;
	int NHW = N*H*W;
	int chunk_size = (NHW + thread_count - 1) / thread_count;
	int* out_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in1_offsets = (int*)malloc(sizeof(int)*NHW);
	int idx = 0;
	for (n = 0; n < N; n++)
	{
		for (h = 0; h < H; h++)
		{
			for (w = 0; w < W; w++)
			{
				out_offsets[idx] = n*out_sliceStep + h*out_widthStep + w*out_pixelStep;
				in_offsets[idx] = n*in_sliceStep[0] + h*in_widthStep[0] + w*in_pixelStep[0];
				in1_offsets[idx] = n*in_sliceStep[1] + h*in_widthStep[1] + w*in_pixelStep[1];
				idx++;
			}
		}
	}

#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
	for (idx = 0; idx < NHW; idx++)
	{
		const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
		const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
		float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
		const float* in_c_ptr, *in1_c_ptr;
		float* out_c_ptr;
		int c;
		for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
			c < C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			zq_mm_store_ps(out_c_ptr, zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
		}
	}
	for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
	{
		idx = 0;
		for (n = 0; n < N; n++)
		{
			for (h = 0; h < H; h++)
			{
				for (w = 0; w < W; w++)
				{
					in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
					idx++;
				}
			}
		}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C;
				c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
			{
				zq_mm_store_ps(out_c_ptr, zq_mm_mul_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
			}
		}
	}
	free(in_offsets);
	free(in1_offsets);
	free(out_offsets);
}

void zq_cnn_eltwise_max_32f_align(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep
)
{
	int n, h, w, c, tensor_id;
	const float* in_slice_ptr, *in_row_ptr, *in_pix_ptr, *in_c_ptr;
	const float* in1_slice_ptr, *in1_row_ptr, *in1_pix_ptr, *in1_c_ptr;
	float* out_slice_ptr, *out_row_ptr, *out_pix_ptr, *out_c_ptr;
	for (n = 0, in_slice_ptr = in_tensor4D_data[0], in1_slice_ptr = in_tensor4D_data[1], out_slice_ptr = out_tensor4D_data;
		n < N;
		n++, in_slice_ptr += in_sliceStep[0], in1_slice_ptr += in_sliceStep[1], out_slice_ptr += out_sliceStep)
	{
		for (h = 0, in_row_ptr = in_slice_ptr, in1_row_ptr = in1_slice_ptr, out_row_ptr = out_slice_ptr;
			h < H;
			h++, in_row_ptr += in_widthStep[0], in1_row_ptr += in_widthStep[1], out_row_ptr += out_widthStep)
		{
			for (w = 0, in_pix_ptr = in_row_ptr, in1_pix_ptr = in1_row_ptr, out_pix_ptr = out_row_ptr;
				w < W;
				w++, in_pix_ptr += in_pixelStep[0], in1_pix_ptr += in_pixelStep[1], out_pix_ptr += out_pixelStep)
			{
				for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
					c < C;
					c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
				{
					zq_mm_store_ps(out_c_ptr, zq_mm_max_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
				}
			}
		}
	}
	for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
	{
		for (n = 0, in_slice_ptr = in_tensor4D_data[tensor_id], out_slice_ptr = out_tensor4D_data;
			n < N;
			n++, in_slice_ptr += in_sliceStep[tensor_id], out_slice_ptr += out_sliceStep)
		{
			for (h = 0, in_row_ptr = in_slice_ptr, out_row_ptr = out_slice_ptr;
				h < H;
				h++, in_row_ptr += in_widthStep[tensor_id], out_row_ptr += out_widthStep)
			{
				for (w = 0, in_pix_ptr = in_row_ptr, out_pix_ptr = out_row_ptr;
					w < W;
					w++, in_pix_ptr += in_pixelStep[tensor_id], out_pix_ptr += out_pixelStep)
				{
					for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
						c < C;
						c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
					{
						zq_mm_store_ps(out_c_ptr, zq_mm_max_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
					}
				}
			}
		}
	}
}

void zq_cnn_eltwise_max_32f_align_omp(
	int in_tensor_num,	//must be >=2
	const float** in_tensor4D_data,
	int N,
	int H,
	int W,
	int C,
	const int* in_pixelStep,
	const int* in_widthStep,
	const int* in_sliceStep,
	float* out_tensor4D_data,
	int out_pixelStep,
	int out_widthStep,
	int out_sliceStep,
	int thread_count
)
{
	int n, h, w, tensor_id;
	int NHW = N*H*W;
	int chunk_size = (NHW + thread_count - 1) / thread_count;
	int* out_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in_offsets = (int*)malloc(sizeof(int)*NHW);
	int* in1_offsets = (int*)malloc(sizeof(int)*NHW);
	int idx = 0;
	for (n = 0; n < N; n++)
	{
		for (h = 0; h < H; h++)
		{
			for (w = 0; w < W; w++)
			{
				out_offsets[idx] = n*out_sliceStep + h*out_widthStep + w*out_pixelStep;
				in_offsets[idx] = n*in_sliceStep[0] + h*in_widthStep[0] + w*in_pixelStep[0];
				in1_offsets[idx] = n*in_sliceStep[1] + h*in_widthStep[1] + w*in_pixelStep[1];
				idx++;
			}
		}
	}

#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
	for (idx = 0; idx < NHW; idx++)
	{
		const float* in_pix_ptr = in_tensor4D_data[0] + in_offsets[idx];
		const float* in1_pix_ptr = in_tensor4D_data[1] + in1_offsets[idx];
		float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
		const float* in_c_ptr, *in1_c_ptr;
		float* out_c_ptr;
		int c;
		for (c = 0, in_c_ptr = in_pix_ptr, in1_c_ptr = in1_pix_ptr, out_c_ptr = out_pix_ptr;
			c < C;
			c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, in1_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
		{
			zq_mm_store_ps(out_c_ptr, zq_mm_max_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(in1_c_ptr)));
		}
	}
	for (tensor_id = 2; tensor_id < in_tensor_num; tensor_id++)
	{
		idx = 0;
		for (n = 0; n < N; n++)
		{
			for (h = 0; h < H; h++)
			{
				for (w = 0; w < W; w++)
				{
					in_offsets[idx] = n*in_sliceStep[tensor_id] + h*in_widthStep[tensor_id] + w*in_pixelStep[tensor_id];
					idx++;
				}
			}
		}
#pragma omp parallel for schedule(static, chunk_size) num_threads(thread_count)
		for (idx = 0; idx < NHW; idx++)
		{
			const float* in_pix_ptr = in_tensor4D_data[tensor_id] + in_offsets[idx];
			float* out_pix_ptr = out_tensor4D_data + out_offsets[idx];
			const float* in_c_ptr;
			float* out_c_ptr;
			int c;
			for (c = 0, in_c_ptr = in_pix_ptr, out_c_ptr = out_pix_ptr;
				c < C;
				c += zq_mm_align_size, in_c_ptr += zq_mm_align_size, out_c_ptr += zq_mm_align_size)
			{
				zq_mm_store_ps(out_c_ptr, zq_mm_max_ps(zq_mm_load_ps(in_c_ptr), zq_mm_load_ps(out_c_ptr)));
			}
		}
	}
	free(in_offsets);
	free(in1_offsets);
	free(out_offsets);
}