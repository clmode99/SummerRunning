//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Object.cpp
//!
//! @brief  Objectクラスの定義
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "Object.h"


/* クラスの定義 */
/* ----------------------------------------
関数名：Object::Object
概要　：Objectクラスのコンストラクタ(引数なし)
引数　：なし(void)
戻り値：なし
---------------------------------------- */
Object::Object()
	:grp_width(0), grp_height(0), pos_x(0.0f), pos_y(0.0f), spd_x(0.0f), spd_y(0.0f), grp_handle(0)
{}

/* -------------------------------------------------------
関数名：Object::Object
概要　：Objectクラスのコンストラクタ(引数あり)
引数　：幅(int)、高さ(int)、座標Ｘ(float)、座標Ｙ(float)
		速度Ｘ(float)、座標Ｙ(float)
戻り値：なし
------------------------------------------------------- */
Object::Object(int w, int h, float px, float py, float sx, float sy)
	:grp_width(w), grp_height(h), pos_x(px), pos_y(py), spd_x(sx), spd_y(sy), grp_handle(0)
{}

/* ----------------------------------------
関数名：Object::Update
概要　：更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Object::Update()
{}

/* ----------------------------------------
関数名：Object::Draw
概要　：描画する
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Object::Draw()
{
	DrawGraph(static_cast<int>(pos_x), static_cast<int>(pos_y), grp_handle, TRUE);
}

/* ------------------------------------------------------------------------------
関数名：Object::LoadGraph
概要　：メモリに指定された画像を読み込み、グラフィックハンドルメンバに代入する
引数　：ファイル名(const char*)
戻り値：なし(void)
------------------------------------------------------------------------------ */
void Object::LoadGraphic(const char *file_name)
{
	grp_handle = LoadGraph(file_name);
}

/* ------------------------------------------------------------------------------
関数名：Object::GetLeftBorder
概要　：左端の座標を取得する
引数　：なし(void)
戻り値：左端の座標(float)
------------------------------------------------------------------------------ */
float Object::GetLeftBorder() const
{
	return pos_x;
}

/* ------------------------------------------------------------------------------
関数名：Object::GetRightBorder
概要　：右端の座標を取得する
引数　：なし(void)
戻り値：右端の座標(float)
------------------------------------------------------------------------------ */
float Object::GetRightBorder() const
{
	return pos_x + (static_cast<float>(grp_width));
}

/* ------------------------------------------------------------------------------
関数名：Object::GetUpBorder
概要　：上端の座標を取得する
引数　：なし(void)
戻り値：上端の座標(float)
------------------------------------------------------------------------------ */
float Object::GetUpBorder() const
{
	return pos_y;
}

/* ------------------------------------------------------------------------------
関数名：Object::GetDownBorder
概要　：下端の座標を取得する
引数　：なし(void)
戻り値：下端の座標(float)
------------------------------------------------------------------------------ */
float Object::GetDownBorder() const
{
	return pos_y + (static_cast<float>(grp_height));
}