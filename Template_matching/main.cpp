/*�擪�œ��{���ł�����ł����΃\�[�X�c���[�ŕ\�������Ƃ��ɕ����������Ȃ��炵���̂�*/
#include "naricommon.h"
#include "ip/narigaussian.h"

#include "naritimer.h"
#include "naricaseinfo.h"
#include <algorithm>
#include "other/narimhd.h"

#include <sstream>
#include "naricommon.h"
#include "narisystem.h"
#include "naripathline.h"
#include "naricaseinfo.h"
#include "ip/narimorphology.h"
#include "ip/narilabeling.h"

#include "ip/naricontour.h"
#include "ip/naridistance.h"
#include "other/narimhd.h"
#include "naritimer.h"
#include "ip/narirbf.h"
#include "../mist/vector.h"
#include "narivectorpp.h"
#include "ip/nariinterpolate.h"

#include "raw_io.h"
#include "info.h"
#include "template_matching.h"
#include "set_point.h"

#include <chrono>
#include <iostream>

template <class IMG_T>
void deformation_using_movement(int xeRef, int yeRef, int zeRef, int xeFl, int yeFl, int zeFl, nari::vector<float> &imgMoveX, nari::vector<float> &imgMoveY, nari::vector<float> &imgMoveZ, nari::vector<IMG_T> &imgI, nari::vector<IMG_T> &imgO)
{
	for (int z = 0; z < zeRef; z++)
	{
		for (int y = 0; y < yeRef; y++)
		{
			for (int x = 0; x < xeRef; x++)
			{
				int s = z * xeRef * yeRef + y * xeRef + x;
				//std::cout << imgMoveX[s] <<","<< imgMoveY[s] << "," << imgMoveZ[s] <<std::endl;
				//std::cout << imgI[s] << std::endl;
				imgO[s] = static_cast<IMG_T>(nari::interpolate_value::linear(imgI.ptr(), imgMoveX[s], imgMoveY[s], imgMoveZ[s], xeFl, yeFl, zeFl));
				//std::cout << imgO[s] << std::endl;
			}
		}
	}
}

