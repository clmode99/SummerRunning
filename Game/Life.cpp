//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Life.cpp
//!
//! @brief  Lifeクラスの定義
//!
//! @date   2016.08.19
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "GamePlay.h"
#include "Life.h"


/* クラスの定義 */
/* ----------------------------------------
関数名：Life::Life
概要　：Lifeクラスのコンストラクタ
引数　：幅(int)、高さ(int)、座標Ｘ(float)、座標Ｙ(float)
		速度Ｘ(float)、座標Ｙ(float)
戻り値：なし
---------------------------------------- */
Life::Life(int w, int h, float px, float py, float sx, float sy)
	:Object(w, h, px, py, sx, sy),
	grp_damage_handle(0)
{}

/* ----------------------------------------
関数名：Life::LoadGraphic
概要　：画像をメモリに読み込む
引数　：ファイル名(const char*, const char*)
戻り値：なし(void)
---------------------------------------- */
void Life::LoadGraphic(const char *file_name1, const char *file_name2)
{
	grp_handle = LoadGraph(file_name1);			// ライフ
	grp_damage_handle = LoadGraph(file_name2);	// ダメージ
}

/* ----------------------------------------
関数名：Life::Draw
概要　：描画する
引数　：プレイヤーのライフ(const int)
戻り値：なし(void)
---------------------------------------- */
void Life::Draw(const int player_life)
{
	/* ローカル変数の初期化 */
	int grp_handle_temp = 0;			// グラフィックハンドル。一時変数

	for (int i = 1; i <= MAX_LIFE; i++)
	{
		if (i <= player_life)
		{
			grp_handle_temp = grp_handle;
		}
		else
		{
			grp_handle_temp = grp_damage_handle;
		}

		DrawGraph(static_cast<int>(pos_x + (CHIP_SIZE * 2 * i)), static_cast<int>(pos_y), grp_handle_temp, TRUE);
	}
	
}