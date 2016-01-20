#ifndef __SET_POINT__
#define __SET_POINT__

#include "narivectorpp.h"
#include "info.h"

template <class L, class D>
void set_point(std::string &dir_reflist, nari::vector<L> &imgLabel, int xeRef, int yeRef, int zeRef, nari::vector<nari::vector<D>> &DispRef)
{

	//浮動座標を格納する配列を用意
	nari::vector<int> disp(3);

	//テキストファイル保存先パスを指定
	std::ofstream Ref_list(dir_reflist);
	//顔側の端点　[0]　(この点で切ったsagittal平面で後頭部を含め他7点をとる)
	for (int y = 0; y < yeRef; y++) {
		for (int x = 0; x < xeRef; x++) {
			for (int z = 0; z < zeRef; z++) {
				int s = x + y * xeRef + z * xeRef*yeRef;
				if (imgLabel[s] == 1) {
					//座標をRef_listにテキストとして保存
					Ref_list << x << std::endl;
					Ref_list << y << std::endl;
					Ref_list << z << std::endl;
					//ベクターにも保存(テンプレートマッチング用)
					disp[0] = x;
					disp[1] = y;
					disp[2] = z;
					DispRef.push_back(disp);
					//ループ抜けます
					x = xeRef - 1;
					y = yeRef - 1;
					z = zeRef - 1;
				}
			}
		}
	}


	//後頭部　[1]
	for (int y = yeRef - 1; y > 0; y--) {
		int x = DispRef[0][0];
		int z = DispRef[0][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			y = 1;
		}
	}


	//顔面から後頭部までを8等分割にしたときの断面①②③④⑤⑥⑦と24分割した時の一番後頭部側の⑧
	//①のsagittal断面の頭側[2]と首側[3]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}

	//②のsagittal断面の頭側[3]と首側[4]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}

	//③のsagittal断面の頭側[6]と首側[7]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}

	//④のsagittal断面の頭側[8]と首側[9]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}
	//⑤のsagittal断面の頭側[10]と首側[11]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}


	//⑥のsagittal断面の頭側[12]と首側[13]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}
	//⑦のsagittal断面の頭側[14]と首側[15]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}

	//⑧のsagittal断面の頭側[16]と首側[17]
	for (int z = 0; z < zeRef; z++) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = zeRef - 1;
		}
	}

	for (int z = zeRef - 1; z > 0; z--) {
		int x = DispRef[0][0];
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜けます
			z = 1;
		}
	}


	//①のcoronal断面でみたときの左[18]右[19]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int z = (DispRef[2][2] + DispRef[3][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 7 + DispRef[1][1]) / 8;
		int z = (DispRef[2][2] + DispRef[3][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}

	//②のcoronal断面でみたときの左[20]右[21]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int z = (DispRef[4][2] + DispRef[5][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1]) / 4;
		int z = (DispRef[4][2] + DispRef[5][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}

	//③のcoronal断面でみたときの左[22]右[23]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = (DispRef[6][2] + DispRef[7][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = (DispRef[6][2] + DispRef[7][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//③ののcoronal断面でみたときの左[24]右[25]端点(下)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = DispRef[7][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 5 + DispRef[1][1] * 3) / 8;
		int z = DispRef[7][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}



	//④のcoronal断面でみたときの左[26]右[27]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = (DispRef[8][2] + DispRef[9][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = (DispRef[8][2] + DispRef[9][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//④のcoronal断面でみたときの左[28]右[29]端点(下)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = DispRef[9][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1]) / 2;
		int z = DispRef[9][2];
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}

	//⑤のcoronal断面でみたときの左[30]右[31]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//⑤のcoronal断面でみたときの左[32]右[33]端点(下)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] * 3 + DispRef[1][1] * 5) / 8;
		int z = (DispRef[10][2] + DispRef[11][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//⑥のcoronal断面でみたときの左[34]右[35]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//⑥のcoronal断面でみたときの左[36]右[37]端点(下)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 3) / 4;
		int z = (DispRef[12][2] + DispRef[13][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//⑦のcoronal断面でみたときの左[38]右[39]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//⑦のcoronal断面でみたときの左[40]右[41]端点(下)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 7) / 8;
		int z = (DispRef[14][2] + DispRef[15][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//⑧のcoronal断面でみたときの左[42]右[43]端点
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int z = (DispRef[16][2] + DispRef[17][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	for (int x = xeRef - 1; x > 0; x--) {
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int z = (DispRef[16][2] + DispRef[17][2]) / 2;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = 1;
		}
	}
	//⑧のcoronal断面でみたときの左[44]右[45]端点(下)
	for (int x = 0; x < xeRef; x++) {
		int y = (DispRef[0][1] + DispRef[1][1] * 23) / 24;
		int z = (DispRef[16][2] + DispRef[17][2] * 3) / 4;
		int s = x + y * xeRef + z * xeRef*yeRef;
		if (imgLabel[s] == 1) {
			//座標をRef_listにテキストとして保存
			Ref_list << x << std::endl;
			Ref_list << y << std::endl;
			Ref_list << z << std::endl;
			//ベクターにも保存(テンプレートマッチング用)
			disp[0] = x;
			disp[1] = y;
			disp[2] = z;
			DispRef.push_back(disp);
			//ループ抜ける
			x = xeRef - 1;
		}
	}

	

}

#endif