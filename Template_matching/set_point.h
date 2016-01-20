#ifndef __SET_POINT__
#define __SET_POINT__

#include "narivectorpp.h"
#include "info.h"

template <class L, class D>
void set_point(std::string &dir_reflist, nari::vector<L> &imgLabel, int xeRef, int yeRef, int zeRef, nari::vector<nari::vector<D>> &DispRef)
{

	//�������W���i�[����z���p��
	nari::vector<int> disp(3);

	//�e�L�X�g�t�@�C���ۑ���p�X���w��
	std::ofstream Ref_list(dir_reflist);
	//�瑤�̒[�_�@[0]�@(���̓_�Ő؂���sagittal���ʂŌ㓪�����܂ߑ�7�_���Ƃ�)
	for (int y = 0; y < yeRef; y++) {
		for (int x = 0; x < xeRef; x++) {
			for (int z = 0; z < zeRef; z++) {
				int s = x + y * xeRef + z * xeRef*yeRef;
				if (imgLabel[s] == 1) {
					//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
					Ref_list << x << std::endl;
					Ref_list << y << std::endl;
					Ref_list << z << std::endl;
					//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
					disp[0] = x;
					disp[1] = y;
					disp[2] = z;
					DispRef.push_back(disp);
					//���[�v�����܂�
					x = xeRef - 1;
					y = yeRef - 1;
					z = zeRef - 1;
				}
			}
		}
	}


	//�㓪���@[1]
	for (int y = yeRef - 1; y > 0; y--) {
		int x = DispRef[0][0];
		int z = DispRef[0][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			y = 1;
		}
	}


	//��ʂ���㓪���܂ł�8�������ɂ����Ƃ��̒f�ʇ@�A�B�C�D�E�F��24�����������̈�Ԍ㓪�����̇G
	//�@��sagittal�f�ʂ̓���[2]�Ǝ�[3]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}

	//�A��sagittal�f�ʂ̓���[3]�Ǝ�[4]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}

	//�B��sagittal�f�ʂ̓���[6]�Ǝ�[7]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}

	//�C��sagittal�f�ʂ̓���[8]�Ǝ�[9]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}
	//�D��sagittal�f�ʂ̓���[10]�Ǝ�[11]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}


	//�E��sagittal�f�ʂ̓���[12]�Ǝ�[13]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}
	//�F��sagittal�f�ʂ̓���[14]�Ǝ�[15]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}

	//�G��sagittal�f�ʂ̓���[16]�Ǝ�[17]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v�����܂�
			z = 1;
		}
	}


	//�@��coronal�f�ʂł݂��Ƃ��̍�[18]�E[19]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int z = (DispRef[2][2] + DispRef[3][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int z = (DispRef[2][2] + DispRef[3][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}

	//�A��coronal�f�ʂł݂��Ƃ��̍�[20]�E[21]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int z = (DispRef[4][2] + DispRef[5][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int z = (DispRef[4][2] + DispRef[5][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}

	//�B��coronal�f�ʂł݂��Ƃ��̍�[22]�E[23]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = (DispRef[6][2] + DispRef[7][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = (DispRef[6][2] + DispRef[7][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�B�̂�coronal�f�ʂł݂��Ƃ��̍�[24]�E[25]�[�_(��)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = DispRef[7][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = DispRef[7][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}



	//�C��coronal�f�ʂł݂��Ƃ��̍�[26]�E[27]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = (DispRef[8][2] + DispRef[9][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = (DispRef[8][2] + DispRef[9][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�C��coronal�f�ʂł݂��Ƃ��̍�[28]�E[29]�[�_(��)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = DispRef[9][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = DispRef[9][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}

	//�D��coronal�f�ʂł݂��Ƃ��̍�[30]�E[31]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�D��coronal�f�ʂł݂��Ƃ��̍�[32]�E[33]�[�_(��)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�E��coronal�f�ʂł݂��Ƃ��̍�[34]�E[35]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�E��coronal�f�ʂł݂��Ƃ��̍�[36]�E[37]�[�_(��)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�F��coronal�f�ʂł݂��Ƃ��̍�[38]�E[39]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�F��coronal�f�ʂł݂��Ƃ��̍�[40]�E[41]�[�_(��)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�G��coronal�f�ʂł݂��Ƃ��̍�[42]�E[43]�[�_
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int z = (DispRef[16][2] + DispRef[17][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int z = (DispRef[16][2] + DispRef[17][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = 1;
		}
	}
	//�G��coronal�f�ʂł݂��Ƃ��̍�[44]�E[45]�[�_(��)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int z = (DispRef[16][2] + DispRef[17][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//���[�v������
			x = xeRef - 1;
		}
	}

	

}

#endif