//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Face.cpp
//!
//! @brief  Faceクラスの定義
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "Face.h"


/* クラスの定義 */
/* -------------------------------------------------------
関数名：Face::Face
概要　：Faceクラスのコンストラクタ
引数　：幅(int)、高さ(int)、座標Ｘ(float)、座標Ｙ(float)
		速度Ｘ(float)、座標Ｙ(float)
戻り値：なし
-------------------------------------------------------- */
Face::Face(int w, int h, float px, float py, float sx, float sy)
	:Object(w, h, px, py, sx, sy),
	grp_caution_handle(0), grp_danger_handle(0)
{}

/* -------------------------------------------------------
関数名：Face::LoadGraphic
概要　：画像をメモリに読み込む
引数　：読み込む画像のファイル名(const char*, const char*, const char*)
戻り値：なし(void)
-------------------------------------------------------- */
void Face::LoadGraphic(const char *file_name1, const char *file_name2, const char *file_name3)
{
	grp_fine_handle = LoadGraph(file_name1);			// ノーマル
	grp_caution_handle = LoadGraph(file_name2);			// 注意
	grp_danger_handle = LoadGraph(file_name3);			// 危険

	grp_handle = grp_fine_handle;						// 最初はノーマル
}

/* -------------------------------------------------------
関数名：Face::Update
概要　：更新する
引数　：プレイヤーのライフ(const int)
戻り値：なし(void)
-------------------------------------------------------- */
void Face::Update(const int player_life)
{
	/* ライフに応じてグラフィックハンドルを設定する */
	if (player_life >= 7)				// ノーマル(７～１０）
	{
		grp_handle = grp_fine_handle;
	}
	else if (player_life >= 4)			// 注意(４～６）
	{
		grp_handle = grp_caution_handle;
	}
	else								//危険(０～３）
	{
		grp_handle = grp_danger_handle;
	}
}