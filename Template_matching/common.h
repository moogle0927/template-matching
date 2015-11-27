/*先頭で日本語を打ち込んでおけばソースツリーで表示したときに文字化けしないらしいので*/
#pragma once
#include<iostream>
#include <string>
#include <algorithm>
#include <vector>

#include <kawamhd.h>

#include <naricommon.h>
#include <nariinfocontroller.h>
#include <narifile.h>



/* 入力(特徴の型) */
typedef unsigned short feat_T;

/* マスクの型 */
typedef unsigned char mask_T;

/* ラベルの型 */
typedef unsigned char label_T;

/* セグメンテーション結果の型 */
typedef unsigned char seg_T;