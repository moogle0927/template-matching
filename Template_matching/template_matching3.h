#pragma once
/*�擪�œ��{���ł�����ł����΃\�[�X�c���[�ŕ\�������Ƃ��ɕ����������Ȃ��炵���̂�*/
#ifndef __TEMPLATE_MATCHONG3__
#define __TEMPLATE_MATCHONG3__

#include "narivectorpp.h"
//#include "nmi_matching_It.h"
#include <omp.h>
#include "stdlib.h"

template <class T, class M>
void template_mathcing3(const nari::vector<T> &imgRef, const nari::vector<M> &imgFl, const nari::vector<nari::vector<int>> &DispRef,
	nari::vector<nari::vector<int>> &DispFl, const nari::vector<nari::vector<int>> &DispPre, int xeRef, int yeRef, int zeRef, int xeFl, int yeFl, int zeFl,
	int tmp, const nari::vector<int> &rangex, const nari::vector<int> &rangey, const nari::vector<int> &rangez)
{
	int disp_num = DispRef.size();
	std::cout << disp_num << std::endl;

	int tmp_size = (tmp * 2 + 1)*(tmp * 2 + 1)*(tmp * 2 + 1);

	//�ǂ݌����񂾌v���_���ׂĂ𑖍����郋�[�v
	//����NMI�̊֐����g���ƂȂ������񉻂Œl��������̂�NMI���g�p����ۂ͕��񉻂͊O���Ă�����������
#pragma omp parallel for schedule(dynamic) num_threads(8)
	for (int a = 0; a < disp_num; a++) {
		nari::vector<int> disp(3);
		nari::vector<short> tmp_Ref(tmp_size);
		nari::vector<int> tmp_space((tmp_size), 0);
		int t = 0;
		int v = 0;
		//�e���v���[�g�}�b�`���O�O�ɂ��炩���߈ʒu���킹���������̉摜�̃e���v���[�g�쐬
		for (int r = 0; r < 2 * tmp + 1; r++) {
			for (int q = 0; q < 2 * tmp + 1; q++) {
				for (int p = 0; p < 2 * tmp + 1; p++) {
					int x = DispRef[a][0] - tmp + p;
					int y = DispRef[a][1] - tmp + q;
					int z = DispRef[a][2] - tmp + r;
					//�e���v���[�g���摜����͂ݏo���ꍇ(0,0,0)�̔Z�x�l������
					if ((x >= 0) && (y >= 0) && (z >= 0) && (x < xeRef) && (y < yeRef) && (z < zeRef)) {
						int s = xeRef*yeRef*z + xeRef*y + x;
						//�e���v���[�g���̉�f��0�`32�ɐ��K��
						//tmp_Ref[t] = imgRef[s]*32/65535;
						tmp_Ref[t] = imgRef[s];
						t++;
					}
					else {
						//tmp_space�Ƀe���v���[�g�̉�f�������ĂȂ���f�ԍ����P��
						tmp_Ref[t] = 500;
						tmp_space[t] = 1;
						t++;
					}
				}
			}
		}

		//std::cout << "(^^)<�e���v���[�g�����" << std::endl;

		//�]���l�ő�l�ƑΉ��_�̍��W���i�[����ϐ����`
		//���ݏ��ʂ̍ő�l���i�[����ϐ����`
		//double nmi_max = 0;

		//���֌W�����i�[����ϐ����`
		double cc = 0, cc_max = 0;

		//�Ή��_�̍��W������ϐ�
		int xs, ys, zs;

		//�e���v���[�g�}�b�`���O�J�n
		for (int k = 0; k < rangez[a] * 2 + 1; k++) {
			for (int j = 0; j < rangey[a] * 2 + 1; j++) {
				for (int i = 0; i < rangex[a] * 2 + 1; i++) {
					nari::vector<short> tmp_Fl(tmp_size);
					int u = 0;
					//�ʒu���킹����鑤�̉摜�e���v���[�g�쐬
					for (int r = 0; r < 2 * tmp + 1; r++) {
						for (int q = 0; q < 2 * tmp + 1; q++) {
							for (int p = 0; p < 2 * tmp + 1; p++) {
								int x = DispPre[a][0] - rangex[a] + i - tmp + p;
								int y = DispPre[a][1] - rangey[a] + j - tmp + q;
								int z = DispPre[a][2] - rangez[a] + k - tmp + r;
								//�e���v���[�g���摜����͂ݏo�Ȃ���΃e���v���[�g����
								if ((x >= 0) && (y >= 0) && (z >= 0) && (x < xeFl) && (y < yeFl) && (z < zeFl)) {
									int s = xeFl*yeFl*z + xeFl*y + x;
									//tmp_Fl[u] = imgFl[s]*32/65535;
									tmp_Fl[u] = imgFl[s];
									u++;
								}
								else {
									tmp_Fl[u] = 500;
									u++;
								}

							}
						}
					}

					//��������e���v���[�g���m�̑��֌W�����v�Z
					double meanref = 0.0, meanfl = 0.0;
					int tmp_true = 0;
					for (int c = 0; c < tmp_size; c++) {
						if (tmp_space[c] == 0) {
							meanref += tmp_Ref[c];
							meanfl += tmp_Fl[c];
							tmp_true++;
						}
					}
					meanref = meanref / tmp_true;
					meanfl = meanfl / tmp_true;

					double stdref = 0.0, stdfl = 0.0, cov = 0.0;
					for (int c = 0; c < tmp_size; c++) {
						if (tmp_space[c] == 0) {
							stdref += (tmp_Ref[c] - meanref)*(tmp_Ref[c] - meanref);
							stdfl += (tmp_Fl[c] - meanfl)*(tmp_Fl[c] - meanfl);
							cov += (tmp_Ref[c] - meanref)*(tmp_Fl[c] - meanfl);
						}
					}

					//���U0�ɂȂ�ƕ��ꂪ0�ɂȂ�̂ŃX�L�b�v
					if (stdfl != 0) {
						cc = cov / (sqrt(stdref)*sqrt(stdfl));
					}


					//���֌W�����ő�l���Ƃ�Ƃ��̍��W��ۑ�

					if (cc >= cc_max) {
						cc_max = cc;
						xs = DispPre[a][0] - rangex[a] + i;
						ys = DispPre[a][1] - rangey[a] + j;
						zs = DispPre[a][2] - rangez[a] + k;
						//std::cout << "stdref=" << stdref << std::endl;
						//std::cout << "cc=" << cc << std::endl;
					}

					//���֌W�����P�̂Ƃ��̂ݍ̗p(�f�o�b�O)
					/*if (cc == 1){
					xs = DispRef[a][0] - rangex + i;
					ys = DispRef[a][1] - rangey + j;
					zs = DispRef[a][2] - rangez + k;
					}
					*/
					////NMI(���ݏ���)�ɂ��]��
					//double nmi = calc_NMI(tmp_Ref, tmp_Fl); //NMI�i��Ǘ�vs�����Ǘ�j
					//���ݍő��nmi���傫����ΑΉ��_�̍��W���X�V
					/*if (nmi > nmi_max){
					nmi_max = nmi;
					xs = DispRef[a][0] - rangex + i;
					ys = DispRef[a][1] - rangey + j;
					zs = DispRef[a][2] - rangez + k;
					}*/


					//���S�Ɉ�v�����Ƃ������Ή��_�Ƃ���(TM�̃f�o�b�O�ɂǂ���)
					/*int count = 0;
					for ( int c=0 ; c<u ; c++){
					int X = tmp_Ref[c]-tmp_Fl[c];
					if (X != 0)count++;
					}
					if (count == 0){
					xs = DispRef[a][0] - rangex + i;
					ys = DispRef[a][1] - rangey + j;
					zs = DispRef[a][2] - rangez + k;
					}*/

				}

			}
			//std::cout << "(�L�E�ցE)<�������H�H" << std::endl;
		}
		disp[0] = xs;
		disp[1] = ys;
		disp[2] = zs;
		DispFl[a] = (disp);

		//std::cout << "(^^)<�T���_�݂���" << std::endl;
		//std::cout << "a=" << a << std::endl;
		//std::cout << "x=" << DispPre[a][0] << " y=" << DispPre[a][1] << " z=" << DispPre[a][2] << std::endl;
		//std::cout << "xs=" << DispFl[a][0] << " ys=" << DispFl[a][1] << " zs=" << DispFl[a][2] << std::endl;
	}
}
#endif