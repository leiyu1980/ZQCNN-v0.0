#ifndef _ZQ_FACE_DATABASE_COMPACT_H_
#define _ZQ_FACE_DATABASE_COMPACT_H_
#pragma once

#include <malloc.h>
#include <stdio.h>
#include <vector>
#include <omp.h>
#include "ZQ_FaceRecognizerSphereFace.h"
#include "ZQ_MathBase.h"

namespace ZQ
{
	class ZQ_FaceDatabaseCompact
	{
		enum CONST_VAL {
			FEAT_ALIGNED_SIZE = 32
		};
	public:
		ZQ_FaceDatabaseCompact() 
		{
			dim = 0;
			person_num = 0;
			person_face_num = 0;
			total_face_num = 0;
			person_face_offset = 0;
			all_face_feats = 0;
		}
		~ZQ_FaceDatabaseCompact() {}

		bool LoadFromFile(const char* feats_file, const char* names_file)
		{
			_clear();
			if (!_load_feats(feats_file))
			{
				_clear();
				return false;
			}
			if (!_load_names(names_file))
			{
				_clear();
				return false;
			}
			if (person_num != names.size())
			{
				_clear();
				return false;
			}
			return true;
		}

		bool Search(int feat_dim, int feat_num, const float* feat, std::vector<int>& out_ids,
			std::vector<float>& out_scores, std::vector<std::string>& out_names, int max_num, int max_thread_num) const
		{
			return _find_the_best_matches(feat_dim, feat_num, feat, out_ids, out_scores, out_names, max_num, max_thread_num);
		}

	private:
		int dim;
		int person_num;
		int* person_face_num;
		__int64 total_face_num;
		__int64* person_face_offset;
		float* all_face_feats;
		std::vector<std::string> names;

	private:
		void _clear()
		{
			dim = 0;
			person_num = 0;
			total_face_num = 0;
			if (person_face_num)
			{
				free(person_face_num);
				person_face_num = 0;
			}
			if (person_face_offset)
			{
				free(person_face_offset);
				person_face_offset = 0;
			}
			if (all_face_feats)
			{
				_aligned_free(all_face_feats);
				all_face_feats = 0;
			}
			names.clear();
		}

		bool _load_feats(const char* file)
		{
			FILE* in = 0;
			if (0 != fopen_s(&in, file, "rb"))
			{
				return false;
			}

			if (1 != fread(&dim, sizeof(int), 1, in) || dim <= 0)
			{
				fclose(in);
				return false;
			}

			if (1 != fread(&person_num, sizeof(int), 1, in) || person_num <= 0)
			{
				fclose(in);
				return false;
			}

			person_face_num = (int*)malloc(sizeof(int)*person_num);
			person_face_offset = (__int64*)malloc(sizeof(__int64)*person_num);
			if (person_face_num == 0 || person_face_offset == 0)
			{
				fclose(in);
				return false;
			}
			if (person_num != fread(person_face_num, sizeof(int), person_num, in))
			{
				fclose(in);
				return false;
			}
			total_face_num = 0;
			for (int i = 0; i < person_num; i++)
			{
				if (person_face_num[i] <= 0)
				{
					fclose(in);
					return false;
				}
				person_face_offset[i] = total_face_num;
				total_face_num += person_face_num[i];
			}

			all_face_feats = (float*)_aligned_malloc(sizeof(float)*total_face_num*dim, FEAT_ALIGNED_SIZE);
			if (all_face_feats == 0)
			{
				fclose(in);
				return false;
			}

			if (total_face_num*dim != fread(all_face_feats, sizeof(float), total_face_num*dim, in))
			{
				fclose(in);
				return false;
			}
			fclose(in);
			return true;
		}

		bool _load_names(const char* file)
		{
			FILE* in = 0;
			if (0 != fopen_s(&in, file, "r"))
				return false;
			char line[200] = { 0 };
			while (true)
			{
				line[0] = '\0';
				fgets(line, 199, in);
				if (line[0] == '\0')
					break;
				int len = strlen(line);
				if (line[len - 1] == '\n')
					line[--len] = '\0';
				names.push_back(std::string(line));
			}

			fclose(in);
			return true;
		}

