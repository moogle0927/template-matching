/*先頭で日本語を打ち込んでおけばソースツリーで表示したときに文字化けしないらしいので*/
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>


long long get_file_size(const std::string filename)
{
	FILE *fp;
	struct _stat64 st;
	if (fopen_s(&fp, filename.c_str(), "rb") != 0) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		std::abort();
	}
	_fstat64(_fileno(fp), &st);
	fclose(fp);
	return st.st_size;
}


template< class T >
void read_vector(std::vector<T> &v, const std::string filename) {

	auto num = get_file_size(filename) / sizeof(T);
	FILE *fp;
	if (fopen_s(&fp, filename.c_str(), "rb") != 0) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		std::abort();
	}
	v.resize(num);
	fread(v.data(), sizeof(T), num, fp);

	fclose(fp);
}

template< class T >
void write_vector(std::vector<T> &v, const std::string filename) {
	FILE *fp;
	if (fopen_s(&fp, filename.c_str(), "wb") != 0) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		std::abort();
	}
	fwrite(v.data(), sizeof(T), v.size(), fp);
	fclose(fp);
}


template< class T >
void txt_to_vec(std::vector<T>& v, std::string filename)
{
	std::cout << filename << std::endl;
	std::ifstream file(filename);
	std::string buf;
	std::cout << "aaa" << std::endl;
	while (file && getline(file, buf))
	{
		v.push_back(buf);
	}
}

template< class T >
void vec_to_txt(std::vector<T>& v, std::string filename)
{
	std::cout << filename << std::endl;
	std::ofstream file(filename);

	for (size_t i = 0; i < v.size(); i++)
	{
		file << v[i] << std::endl;
	}
}
