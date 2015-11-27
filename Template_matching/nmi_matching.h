#/*�擪�œ��{���ł�����ł����΃\�[�X�c���[�ŕ\�������Ƃ��ɕ����������Ȃ��炵���̂�*/
#include <vector>
#include <list>
#include <cmath>
#include "narivectorpp.h"

//���K�����ݏ��ʂ��v�Z����Ƃ��̃r������ύX����Ƃ��́C
//�ȉ���hist_level��ύX����
const int hist_level = 32;
double hist[hist_level][hist_level];
double hist_r[hist_level];
double hist_f[hist_level];

namespace {
	typedef nari::vector< short > ImageType;

	double get_nmi(double c)
	{
		double log_c = std::log(c);
		double nmi;
		double h(0), hf(0), hfr(0);
		for (int ii = 0; ii < hist_level; ii++)
		{
			if (hist_f[ii]) //0����@��0�̂Ƃ���true�Ŏ��s
			{
				h += hist_f[ii] * (std::log(hist_f[ii]) - log_c);
			}
			if (hist_r[ii]) //0����@��0�̂Ƃ���true�Ŏ��s
			{
				hf += hist_r[ii] * (std::log(hist_r[ii]) - log_c);
			}
			for (int jj = 0; jj < hist_level; jj++)
			{
				if (hist[jj][ii]) //0����@
				{
					hfr += hist[jj][ii] * (std::log(hist[jj][ii]) - log_c);
				}
			}
		}
		nmi = (h + hf) / hfr;
		return nmi;
	}

	//�A���P�x�q�X�g�O�����쐬
	//mask�͏W�ϋy�яW�ϋ^���̈�̃x�N�g��
	bool make_histgram(ImageType &It1, ImageType &It2, int c)
	{
		int count = 0;

		//�q�X�g�O����������
		for (int i = 0; i < hist_level; i++) {
			hist_r[i] = 0;
			hist_f[i] = 0;
			for (int j = 0; j < hist_level; j++)
				hist[i][j] = 0;
		}

		//�e���v���[�g�̉�f��������for�����܂킷
		for (int i = 0; i < c; i++)
		{
			//�e�r���ɏd�݂����鏈�����������ꍇ�C�ȉ��̃q�X�g�O�������������̏ꏊ������
			hist[It1[i]][It2[i]] += 1; //�񎟌��q�X�g�O�����̊Y���Z�x�l�r������
			hist_r[It1[i]] += 1; //�f�[�^�x�[�X���q�X�g�O�����̊Y���Z�x�l�r������
			hist_f[It2[i]] += 1; //�e�X�g�摜���q�X�g�O�����̊Y���Z�x�l�r������
			count++;
		}

		if (count == 0) return false;

		return true;
	}

	//main�ňȉ��̊֐����Ăяo��
	double calc_NMI(ImageType &It1, ImageType &It2)
	{
		int c = It1.size(); //���͂����e���v���[�g�̉�f���l��
							// �񎟌��P�x�q�X�g�O�����̍쐬
		if (!make_histgram(It1, It2, c))
			return 0; //false�̂Ƃ��C0���o�͂���
					  //false�ɂȂ�̂́Cmake_histgram���ŁC�q�X�g�O�����̑S�r�����O�̂Ƃ�

					  // ���K�����ݏ��ʂ̌v�Z
		return get_nmi(c);
	}
}