		bool _find_the_best_matches(int feat_dim, int feat_num, const float* feat, std::vector<int>& out_ids,
			std::vector<float>& out_scores, std::vector<std::string>& out_names, int max_num, int max_thread_num) const 
		{
			if (person_num <= 0 || feat_dim != dim || feat_num <= 0)
				return false;

			int widthStep = (sizeof(float)*dim + FEAT_ALIGNED_SIZE) / FEAT_ALIGNED_SIZE * FEAT_ALIGNED_SIZE;

			float* feat_aligned = (float*)_aligned_malloc(widthStep*feat_num, FEAT_ALIGNED_SIZE);
			if (feat_aligned == 0)
				return false;
			for(int i = 0;i < feat_num;i++)
				memcpy(((char*)feat_aligned)+widthStep*i, feat+feat_dim*i, sizeof(float)*dim);
			float* scores = (float*)malloc(sizeof(float)*total_face_num);
			if (scores == 0)
			{
				_aligned_free(feat_aligned);
				return false;
			}
			for (int i = 0; i < total_face_num; i++)
				scores[i] = -FLT_MAX;

			int num_procs = omp_get_num_procs();
			int real_threads = __max(1, __min(max_thread_num, num_procs - 1));

			if (real_threads == 1)
			{
				for (int j = 0; j < feat_num; j++)
				{
					float* tmp_feat = (float*)(((char*)feat_aligned) + widthStep*j);
					int chunk_size = (total_face_num + real_threads - 1) / real_threads;
					if (dim == 256)
					{
						for (int i = 0; i < total_face_num; i++)
						{
							scores[i] = ZQ_FaceRecognizerSphereFace::_cal_similarity_avx_dim256(tmp_feat, all_face_feats + i*dim);
						}
					}
					else if (dim == 512)
					{
						for (int i = 0; i < total_face_num; i++)
						{
							scores[i] = ZQ_FaceRecognizerSphereFace::_cal_similarity_avx_dim512(tmp_feat, all_face_feats + i*dim);
						}
					}
					else
					{
						for (long long i = 0; i < total_face_num; i++)
						{
							scores[i] = ZQ_MathBase::DotProduct(dim, tmp_feat, all_face_feats + i*dim);
						}
					}
				}
			}
			else
			{
				for (int j = 0; j < feat_num; j++)
				{
					float* tmp_feat = (float*)(((char*)feat_aligned) + widthStep*j);
					int chunk_size = (total_face_num + real_threads - 1) / real_threads;
					if (dim == 256)
					{
#pragma omp parallel for schedule(static, chunk_size) num_threads(real_threads)
						for (int i = 0; i < total_face_num; i++)
						{
							scores[i] = ZQ_FaceRecognizerSphereFace::_cal_similarity_avx_dim256(tmp_feat, all_face_feats + i*dim);
						}
					}
					else if (dim == 512)
					{
#pragma omp parallel for schedule(static, chunk_size) num_threads(real_threads)
						for (int i = 0; i < total_face_num; i++)
						{
							scores[i] = ZQ_FaceRecognizerSphereFace::_cal_similarity_avx_dim512(tmp_feat, all_face_feats + i*dim);
						}
					}
					else
					{
#pragma omp parallel for schedule(static, chunk_size) num_threads(real_threads)
						for (long long i = 0; i < total_face_num; i++)
						{
							scores[i] = ZQ_MathBase::DotProduct(dim, tmp_feat, all_face_feats + i*dim);
						}
					}
				}
			}
			

			float* max_scores = (float*)malloc(sizeof(float)*person_num);
			if (max_scores == 0)
			{
				_aligned_free(feat_aligned);
				free(scores);
				return false;
			}

			if (real_threads == 1)
			{
				for (int i = 0; i < person_num; i++)
				{
					float tmp = -FLT_MAX;
					for (long long j = person_face_offset[i]; j < person_face_offset[i]+person_face_num[i]; j++)
					{
						tmp = __max(tmp, scores[j]);
					}
					max_scores[i] = tmp;
				}
			}
			else
			{
				int chunk_size = (person_num + real_threads - 1) / real_threads;
#pragma omp parallel for schedule(static, chunk_size) num_threads(real_threads)
				for (int i = 0; i < person_num; i++)
				{
					float tmp = -FLT_MAX;
					for (long long j = person_face_offset[i]; j < person_face_offset[i] + person_face_num[i]; j++)
					{
						tmp = __max(tmp, scores[j]);
					}
					max_scores[i] = tmp;
				}
			}
			
			_aligned_free(feat_aligned);
			free(scores);

			
			int* ids = (int*)malloc(sizeof(int)*person_num);
			if (ids == 0)
			{
				free(max_scores);
				return false;
			}
			for (int i = 0; i < person_num; i++)
			{
				ids[i] = i;
			}


			out_ids.clear();
			out_scores.clear();
			out_names.clear();
			for (int i = 0; i < __min(max_num, person_num); i++)
			{
				float cur_max_score = max_scores[i];
				int max_id = i;
				for (int j = i + 1; j < person_num; j++)
				{
					if (cur_max_score < max_scores[j])
					{
						max_id = j;
						cur_max_score = max_scores[j];
					}
				}
				int tmp_id = ids[i];
				ids[i] = ids[max_id];
				ids[max_id] = tmp_id;
				float tmp_score = max_scores[i];
				max_scores[i] = max_scores[max_id];
				max_scores[max_id] = tmp_score;

				out_ids.push_back(ids[i]);
				out_scores.push_back(max_scores[i]);
				out_names.push_back(names[ids[i]]);
			}
		
			free(max_scores);
			free(ids);
			return true;
		}
	};
}
#endif
