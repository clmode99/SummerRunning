//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Item.cpp
//!
//! @brief  Itemクラスの定義
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* インクルードファイル */
#include "Item.h"
#include "Common.h"	// SCREEN_HEIGHT
#include "GamePlay.h"


/* クラスの定義 */
/* ----------------------------------------
関数名：Item::Item
概要　：Itemクラスのコンストラクタ
引数　：なし(void)
戻り値：なし
---------------------------------------- */
Item::Item(int w, int h, float px, float py, float sx, float sy)
	: Object(w, h, px, py, sx, sy), exist_state(false), kind(NONE), is_fadeout(false), opacity(MAX_OPACITY)
{}

/* ----------------------------------------
関数名：Item::Update
概要　：更新処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Item::Update(void)
{
	// 移動処理(※関数化候補)
	if (is_fadeout == false)
	{
		pos_y += spd_y;
	}

	// 画面下まできたら消す
	if (pos_y >= SCREEN_HEIGHT)
	{
		Delete();
	}

	// 当たったらフェードアウトする(※関数化候補)
	if (is_fadeout == true)
	{
		pos_y += 4.0f;			// 若干座標下げることで、それっぽい演出にしてみる
		
		opacity -= 40;			// ４０が丁度よかった
		if (opacity <= 0)
		{
			Delete();
		}
	}
}

/* ----------------------------------------
関数名：Item::Draw
概要　：描画処理
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Item::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);			// 不透明度設定

	DrawGraph((int)pos_x, (int)pos_y, grp_handle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				// もとに戻さないとおかしくなる
}

/* --------------------------------------------------------------
関数名：Item::Create
概要　：アイテムを作る
引数　：出現レーン(const int)、グラフィックハンドル(const int)、種類(const KIND)
戻り値：なし(void)
--------------------------------------------------------------- */
void Item::Create(const int lane, const int handle, const KIND kind_temp)
{
	// アイテムの座標Ｘを決める(※関数化候補)
	switch (lane)
	{
	case 0:
		pos_x = ITEM0_X;
		break;

	case 1:
		pos_x = ITEM1_X;
		break;

	case 2:
		pos_x = ITEM2_X;
		break;

	case 3:
		pos_x = ITEM3_X;
		break;

	default:
		Error();
		break;
	}

	// グラフィックハンドル設定 (LoadGraphic的な)
	grp_handle = handle;

	// 種類設定
	kind = kind_temp;

	exist_state = true;
}

/* ----------------------------------------
関数名：Item::Delete
概要　：アイテムを消す
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Item::Delete(void)
{
	exist_state = false;
	is_fadeout = false;
	opacity = MAX_OPACITY;
	kind = NONE;
	grp_handle = 0;

	// 位置を戻す
	pos_x = 0.0f;
	pos_y = 0.0f;
}

/* ----------------------------------------
関数名：Item::UpSpeed
概要　：速度を上げる
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Item::UpSpeed(void)
{
	spd_y = 9.0f;
}

/* ----------------------------------------
関数名：Item::ResetSpeed
概要　：速度をリセットする
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Item::ResetSpeed(void)
{
	spd_y = 7.0f;
}

/* ----------------------------------------
関数名：Item::IsExistState
概要　：アイテムが存在するか
引数　：なし(void)
戻り値：存在する(true)、存在しない(false)
---------------------------------------- */
bool Item::IsExistState(void)
{
	return exist_state;
}

/* ----------------------------------------
関数名：Item::GetKind
概要　：種類を取得する
引数　：なし(void)
戻り値：種類(KIND)
---------------------------------------- */
KIND Item::GetKind(void)
{
	return kind;
}

/* ----------------------------------------------------
関数名：Item::IsFadeOut
概要　：フェードアウトしてるか
引数　：なし(void)
戻り値：フェードアウトしてる(true)、してない(false)
---------------------------------------------------- */
bool Item::IsFadeOut(void)
{
	return is_fadeout;
}

/* ----------------------------------------
関数名：Item::StartFadeout
概要　：フェードアウト開始
引数　：なし(void)
戻り値：なし(void)
---------------------------------------- */
void Item::StartFadeout(void)
{
	is_fadeout = true;
}