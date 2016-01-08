/*�擪�œ��{���ł�����ł����΃\�[�X�c���[�ŕ\�������Ƃ��ɕ����������Ȃ��炵���̂�*/
#ifndef __TEMPLATE_MATCHONG__
#define __TEMPLATE_MATCHONG__

#include "narivectorpp.h"
//#include "nmi_matching_It.h"
#include <omp.h>

template <class T, class M>
void template_mathcing(const nari::vector<T> &imgRef, const nari::vector<M> &imgFl, const nari::vector<nari::vector<int>> &DispRef,
	nari::vector<nari::vector<int>> &DispFl, int xeRef, int yeRef, int zeRef, int xeFl, int yeFl, int zeFl,
	int tmp, int rangex, int rangey, int rangez)
{
	int disp_num = DispRef.size();

	int tmp_size = (tmp * 2 + 1)*(tmp * 2 + 1)*(tmp * 2 + 1);

	//�ǂ݌����񂾌v���_���ׂĂ𑖍����郋�[�v
	//����NMI�̊֐����g���ƂȂ������񉻂Œl��������̂�NMI���g�p����ۂ͕��񉻂͊O���Ă�����������
#pragma omp parallel for schedule(dynamic) num_threads(8)
	for (int a = 0; a < disp_num; a++) {
		nari::vector<int> disp(3);
		nari::vector<short> tmp_Ref(tmp_size);
		int t = 0;
		int v = 0;
		//�e���v���[�g�}�b�`���O�O�ɂ��炩���߈ʒu���킹���������̉摜�̃e���v���[�g�쐬
		for (int r = 0; r < 2 * tmp + 1; r++) {
			for (int q = 0; q < 2 * tmp + 1; q++) {
				for (int p = 0; p < 2 * tmp + 1; p++) {
					int x = DispRef[a][0] - tmp + p;
					int y = DispRef[a][1] - tmp + q;
					int z = DispRef[a][2] - tmp + r;
					//�e���v���[�g���摜����͂ݏo���ꍇ�͐܂�Ԃ����摜������
					if (x < 0) x = - x;
					if (y < 0) y = - y;
					if (z < 0) z = - z;
					if (x > xeRef - 1) x = 2 * (xeRef - 1) - x;
					if (y > yeRef - 1) y = 2 * (yeRef - 1) - y;
					if (z > zeRef - 1) z = 2 * (zeRef - 1) - z;
					int s = xeRef*yeRef*z + xeRef*y + x;
					//�e���v���[�g���̉�f��0�`32�ɐ��K��
					//tmp_Ref[t] = imgRef[s]*32/65535;
					tmp_Ref[t] = imgRef[s];
					//std::cout << tmp_Ref[t] ;
					t++;

				}
			}
		}

		std::cout << "(^^)<�e���v���[�g�����" << std::endl;

		//�]���l�ő�l�ƑΉ��_�̍��W���i�[����ϐ����`
		//���ݏ��ʂ̍ő�l���i�[����ϐ����`
		//double nmi_max = 0;

		//���֌W�����i�[����ϐ����`
		double cc = 0, cc_max = 0;

		//�Ή��_�̍��W������ϐ�
		int xs, ys, zs;

		//�e���v���[�g�}�b�`���O�J�n
		for (int k = 0; k < rangez * 2 + 1; k++) {
			for (int j = 0; j < rangey * 2 + 1; j++) {
				for (int i = 0; i < rangex * 2 + 1; i++) {
					nari::vector<short> tmp_Fl(tmp_size);
					int u = 0;
					//�ʒu���킹����鑤�̉摜�e���v���[�g�쐬
					for (int r = 0; r < 2 * tmp + 1; r++) {
						for (int q = 0; q < 2 * tmp + 1; q++) {
							for (int p = 0; p < 2 * tmp + 1; p++) {
								int x = DispRef[a][0] - rangex + i - tmp + p;
								int y = DispRef[a][1] - rangey + j - tmp + q;
								int z = DispRef[a][2] - rangez + k - tmp + r;
								//�e���v���[�g���摜����͂ݏo���ꍇ�͐܂�Ԃ����摜������
								if (x < 0) x = -x;
								if (y < 0) y = -y;
								if (z < 0) z = -z;
								if (x > xeFl - 1) x = 2 * (xeFl - 1) - x;
								if (y > yeFl - 1) y = 2 * (yeFl - 1) - y;
								if (z > zeFl - 1) z = 2 * (zeFl - 1) - z;
								int s = xeFl*yeFl*z + xeFl*y + x;
								//tmp_Fl[u] = imgFl[s]*32/65535;
								tmp_Fl[u] = imgFl[s];

								u++;

							}
						}
					}

					//��������e���v���[�g���m�̑��֌W�����v�Z
					double meanref = 0.0, meanfl = 0.0;
					for (int c = 0; c<tmp_size; c++) {
						meanref += tmp_Ref[c];
						meanfl += tmp_Fl[c];
					}
					meanref = meanref / tmp_size;
					meanfl = meanfl / tmp_size;

					double stdref = 0.0, stdfl = 0.0, cov = 0.0;
					for (int c = 0; c<tmp_size; c++) {
						stdref += (tmp_Ref[c] - meanref)*(tmp_Ref[c] - meanref);
						stdfl += (tmp_Fl[c] - meanfl)*(tmp_Fl[c] - meanfl);
						cov += (tmp_Ref[c] - meanref)*(tmp_Fl[c] - meanfl);
					}

					//���U0�ɂȂ�ƕ��ꂪ0�ɂȂ�̂ŃX�L�b�v
					if (stdfl != 0) {
						cc = cov / (sqrt(stdref)*sqrt(stdfl));
					}


					//���֌W�����ő�l���Ƃ�Ƃ��̍��W��ۑ�

					if (cc >= cc_max) {
						cc_max = cc;
						xs = DispRef[a][0] - rangex + i;
						ys = DispRef[a][1] - rangey + j;
						zs = DispRef[a][2] - rangez + k;
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

		std::cout << "(^^)<�T���_�݂���" << std::endl;
		std::cout << "a=" << a << std::endl;
		std::cout << "x=" << DispRef[a][0] << " y=" << DispRef[a][1] << " z=" << DispRef[a][2] << std::endl;
		std::cout << "xs=" << DispFl[a][0] << " ys=" << DispFl[a][1] << " zs=" << DispFl[a][2] << std::endl;
	}
}
#endif
