//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Bg.cpp
//!
//! @brief  Bgクラスの定義
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "Bg.h"


/* クラスの定義 */
/* ----------------------------------------
関数名：Bg::Bg
概要　：Bgクラスのコンストラクタ
引数　：なし(void)
戻り値：なし
---------------------------------------- */
Bg::Bg(BG_TYPE type)
	: Object(640, 480, 0.0f, 0.0f, 0.0f, 0.0f), type(type)
{
	if (type == SCROLL)
	{
		ResetPosition();
	}
}

/* ----------------------------------------
関数名：Bg::Update
概要　：更新処理
引数　：制限時間(const int)
戻り値：なし(void)
---------------------------------------- */
void Bg::Update(const int time_limit)
{
	/* スクロール処理 */
	if (type == SCROLL)
	{
		if (is_draw1 == true)
		{
			grp_y -= spd_y;
			if ((grp_y < 0) && (is_draw2 == false))
			{
				grp_y2 = 960;
				is_draw2 = true;
			}
			if (grp_y < -480)
			{
				is_draw1 = false;
			}
		}

		if (is_draw2 == true)
		{
			grp_y2 -= spd_y;
			if ((grp_y2 < 0) && (is_draw1 == false))
			{
				grp_y = 958;			// -2してるのは微調整
				is_draw1 = true;
			}

			if (grp_y2 < -480)
			{
				is_draw2 = false;
			}
		}
	}

	/* １０秒切ったらスピードアップ */
	if (time_limit < 10)
	{
		UpSpeed();
	}
}

/* ----------------------------------------
関数名：Bg::Draw
概要　：描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Bg::Draw(void)
{
	if (type == SCROLL)
	{
		if (is_draw1 == true)
		{
			DrawRectGraph(pos_x, pos_y, 0, grp_y, 640, 480, grp_handle, TRUE, FALSE);
		}
		if (is_draw2 == true)
		{
			DrawRectGraph(pos_x, pos_y, 0, grp_y2, 640, 480, grp_handle, TRUE, FALSE);
		}
	}
	else
	{
		DrawGraph(pos_x, pos_y, grp_handle, TRUE);
	}
}

/* ----------------------------------------
関数名：Bg::ResetPositon
概要　：座標をリセットする
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Bg::ResetPosition(void)
{
	grp_height = 960;
	grp_y = 480;
	grp_y2 = 960;
	spd_y = 2;
	is_draw1 = true;
	is_draw2 = false;
}

/* ----------------------------------------
関数名：Bg::Upspeed
概要　：速度を上げる
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Bg::UpSpeed(void)
{
	spd_y = 4;
}