void main(int argc, char *argv[])
{
	auto start = std::chrono::system_clock::now();


	//�����炭rbf�ό`�Ɏg���^�̒�`�C3�����p���H
	typedef nari::rbf<double, double, 3> rbf_t;
	typedef rbf_t::disp_t disp_t_3;
	typedef rbf_t::disp_list_t disp_list_t_3;


	//�e�L�X�g��path���e���v���[�g�}�b�`���O�̃p�����[�^���ǂ߂�悤�ɂ��܂���
	if (argc != 2)
	{
		std::cout << "usage : make_filter.exe input_info.txt" << std::endl << "Hit enter-key to exit...";
		getchar();
		exit(1);
	}

	text_info input_info;
	input_info.input(argv[1]);
	std::cout << "(�L�E�ցE)" << std::endl;
	// information of case
	nari::case_list_t cases;
	cases.load_file_txt(input_info.pathId, true);
	std::cout << "(�L�E�ցE)" << std::endl;
	//��Ǘ�̏����擾(�T�C�Y�C����_�Ȃ�)
	nari::mhd mhdRef;
	disp_list_t_3 listDisp;
	mhdRef.load(input_info.dirRef + input_info.caseRef_dir + input_info.caseRef_name + ".mhd");
	std::cout << "(�L�E�ցE)" << std::endl;
	int xeRef = mhdRef.size1();
	int yeRef = mhdRef.size2();
	int zeRef = mhdRef.size3();
	double xrRef = mhdRef.reso1();
	double yrRef = mhdRef.reso2();
	double zrRef = mhdRef.reso3();
	//const double shrinkValue = 3.0;	//1/3�ɏk�����܂�
	//int xeRef = (int)(xeRef / shrinkValue + 0.5);
	//int yeRef = (int)(yeRef / shrinkValue + 0.5);
	//int zeRef = (int)(zeRef / shrinkValue + 0.5);
	//double xrRef = xrRef * (double)xeRef / xeRef;
	//double yrRef = yrRef * (double)yeRef / yeRef;
	//double zrRef = zrRef * (double)zeRef / zeRef;
	std::cout << "(�L�E�ցE)" << std::endl;
	nari::mhd mhdRefS;
	mhdRefS = mhdRef;
	mhdRefS.size123(xeRef, yeRef, zeRef);
	mhdRefS.reso123(xrRef, yrRef, zrRef);
	std::cout << "(�L�E�ցE)" << std::endl;
	//��Ǘ�̓ǂݍ���
	nari::vector<short> imgRef;
	imgRef.load_file_bin(input_info.dirRef + input_info.caseRef_dir + input_info.caseRef_name + ".raw");
	//read_vector(imgRR,input_info.dirRef + input_info.caseRef_dir + input_info.caseRef_name + ".raw");
	std::cout << "(�L�E�ցE)" << std::endl;
	nari::vector<unsigned char> imgLabel;
	imgLabel.load_file_bin(input_info.dirRef + input_info.caseRef_dir + input_info.caseRef_name + "_label.raw");

	std::cout << "(�L�E�ցE)" << std::endl;

	int rx = input_info.rangex;
	int ry = input_info.rangey;
	int rz = input_info.rangez;

	int tmp = input_info.tmp;
	int tmp_size = (tmp * 2 + 1)*(tmp * 2 + 1)*(tmp * 2 + 1);
	int delta = input_info.delta;

	std::string dir_reflist = input_info.dirRef + input_info.caseRef_dir + "disp/" + input_info.caseRef_name + ".txt";



	////�T���_���i�[����x�N�^�[��p��
	//nari::vector<int> disp(3);
	//nari::vector<nari::vector<int>> DispRef;
	//int m = 0;

	////���������Ǘ�̃e���v���[�g�}�b�`���O���s���v���_�̍��W���Z�o,�@�ۑ�
	//std::ofstream Ref_list(input_info.dirRef + input_info.caseRef_dir + "disp/" + input_info.caseRef_name + ".txt");

	////�܂��͊i�q��ɉ��̒T���_���Ƃ�
	//for (int x = rx; x < xeRef - rx; x += delta) {
	//	for (int y = ry; y < yeRef - ry; y += delta) {
	//		for (int z = rz; z < zeRef - rz; z += delta) {
	//			//�Ƃ����_�Ńe���v���[�g���쐬���Ă݂�
	//			nari::vector<short> tmp_Ref(tmp_size);
	//			nari::vector<unsigned char> tmp_label(tmp_size);
	//			int t = 0;
	//			for (int r = 0; r < 2 * tmp + 1; r++) {
	//				for (int q = 0; q < 2 * tmp + 1; q++) {
	//					for (int p = 0; p < 2 * tmp + 1; p++) {
	//						int xtmp = x - tmp + p;
	//						int ytmp = y - tmp + q;
	//						int ztmp = z - tmp + r;
	//						//�e���v���[�g���摜����͂ݏo���ꍇ�͐܂�Ԃ����摜������
	//						if (x < 0) x = -x;
	//						if (y < 0) y = -y;
	//						if (z < 0) z = -z;
	//						if (x > xeRef - 1) x = 2 * (xeRef - 1) - x;
	//						if (y > yeRef - 1) y = 2 * (yeRef - 1) - y;
	//						if (z > zeRef - 1) z = 2 * (zeRef - 1) - z;
	//						int s = xeRef*yeRef*ztmp + xeRef*ytmp + xtmp;
	//						tmp_label[t] = imgLabel[s];
	//						tmp_Ref[t] = imgRef[s];
	//						t++;
	//					}
	//				}
	//			}


	//			//�e���v���[�g���̂Ƀ��x��=1�ɂȂ��f�����݂��Ȃ���΍̗p���Ȃ�
	//			int count = 0;
	//			for (int l = 0; l < t; l++) {
	//				if (tmp_label[l] == 1) count++;
	//			}
	//			if (count != 0) {
	//				//�e���v���[�g���̕��U���v�Z���Ă݂�0�łȂ���΍̗p
	//				double meanref = 0.0;
	//				double stdref = 0.0;
	//				for (int c = 0; c < tmp_size; c++) {
	//					meanref += tmp_Ref[c];
	//				}
	//				meanref = meanref / tmp_size;
	//				for (int c = 0; c < tmp_size; c++) {
	//					stdref += (tmp_Ref[c] - meanref)*(tmp_Ref[c] - meanref);
	//				}
	//				//std::cout << stdref << std::endl;
	//				if (stdref != 0.0) {
	//					//���W��Ref_list�Ƀe�L�X�g�Ƃ��ĕۑ�
	//					Ref_list << x << std::endl;
	//					Ref_list << y << std::endl;
	//					Ref_list << z << std::endl;
	//					//�x�N�^�[�ɂ��ۑ�(�e���v���[�g�}�b�`���O�p)
	//					disp[0] = x;
	//					disp[1] = y;
	//					disp[2] = z;
	//					DispRef.push_back(disp);
	//					m++;
	//				}
	//			}
	//		}
	//	}
	//}



	nari::vector<nari::vector<int>> DispRef;
	nari::vector<nari::vector<int>> preRef;
	set_point(dir_reflist, imgLabel, xeRef, yeRef, zeRef, DispRef);

	//[26][27]�̒��_�̍��W��preRef�ɒǉ�
	int x_46 = (DispRef[26][0] + DispRef[27][0]) / 2;
	int y_46 = DispRef[26][1];
	int z_46 = DispRef[26][2];
	//preRef�ɕۑ�
	nari::vector<int> disp(3);
	disp[0] = x_46;
	disp[1] = y_46;
	disp[2] = z_46;
	preRef.push_back(disp);

	//�v���_�̍��W�����[�h,listDisp�ɑ��
	rbf_t::load_cordinates(input_info.dirRef + input_info.caseRef_dir + "disp/" + input_info.caseRef_name + ".txt", listDisp);

	//�Ǘ჋�[�v
	for (int i = 0; i < cases.size(); i++)
	{
		std::cout << "case : " << i + 1 << std::endl;

		//�����Ǘ�̏����擾(�T�C�Y�C����_�Ȃ�)
		nari::mhd mhdFl;
		mhdFl.load(input_info.dirFl + cases[i].dir + cases[i].basename + ".mhd");


		int xeFl = mhdFl.size1();
		int yeFl = mhdFl.size2();
		int zeFl = mhdFl.size3();
		double xrFl = mhdFl.reso1();
		double yrFl = mhdFl.reso2();
		double zrFl = mhdFl.reso3();
		//int xeFl = (int)(xeFl / shrinkValue + 0.5);
		//int yeFl = (int)(yeFl / shrinkValue + 0.5);
		//int zeFl = (int)(zeFl / shrinkValue + 0.5);
		//double xrFl = xrFl * (double)xeFl / xeFl;
		//double yrFl = yrFl * (double)yeFl / yeFl;
		//double zrFl = zrFl * (double)zeFl / zeFl;

		nari::mhd mhdFlS;
		mhdFlS = mhdFl;
		mhdFlS.size123(xeFl, yeFl, zeFl);
		mhdFlS.reso123(xrFl, yrFl, zrFl);

		std::cout << "(^^)<�摜�ǂݍ��ނ�" << std::endl;

		//�����Ǘ�̓ǂݍ���
		nari::vector<short> imgFl(xeFl * yeFl * zeFl);
		imgFl.load_file_bin(input_info.dirFl + cases[i].dir + cases[i].basename + ".raw");
		//�����Ǘ�̌v���_���i�[����x�N�g����p��
		nari::vector<nari::vector<int>> DispFl(DispRef.size());

		int mm = preRef[0][0];
		std::cout << mm << std::endl;

		////��������̏����͑�܂��ȕ��s�ړ����s������
		nari::vector<nari::vector<int>> preFl(1);
		//[46]�̓_�̂�preTM
		template_mathcing(imgRef, imgFl, preRef, preFl, xeRef, yeRef, zeRef,
			xeFl, yeFl, zeFl, input_info.tmp, rx, ry, rz);
		//preTM�̌��ʂ����Ƃɉ摜��Ref��Fl���s�ړ�������
		//�ړ���i�[�p�i��Ǘ�̍��W����Ή����镂���Ǘ�̍��W���擾�j
		nari::vector<float> imgMoveX(xeRef * yeRef * zeRef);
		nari::vector<float> imgMoveY(xeRef * yeRef * zeRef);
		nari::vector<float> imgMoveZ(xeRef * yeRef * zeRef);
		int move_x = preRef[0][0] - preFl[0][0];
		int move_y = preRef[0][1] - preFl[0][1];
		int move_z = preRef[0][2] - preFl[0][2];

		std::cout << move_x << std::endl;
		std::cout << move_y << std::endl;
		std::cout << move_z << std::endl;

		for (int z = 0; z < zeRef; z++)
		{
			for (int y = 0; y < yeRef; y++)
			{
				for (int x = 0; x < xeRef; x++)
				{
					int s = z * xeRef * yeRef + y * xeRef + x;
					imgMoveX[s] = (float)x+move_x;
					imgMoveY[s] = (float)y+move_y;
					imgMoveZ[s] = (float)z+move_z;
				}
			}
		}

		std::cout << imgMoveX[3] << std::endl;
		std::cout << imgMoveY[3] << std::endl;
		std::cout << imgMoveZ[3] << std::endl;
		//imgI�ɕ����Ǘ��ǂݍ����imgO��
		nari::vector<short> imgI(xeRef * yeRef * zeRef),imgO(xeRef * yeRef * zeRef);
		mhdRef.load_mhd_and_image(imgI, input_info.dirFl + cases[i].dir + cases[i].basename + ".mhd");
		//�ȒP�ȕ��s�ړ����s���������ʂ�imgRef2�ɕۑ�
		deformation_using_movement(xeRef, yeRef, zeRef, xeRef, yeRef, zeRef, imgMoveX, imgMoveY, imgMoveZ, imgI, imgO);
		mhdRef.save_mhd_and_image(imgO, input_info.dirFl + cases[i].dir + "premove/" + cases[i].basename + ".raw");

		std::cout << "(^^)<TM�����" << std::endl;
		//�e���v���[�g�}�b�`���O
		template_mathcing(imgRef, imgO, DispRef, DispFl, xeRef, yeRef, zeRef,
			xeFl, yeFl, zeFl, input_info.tmp, rx, ry, rz);
		std::cout << "�`�e���v���[�g�}�b�`���O�I��<(_ _)>�`" << std::endl;
		//�e���v���[�g�}�b�`���O�ɂ�茈�肵���Ή��_�̍��W���e�L�X�g�ɕۑ�
		std::ofstream Fl_list(input_info.dirFl + cases[i].dir + "disp/" + cases[i].basename + ".txt");
		std::cout << "�T�����ʂ��e�L�X�g�ɕۑ������" << std::endl;
		int xs, ys, zs;
		for (int k = 0; k < DispRef.size(); k++) {
			xs = DispFl[k][0];
			ys = DispFl[k][1];
			zs = DispFl[k][2];
			Fl_list << xs << std::endl;
			Fl_list << ys << std::endl;
			Fl_list << zs << std::endl;
		}
		std::cout << "�ۑ�����" << std::endl;

	}
	auto end = std::chrono::system_clock::now();
	auto dur = end - start;
	auto msec = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
	std::cout << "TM��������=" << msec << "sec" << std::endl;
}