/*先頭で日本語を打ち込んでおけばソースツリーで表示したときに文字化けしないらしいので*/

#ifndef __INFO__
#define __INFO__

#include "common.h"
#include "nariinfocontroller.h"
#include "narifile.h"
#include "naricommon.h"
#include <string>

struct text_info
{

	;
	std::string set;
	std::string pathId;
	std::string case_list;

	std::string dirO;
	std::string dirRef;
	std::string dirFl;
	std::string caseRef_dir;
	std::string caseRef_name;
	std::string case_num;
	int tmp;
	int rangex;
	int rangey;
	int rangez;
	int delta;
	double lamb;


	inline void input(const std::string &path) // テキストから入力情報を書き込み
	{
		nari::infocontroller info;
		info.load(path);

		dirRef = nari::file::add_delim(info.get_as_str("dir_ref"));
		dirFl = nari::file::add_delim(info.get_as_str("dir_fl"));
		set = info.get_as_str("casefl");
		pathId = nari::file::add_delim(info.get_as_str("dir_txt"));
		pathId += set;

		dirO = nari::file::add_delim(info.get_as_str("output"));

		caseRef_dir = info.get_as_str("caseref_dir");
		caseRef_name = info.get_as_str("caseref_name");

		tmp = info.get_as_int("tmp_size");
		rangex = info.get_as_int("range_x");
		rangey = info.get_as_int("range_y");
		rangez = info.get_as_int("range_z");
		lamb = info.get_as_double("lamb");
		delta = info.get_as_int("delta");
		case_num = info.get_as_str("case_num");

		info.output();
	}
};


#endif