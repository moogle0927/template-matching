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
#include "template_matching2.h"
#include "set_point.h"

#include <chrono>
#include <iostream>

template <class IMG_T>
void Img_deformation_using_movement(int xeRef, int yeRef, int zeRef, int xeFl, int yeFl, int zeFl, int move_x, int move_y, int move_z, nari::vector<float> &imgMoveX, nari::vector<float> &imgMoveY, nari::vector<float> &imgMoveZ, nari::vector<IMG_T> &imgI, nari::vector<IMG_T> &imgO)
{

	for (int z = 0; z < zeRef; z++)
	{
		for (int y = 0; y < yeRef; y++)
		{
			for (int x = 0; x < xeRef; x++)
			{
				int s = z * xeRef * yeRef + y * xeRef + x;
				//�t�`��500������悤�ɐݒ�
				if ((-1 < (x - move_x)) && ((x - move_x) < xeFl) && (-1 < (y - move_y)) && ((y - move_y) < yeFl) && (-1 < (z - move_z)) && ((z - move_z) < zeFl)) {
					imgO[s] = static_cast<IMG_T>(nari::interpolate_value::linear(imgI.ptr(), imgMoveX[s], imgMoveY[s], imgMoveZ[s], xeFl, yeFl, zeFl));
				}
				else {

					imgO[s] = 500;
				}
			}
		}
	}
}
template <class IMG_T>
void Label_deformation_using_movement(int xeRef, int yeRef, int zeRef, int xeFl, int yeFl, int zeFl, nari::vector<float> &imgMoveX, nari::vector<float> &imgMoveY, nari::vector<float> &imgMoveZ, nari::vector<IMG_T> &imgI, nari::vector<IMG_T> &imgO)
{
	for (int z = 0; z < zeRef; z++)
	{
		for (int y = 0; y < yeRef; y++)
		{
			for (int x = 0; x < xeRef; x++)
			{
				int s = z * xeRef * yeRef + y * xeRef + x;
				imgO[s] = static_cast<IMG_T>(nari::interpolate_value::linear(imgI.ptr(), imgMoveX[s], imgMoveY[s], imgMoveZ[s], xeFl, yeFl, zeFl));
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
		std::cout << preRef[0][0] << " ." << preRef[0][1] << " ." << preRef[0][2] << std::endl;

		////��������̏����͑�܂��ȕ��s�ړ����s������
		nari::vector<nari::vector<int>> preFl(1);
		//[46]�̓_�̂�preTM
		template_mathcing(imgRef, imgFl, preRef, preFl, xeRef, yeRef, zeRef,
			xeFl, yeFl, zeFl, 20, 10, 20, 20);
		//preTM�̌��ʂ����Ƃɉ摜��Ref��Fl�����߂�ꂽ���W�ɕ��s�ړ�������
		//�ړ���i�[�p�i��Ǘ�̍��W����Ή����镂���Ǘ�̍��W���擾�j
		/*nari::vector<int> cor_std(3);
		cor_std[0] = 96;
		cor_std[1] = 105;
		cor_std[2] = 35;*/
		std::cout << "�����܂�" << std::endl;
		nari::vector<float> imgMoveXR(xeRef * yeRef * zeRef);
		nari::vector<float> imgMoveYR(xeRef * yeRef * zeRef);
		nari::vector<float> imgMoveZR(xeRef * yeRef * zeRef);
		nari::vector<float> imgMoveXF(xeRef * yeRef * zeRef);
		nari::vector<float> imgMoveYF(xeRef * yeRef * zeRef);
		nari::vector<float> imgMoveZF(xeRef * yeRef * zeRef);
		std::cout << "�����܂�" << std::endl;
		int moveR_x = 96 - preRef[0][0];
		int moveR_y = 96 - preRef[0][1];
		int moveR_z = 45 - preRef[0][2];
		int moveF_x = 96 - preFl[0][0];
		int moveF_y = 96 - preFl[0][1];
		int moveF_z = 45 - preFl[0][2];
		std::cout << "�����܂�" << std::endl;

		std::cout << moveR_x << " ," << moveR_y << " ," << moveR_z << std::endl;
		std::cout << moveF_x << " ," << moveF_y << " ," << moveF_z << std::endl;


		nari::vector<nari::vector<int>> Disp_pre_Ref;
		nari::vector<int> disp(3);
		std::ofstream Ref_pre_list(input_info.dirRef + input_info.caseRef_dir + "premove/disp/" + input_info.caseRef_name + ".txt");
		for (int a = 0; a < DispRef.size(); a++) {
			int x_pre = DispRef[a][0] + moveR_x;
			int y_pre = DispRef[a][1] + moveR_y;
			int z_pre = DispRef[a][2] + moveR_z;
			Ref_pre_list << x_pre << std::endl;
			Ref_pre_list << y_pre << std::endl;
			Ref_pre_list << z_pre << std::endl;

		}

		for (int z = 0; z < zeRef; z++)
		{
			for (int y = 0; y < yeRef; y++)
			{
				for (int x = 0; x < xeRef; x++)
				{

					int s = z * xeRef * yeRef + y * xeRef + x;
					imgMoveXR[s] = (float)x - moveR_x;
					imgMoveYR[s] = (float)y - moveR_y;
					imgMoveZR[s] = (float)z - moveR_z;



				}
			}
		}
		for (int z = 0; z < zeFl; z++)
		{
			for (int y = 0; y < yeFl; y++)
			{
				for (int x = 0; x < xeFl; x++)
				{
					int s = z * xeFl * yeFl + y * xeFl + x;
					imgMoveXF[s] = (float)x - moveF_x;
					imgMoveYF[s] = (float)y - moveF_y;
					imgMoveZF[s] = (float)z - moveF_z;
				}
			}
		}




		std::cout << imgMoveXR[3] << std::endl;
		std::cout << imgMoveYR[3] << std::endl;
		std::cout << imgMoveZR[3] << std::endl;
		//imgI�ɕ����Ǘ��ǂݍ����imgO��
		nari::vector<short> imgRef2(xeRef * yeRef * zeRef), imgFl2(xeFl * yeFl *zeFl);
		//�ȒP�ȕ��s�ړ����s���������ʂ�imgRef2�ɕۑ�
		Img_deformation_using_movement(xeRef, yeRef, zeRef, xeRef, yeRef, zeRef, moveR_x, moveR_y, moveR_z, imgMoveXR, imgMoveYR, imgMoveZR, imgRef, imgRef2);
		Img_deformation_using_movement(xeFl, yeFl, zeFl, xeFl, yeFl, zeFl, moveF_x, moveF_y, moveF_z, imgMoveXF, imgMoveYF, imgMoveZF, imgFl, imgFl2);
		mhdRef.save_mhd_and_image(imgRef2, input_info.dirRef + input_info.caseRef_dir + "premove/" + input_info.caseRef_name + ".raw");
		mhdFl.save_mhd_and_image(imgFl2, input_info.dirFl + cases[i].dir + "premove/" + cases[i].basename + ".raw");

		std::cout << "(^^)<TM�����" << std::endl;

		for (int k = 0; k < DispRef.size(); k++) {
			DispRef[k][0] = DispRef[k][0] + moveR_x;
			DispRef[k][1] = DispRef[k][1] + moveR_y;
			DispRef[k][2] = DispRef[k][2] + moveR_z;
		}
		//�����摜���x���ƎQ�Ɖ摜�̐������x���ɕ��s�ړ���������
		nari::vector<unsigned char> imgLabel2(xeRef * yeRef * zeRef), imgAnswer(xeFl * yeFl * zeFl), imgAnswer2(xeFl * yeFl * zeFl);
		imgAnswer.load_file_bin("//MISAWA/H/spatial_normalization/answer/" + cases[i].basename + "_label.raw");
		Label_deformation_using_movement(xeRef, yeRef, zeRef, xeRef, yeRef, zeRef, imgMoveXR, imgMoveYR, imgMoveZR, imgLabel, imgLabel2);
		Label_deformation_using_movement(xeFl, yeFl, zeFl, xeFl, yeFl, zeFl, imgMoveXF, imgMoveYF, imgMoveZF, imgAnswer, imgAnswer2);
		mhdRef.save_mhd_and_image(imgLabel2, input_info.dirRef + input_info.caseRef_dir + "premove/" + input_info.caseRef_name + "_label.raw");
		mhdFl.save_mhd_and_image(imgAnswer2, "//MISAWA/H/spatial_normalization/answer/premove/" + cases[i].basename + "_label.raw");

		////����ό`��쐬�̈�
		template_mathcing_2(imgRef2, imgFl2, imgAnswer2, DispRef, DispFl, xeRef, yeRef, zeRef,
			xeFl, yeFl, zeFl, input_info.tmp, rx, ry, rz);

		////�e���v���[�g�}�b�`���O
		//template_mathcing(imgRef2, imgFl2, DispRef, DispFl, xeRef, yeRef, zeRef,
		//	xeFl, yeFl, zeFl, input_info.tmp, rx, ry, rz);
		std::cout << "�`�e���v���[�g�}�b�`���O�I��<(_ _)>�`" << std::endl;
		//�e���v���[�g�}�b�`���O�ɂ�茈�肵���Ή��_�̍��W���e�L�X�g�ɕۑ�
		std::ofstream Fl_list(input_info.dirFl + cases[i].dir + "premove/disp/" + cases[i].basename + ".txt");
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