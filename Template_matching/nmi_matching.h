#/*先頭で日本語を打ち込んでおけばソースツリーで表示したときに文字化けしないらしいので*/
#include <vector>
#include <list>
#include <cmath>
#include "narivectorpp.h"

//正規化相互情報量を計算するときのビン数を変更するときは，
//以下のhist_levelを変更する
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
			if (hist_f[ii]) //0判定　非0のときにtrueで実行
			{
				h += hist_f[ii] * (std::log(hist_f[ii]) - log_c);
			}
			if (hist_r[ii]) //0判定　非0のときにtrueで実行
			{
				hf += hist_r[ii] * (std::log(hist_r[ii]) - log_c);
			}
			for (int jj = 0; jj < hist_level; jj++)
			{
				if (hist[jj][ii]) //0判定　
				{
					hfr += hist[jj][ii] * (std::log(hist[jj][ii]) - log_c);
				}
			}
		}
		nmi = (h + hf) / hfr;
		return nmi;
	}

	//連合輝度ヒストグラム作成
	//maskは集積及び集積疑い領域のベクトル
	bool make_histgram(ImageType &It1, ImageType &It2, int c)
	{
		int count = 0;

		//ヒストグラム初期化
		for (int i = 0; i < hist_level; i++) {
			hist_r[i] = 0;
			hist_f[i] = 0;
			for (int j = 0; j < hist_level; j++)
				hist[i][j] = 0;
		}

		//テンプレートの画素数分だけfor文をまわす
		for (int i = 0; i < c; i++)
		{
			//各ビンに重みをつける処理をしたい場合，以下のヒストグラム増加処理の場所を改良
			hist[It1[i]][It2[i]] += 1; //二次元ヒストグラムの該当濃度値ビン増加
			hist_r[It1[i]] += 1; //データベース側ヒストグラムの該当濃度値ビン増加
			hist_f[It2[i]] += 1; //テスト画像側ヒストグラムの該当濃度値ビン増加
			count++;
		}

		if (count == 0) return false;

		return true;
	}

	//mainで以下の関数を呼び出す
	double calc_NMI(ImageType &It1, ImageType &It2)
	{
		int c = It1.size(); //入力したテンプレートの画素数獲得
							// 二次元輝度ヒストグラムの作成
		if (!make_histgram(It1, It2, c))
			return 0; //falseのとき，0を出力する
					  //falseになるのは，make_histgram内で，ヒストグラムの全ビンが０のとき

					  // 正規化相互情報量の計算
		return get_nmi(c);
	}
}
